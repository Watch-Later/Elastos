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

//This file is autogenerated for
//    DeviceFormFactor.java
//put this file at the end of the include list
//so the type definition used in this file will be found
#ifndef ELASTOS_DEVICEFORMFACTOR_CALLBACK_DEC_HH
#define ELASTOS_DEVICEFORMFACTOR_CALLBACK_DEC_HH


#ifdef __cplusplus
extern "C"
{
#endif
    extern void Elastos_DeviceFormFactor_InitCallback(HANDLE cb);
#ifdef __cplusplus
}
#endif

namespace Elastos {
namespace Droid {
namespace Webkit {
namespace Webview {
namespace Chromium {
namespace Ui {
namespace Base {

struct ElaDeviceFormFactorCallback
{
    Boolean (*elastos_DeviceFormFactor_isTablet)(IInterface* context);
};

void* DeviceFormFactor::ElaDeviceFormFactorCallback_Init()
{
    static ElaDeviceFormFactorCallback sElaDeviceFormFactorCallback;

    sElaDeviceFormFactorCallback.elastos_DeviceFormFactor_isTablet = &DeviceFormFactor::IsTablet;

    Elastos_DeviceFormFactor_InitCallback((HANDLE)&sElaDeviceFormFactorCallback);
    return &sElaDeviceFormFactorCallback;
}

static void* sPElaDeviceFormFactorCallback = DeviceFormFactor::ElaDeviceFormFactorCallback_Init();

} // namespace Base
} // namespace Ui
} // namespace Chromium
} // namespace Webview
} // namespace Webkit
} // namespace Droid
} // namespace Elastos

#endif //ELASTOS_DEVICEFORMFACTOR_CALLBACK_DEC_HH
