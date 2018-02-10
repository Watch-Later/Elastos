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
//    BitmapHelper.java
//put this file at the end of the include list
//so the type definition used in this file will be found
#ifndef ELASTOS_BITMAPHELPER_CALLBACK_DEC_HH
#define ELASTOS_BITMAPHELPER_CALLBACK_DEC_HH


#ifdef __cplusplus
extern "C"
{
#endif
    extern void Elastos_BitmapHelper_InitCallback(HANDLE cb);
#ifdef __cplusplus
}
#endif

namespace Elastos {
namespace Droid {
namespace Webkit {
namespace Webview {
namespace Chromium {
namespace Ui {
namespace Gfx {

struct ElaBitmapHelperCallback
{
    AutoPtr<IInterface> (*elastos_BitmapHelper_createBitmap)(Int32 width, Int32 height, Int32 bitmapFormatValue);
    AutoPtr<IInterface> (*elastos_BitmapHelper_decodeDrawableResource)(const String& name, Int32 reqWidth, Int32 reqHeight);
    Int32 (*elastos_BitmapHelper_getBitmapFormatForConfig)(Int32 bitmapConfig);
};

void* BitmapHelper::ElaBitmapHelperCallback_Init()
{
    static ElaBitmapHelperCallback sElaBitmapHelperCallback;

    sElaBitmapHelperCallback.elastos_BitmapHelper_createBitmap = &BitmapHelper::CreateBitmap;
    sElaBitmapHelperCallback.elastos_BitmapHelper_decodeDrawableResource = &BitmapHelper::DecodeDrawableResource;
    sElaBitmapHelperCallback.elastos_BitmapHelper_getBitmapFormatForConfig = &BitmapHelper::GetBitmapFormatForConfig;

    Elastos_BitmapHelper_InitCallback((HANDLE)&sElaBitmapHelperCallback);
    return &sElaBitmapHelperCallback;
}

static void* sPElaBitmapHelperCallback = BitmapHelper::ElaBitmapHelperCallback_Init();

} // namespace Gfx
} // namespace Ui
} // namespace Chromium
} // namespace Webview
} // namespace Webkit
} // namespace Droid
} // namespace Elastos

#endif //ELASTOS_BITMAPHELPER_CALLBACK_DEC_HH
