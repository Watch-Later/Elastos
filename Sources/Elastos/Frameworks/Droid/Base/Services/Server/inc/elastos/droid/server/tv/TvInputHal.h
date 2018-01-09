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

#ifndef __ELASTOS_DROID_SERVER_TV_TVINPUTHAL_H__
#define __ELASTOS_DROID_SERVER_TV_TVINPUTHAL_H__

#include "_Elastos.Droid.Server.h"
#include <elastos/core/Object.h>
#include <elastos/droid/ext/frameworkext.h>
#include <Elastos.Droid.Os.h>

using Elastos::Core::IArrayOf;
using Elastos::Droid::Media::Tv::ITvInputHardwareInfo;
using Elastos::Droid::Media::Tv::ITvStreamConfig;
using Elastos::Droid::Os::IHandler;
using Elastos::Droid::Os::IHandlerCallback;
using Elastos::Droid::Os::IMessage;
using Elastos::Droid::Os::IMessageQueue;
using Elastos::Droid::Utility::ISparseArray;
using Elastos::Droid::Utility::ISparseInt32Array;
using Elastos::Droid::View::ISurface;
using Elastos::Utility::IQueue;

namespace android {

class JTvInputHal;

} // namespace android

namespace Elastos {
namespace Droid {
namespace Server {
namespace Tv {

/**
 * Provides access to the low-level TV input hardware abstraction layer.
 */
class TvInputHal
    : public Object
    , public IHandlerCallback
{
    friend class android::JTvInputHal;

public:
    CAR_INTERFACE_DECL()

    TvInputHal();

    ~TvInputHal();

    CARAPI constructor(
        /* [in] */ ITvInputHalCallback* callback);

    CARAPI Init();

    CARAPI AddStream(
        /* [in] */ Int32 deviceId,
        /* [in] */ ISurface* surface,
        /* [in] */ ITvStreamConfig* streamConfig,
        /* [out] */ Int32* result);

    CARAPI RemoveStream(
        /* [in] */ Int32 deviceId,
        /* [in] */ ITvStreamConfig* streamConfig,
        /* [out] */ Int32* result);

    CARAPI Close();

    // @Override
    CARAPI HandleMessage(
        /* [in] */ IMessage* msg,
        /* [out] */ Boolean* result);

private:
    CARAPI_(Int64) NativeOpen(
        /* [in] */ TvInputHal* thiz,
        /* [in] */ IMessageQueue* queue);

    static CARAPI_(Int32) NativeAddStream(
        /* [in] */ Int64 ptr,
        /* [in] */ Int32 deviceId,
        /* [in] */ Int32 streamId,
        /* [in] */ ISurface* surface);

    static CARAPI_(Int32) NativeRemoveStream(
        /* [in] */ Int64 ptr,
        /* [in] */ Int32 deviceId,
        /* [in] */ Int32 streamId);

    static CARAPI_(AutoPtr<IArrayOf>) NativeGetStreamConfigs(
        /* [in] */ Int64 ptr,
        /* [in] */ Int32 deviceId,
        /* [in] */ Int32 generation);

    static CARAPI NativeClose(
        /* [in] */ Int64 ptr);

    CARAPI RetrieveStreamConfigsLocked(
        /* [in] */ Int32 deviceId);

    // Called from native
    CARAPI DeviceAvailableFromNative(
        /* [in] */ ITvInputHardwareInfo* info);

    CARAPI DeviceUnavailableFromNative(
        /* [in] */ Int32 deviceId);

    CARAPI StreamConfigsChangedFromNative(
        /* [in] */ Int32 deviceId);

    CARAPI FirstFrameCapturedFromNative(
        /* [in] */ Int32 deviceId,
        /* [in] */ Int32 streamId);

public:
    static const Int32 SUCCESS;
    static const Int32 ERROR_NO_INIT;
    static const Int32 ERROR_STALE_CONFIG;
    static const Int32 ERROR_UNKNOWN;

    static const Int32 EVENT_DEVICE_AVAILABLE;
    static const Int32 EVENT_DEVICE_UNAVAILABLE;
    static const Int32 EVENT_STREAM_CONFIGURATION_CHANGED;
    static const Int32 EVENT_FIRST_FRAME_CAPTURED;

private:
    static const Boolean DEBUG;
    static const String TAG;

    Object mLock;
    Int64 mPtr;
    AutoPtr<ITvInputHalCallback> mCallback;
    AutoPtr<IHandler> mHandler;
    AutoPtr<ISparseInt32Array> mStreamConfigGenerations;
    AutoPtr<ISparseArray> mStreamConfigs;

    // Handler.Callback implementation

    AutoPtr<IQueue> mPendingMessageQueue;
};

} // namespace Tv
} // namespace Server
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_SERVER_TV_TVINPUTHAL_H__
