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

#ifndef __ELASTOS_DROID_JAVAPROXY_CMEDIASESSIONCALLBACKSTUBNATIVE_H__
#define __ELASTOS_DROID_JAVAPROXY_CMEDIASESSIONCALLBACKSTUBNATIVE_H__

#include "_Elastos_Droid_JavaProxy_CMediaSessionCallbackStubNative.h"
#include "Elastos.Droid.Os.h"
#include "Elastos.Droid.Media.h"
#include <elastos/core/Object.h>
#include <jni.h>

using Elastos::Droid::Content::IIntent;
using Elastos::Droid::Os::IBinder;
using Elastos::Droid::Os::IBinder;
using Elastos::Droid::Os::IBundle;
using Elastos::Droid::Os::IResultReceiver;
using Elastos::Droid::Media::Session::IISessionCallback;
using Elastos::Droid::Media::IRating;

namespace Elastos {
namespace Droid {
namespace JavaProxy {

CarClass(CMediaSessionCallbackStubNative)
    , public Object
    , public IISessionCallback
    , public IBinder
{
public:
    ~CMediaSessionCallbackStubNative();

    CAR_INTERFACE_DECL()

    CAR_OBJECT_DECL()

    CARAPI ToString(
        /* [out] */ String* str);

    CARAPI constructor(
        /* [in] */ HANDLE jVM,
        /* [in] */ HANDLE jInstance);

    CARAPI OnCommand(
        /* [in] */ const String& command,
        /* [in] */ IBundle * args,
        /* [in] */ IResultReceiver * cb);

    CARAPI OnMediaButton(
        /* [in] */ IIntent * mediaButtonIntent,
        /* [in] */ Int32 sequenceNumber,
        /* [in] */ IResultReceiver * cb);

    // These callbacks are for the TransportPerformer
    CARAPI OnPlay();

    CARAPI OnPlayFromMediaId(
        /* [in] */ const String& mediaId,
        /* [in] */ IBundle * extras);

    CARAPI OnPlayFromSearch(
        /* [in] */ const String& query,
        /* [in] */ IBundle * extras);

    CARAPI OnSkipToTrack(
        /* [in] */ Int64 id);

    CARAPI OnPause();

    CARAPI OnStop();

    CARAPI OnNext();

    CARAPI OnPrevious();

    CARAPI OnFastForward();

    CARAPI OnRewind();

    CARAPI OnSeekTo(
        /* [in] */ Int64 pos);

    CARAPI OnRate(
        /* [in] */ IRating * rating);

    // @Override
    CARAPI SetRemoteControlClientBrowsedPlayer();

    // @Override
    CARAPI SetRemoteControlClientPlayItem(
        /* [in] */ Int64 uid,
        /* [in] */ Int32 scope);

    // @Override
    CARAPI GetRemoteControlClientNowPlayingEntries();

    CARAPI OnCustomAction(
        /* [in] */ const String& action,
        /* [in] */ IBundle * args);

    // These callbacks are for volume handling
    CARAPI OnAdjustVolume(
        /* [in] */ Int32 direction);

    CARAPI OnSetVolumeTo(
        /* [in] */ Int32 value);

private:
    static const String TAG;

    JavaVM* mJVM;
    jobject mJInstance;
};

} // JavaProxy
} // Droid
} // Elastos

#endif // __ELASTOS_DROID_JAVAPROXY_CMEDIASESSIONCALLBACKSTUBNATIVE_H__
