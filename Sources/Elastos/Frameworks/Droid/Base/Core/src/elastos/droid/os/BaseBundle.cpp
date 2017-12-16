//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

#include "Elastos.Droid.Content.h"
#include "Elastos.Droid.Os.h"
#include "elastos/droid/os/BaseBundle.h"
#include <elastos/core/CoreUtils.h>
#include <elastos/core/StringBuilder.h>
#include <elastos/utility/logging/Logger.h>
#include "elastos/droid/utility/CArrayMap.h"
#include "elastos/droid/utility/CSparseArray.h"
#include <utils/CallStack.h>
#include <binder/Parcel.h>

using Elastos::Core::CoreUtils;
using Elastos::Core::StringBuilder;
using Elastos::Core::CByte;
using Elastos::Core::CChar32;
using Elastos::Core::CBoolean;
using Elastos::Core::CInteger16;
using Elastos::Core::CInteger32;
using Elastos::Core::CInteger64;
using Elastos::Core::CFloat;
using Elastos::Core::CDouble;
using Elastos::Core::CString;
using Elastos::Core::EIID_ICharSequence;
using Elastos::Utility::Logging::Logger;
using Elastos::Utility::CArrayList;
using Elastos::Utility::IList;
using Elastos::Utility::IIterator;
using Elastos::Utility::IMapEntry;
using Elastos::Droid::Utility::CArrayMap;
using Elastos::Droid::Utility::CSparseArray;
using Elastos::Droid::Utility::ISparseArray;

