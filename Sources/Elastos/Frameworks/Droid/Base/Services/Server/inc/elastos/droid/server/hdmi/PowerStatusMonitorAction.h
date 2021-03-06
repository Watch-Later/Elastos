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

#ifndef __ELASTOS_DROID_SERVER_HDMI_POWERSTATUSMONITORACTION_H__
#define __ELASTOS_DROID_SERVER_HDMI_POWERSTATUSMONITORACTION_H__

#include "_Elastos.Droid.Server.h"
#include "elastos/droid/server/hdmi/HdmiCecFeatureAction.h"
#include <elastos/droid/ext/frameworkext.h>
#include <elastos/core/Object.h>
#include <Elastos.Droid.Utility.h>

using Elastos::Utility::IList;
using Elastos::Droid::Utility::ISparseInt32Array;

namespace Elastos {
namespace Droid {
namespace Server {
namespace Hdmi {

/**
 * Action that check each device's power status.
 */
class PowerStatusMonitorAction
    : public HdmiCecFeatureAction
    , public IPowerStatusMonitorAction
{
private:
    class InnerSub_SendMessageCallback
        : public Object
        , public IHdmiControlServiceSendMessageCallback
    {
    public:
        CAR_INTERFACE_DECL()

        InnerSub_SendMessageCallback(
            /* [in] */ PowerStatusMonitorAction* host,
            /* [in] */ Int32 logicalAddress);

        //@Override
        CARAPI OnSendCompleted(
            /* [in] */ Int32 error);

    private:
        PowerStatusMonitorAction* mHost;
        Int32 mLogicalAddress;
    };

public:
    CAR_INTERFACE_DECL()

    PowerStatusMonitorAction();

    CARAPI constructor(
        /* [in] */ IHdmiCecLocalDevice* source);

    // @Override
    CARAPI Start(
        /* [out] */ Boolean* result);

    // @Override
    CARAPI ProcessCommand(
        /* [in] */ IHdmiCecMessage* cmd,
        /* [out] */ Boolean* result);

    // @Override
    CARAPI HandleTimerEvent(
        /* [in] */ Int32 state);

private:
    CARAPI_(Boolean) HandleReportPowerStatus(
        /* [in] */ IHdmiCecMessage* cmd);

    CARAPI HandleTimeout();

    CARAPI ResetPowerStatus(
        /* [in] */ IList* deviceInfos);

    CARAPI QueryPowerStatus();

    CARAPI UpdatePowerStatus(
        /* [in] */ Int32 logicalAddress,
        /* [in] */ Int32 newStatus,
        /* [in] */ Boolean remove);

private:
    static const String TAG;

    // State that waits for <Report Power Status> once sending <Give Device Power Status>
    // to all external devices.
    static const Int32 STATE_WAIT_FOR_REPORT_POWER_STATUS;
    // State that waits for next monitoring
    static const Int32 STATE_WAIT_FOR_NEXT_MONITORING;

    static const Int32 INVALID_POWER_STATUS;

    // Monitoring interval (60s)
    static const Int32 MONITIROING_INTERNAL_MS;

    // Timeout once sending <Give Device Power Status>
    static const Int32 REPORT_POWER_STATUS_TIMEOUT_MS;

    // Container for current power status of all external devices.
    // The key is a logical address a device and the value is current power status of it
    // Whenever the action receives <Report Power Status> from a device,
    // it removes an entry of the given device.
    // If this is non-empty when timeout for STATE_WAIT_FOR_REPORT_POWER_STATUS happens,
    // updates power status of all remaining devices into POWER_STATUS_UNKNOWN.
    AutoPtr<ISparseInt32Array> mPowerStatus;
};

} // namespace Hdmi
} // namespace Server
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_SERVER_HDMI_POWERSTATUSMONITORACTION_H__
