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
#include "elastos/droid/graphics/CCornerPathEffect.h"
#include <skia/effects/SkCornerPathEffect.h>

namespace Elastos {
namespace Droid {
namespace Graphics {

CAR_OBJECT_IMPL(CCornerPathEffect);
CAR_INTERFACE_IMPL(CCornerPathEffect, PathEffect, ICornerPathEffect);
ECode CCornerPathEffect::constructor(
    /* [in] */ Float radius)
{
    mNativeInstance = NativeCreate(radius);
    return NOERROR;
}

Int64 CCornerPathEffect::NativeCreate(
    /* [in] */ Float radius)
{
    SkPathEffect* effect = SkCornerPathEffect::Make(radius).release();
    return reinterpret_cast<Int64>(effect);
}

} // namespace Graphics
} // namepsace Droid
} // namespace Elastos