namespace Elastos {
namespace Droid {
namespace Os {

AutoPtr<IParcel> InitEMPTY_PARCEL()
{
    AutoPtr<IParcel> empty;
    CParcel::New((IParcel**)&empty);
    return empty;
}

CAR_INTERFACE_IMPL(BaseBundle, Object, IBaseBundle)

const String BaseBundle::TAG("BaseBundle");
const Boolean BaseBundle::DEBUG = FALSE;

const Int32 BaseBundle::BUNDLE_MAGIC = 0x4C444E42; // 'B' 'N' 'D' 'L'
const AutoPtr<IParcel> BaseBundle::EMPTY_PARCEL = InitEMPTY_PARCEL();

const Int32 BaseBundle::VAL_NULL = -1;
const Int32 BaseBundle::VAL_NOT_NULL = 0;
const Int32 BaseBundle::VAL_STRING = 1;
const Int32 BaseBundle::VAL_INTEGER32 = 2;
const Int32 BaseBundle::VAL_MAP = 3;
const Int32 BaseBundle::VAL_BUNDLE = 4;
const Int32 BaseBundle::VAL_PARCELABLE = 5;
const Int32 BaseBundle::VAL_INTEGER16 = 6;
const Int32 BaseBundle::VAL_INTEGER64 = 7;
const Int32 BaseBundle::VAL_FLOAT = 8;
const Int32 BaseBundle::VAL_DOUBLE = 9;
const Int32 BaseBundle::VAL_BOOLEAN = 10;
const Int32 BaseBundle::VAL_CHARSEQUENCE = 11;
const Int32 BaseBundle::VAL_LIST  = 12;
const Int32 BaseBundle::VAL_SPARSEARRAY = 13;
const Int32 BaseBundle::VAL_BYTEARRAY = 14;
const Int32 BaseBundle::VAL_STRINGARRAY = 15;
const Int32 BaseBundle::VAL_IBINDER = 16;
const Int32 BaseBundle::VAL_PARCELABLEARRAY = 17;
const Int32 BaseBundle::VAL_OBJECTARRAY = 18;
const Int32 BaseBundle::VAL_INTARRAY = 19;
const Int32 BaseBundle::VAL_LONGARRAY = 20;
const Int32 BaseBundle::VAL_BYTE = 21;
const Int32 BaseBundle::VAL_SERIALIZABLE = 22;
const Int32 BaseBundle::VAL_SPARSEBOOLEANARRAY = 23;
const Int32 BaseBundle::VAL_BOOLEANARRAY = 24;
const Int32 BaseBundle::VAL_CHARSEQUENCEARRAY = 25;
const Int32 BaseBundle::VAL_ARRAYOF = 26;

BaseBundle::BaseBundle()
{
}

ECode BaseBundle::constructor(
    /* [in] */ IClassLoader* loader,
    /* [in] */ Int32 capacity)
{
    if (capacity > 0) {
        CArrayMap::New(capacity, (IArrayMap**)&mMap);
    }
    else {
        CArrayMap::New((IArrayMap**)&mMap);
    }

    mClassLoader = loader;

    return NOERROR;
}

ECode BaseBundle::constructor()
{
    return constructor((IClassLoader*)NULL, 0);
}

ECode BaseBundle::constructor(
    /* [in] */ IParcel* parcelledData)
{
    return ReadFromParcelInner(parcelledData);
}

ECode BaseBundle::constructor(
    /* [in] */ IParcel* parcelledData,
    /* [in] */ Int32 length)
{
    return ReadFromParcelInner(parcelledData, length);
}

ECode BaseBundle::constructor(
    /* [in] */ IClassLoader* loader)
{
    return constructor(loader, 0);
}

ECode BaseBundle::constructor(
    /* [in] */ Int32 capacity)
{
    return constructor((IClassLoader*)NULL, capacity);
}

ECode BaseBundle::constructor(
    /* [in] */ IBaseBundle* bundle)
{
    BaseBundle* b = (BaseBundle*)bundle;
    if (b->mParcelledData != NULL) {
        if (b->mParcelledData == EMPTY_PARCEL) {
            mParcelledData = EMPTY_PARCEL;
        }
        else {
            CParcel::New((IParcel**)&mParcelledData);
            Int32 size;
            b->mParcelledData->GetDataSize(&size);
            mParcelledData->AppendFrom(b->mParcelledData, 0, size);
            mParcelledData->SetDataPosition(0);
        }
    } else {
        mParcelledData = NULL;
    }

    mMap = NULL;
    if (b->mMap != NULL) {
        CArrayMap::New(b->mMap, (IArrayMap**)&mMap);
    }

    mClassLoader = b->mClassLoader;
    mJavaData = b->mJavaData;
    return NOERROR;
}

ECode BaseBundle::GetPairValue(
    /* [out] */ String* str)
{
    VALIDATE_NOT_NULL(str)
    *str = String(NULL);

    Unparcel();
    Int32 size;
    mMap->GetSize(&size);
    if (size > 1) {
        Logger::W(TAG, "getPairValue() used on Bundle with multiple pairs.");
    }
    if (size == 0) {
        return NOERROR;
    }
    AutoPtr<IInterface> obj;
    mMap->GetValueAt(0, (IInterface**)&obj);

    if (obj == NULL) {
        return NOERROR;
    }
    else if (ICharSequence::Probe(obj) == NULL) {
        TypeWarning(String("getPairValue()"), String("String"));
        return NOERROR;
    }

    ICharSequence::Probe(obj)->ToString(str);
    return NOERROR;
}

ECode BaseBundle::SetClassLoader(
    /* [in] */ IClassLoader* loader)
{
    mClassLoader = loader;
    return NOERROR;
}

ECode BaseBundle::GetClassLoader(
    /* [out] */ IClassLoader** loader)
{
    VALIDATE_NOT_NULL(loader)
    if (mClassLoader == NULL) {
        mClassLoader = Object::GetClassLoader(TO_IINTERFACE(this));
    }
    *loader = mClassLoader;
    REFCOUNT_ADD(*loader)
    return NOERROR;
}

void BaseBundle::Unparcel()
{
    if (mParcelledData == NULL) {
        if (DEBUG) Logger::D(TAG, "Unparcel %p : no parcelled data", this);
        return;
    }

    if (mParcelledData == EMPTY_PARCEL) {
        if (DEBUG) Logger::D(TAG, "Unparcel %p : empty", this);

        if (mMap == NULL) {
            CArrayMap::New(1, (IArrayMap**)&mMap);
        }
        else {
            mMap->Erase();
        }
        mParcelledData = NULL;
        return;
    }

    Int32 N;
    mParcelledData->ReadInt32(&N);
    if (DEBUG) Logger::D(TAG, "Unparcel %p: reading %d maps.", this, N);
    if (N < 0) {
        return;
    }
    if (mMap == NULL) {
        CArrayMap::New(N, (IArrayMap**)&mMap);
    }
    else {
        mMap->Erase();
        mMap->EnsureCapacity(N);
    }
    ReadArrayMapInternal(mParcelledData, mMap, N, mClassLoader);
    //mParcelledData->Recycle();
    mParcelledData = NULL;
    if (DEBUG) Logger::D(TAG, "Unparcel %p: final map: %p", this, mMap.Get());
}

ECode BaseBundle::IsParcelled(
    /* [out] */ Boolean* result)
{
    VALIDATE_NOT_NULL(result)
    *result = mParcelledData != NULL;
    return NOERROR;
}

ECode BaseBundle::GetSize(
    /* [out] */ Int32 * size)
{
    VALIDATE_NOT_NULL(size)
    Unparcel();
    return mMap->GetSize(size);
}

ECode BaseBundle::IsEmpty(
    /* [out] */ Boolean* empty)
{
    VALIDATE_NOT_NULL(empty)
    Unparcel();
    return mMap->IsEmpty(empty);
}

ECode BaseBundle::Clear()
{
    Unparcel();
    return mMap->Clear();
}

ECode BaseBundle::ContainsKey(
    /* [in] */ const String& key,
    /* [out] */ Boolean* result)
{
    VALIDATE_NOT_NULL(result)
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    return mMap->ContainsKey(keyObj, result);
}

ECode BaseBundle::Get(
    /* [in] */ const String& key,
    /* [out] */ IInterface** obj)
{
    VALIDATE_NOT_NULL(obj)
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    return mMap->Get(keyObj, obj);
}

ECode BaseBundle::Remove(
    /* [in] */ const String& key)
{
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    return mMap->Remove(keyObj);
}

ECode BaseBundle::PutAll(
    /* [in] */ IPersistableBundle* bundle)
{
    Unparcel();
    BaseBundle* bb = (BaseBundle*)bundle;
    bb->Unparcel();
    return mMap->PutAll(IMap::Probe(bb->mMap));
}

ECode BaseBundle::PutAll(
    /* [in] */ IMap* map)
{
    Unparcel();
    return mMap->PutAll(map);
}

ECode BaseBundle::GetKeySet(
    /* [out] */ ISet** set)
{
    VALIDATE_NOT_NULL(set)
    Unparcel();
    return mMap->GetKeySet(set);
}

ECode BaseBundle::PutBoolean(
    /* [in] */ const String& key,
    /* [in] */ Boolean value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IBoolean> valueObj = CoreUtils::Convert(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutByte(
    /* [in] */ const String& key,
    /* [in] */ Byte value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IByte> valueObj = CoreUtils::ConvertByte(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutChar(
    /* [in] */ const String& key,
    /* [in] */ Char32 value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IChar32> valueObj = CoreUtils::ConvertChar32(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutInt16(
    /* [in] */ const String& key,
    /* [in] */ Int16 value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IInteger16> valueObj = CoreUtils::Convert(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutInt32(
    /* [in] */ const String& key,
    /* [in] */ Int32 value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IInteger32> valueObj = CoreUtils::Convert(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutInt64(
    /* [in] */ const String& key,
    /* [in] */ Int64 value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IInteger64> valueObj = CoreUtils::Convert(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutFloat(
    /* [in] */ const String& key,
    /* [in] */ Float value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IFloat> valueObj = CoreUtils::Convert(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutDouble(
    /* [in] */ const String& key,
    /* [in] */ Double value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IDouble> valueObj = CoreUtils::Convert(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());}

ECode BaseBundle::PutString(
    /* [in] */ const String& key,
    /* [in] */ const String& value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<ICharSequence> valueObj = CoreUtils::Convert(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutCharSequence(
    /* [in] */ const String& key,
    /* [in] */ ICharSequence* value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    return mMap->Put(keyObj.Get(), value);
}

ECode BaseBundle::PutIntegerArrayList(
    /* [in] */ const String& key,
    /* [in] */ IArrayList* value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    return mMap->Put(keyObj.Get(), value);
}

ECode BaseBundle::PutStringArrayList(
    /* [in] */ const String& key,
    /* [in] */ IArrayList* value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    return mMap->Put(keyObj.Get(), value);
}

ECode BaseBundle::PutCharSequenceArrayList(
    /* [in] */ const String& key,
    /* [in] */ IArrayList* value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    return mMap->Put(keyObj.Get(), value);
}

ECode BaseBundle::PutSerializable(
    /* [in] */ const String& key,
    /* [in] */ ISerializable* value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    return mMap->Put(keyObj.Get(), value);
}

ECode BaseBundle::PutBooleanArray(
    /* [in] */ const String& key,
    /* [in] */ ArrayOf<Boolean>* value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IArrayOf> valueObj = CoreUtils::Convert(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutByteArray(
    /* [in] */ const String& key,
    /* [in] */ ArrayOf<Byte>* value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IArrayOf> valueObj = CoreUtils::ConvertByteArray(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutCharArray(
    /* [in] */ const String& key,
    /* [in] */ ArrayOf<Char32>* value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IArrayOf> valueObj = CoreUtils::ConvertChar32Array(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutInt16Array(
    /* [in] */ const String& key,
    /* [in] */ ArrayOf<Int16>* value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IArrayOf> valueObj = CoreUtils::Convert(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutInt32Array(
    /* [in] */ const String& key,
    /* [in] */ ArrayOf<Int32>* value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IArrayOf> valueObj = CoreUtils::Convert(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutInt64Array(
    /* [in] */ const String& key,
    /* [in] */ ArrayOf<Int64>* value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IArrayOf> valueObj = CoreUtils::Convert(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutFloatArray(
    /* [in] */ const String& key,
    /* [in] */ ArrayOf<Float>* value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IArrayOf> valueObj = CoreUtils::Convert(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutDoubleArray(
    /* [in] */ const String& key,
    /* [in] */ ArrayOf<Double>* value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IArrayOf> valueObj = CoreUtils::Convert(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutStringArray(
    /* [in] */ const String& key,
    /* [in] */ ArrayOf<String>* value)
{
    assert(key != NULL);
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IArrayOf> valueObj = CoreUtils::Convert(value);
    return mMap->Put(keyObj.Get(), valueObj.Get());
}

ECode BaseBundle::PutCharSequenceArray(
    /* [in] */ const String& key,
    /* [in] */ ArrayOf<ICharSequence*>* value)
{
    Unparcel();
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IArrayOf> arrObj = CoreUtils::Convert(value, EIID_ICharSequence);

    return mMap->Put(keyObj.Get(), arrObj.Get());
}

void BaseBundle::TypeWarning(
    /* [in] */ const String& key,
    /* [in] */ const String& className)
{
    StringBuilder sb("Error: Attempt to cast generated internal exception, Key: ");
    sb.Append(key);
    sb.Append(", className: ");
    sb.Append(className);
    Logger::W(TAG, sb.ToString());
    android::CallStack stack;
    stack.update();
    Logger::W(TAG, "backtrace:%s\n", stack.toString("").string());
    assert(0 && "Please fix error!");
}

AutoPtr<IInterface> BaseBundle::GetValue(
    /* [in] */ const String& key)
{
    AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
    AutoPtr<IInterface> obj;
    mMap->Get(keyObj.Get(), (IInterface**)&obj);
    return obj;
}

ECode BaseBundle::GetBoolean(
    /* [in] */ const String& key,
    /* [out] */ Boolean* value)
{
    return GetBoolean(key, FALSE, value);
}

ECode BaseBundle::GetBoolean(
    /* [in] */ const String& key,
    /* [in] */ Boolean defaultValue,
    /* [out] */ Boolean* value)
{
    VALIDATE_NOT_NULL(value)
    *value = defaultValue;

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    IBoolean* o = IBoolean::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("IBoolean"));
        return NOERROR;
    }

    return o->GetValue(value);
}

ECode BaseBundle::GetByte(
    /* [in] */ const String& key,
    /* [out] */ Byte* value)
{
    return GetByte(key, (Byte)0, value);
}

ECode BaseBundle::GetByte(
    /* [in] */ const String& key,
    /* [in] */ Byte defaultValue,
    /* [out] */ Byte* value)
{
    VALIDATE_NOT_NULL(value)
    *value = defaultValue;

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    IByte* o = IByte::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("IByte"));
        return NOERROR;
    }

    return o->GetValue(value);
}

ECode BaseBundle::GetChar(
    /* [in] */ const String& key,
    /* [out] */ Char32* value)
{
    return GetChar(key, (Char32)0, value);
}

ECode BaseBundle::GetChar(
    /* [in] */ const String& key,
    /* [in] */ Char32 defaultValue,
    /* [out] */ Char32* value)
{
    VALIDATE_NOT_NULL(value)
    *value = defaultValue;

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    IChar32* o = IChar32::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("IChar32"));
        return NOERROR;
    }

    return o->GetValue(value);
}

ECode BaseBundle::GetInt16(
    /* [in] */ const String& key,
    /* [out] */ Int16* value)
{
    return GetInt16(key, 0, value);
}

ECode BaseBundle::GetInt16(
    /* [in] */ const String& key,
    /* [in] */ Int16 defaultValue,
    /* [out] */ Int16* value)
{
    VALIDATE_NOT_NULL(value)
    *value = defaultValue;

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    IInteger16* o = IInteger16::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("IInteger16"));
        return NOERROR;
    }

    return o->GetValue(value);
}

ECode BaseBundle::GetInt32(
    /* [in] */ const String& key,
    /* [out] */ Int32* value)
{
    return GetInt32(key, 0, value);
}

ECode BaseBundle::GetInt32(
    /* [in] */ const String& key,
    /* [in] */ Int32 defaultValue,
    /* [out] */ Int32* value)
{
    VALIDATE_NOT_NULL(value)
    *value = defaultValue;

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    IInteger32* o = IInteger32::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("IInteger32"));
        return NOERROR;
    }

    return o->GetValue(value);
}

ECode BaseBundle::GetInt64(
    /* [in] */ const String& key,
    /* [out] */ Int64* value)
{
    return GetInt64(key, 0, value);
}

ECode BaseBundle::GetInt64(
    /* [in] */ const String& key,
    /* [in] */ Int64 defaultValue,
    /* [out] */ Int64* value)
{
    VALIDATE_NOT_NULL(value)
    *value = defaultValue;

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    IInteger64* o = IInteger64::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("IInteger64"));
        return NOERROR;
    }

    return o->GetValue(value);
}

ECode BaseBundle::GetFloat(
    /* [in] */ const String& key,
    /* [out] */ Float* value)
{
    return GetFloat(key, 0, value);
}

ECode BaseBundle::GetFloat(
    /* [in] */ const String& key,
    /* [in] */ Float defaultValue,
    /* [out] */ Float* value)
{
    VALIDATE_NOT_NULL(value)
    *value = defaultValue;

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    IFloat* o = IFloat::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("IFloat"));
        return NOERROR;
    }

    return o->GetValue(value);
}

ECode BaseBundle::GetDouble(
    /* [in] */ const String& key,
    /* [out] */ Double* value)
{
    return GetDouble(key, 0, value);
}

ECode BaseBundle::GetDouble(
    /* [in] */ const String& key,
    /* [in] */ Double defaultValue,
    /* [out] */ Double* value)
{
    VALIDATE_NOT_NULL(value)
    *value = defaultValue;

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    IDouble* o = IDouble::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("IDouble"));
        return NOERROR;
    }

    return o->GetValue(value);
}

ECode BaseBundle::GetString(
    /* [in] */ const String& key,
    /* [out] */ String* value)
{
    VALIDATE_NOT_NULL(value)
    *value = String(NULL);

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    ICharSequence* o = ICharSequence::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("ICharSequence"));
        return NOERROR;
    }

    return o->ToString(value);
}

ECode BaseBundle::GetString(
    /* [in] */ const String& key,
    /* [in] */ const String& defaultValue,
    /* [out] */ String* value)
{
    VALIDATE_NOT_NULL(value)
    *value = defaultValue;

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    ICharSequence* o = ICharSequence::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("ICharSequence"));
        return NOERROR;
    }

    return o->ToString(value);
}

ECode BaseBundle::GetCharSequence(
    /* [in] */ const String& key,
    /* [out] */ ICharSequence** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    ICharSequence* o = ICharSequence::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("ICharSequence"));
        return NOERROR;
    }

    *value = o;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::GetCharSequence(
    /* [in] */ const String& key,
    /* [in] */ ICharSequence* defaultValue,
    /* [out] */ ICharSequence** value)
{
    VALIDATE_NOT_NULL(value)

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        *value = defaultValue;
        REFCOUNT_ADD(*value);
        return NOERROR;
    }

    ICharSequence* o = ICharSequence::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("ICharSequence"));
        *value = defaultValue;
        REFCOUNT_ADD(*value);
        return NOERROR;
    }

    *value = o;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::GetSerializable(
    /* [in] */ const String& key,
    /* [out] */ ISerializable** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    ISerializable* o = ISerializable::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("ISerializable"));
        return NOERROR;
    }

    *value = o;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::GetIntegerArrayList(
    /* [in] */ const String& key,
    /* [out] */ IArrayList** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    IArrayList* o = IArrayList::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("IArrayList<IInteger32>"));
        return NOERROR;
    }

    *value = o;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::GetStringArrayList(
    /* [in] */ const String& key,
    /* [out] */ IArrayList** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    IArrayList* o = IArrayList::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("IArrayList<ICharSequence>"));
        return NOERROR;
    }

    *value = o;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::GetCharSequenceArrayList(
    /* [in] */ const String& key,
    /* [out] */ IArrayList** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NOERROR;
    }

    IArrayList* o = IArrayList::Probe(obj);
    if (o == NULL) {
        TypeWarning(key, String("IArrayList<ICharSequence>"));
        return NOERROR;
    }

    *value = o;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

AutoPtr<IArrayOf> BaseBundle::GetIArrayOf(
    /* [in] */ const String& key,
    /* [in] */ const String& className)
{
    AutoPtr<IInterface> obj = GetValue(key);
    if (obj == NULL) {
        return NULL;
    }

    AutoPtr<IArrayOf> arrayOf = IArrayOf::Probe(obj);
    if (arrayOf == NULL) {
        TypeWarning(key, className);
        return NULL;
    }

    return arrayOf;
}

ECode BaseBundle::GetBooleanArray(
    /* [in] */ const String& key,
    /* [out, callee] */ ArrayOf<Boolean>** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IArrayOf> arrObj = GetIArrayOf(key, String("BooleanArray"));
    AutoPtr<ArrayOf<Boolean> > array;
    if (arrObj) {
        Int32 length;
        arrObj->GetLength(&length);
        array = ArrayOf<Boolean>::Alloc(length);
        IBoolean* o;
        for (Int32 i = 0; i < length; ++i) {
            Boolean item = FALSE;
            AutoPtr<IInterface> obj;
            arrObj->Get(i, (IInterface**)&obj);
            o = IBoolean::Probe(obj);
            if (o != NULL) {
                o->GetValue(&item);
            }
            array->Set(i, item);
        }
    }

    *value = array;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::GetByteArray(
    /* [in] */ const String& key,
    /* [out, callee] */ ArrayOf<Byte>** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IArrayOf> arrObj = GetIArrayOf(key, String("IArrayOf<IByte>"));
    AutoPtr<ArrayOf<Byte> > array;
    if (arrObj) {
        Int32 length;
        arrObj->GetLength(&length);
        array = ArrayOf<Byte>::Alloc(length);
        IByte* o;
        for (Int32 i = 0; i < length; ++i) {
            Byte item = 0;
            AutoPtr<IInterface> obj;
            arrObj->Get(i, (IInterface**)&obj);
            o = IByte::Probe(obj);
            if (o != NULL) {
                o->GetValue(&item);
            }
            array->Set(i, item);
        }
    }

    *value = array;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::GetInt16Array(
    /* [in] */ const String& key,
    /* [out, callee] */ ArrayOf<Int16>** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IArrayOf> arrObj = GetIArrayOf(key, String("IArrayOf<IInteger16>"));
    AutoPtr<ArrayOf<Int16> > array;
    if (arrObj) {
        Int32 length;
        arrObj->GetLength(&length);
        array = ArrayOf<Int16>::Alloc(length);
        IInteger16* o;
        for (Int32 i = 0; i < length; ++i) {
            Int16 item = 0;
            AutoPtr<IInterface> obj;
            arrObj->Get(i, (IInterface**)&obj);
            o = IInteger16::Probe(obj);
            if (o != NULL) {
                o->GetValue(&item);
            }
            array->Set(i, item);
        }
    }

    *value = array;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::GetCharArray(
    /* [in] */ const String& key,
    /* [out, callee] */ ArrayOf<Char32>** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IArrayOf> arrObj = GetIArrayOf(key, String("IArrayOf<IChar32>"));
    AutoPtr<ArrayOf<Char32> > array;
    if (arrObj) {
        Int32 length;
        arrObj->GetLength(&length);
        array = ArrayOf<Char32>::Alloc(length);
        IChar32* o;
        for (Int32 i = 0; i < length; ++i) {
            Char32 item = 0;
            AutoPtr<IInterface> obj;
            arrObj->Get(i, (IInterface**)&obj);
            o = IChar32::Probe(obj);
            if (o != NULL) {
                o->GetValue(&item);
            }
            array->Set(i, item);
        }
    }

    *value = array;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::GetInt32Array(
    /* [in] */ const String& key,
    /* [out, callee] */ ArrayOf<Int32>** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IArrayOf> arrObj = GetIArrayOf(key, String("IArrayOf<IInteger32>"));
    AutoPtr<ArrayOf<Int32> > array;
    if (arrObj) {
        Int32 length;
        arrObj->GetLength(&length);
        array = ArrayOf<Int32>::Alloc(length);
        IInteger32* o;
        for (Int32 i = 0; i < length; ++i) {
            Int32 item = 0;
            AutoPtr<IInterface> obj;
            arrObj->Get(i, (IInterface**)&obj);
            o = IInteger32::Probe(obj);
            if (o != NULL) {
                o->GetValue(&item);
            }
            array->Set(i, item);
        }
    }

    *value = array;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::GetInt64Array(
    /* [in] */ const String& key,
    /* [out, callee] */ ArrayOf<Int64>** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IArrayOf> arrObj = GetIArrayOf(key, String("IArrayOf<IInteger64>"));
    AutoPtr<ArrayOf<Int64> > array;
    if (arrObj) {
        Int32 length;
        arrObj->GetLength(&length);
        array = ArrayOf<Int64>::Alloc(length);
        IInteger64* o;
        for (Int32 i = 0; i < length; ++i) {
            Int64 item = 0;
            AutoPtr<IInterface> obj;
            arrObj->Get(i, (IInterface**)&obj);
            o = IInteger64::Probe(obj);
            if (o != NULL) {
                o->GetValue(&item);
            }
            array->Set(i, item);
        }
    }

    *value = array;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::GetFloatArray(
    /* [in] */ const String& key,
    /* [out, callee] */ ArrayOf<Float>** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IArrayOf> arrObj = GetIArrayOf(key, String("IArrayOf<IFloat>"));
    AutoPtr<ArrayOf<Float> > array;
    if (arrObj) {
        Int32 length;
        arrObj->GetLength(&length);
        array = ArrayOf<Float>::Alloc(length);
        IFloat* o;
        for (Int32 i = 0; i < length; ++i) {
            Float item = 0;
            AutoPtr<IInterface> obj;
            arrObj->Get(i, (IInterface**)&obj);
            o = IFloat::Probe(obj);
            if (o != NULL) {
                o->GetValue(&item);
            }
            array->Set(i, item);
        }
    }

    *value = array;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::GetDoubleArray(
    /* [in] */ const String& key,
    /* [out, callee] */ ArrayOf<Double>** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IArrayOf> arrObj = GetIArrayOf(key, String("IArrayOf<IDouble>"));
    AutoPtr<ArrayOf<Double> > array;
    if (arrObj) {
        Int32 length;
        arrObj->GetLength(&length);
        array = ArrayOf<Double>::Alloc(length);
        IDouble* o;
        for (Int32 i = 0; i < length; ++i) {
            Double item = 0;
            AutoPtr<IInterface> obj;
            arrObj->Get(i, (IInterface**)&obj);
            o = IDouble::Probe(obj);
            if (o != NULL) {
                o->GetValue(&item);
            }
            array->Set(i, item);
        }
    }

    *value = array;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::GetStringArray(
    /* [in] */ const String& key,
    /* [out, callee] */ ArrayOf<String>** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IArrayOf> arrObj = GetIArrayOf(key, String("IArrayOf<ICharSequence>"));
    AutoPtr<ArrayOf<String> > array;
    if (arrObj) {
        Int32 length;
        arrObj->GetLength(&length);
        array = ArrayOf<String>::Alloc(length);
        ICharSequence* csq;
        for (Int32 i = 0; i < length; ++i) {
            String item;
            AutoPtr<IInterface> obj;
            arrObj->Get(i, (IInterface**)&obj);
            csq = ICharSequence::Probe(obj);
            if (csq != NULL) {
                csq->ToString(&item);
            }
            array->Set(i, item);
        }
    }

    *value = array;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::GetCharSequenceArray(
    /* [in] */ const String& key,
    /* [out, callee] */ ArrayOf<ICharSequence*>** value)
{
    VALIDATE_NOT_NULL(value)
    *value = NULL;

    Unparcel();
    AutoPtr<IArrayOf> arrObj = GetIArrayOf(key, String("IArrayOf<ICharSequence>"));
    AutoPtr<ArrayOf<ICharSequence*> > array;
    if (arrObj) {
        Int32 length;
        arrObj->GetLength(&length);
        array = ArrayOf<ICharSequence*>::Alloc(length);
        for (Int32 i = 0; i < length; ++i) {
            AutoPtr<IInterface> obj;
            arrObj->Get(i, (IInterface**)&obj);
            array->Set(i, ICharSequence::Probe(obj));
        }
    }

    *value = array;
    REFCOUNT_ADD(*value);
    return NOERROR;
}

ECode BaseBundle::WriteValue(
    /* [in] */ IParcel* dest,
    /* [in] */ IInterface* obj)
{
    if (obj == NULL) {
        dest->WriteInt32(VAL_NULL);
        return NOERROR;
    }
    // else if (v instanceof String) {
    //     writeInt(VAL_STRING);
    //     writeString((String) v);
    // }
    else if (IInteger32::Probe(obj) != NULL) {
        Int32 v;
        IInteger32::Probe(obj)->GetValue(&v);
        dest->WriteInt32(VAL_INTEGER32);
        dest->WriteInt32(v);
        return NOERROR;
    }
    // else if (IMap::Probe(obj) != NULL) {
    //     // writeInt(VAL_MAP);
    //     // writeMap((Map) v);
    //     Logger::I(TAG, " ======================= BaseBundle::WriteValue IMap! ============");
    //     return NOERROR;
    // }
    else if (IBundle::Probe(obj) != NULL) {
        // // Must be before Parcelable
        dest->WriteInt32(VAL_BUNDLE);
        dest->WriteInterfacePtr(obj);
        return NOERROR;
    }
    else if (IParcelable::Probe(obj) != NULL) {
        dest->WriteInt32(VAL_PARCELABLE);
        dest->WriteInterfacePtr(obj);
        return NOERROR;
    }
    else if (IInteger16::Probe(obj) != NULL) {
        Int16 v;
        IInteger16::Probe(obj)->GetValue(&v);
        dest->WriteInt32(VAL_INTEGER16);
        dest->WriteInt32((Int32)v);
        return NOERROR;
    }
    else if (IInteger64::Probe(obj) != NULL) {
        Int64 v;
        IInteger64::Probe(obj)->GetValue(&v);
        dest->WriteInt32(VAL_INTEGER64);
        dest->WriteInt64(v);
        return NOERROR;
    }
    else if (IFloat::Probe(obj) != NULL) {
        Float v;
        IFloat::Probe(obj)->GetValue(&v);
        dest->WriteInt32(VAL_FLOAT);
        dest->WriteFloat(v);
        return NOERROR;
    }
    else if (IDouble::Probe(obj) != NULL) {
        Double v;
        IDouble::Probe(obj)->GetValue(&v);
        dest->WriteInt32(VAL_DOUBLE);
        dest->WriteDouble(v);
        return NOERROR;
    }
    else if (IBoolean::Probe(obj) != NULL) {
        Boolean v;
        IBoolean::Probe(obj)->GetValue(&v);
        dest->WriteInt32(VAL_BOOLEAN);
        dest->WriteInt32(v ? 1 : 0);
        return NOERROR;
    }
    else if (ICharSequence::Probe(obj) != NULL) {
        // Must be after String
        String v;
        ICharSequence::Probe(obj)->ToString(&v);
        dest->WriteInt32(VAL_CHARSEQUENCE);
        // writeCharSequence((CharSequence) v);
        dest->WriteString(v);
        return NOERROR;
    }
    else if (IArrayOf::Probe(obj) != NULL){
        AutoPtr<IArrayOf> array = IArrayOf::Probe(obj);
        Int32 size = 0;
        array->GetLength(&size);
        dest->WriteInt32(VAL_ARRAYOF);
        InterfaceID iid;
        array->GetTypeId(&iid);
        dest->WriteEMuid(iid);
        dest->WriteInt32(size);
        for (Int32 i = 0; i < size; ++i) {
            AutoPtr<IInterface> elem;
            array->Get(i, (IInterface**)&elem);
            WriteValue(dest, elem);
        }
        return NOERROR;
    }
    else if (IList::Probe(obj) != NULL) {
        dest->WriteInt32(VAL_LIST);
    //     writeList((List) v);
        AutoPtr<IList> list = IList::Probe(obj);
        Int32 N;
        list->GetSize(&N);
        dest->WriteInt32(N);
        Int32 i = 0;
        while (i < N) {
            AutoPtr<IInterface> elem;
            list->Get(i, (IInterface**)&elem);
            WriteValue(dest, elem);
            i++;
        }
        return NOERROR;
    }
    else if (ISparseArray::Probe(obj) != NULL) {
        dest->WriteInt32(VAL_SPARSEARRAY);
        // WriteSparseArray((SparseArray) v);
        // if (val == NULL) {
        //     dest->WriteInt32(-1);
        //     return NOERROR;
        // }
        AutoPtr<ISparseArray> o = ISparseArray::Probe(obj);
        Int32 N = 0;
        o->GetSize(&N);
        dest->WriteInt32(N);
        Int32 i = 0, k = 0;
        while (i < N) {
            o->KeyAt(i, &k);
            dest->WriteInt32(k);
            AutoPtr<IInterface> v;
            o->ValueAt(i, (IInterface**)&v);
            WriteValue(dest, v);
            i++;
        }
        return NOERROR;
    }
    // else if (v instanceof boolean[]) {
    //     writeInt(VAL_BOOLEANARRAY);
    //     writeBooleanArray((boolean[]) v);
    // }
    // else if (v instanceof byte[]) {
    //     writeInt(VAL_BYTEARRAY);
    //     writeByteArray((byte[]) v);
    // }
    // else if (v instanceof String[]) {
    //     writeInt(VAL_STRINGARRAY);
    //     writeStringArray((String[]) v);
    // }
    // else if (v instanceof CharSequence[]) {
    //     // Must be after String[] and before Object[]
    //     writeInt(VAL_CHARSEQUENCEARRAY);
    //     writeCharSequenceArray((CharSequence[]) v);
    // }
    else if (IBinder::Probe(obj) != NULL) {
        dest->WriteInt32(VAL_IBINDER);
        dest->WriteInterfacePtr(obj);
        return NOERROR;
    }
    // else if (v instanceof Parcelable[]) {
    //     writeInt(VAL_PARCELABLEARRAY);
    //     writeParcelableArray((Parcelable[]) v, 0);
    // }
    // else if (v instanceof Object[]) {
    //     writeInt(VAL_OBJECTARRAY);
    //     writeArray((Object[]) v);
    // }
    // else if (v instanceof int[]) {
    //     writeInt(VAL_INTARRAY);
    //     writeIntArray((int[]) v);
    // }
    // else if (v instanceof long[]) {
    //     writeInt(VAL_LONGARRAY);
    //     writeLongArray((long[]) v);
    // }
    else if (IByte::Probe(obj) != NULL) {
        Byte v;
        IByte::Probe(obj)->GetValue(&v);
        dest->WriteInt32(VAL_BYTE);
        dest->WriteInt32((Int32)v);
        return NOERROR;
    }
    // else if (v instanceof Serializable) {
    //     // Must be last
    //     writeInt(VAL_SERIALIZABLE);
    //     writeSerializable((Serializable) v);
    // }
    else {
        Logger::D(TAG, "Unable to marshal value %p, obj=[%s]", obj, TO_CSTR(obj));
        android::CallStack stack;
        stack.update();
        Logger::W(TAG, "backtrace:%s\n", stack.toString("").string());
        assert(0);
        return E_RUNTIME_EXCEPTION;
    }
    return NOERROR;
}

AutoPtr<IInterface> BaseBundle::ReadValue(
    /* [in] */ IParcel* source,
    /* [in] */ const String& keyStr)
{
    Int32 type;
    source->ReadInt32(&type);

    switch (type) {
    case VAL_NULL:
        return NULL;
    // case VAL_STRING:
    //     return readString();
    case VAL_INTEGER32: {
        Int32 v;
        source->ReadInt32(&v);
        AutoPtr<IInteger32> obj;
        CInteger32::New(v, (IInteger32**)&obj);
        return obj;
    }
    // case VAL_MAP:
    //     return readHashMap(loader);

    case VAL_PARCELABLE:{
        AutoPtr<IParcelable> obj;
        source->ReadInterfacePtr((Handle32*)&obj);
        if(obj == NULL){
            Logger::E(TAG, "Read IParcelable got null");
        }
        return obj;
    }
    case VAL_INTEGER16: {
        Int32 v;
        source->ReadInt32(&v);
        Int16 sv = (Int16)v;
        AutoPtr<IInteger16> obj;
        CInteger16::New(sv, (IInteger16**)&obj);
        return obj;
    }
    case VAL_INTEGER64: {
        Int64 v;
        source->ReadInt64(&v);
        AutoPtr<IInteger64> obj;
        CInteger64::New(v, (IInteger64**)&obj);
        return obj;
    }
    case VAL_FLOAT: {
        Float v;
        source->ReadFloat(&v);
        AutoPtr<IFloat> obj;
        CFloat::New(v, (IFloat**)&obj);
        return obj;
    }
    case VAL_DOUBLE: {
        Double v;
        source->ReadDouble(&v);
        AutoPtr<IDouble> obj;
        CDouble::New(v, (IDouble**)&obj);
        return obj;
    }
    case VAL_BOOLEAN: {
        Int32 v;
        source->ReadInt32(&v);
        AutoPtr<IBoolean> obj;
        CBoolean::New(v == 1, (IBoolean**)&obj);
        return obj;
    }
    case VAL_CHARSEQUENCE: {
        String v;
        source->ReadString(&v);
        AutoPtr<ICharSequence> obj;
        CString::New(v, (ICharSequence**)&obj);
        return obj;
    }
    case VAL_LIST:{
        Int32 N;
        source->ReadInt32(&N);
        if (N < 0) {
            return NULL;
        }

        AutoPtr<IList> list;
        CArrayList::New(N, (IList**)&list);
        while (N > 0) {
            AutoPtr<IInterface> value = ReadValue(source, keyStr);
            list->Add(value);
            N--;
        }
        return list;
    }

    // case VAL_BOOLEANARRAY:
    //     return createBooleanArray();
    // case VAL_BYTEARRAY:
    //     return createByteArray();
    // case VAL_STRINGARRAY:
    //     return readStringArray();
    // case VAL_CHARSEQUENCEARRAY:
    //     return readCharSequenceArray();
    case VAL_IBINDER: {
        AutoPtr<IBinder> obj;
        source->ReadInterfacePtr((Handle32*)&obj);
        if(obj == NULL){
            Logger::E(TAG, "Read IBinder got null");
        }
        return obj;
    }
    // case VAL_OBJECTARRAY:
    //     return readArray(loader);
    // case VAL_INTARRAY:
    //     return createIntArray();
    // case VAL_LONGARRAY:
    //     return createLongArray();
    case VAL_BYTE: {
        Int32 v;
        source->ReadInt32(&v);
        AutoPtr<IByte> obj;
        CByte::New((Byte)v, (IByte**)&obj);
        return obj;
    }
    // case VAL_SERIALIZABLE:
    //     return readSerializable();
    // case VAL_PARCELABLEARRAY:
    //     return readParcelableArray(loader);
    case VAL_ARRAYOF: {
        InterfaceID iid;
        source->ReadEMuid(&iid);
        Int32 size = 0;
        source->ReadInt32(&size);
        AutoPtr<IArrayOf> array;
        CArrayOf::New(iid, size, (IArrayOf**)&array);
        for (Int32 i = 0; i < size; ++i) {
            AutoPtr<IInterface> elem = ReadValue(source, keyStr);
            array->Set(i, elem);
        }
        return array;
    }
    case VAL_SPARSEARRAY: {
        Int32 N = 0;
        source->ReadInt32(&N);
        if (N < 0) {
            return NULL;
        }

        AutoPtr<ISparseArray> sa;
        CSparseArray::New(N, (ISparseArray**)&sa);

        while (N > 0) {
            Int32 key = 0;
            source->ReadInt32(&key);
            AutoPtr<IInterface> value = ReadValue(source, keyStr);
            //Log.i(TAG, "Unmarshalling key=" + key + " value=" + value);
            sa->Append(key, value);
            N--;
        }

        return sa;
    }
    // case VAL_SPARSEBOOLEANARRAY:
    //     return readSparseBooleanArray();
    case VAL_BUNDLE:{
        AutoPtr<IParcelable> obj;
        source->ReadInterfacePtr((Handle32*)&obj);
        if(obj == NULL){
            Logger::E(TAG, "Read IBundle got null");
        }
        return obj;
    }
    default:
        Logger::D(TAG, "- Unmarshalling unknown type code %d for key: %s", type, keyStr.string());
        android::CallStack stack;
        stack.update();
        Logger::W(TAG, "backtrace:%s\n", stack.toString("").string());
        assert(0);
    }
    return NULL;
}

ECode BaseBundle::ReadArrayMapInternal(
    /* [in] */ IParcel* source,
    /* [in] */ IArrayMap* arrayMap,
    /* [in] */ Int32 size,
    /* [in] */ IClassLoader* classLoader)
{
    if (IAndroidParcelWrapper::Probe(source) ==  NULL) {
        while (size > 0) {
            String key;
            source->ReadString(&key);
            AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
            AutoPtr<IInterface> valueObj = ReadValue(source, key);

            arrayMap->Put(keyObj.Get(), valueObj.Get());
            size--;
        }
    }
    else { // for running Elastos App on Android OS.
        while (size > 0) {
            String key;
            source->ReadString(&key);
            AutoPtr<ICharSequence> keyObj = CoreUtils::Convert(key);
            AutoPtr<IInterface> valueObj;
            source->ReadValue((IInterface**)&valueObj);

            arrayMap->Put(keyObj.Get(), valueObj.Get());
            size--;
        }
    }
    return NOERROR;
}

ECode BaseBundle::WriteArrayMapInternal(
    /* [in] */ IParcel* dest,
    /* [in] */ IArrayMap* map)
{
    assert(map != NULL);

    Int32 size = 0;
    map->GetSize(&size);
    dest->WriteInt32(size);

    if (size > 0) {
        AutoPtr<ISet> outset;
        map->GetEntrySet((ISet**)&outset);
        AutoPtr<IIterator> it;
        outset->GetIterator((IIterator**)&it);
        Boolean hasNext = FALSE;
        String key;
        while ((it->HasNext(&hasNext), hasNext)) {
            AutoPtr<IInterface> outface;
            it->GetNext((IInterface**)&outface);
            AutoPtr<IMapEntry> entry = IMapEntry::Probe(outface);
            AutoPtr<IInterface> obj;
            entry->GetKey((IInterface**)&obj);
            assert(ICharSequence::Probe(obj) != NULL);
            ICharSequence::Probe(obj)->ToString(&key);
            dest->WriteString(key);

            obj = NULL;
            entry->GetValue((IInterface**)&obj);
            WriteValue(dest, obj);
        }
    }

    return NOERROR;
}

ECode BaseBundle::WriteToParcelInner(
    /* [in] */ IParcel* dest)
{
    Int32 length = 0;
    if (mParcelledData != NULL) {
        if (mParcelledData == EMPTY_PARCEL) {
            dest->WriteInt32(0);
        }
        else {
            mParcelledData->GetDataSize(&length);
            dest->WriteInt32(length);
            dest->WriteInt32(BUNDLE_MAGIC); // 'B' 'N' 'D' 'L'
            dest->AppendFrom(mParcelledData, 0, length);
        }
    }
    else {
        // Special case for empty bundles.
        Int32 size = 0;
        if (mMap) {
            mMap->GetSize(&size);
        }
        if (size == 0) {
            dest->WriteInt32(0);
        }
        else {
            Int32 lengthPos;
            dest->GetDataPosition(&lengthPos);

            dest->WriteInt32(-1); // dummy, will hold length
            dest->WriteInt32(BUNDLE_MAGIC); // 'B' 'N' 'D' 'L'

            Int32 startPos, endPos;
            dest->GetDataPosition(&startPos);
            WriteArrayMapInternal(dest, mMap);
            dest->GetDataPosition(&endPos);

            // Backpatch length
            dest->SetDataPosition(lengthPos);
            length = endPos - startPos;
            dest->WriteInt32(length);
            dest->SetDataPosition(endPos);
        }
    }

    if (length != 0) {
        if (mJavaData != NULL) {
           dest->WriteInt32(mJavaData->GetLength());
           dest->WriteArrayOf((Handle32)mJavaData.Get());
        }
        else {
           dest->WriteInt32(0);
        }
    }

    return NOERROR;
}

ECode BaseBundle::ReadFromParcelInner(
    /* [in] */ IParcel* parcel)
{
    Int32 length;
    parcel->ReadInt32(&length);
    if (length < 0) {
        // throw new RuntimeException("Bad length in parcel: " + length);
        return E_RUNTIME_EXCEPTION;
    }
    FAIL_RETURN(ReadFromParcelInner(parcel, length));
    return NOERROR;
}

ECode BaseBundle::ReadFromParcelInner(
    /* [in] */ IParcel* source,
    /* [in] */ Int32 length)
{
    if (length == 0) {
        // Empty Bundle or end of data.
        mParcelledData = EMPTY_PARCEL;
        return NOERROR;
    }

    android::Parcel* parcel;
    source->GetDataPayload((Handle32*)&parcel);

    Int32 magic;
    source->ReadInt32(&magic);
    if (magic != BUNDLE_MAGIC) {
        //noinspection ThrowableInstanceNeverThrown
        // String st = Log.getStackTraceString(new RuntimeException());
        // Log.e("Bundle", "readBundle: bad magic number");
        // Log.e("Bundle", "readBundle: trace = " + st);
        Logger::E(TAG, "Bad magic number for Bundle: 0x%08x", magic);
        return E_ILLEGAL_STATE_EXCEPTION;
    }

    // Advance within this Parcel
    Int32 offset;
    source->GetDataPosition(&offset);
    source->SetDataPosition(offset + length);

    mParcelledData = NULL;
    CParcel::New((IParcel**)&mParcelledData);
    mParcelledData->SetDataPosition(0);
    mParcelledData->AppendFrom(source, offset, length);
    mParcelledData->SetDataPosition(0);

    Int32 javaDataLength;
    source->ReadInt32(&javaDataLength);
    if (javaDataLength > 0) {
       AutoPtr<ArrayOf<Byte> > data;
       source->ReadArrayOf((Handle32*)&data);
       mJavaData = data;
    }
    return NOERROR;
}

ECode BaseBundle::SetJavaData(
    /* [in] */ ArrayOf<Byte>* data)
{
    mJavaData = data;
    return NOERROR;
}

ECode BaseBundle::GetJavaData(
    /* [out, callee] */ ArrayOf<Byte>** data)
{
    VALIDATE_NOT_NULL(data)
    *data = mJavaData;
    REFCOUNT_ADD(*data)
    return NOERROR;
}

} // namespace Os
} // namespace Droid
} // namespace Elastos
