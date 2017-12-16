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

#ifndef __ELASTOS_DROID_VIEW_INPUTMETHOD_CIINPUTMETHODCLIENT_H__
#define __ELASTOS_DROID_VIEW_INPUTMETHOD_CIINPUTMETHODCLIENT_H__

#include "_Elastos_Droid_View_InputMethod_CIInputMethodClient.h"
#include "elastos/droid/view/inputmethod/CInputMethodManager.h"
#include <elastos/core/Object.h>
#include <binder/Binder.h>

namespace Elastos {
namespace Droid {
namespace View {
namespace InputMethod {

CarClass(CIInputMethodClient)
    , public Object
    , public IInputMethodClient
    , public IBinder
{
public:
    CAR_INTERFACE_DECL()

    CAR_OBJECT_DECL()

    CARAPI constructor(
        /* [in] */ IInputMethodManager* host);

    CARAPI SetUsingInputMethod(
        /* [in] */ Boolean state);

    CARAPI OnBindMethod(
        /* [in] */ IInputBindResult* res);

    CARAPI OnUnbindMethod(
        /* [in] */ Int32 sequence);

    CARAPI SetActive(
        /* [in] */ Boolean active);

    CARAPI ToString(
        /* [out] */ String* str);

    CARAPI SetUserActionNotificationSequenceNumber(
        /* [in] */ Int32 sequenceNumber);

public:
    android::IBinder* mBBinder;

private:
    CInputMethodManager* mHost;
};

} // namespace InputMethod
} // namespace View
} // namespace Droid
} // namespace Elastos

#endif  //__ELASTOS_DROID_VIEW_INPUTMETHOD_CIINPUTMETHODCLIENT_H__
