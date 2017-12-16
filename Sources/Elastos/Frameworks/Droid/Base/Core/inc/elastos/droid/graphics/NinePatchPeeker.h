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

#ifndef __ELASTOS_DROID_GRAPHICS_NINEPATCHPEEKER_H__
#define __ELASTOS_DROID_GRAPHICS_NINEPATCHPEEKER_H__

#include <skia/core/SkPngChunkReader.h>
#include <androidfw/ResourceTypes.h>

namespace Elastos {
namespace Droid {
namespace Graphics {

////////////////////////////////////////////////////////////////////////////////
// NinePatchPeeker

class NinePatchPeeker : public SkPngChunkReader {
public:
    NinePatchPeeker()
            : mPatch(NULL)
            , mPatchSize(0)
            , mHasInsets(false)
            , mOutlineRadius(0)
            , mOutlineAlpha(0) {
        memset(mOpticalInsets, 0, 4 * sizeof(int32_t));
        memset(mOutlineInsets, 0, 4 * sizeof(int32_t));
    }

    ~NinePatchPeeker() {
        free(mPatch);
    }

    bool readChunk(const char tag[], const void* data, size_t length) override;

    android::Res_png_9patch* mPatch;
    size_t mPatchSize;
    bool mHasInsets;
    int32_t mOpticalInsets[4];
    int32_t mOutlineInsets[4];
    float mOutlineRadius;
    uint8_t mOutlineAlpha;
};

} // namespace Graphics
} // namepsace Droid
} // namespace Elast

#endif //__ELASTOS_DROID_GRAPHICS_NINEPATCHPEEKER_H__
