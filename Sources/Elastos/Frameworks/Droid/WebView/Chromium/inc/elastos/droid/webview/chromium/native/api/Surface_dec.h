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
//    Surface.class
//put this file at the end of the include list
//so the type definition used in this file will be found
#ifndef ELASTOS_SURFACE_CALLBACK_DEC_HH
#define ELASTOS_SURFACE_CALLBACK_DEC_HH


#ifdef __cplusplus
extern "C"
{
#endif
    extern void Elastos_Surface_InitCallback(HANDLE cb);
#ifdef __cplusplus
}
#endif

namespace Elastos {
namespace Droid {
namespace Webkit {
namespace Webview {
namespace Chromium {
namespace Api {

struct ElaSurfaceCallback
{
    void (*elastos_Surface_finalize)(IInterface* obj);
    void (*elastos_Surface_release)(IInterface* obj);
    Boolean (*elastos_Surface_isValid)(IInterface* obj);
    AutoPtr<IInterface> (*elastos_Surface_lockCanvas)(IInterface* obj, IInterface* p0);
    void (*elastos_Surface_unlockCanvasAndPost)(IInterface* obj, IInterface* p0);
    void (*elastos_Surface_unlockCanvas)(IInterface* obj, IInterface* p0);
    Int32 (*elastos_Surface_describeContents)(IInterface* obj);
    void (*elastos_Surface_readFromParcel)(IInterface* obj, IInterface* p0);
    void (*elastos_Surface_writeToParcel)(IInterface* obj, IInterface* p0, Int32 p1);
    String (*elastos_Surface_toString)(IInterface* obj);
    AutoPtr<IInterface> (*elastos_Surface_Constructor)(IInterface* p0);
};

void* AwSurface::ElaSurfaceCallback_Init()
{
    static ElaSurfaceCallback sElaSurfaceCallback;

    sElaSurfaceCallback.elastos_Surface_finalize = &AwSurface::Finalize;
    sElaSurfaceCallback.elastos_Surface_release = &AwSurface::ReleaseResources;
    sElaSurfaceCallback.elastos_Surface_isValid = &AwSurface::IsValid;
    sElaSurfaceCallback.elastos_Surface_lockCanvas = &AwSurface::LockCanvas;
    sElaSurfaceCallback.elastos_Surface_unlockCanvasAndPost = &AwSurface::UnlockCanvasAndPost;
    sElaSurfaceCallback.elastos_Surface_unlockCanvas = &AwSurface::UnlockCanvas;
    sElaSurfaceCallback.elastos_Surface_describeContents = &AwSurface::DescribeContents;
    sElaSurfaceCallback.elastos_Surface_readFromParcel = &AwSurface::ReadFromParcel;
    sElaSurfaceCallback.elastos_Surface_writeToParcel = &AwSurface::WriteToParcel;
    sElaSurfaceCallback.elastos_Surface_toString = &AwSurface::ToString;
    sElaSurfaceCallback.elastos_Surface_Constructor = &AwSurface::Constructor;

    Elastos_Surface_InitCallback((HANDLE)&sElaSurfaceCallback);
    return &sElaSurfaceCallback;
}

static void* sPElaSurfaceCallback = AwSurface::ElaSurfaceCallback_Init();

} // namespace Api
} // namespace Chromium
} // namespace Webview
} // namespace Webkit
} // namespace Droid
} // namespace Elastos

#endif //ELASTOS_SURFACE_CALLBACK_DEC_HH
