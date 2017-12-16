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

#ifndef __ELASTOS_DROID_GRAPHICS_CCOMPOSESHADER_H__
#define __ELASTOS_DROID_GRAPHICS_CCOMPOSESHADER_H__

#include "_Elastos_Droid_Graphics_CComposeShader.h"
#include "elastos/droid/graphics/Shader.h"

namespace Elastos {
namespace Droid {
namespace Graphics {

CarClass(CComposeShader)
    , public Shader
    , public IComposeShader
{
public:
    CAR_OBJECT_DECL()

    CAR_INTERFACE_DECL()

    CComposeShader();

    /**
     * Create a new compose shader, given shaders A, B, and a combining mode.
     * When the mode is applied, it will be given the result from shader A as its
     * "dst", and the result from shader B as its "src".
     *
     * @param shaderA  The colors from this shader are seen as the "dst" by the mode
     * @param shaderB  The colors from this shader are seen as the "src" by the mode
     * @param mode     The mode that combines the colors from the two shaders. If mode
     *                 is null, then SRC_OVER is assumed.
     */
    CARAPI constructor(
        /* [in] */ IShader* shaderA,
        /* [in] */ IShader* shaderB,
        /* [in] */ IXfermode* mode);

    /**
     * Create a new compose shader, given shaders A, B, and a combining PorterDuff mode.
     * When the mode is applied, it will be given the result from shader A as its
     * "dst", and the result from shader B as its "src".
     *
     * @param shaderA  The colors from this shader are seen as the "dst" by the mode
     * @param shaderB  The colors from this shader are seen as the "src" by the mode
     * @param mode     The PorterDuff mode that combines the colors from the two shaders.
     */
    CARAPI constructor(
        /* [in] */ IShader* shaderA,
        /* [in] */ IShader* shaderB,
        /* [in] */ PorterDuffMode mode);

protected:
    /**
     * @hide
     */
    // @Override
    CARAPI Copy(
        /* [out] */ IShader** shader);

    // @Override
    CARAPI_(Int64) CreateNativeInstance(
        /* [in] */ IMatrix* matrix);

private:
    static CARAPI_(Int64) NativeCreate(
        /* [in] */ Int64 nativeMatrix,
        /* [in] */ Int64 nativeShaderA,
        /* [in] */ Int64 nativeShaderB,
        /* [in] */ Int64 nativeMode);

private:
    PorterDuffMode mPorterDuffMode;

    /**
     * Hold onto the shaders to avoid GC.
     */
    AutoPtr<IShader> mShaderA;

    AutoPtr<IShader> mShaderB;
};

} // namespace Graphics
} // namepsace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_GRAPHICS_CCOMPOSESHADER_H__
