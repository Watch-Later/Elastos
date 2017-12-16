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

#include "elastos/droid/graphics/CLayerRasterizer.h"

namespace Elastos {
namespace Droid {
namespace Graphics {

CAR_OBJECT_IMPL(CLayerRasterizer);
CAR_INTERFACE_IMPL(CLayerRasterizer, Rasterizer, ILayerRasterizer);
ECode CLayerRasterizer::constructor()
{
    return NOERROR;
}

ECode CLayerRasterizer::AddLayer(
    /* [in] */ IPaint* paint,
    /* [in] */ Float dx,
    /* [in] */ Float dy)
{
    return NOERROR;
}

ECode CLayerRasterizer::AddLayer(
    /* [in] */ IPaint* paint)
{
    return NOERROR;
}

} // namespace Graphics
} // namepsace Droid
} // namespace Elastos
