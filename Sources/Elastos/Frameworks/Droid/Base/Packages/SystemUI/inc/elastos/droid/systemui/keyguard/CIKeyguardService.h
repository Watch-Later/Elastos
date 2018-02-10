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

#ifndef __ELASTOS_DROID_SYSTEMUI_KEYGUARD_CIKEYGUARDSERVICE_H__
#define __ELASTOS_DROID_SYSTEMUI_KEYGUARD_CIKEYGUARDSERVICE_H__

#include "_Elastos_Droid_SystemUI_Keyguard_CIKeyguardService.h"
#include "Elastos.Droid.Internal.h"
#include <elastos/core/Object.h>

using Elastos::Droid::Os::IBinder;
using Elastos::Droid::Os::IBundle;
using Elastos::Droid::Internal::Policy::IIKeyguardExitCallback;
using Elastos::Droid::Internal::Policy::IIKeyguardService;
using Elastos::Droid::Internal::Policy::IIKeyguardShowCallback;
using Elastos::Droid::View::IMotionEvent;
using Elastos::Core::Object;

namespace Elastos {
namespace Droid {
namespace SystemUI {
namespace Keyguard {

class KeyguardService;

CarClass(CIKeyguardService)
    , public Object
    , public IIKeyguardService
    , public IBinder
{
public:
    CAR_OBJECT_DECL()

    CAR_INTERFACE_DECL()

    CIKeyguardService();

    CARAPI constructor(
        /* [in] */ IKeyguardService* host);

    CARAPI constructor(
        /* [in] */ HANDLE host);

    // @Override
    CARAPI IsShowing(
        /* [out] */ Boolean* result);

    // @Override
    CARAPI IsSecure(
        /* [out] */ Boolean* result);

    // @Override
    CARAPI IsShowingAndNotOccluded(
        /* [out] */ Boolean* result);

    // @Override
    CARAPI IsInputRestricted(
        /* [out] */ Boolean* result);

    // @Override
    CARAPI VerifyUnlock(
        /* [in] */ IIKeyguardExitCallback* callback);

    // @Override
    CARAPI KeyguardDone(
        /* [in] */ Boolean authenticated,
        /* [in] */ Boolean wakeup);

    // @Override
    CARAPI SetOccluded(
        /* [in] */ Boolean isOccluded,
        /* [out] */ Int32* result);

    // @Override
    CARAPI Dismiss();

    // @Override
    CARAPI OnDreamingStarted();

    // @Override
    CARAPI OnDreamingStopped();

    // @Override
    CARAPI OnScreenTurnedOff(
        /* [in] */ Int32 reason);

    // @Override
    CARAPI OnScreenTurnedOn(
        /* [in] */ IIKeyguardShowCallback* callback);

    // @Override
    CARAPI SetKeyguardEnabled(
        /* [in] */ Boolean enabled);

    // @Override
    CARAPI IsDismissable(
        /* [out] */ Boolean* result);

    // @Override
    CARAPI OnSystemReady();

    // @Override
    CARAPI DoKeyguardTimeout(
        /* [in] */ IBundle* options);

    // @Override
    CARAPI SetCurrentUser(
        /* [in] */ Int32 userId);

    // @Override
    CARAPI ShowAssistant();

    // @Override
    CARAPI Dispatch(
        /* [in] */ IMotionEvent* event);

    // @Override
    CARAPI LaunchCamera();

    // @Override
    CARAPI OnBootCompleted();

    // @Override
    CARAPI StartKeyguardExitAnimation(
        /* [in] */ Int64 startTime,
        /* [in] */ Int64 fadeoutDuration);

    // @Override
    CARAPI OnActivityDrawn();

    CARAPI ToString(
        /* [out] */ String* str);

private:
    Boolean mIsOccluded;

    KeyguardService* mHost;
};

} // namespace Keyguard
} // namespace SystemUI
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_SYSTEMUI_KEYGUARD_CIKEYGUARDSERVICE_H__