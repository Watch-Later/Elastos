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

#ifndef __ELASTOS_DROID_GRAPHICS_CREATEOUTPUTSTREAMADAPTOR_H__
#define __ELASTOS_DROID_GRAPHICS_CREATEOUTPUTSTREAMADAPTOR_H__

#include <Elastos.CoreLibrary.h>
#include <skia/core/SkStream.h>

using Elastos::IO::IInputStream;
using Elastos::IO::IOutputStream;

namespace Elastos {
namespace Droid {
namespace Graphics {

SkStream* CreateInputStreamAdaptor(
    /* [in] */ IInputStream* stream,
    /* [in] */ ArrayOf<Byte>* storage);

SkStreamRewindable* CopyElastosInputStream(
    /* [in] */ IInputStream* stream,
    /* [in] */ ArrayOf<Byte>* storage);

SkWStream* CreateOutputStreamAdaptor(
    /* [in] */ IOutputStream* stream,
    /* [in] */ ArrayOf<Byte>* storage);

} // namespace Graphics
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_GRAPHICS_CREATEOUTPUTSTREAMADAPTOR_H__
