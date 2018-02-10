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

#include "elastos/droid/javaproxy/CInputDevicesChangedListenerNative.h"
#include "elastos/droid/javaproxy/Util.h"
#include <elastos/utility/logging/Logger.h>

using Elastos::Droid::Hardware::Input::EIID_IInputDevicesChangedListener;
using Elastos::Droid::Os::EIID_IBinder;
using Elastos::Utility::Logging::Logger;

namespace Elastos {
namespace Droid {
namespace JavaProxy {

const String CInputDevicesChangedListenerNative::TAG("CInputDevicesChangedListenerNative");

CAR_INTERFACE_IMPL_2(CInputDevicesChangedListenerNative, Object, IInputDevicesChangedListener, IBinder)

CAR_OBJECT_IMPL(CInputDevicesChangedListenerNative)

CInputDevicesChangedListenerNative::~CInputDevicesChangedListenerNative()
{
    JNIEnv* env;
    mJVM->AttachCurrentThread(&env, NULL);
    env->DeleteGlobalRef(mJInstance);
}

ECode CInputDevicesChangedListenerNative::constructor(
    /* [in] */ HANDLE jVM,
    /* [in] */ HANDLE jInstance)
{
    mJVM = (JavaVM*)jVM;
    mJInstance = (jobject)jInstance;
    return NOERROR;
}

ECode CInputDevicesChangedListenerNative::OnInputDevicesChanged(
    /* [in] */ ArrayOf<Int32>* deviceIdAndGeneration)
{
    // LOGGERD(TAG, "+ CInputDevicesChangedListenerNative::OnInputDevicesChanged()");

    JNIEnv* env;
    mJVM->AttachCurrentThread(&env, NULL);

    jclass c = env->FindClass("android/hardware/input/IInputDevicesChangedListener");
    Util::CheckErrorAndLog(env, TAG, "FindClass: IInputDevicesChangedListener", __LINE__);

    jmethodID m = env->GetMethodID(c, "onInputDevicesChanged", "([I)V");
    Util::CheckErrorAndLog(env, TAG, "GetMethodID: onInputDevicesChanged", __LINE__);

    jintArray jdeviceIdAndGeneration = NULL;
    if (deviceIdAndGeneration != NULL) {
        jdeviceIdAndGeneration = Util::ToJavaIntArray(env, deviceIdAndGeneration);
    }

    env->CallVoidMethod(mJInstance, m, jdeviceIdAndGeneration);
    Util::CheckErrorAndLog(env, TAG, "CallVoidMethod: onInputDevicesChanged", __LINE__);

    env->DeleteLocalRef(c);
    if(jdeviceIdAndGeneration){
        env->DeleteLocalRef(jdeviceIdAndGeneration);
    }

    // LOGGERD(TAG, "- CInputDevicesChangedListenerNative::OnInputDevicesChanged()");
    return NOERROR;
}

ECode CInputDevicesChangedListenerNative::ToString(
    /* [out] */ String* str)
{
    // LOGGERD(TAG, "+ CInputDevicesChangedListenerNative::ToString()");

    JNIEnv* env;
    mJVM->AttachCurrentThread(&env, NULL);

    jclass c = env->FindClass("java/lang/Object");
    Util::CheckErrorAndLog(env, TAG, "FindClass: Object %d", __LINE__);

    jmethodID m = env->GetMethodID(c, "toString", "()Ljava/lang/String;");
    Util::CheckErrorAndLog(env, TAG, "GetMethodID: toString %d", __LINE__);

    jstring jstr = (jstring)env->CallObjectMethod(mJInstance, m);
    Util::CheckErrorAndLog(env, TAG, "CallVoidMethod: toString %d", __LINE__);

    *str = Util::GetElString(env, jstr);

    env->DeleteLocalRef(c);
    env->DeleteLocalRef(jstr);

    // LOGGERD(TAG, "- CInputDevicesChangedListenerNative::ToString()");
    return NOERROR;
}

}
}
}

