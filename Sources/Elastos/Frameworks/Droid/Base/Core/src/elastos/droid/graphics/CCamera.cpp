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

#include "Elastos.Droid.Content.h"
#include "Elastos.Droid.Os.h"
#include "elastos/droid/ext/frameworkext.h"
#include "elastos/droid/graphics/CCamera.h"
#include "elastos/droid/graphics/Matrix.h"
#include "elastos/droid/graphics/CMatrix.h"
#include "elastos/droid/graphics/CCanvas.h"
#include <skia/utils/SkCamera.h>
#include <hwui/Canvas.h>

namespace Elastos {
namespace Droid {
namespace Graphics {

CAR_OBJECT_IMPL(CCamera)

CAR_INTERFACE_IMPL(CCamera, Object, ICamera)

CCamera::CCamera()
    : mNativeInstance(0)
{
}

CCamera::~CCamera()
{
    NativeDestructor();
}

ECode CCamera::constructor()
{
    NativeConstructor();
    return NOERROR;
}

ECode CCamera::Save()
{
    Sk3DView* v = reinterpret_cast<Sk3DView*>(mNativeInstance);
    v->save();
    return NOERROR;
}

ECode CCamera::Restore()
{
    Sk3DView* v = reinterpret_cast<Sk3DView*>(mNativeInstance);
    v->restore();
    return NOERROR;
}

ECode CCamera::Translate(
    /* [in] */ Float x,
    /* [in] */ Float y,
    /* [in] */ Float z)
{
    Sk3DView* v = reinterpret_cast<Sk3DView*>(mNativeInstance);
    v->translate(x, y, z);
    return NOERROR;
}

ECode CCamera::RotateX(
    /* [in] */ Float deg)
{
    Sk3DView* v = reinterpret_cast<Sk3DView*>(mNativeInstance);
    v->rotateX(deg);
    return NOERROR;
}

ECode CCamera::RotateY(
    /* [in] */ Float deg)
{
    Sk3DView* v = reinterpret_cast<Sk3DView*>(mNativeInstance);
    v->rotateY(deg);
    return NOERROR;
}

ECode CCamera::RotateZ(
    /* [in] */ Float deg)
{
    Sk3DView* v = reinterpret_cast<Sk3DView*>(mNativeInstance);
    v->rotateZ(deg);
    return NOERROR;
}

ECode CCamera::Rotate(
    /* [in] */ Float x,
    /* [in] */ Float y,
    /* [in] */ Float z)
{
    Sk3DView* v = reinterpret_cast<Sk3DView*>(mNativeInstance);
    v->rotateX(x);
    v->rotateY(y);
    v->rotateZ(z);
    return NOERROR;
}

ECode CCamera::GetLocationX(
    /* [out] */ Float* locationX)
{
    VALIDATE_NOT_NULL(locationX);
    Sk3DView* v = reinterpret_cast<Sk3DView*>(mNativeInstance);
    *locationX = SkScalarToFloat(v->getCameraLocationX());
    return NOERROR;
}

ECode CCamera::GetLocationY(
    /* [out] */ Float* locationY)
{
    VALIDATE_NOT_NULL(locationY);
    Sk3DView* v = reinterpret_cast<Sk3DView*>(mNativeInstance);
    *locationY = SkScalarToFloat(v->getCameraLocationY());
    return NOERROR;
}

ECode CCamera::GetLocationZ(
    /* [out] */ Float* locationZ)
{
    VALIDATE_NOT_NULL(locationZ);
    Sk3DView* v = reinterpret_cast<Sk3DView*>(mNativeInstance);
    *locationZ = SkScalarToFloat(v->getCameraLocationZ());
    return NOERROR;
}

ECode CCamera::SetLocation(
    /* [in] */ Float x,
    /* [in] */ Float y,
    /* [in] */ Float z)
{
    Sk3DView* v = reinterpret_cast<Sk3DView*>(mNativeInstance);
    v->setCameraLocation(x, y, z);
    return NOERROR;
}

ECode CCamera::GetMatrix(
    /* [in] */ IMatrix* matrix)
{
    NativeGetMatrix(((Matrix*)matrix)->mNativeMatrix);
    return NOERROR;
}

ECode CCamera::ApplyToCanvas(
    /* [in] */ ICanvas* canvas)
{
    Boolean is = FALSE;
    if (canvas->IsHardwareAccelerated(&is), is) {
        if (mMatrix == NULL) {
            CMatrix::New((IMatrix**)&mMatrix);
        }
        GetMatrix(mMatrix);
        canvas->Concat(mMatrix);
    } else {
        NativeApplyToCanvas(((CCanvas*)canvas)->mNativeCanvas);
    }
    return NOERROR;
}

ECode CCamera::DotWithNormal(
    /* [in] */ Float dx,
    /* [in] */ Float dy,
    /* [in] */ Float dz,
    /* [out] */ Float* result)
{
    VALIDATE_NOT_NULL(result);

    Sk3DView* v = reinterpret_cast<Sk3DView*>(mNativeInstance);
    SkScalar dot = v->dotWithNormal(dx, dy, dz);
    *result = SkScalarToFloat(dot);
    return NOERROR;
}

void CCamera::NativeConstructor()
{
    if (mNativeInstance == 0) {
        Sk3DView* view = new Sk3DView();
        mNativeInstance = reinterpret_cast<Int64>(view);
    }
}

void CCamera::NativeDestructor()
{
    if (mNativeInstance != 0) {
        Sk3DView* view = reinterpret_cast<Sk3DView*>(mNativeInstance);
        delete view;
        mNativeInstance = 0;
    }
}

void CCamera::NativeGetMatrix(
    /* [in] */ Int64 nativeMatrix)
{
    SkMatrix* native_matrix =  reinterpret_cast<SkMatrix*>(nativeMatrix);
    Sk3DView* v = reinterpret_cast<Sk3DView*>(mNativeInstance);
    v->getMatrix(native_matrix);
}

void CCamera::NativeApplyToCanvas(
    /* [in] */ Int64 canvasHandle)
{
    SkCanvas* canvas = reinterpret_cast<android::Canvas*>(canvasHandle)->asSkCanvas();
    Sk3DView* v = reinterpret_cast<Sk3DView*>(mNativeInstance);
    v->applyToCanvas(canvas);
}

} // namespace Graphics
} // namepsace Droid
} // namespace Elastos
