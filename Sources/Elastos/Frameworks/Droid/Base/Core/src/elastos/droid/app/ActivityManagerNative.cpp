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

#include "Elastos.Droid.App.h"
#include "Elastos.Droid.Content.h"
#include "elastos/droid/app/ActivityManagerNative.h"
#include "elastos/droid/app/IActivityManager.h"
#include "elastos/droid/os/ServiceManager.h"
#include <elastos/utility/logging/Logger.h>

using Elastos::Droid::Os::IServiceManager;
using Elastos::Droid::Os::ServiceManager;
using Elastos::Droid::Content::IContext;
using Elastos::Droid::Content::IIIntentSender;
using Elastos::Utility::Logging::Logger;

namespace Elastos {
namespace Droid {
namespace App {

Boolean ActivityManagerNative::sSystemReady = FALSE;

AutoPtr<IIActivityManager> ActivityManagerNative::GetDefault()
{
    static AutoPtr<IIActivityManager> sAm;
    if (sAm != NULL) return sAm;

    android::sp<android::IBinder> am = ServiceManager::GetAndroidService(IContext::ACTIVITY_SERVICE);
    if (am == NULL) {
        Logger::W("ActivityManagerNative", "GetDefault(): %s service not ready yet.", IContext::ACTIVITY_SERVICE.string());
    }
    sAm = new IActivityManagerProxy(am);
    return sAm;
}

Boolean ActivityManagerNative::IsSystemReady()
{
    if (!sSystemReady) {
        GetDefault()->TestIsSystemReady(&sSystemReady);
    }
    return sSystemReady;
}

void ActivityManagerNative::BroadcastStickyIntent(
    /* [in] */ IIntent* intent,
    /* [in] */ const String& permission,
    /* [in] */ Int32 userId)
{
    Int32 res;
    String nullStr;
    GetDefault()->BroadcastIntent(
        NULL, intent, nullStr, NULL, IActivity::RESULT_OK, nullStr, NULL,
        nullStr /*permission*/, IAppOpsManager::OP_NONE, FALSE, TRUE, userId, &res);
}

void ActivityManagerNative::NoteWakeupAlarm(
    /* [in] */ IPendingIntent* ps,
    /* [in] */ Int32 sourceUid,
    /* [in] */ const String& sourcePkg)
{
    AutoPtr<IIIntentSender> target;
    ps->GetTarget((IIIntentSender**)&target);
    GetDefault()->NoteWakeupAlarm(target, sourceUid, sourcePkg);
}

} // namespace App
} // namespace Droid
} // namespace Elastos
