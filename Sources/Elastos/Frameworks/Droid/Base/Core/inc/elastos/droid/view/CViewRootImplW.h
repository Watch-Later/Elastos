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

#ifndef __ELASTOS_DROID_VIEW_CVIEWROOTIMPLW_H__
#define __ELASTOS_DROID_VIEW_CVIEWROOTIMPLW_H__

#include "elastos/droid/ext/frameworkext.h"
#include "_Elastos_Droid_View_CViewRootImplW.h"
#include <elastos/core/Object.h>
#include <binder/Binder.h>

using Elastos::Droid::Os::IParcelFileDescriptor;
using Elastos::Droid::Os::IBundle;
using Elastos::Droid::Os::IBinder;
using Elastos::Droid::Graphics::IRect;
using Elastos::Droid::Content::Res::IConfiguration;

namespace Elastos {
namespace Droid {
namespace View {

CarClass(CViewRootImplW)
    , public Object
    , public IIWindow
    , public IBinder
{
public:
    CAR_OBJECT_DECL()

    CAR_INTERFACE_DECL()

    ~CViewRootImplW();

    CARAPI constructor(
        /* [in] */ IViewRootImpl* viewRoot);

    CARAPI Resized(
        /* [in] */ IRect* frame,
        /* [in] */ IRect* overscanInsets,
        /* [in] */ IRect* contentInsets,
        /* [in] */ IRect* visibleInsets,
        /* [in] */ IRect* stableInsets,
        /* [in] */ Boolean reportDraw,
        /* [in] */ IConfiguration* newConfig);

    CARAPI Moved(
        /* [in] */ Int32 newX,
        /* [in] */ Int32 newY);

    CARAPI DispatchAppVisibility(
        /* [in] */ Boolean visible);

    CARAPI DispatchGetNewSurface();

    CARAPI WindowFocusChanged(
        /* [in] */ Boolean hasFocus,
        /* [in] */ Boolean inTouchMode);

    CARAPI ExecuteCommand(
        /* [in] */ const String& command,
        /* [in] */ const String& parameters,
        /* [in] */ IParcelFileDescriptor* descriptor);

    CARAPI CloseSystemDialogs(
        /* [in] */ const String& reason);

    CARAPI DispatchWallpaperOffsets(
        /* [in] */ Float x,
        /* [in] */ Float y,
        /* [in] */ Float xStep,
        /* [in] */ Float yStep,
        /* [in] */ Boolean sync);

    CARAPI DispatchWallpaperCommand(
        /* [in] */ const String& action,
        /* [in] */ Int32 x,
        /* [in] */ Int32 y,
        /* [in] */ Int32 z,
        /* [in] */ IBundle* extras,
        /* [in] */ Boolean sync);

    /* Drag/drop */
    CARAPI DispatchDragEvent(
        /* [in] */ IDragEvent* event);

    CARAPI DispatchSystemUiVisibilityChanged(
        /* [in] */ Int32 seq,
        /* [in] */ Int32 globalVisibility,
        /* [in] */ Int32 localValue,
        /* [in] */ Int32 localChanges);

    CARAPI DoneAnimating();

    CARAPI ToString(
        /* [out] */ String* description);

private:
    static CARAPI_(Int32) CheckCallingPermission(
        /* [in] */ const String& permission);

    CARAPI_(AutoPtr<IViewRootImpl>) GetViewRootImpl();

public:
    android::IBinder* mBBinder;

private:
    AutoPtr<IWeakReference> mViewAncestor;
    AutoPtr<IWindowSession> mWindowSession;
};

} // namespace View
} // namespace Droid
} // namespace Elastos

#endif //__ELASTOS_DROID_VIEW_CVIEWROOTIMPLW_H__
