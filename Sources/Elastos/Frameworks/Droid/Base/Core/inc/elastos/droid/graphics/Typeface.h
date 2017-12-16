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

#ifndef __ELASTOS_DROID_GRAPHICS_TYPEFACE_H__
#define __ELASTOS_DROID_GRAPHICS_TYPEFACE_H__

#include "Elastos.Droid.Graphics.h"
#include "elastos/droid/ext/frameworkext.h"
#include "elastos/droid/graphics/FontListParser.h"
#include <elastos/core/Object.h>
#include <elastos/utility/etl/HashMap.h>

using Elastos::Droid::Content::Res::IAssetManager;
using Elastos::IO::IFile;
using Elastos::Utility::IMap;
using Elastos::Utility::Etl::HashMap;

namespace Elastos {
namespace Droid {
namespace Graphics {

/**
 * The Typeface class specifies the typeface and intrinsic style of a font.
 * This is used in the paint, along with optionally Paint settings like
 * textSize, textSkewX, textScaleX to specify
 * how text appears when drawn (and measured).
 */
class Typeface
    : public Object
    , public ITypeface
{
private:
    class StaticInitializer
    {
    public:
        StaticInitializer();
    };

public:
    CAR_INTERFACE_DECL()

    // don't allow clients to call this directly
    CARAPI constructor(
        /* [in] */ Int64 ni);

    /** Returns the typeface's intrinsic style attributes */
    virtual CARAPI GetStyle(
        /* [out] */ Int32* style);

    /** Returns true if getStyle() has the BOLD bit set. */
    CARAPI IsBold(
        /* [out] */ Boolean* result);

    /** Returns true if getStyle() has the ITALIC bit set. */
    CARAPI IsItalic(
        /* [out] */ Boolean* result);

    // @Override
    virtual CARAPI Equals(
        /* [in] */ IInterface* o,
        /* [out] */ Boolean* e);

    // @Override
    virtual CARAPI GetHashCode(
        /* [out] */ Int32* code);

    /**
     * Create a typeface object given a family name, and option style information.
     * If null is passed for the name, then the "default" font will be chosen.
     * The resulting typeface object can be queried (getStyle()) to discover what
     * its "real" style characteristics are.
     *
     * @param familyName May be null. The name of the font family.
     * @param style  The style (normal, bold, italic) of the typeface.
     *               e.g. NORMAL, BOLD, ITALIC, BOLD_ITALIC
     * @return The best matching typeface.
     */
    static CARAPI Create(
        /* [in] */ const String& familyName,
        /* [in] */ Int32 style,
        /* [out] */ ITypeface** typeface);

    /**
     * Create a typeface object that best matches the specified existing
     * typeface and the specified Style. Use this call if you want to pick a new
     * style from the same family of an existing typeface object. If family is
     * null, this selects from the default font's family.
     *
     * @param family May be null. The name of the existing type face.
     * @param style  The style (normal, bold, italic) of the typeface.
     *               e.g. NORMAL, BOLD, ITALIC, BOLD_ITALIC
     * @return The best matching typeface.
     */
    static CARAPI Create(
        /* [in] */ ITypeface* family,
        /* [in] */ Int32 style,
        /* [out] */ ITypeface** typeface);

    /**
     * Returns one of the default typeface objects, based on the specified style
     *
     * @return the default typeface that corresponds to the style
     */
    static CARAPI DefaultFromStyle(
        /* [in] */ Int32 style,
        /* [out] */ ITypeface** typeface);

    /**
     * Create a new typeface from the specified font data.
     * @param mgr The application's asset manager
     * @param path  The file name of the font data in the assets directory
     * @return The new typeface.
     */
    static CARAPI CreateFromAsset(
        /* [in] */ IAssetManager* mgr,
        /* [in] */ const String& path,
        /* [out] */ ITypeface** typeface);

    /**
     * Create a new typeface from the specified font file.
     *
     * @param path The path to the font data.
     * @return The new typeface.
     */
    static CARAPI CreateFromFile(
        /* [in] */ IFile* path,
        /* [out] */ ITypeface** typeface);

    /**
     * Create a new typeface from the specified font file.
     *
     * @param path The full path to the font data.
     * @return The new typeface.
     */
    static CARAPI CreateFromFile(
        /* [in]*/ const String& path,
        /* [out] */ ITypeface** typeface);

    /**
     * Create a new typeface from an array of font families.
     *
     * @param families array of font families
     * @hide
     */
    static CARAPI CreateFromFamilies(
        /* [in]*/ ArrayOf<IFontFamily*>* families,
        /* [out]*/ ITypeface** typeface);

    /**
     * Create a new typeface from an array of font families, including
     * also the font families in the fallback list.
     *
     * @param families array of font families
     * @hide
     */
    static CARAPI CreateFromFamiliesWithDefault(
        /* [in]*/ ArrayOf<IFontFamily*>* families,
        /* [in] */ Int32 weight,
        /* [in] */ Int32 italic,
        /* [out]*/ ITypeface** typeface);

    /**
     * Clears caches in java and skia.
     * Skia will then reparse font config
     * @hide
     */
    static CARAPI_(void) RecreateDefaults();

protected:
    Typeface();

    virtual ~Typeface();

private:
    static CARAPI_(void) SetDefault(
        /* [in] */ ITypeface* t);

    static CARAPI_(Int64) NativeCreateFromTypeface(
        /* [in] */ Int64 native_instance,
        /* [in] */ Int32 style);

    static CARAPI_(Int64) NativeCreateWeightAlias(
        /* [in] */ Int64 native_instance,
        /* [in] */ Int32 weight);

    static CARAPI_(void) NativeUnref(
        /* [in] */ Int64 native_instance);

    static CARAPI_(Int32) NativeGetStyle(
        /* [in] */ Int64 native_instance);

    static CARAPI_(Int64) NativeCreateFromArray(
        /* [in] */ ArrayOf<Int64>* familyArray,
        /* [in] */ Int32 weight,
        /* [in] */ Int32 italic);

    static CARAPI_(void) NativeSetDefault(
        /* [in] */ Int64 native_instance);

    static CARAPI_(AutoPtr<IFontFamily>) MakeFamilyFromParsed(
        /* [in] */ FontListParser::Family* family,
        /* [in] */ IMap* bufferForPath);

    /**
     * Adds the family from src with the name familyName as a fallback font in dst
     * @param src Source font config
     * @param dst Destination font config
     * @param familyName Name of family to add as a fallback
     */
    static CARAPI_(void) AddFallbackFontsForFamilyName(
        /* [in] */ FontListParser::Config* src,
        /* [in] */ FontListParser::Config* dst,
        /* [in] */ const String& familyName);

    /**
     * Adds any font families in src that do not exist in dst
     * @param src Source font config
     * @param dst Destination font config
     */
    static CARAPI_(void) AddMissingFontFamilies(
        /* [in] */ FontListParser::Config* src,
        /* [in] */ FontListParser::Config* dst);

    /**
     * Adds any aliases in src that do not exist in dst
     * @param src Source font config
     * @param dst Destination font config
     */
    static CARAPI_(void) AddMissingFontAliases(
        /* [in] */ FontListParser::Config* src,
        /* [in] */ FontListParser::Config* dst);

    /*
     * (non-Javadoc)
     *
     * This should only be called once, from the static class initializer block.
     */
    static CARAPI_(void) Init();

    static CARAPI_(AutoPtr<IFile>) GetSystemFontConfigLocation();

    static CARAPI_(AutoPtr<IFile>) GetSystemFontDirLocation();

    static CARAPI_(AutoPtr<IFile>) GetThemeFontConfigLocation();

    static CARAPI_(AutoPtr<IFile>) GetThemeFontDirLocation();

public:
    static const String TAG;

    /** The default NORMAL typeface object */
    static AutoPtr<ITypeface> DEFAULT;
    /**
     * The default BOLD typeface object. Note: this may be not actually be
     * bold, depending on what fonts are installed. Call getStyle() to know
     * for sure.
     */
    static AutoPtr<ITypeface> DEFAULT_BOLD;
    /** The NORMAL style of the default sans serif typeface. */
    static AutoPtr<ITypeface> SANS_SERIF;
    /** The NORMAL style of the default serif typeface. */
    static AutoPtr<ITypeface> SERIF;
    /** The NORMAL style of the default monospace typeface. */
    static AutoPtr<ITypeface> MONOSPACE;

    static AutoPtr< ArrayOf<ITypeface*> > sDefaults;

    typedef HashMap<Int64, AutoPtr<ITypeface> > TypefaceMap;
    typedef HashMap<Int64, AutoPtr<TypefaceMap> > TypefaceCacheMap;
    static TypefaceCacheMap sTypefaceCache;

    static AutoPtr<ITypeface> sDefaultTypeface;
    static HashMap<String, AutoPtr<ITypeface> > sSystemFontMap;
    static AutoPtr<ArrayOf<IFontFamily*> > sFallbackFonts;

    static const String FONTS_CONFIG;

    static const String SANS_SERIF_FAMILY_NAME;

    /* package */
    Int64 mNativeInstance;

private:
    Int32 mStyle;

    // Style value for building typeface.
    static const Int32 STYLE_NORMAL = 0;
    static const Int32 STYLE_ITALIC = 1;

    // Typefaces that we can garbage collect when changing fonts, and so we don't break public APIs
    static AutoPtr<ITypeface> DEFAULT_INTERNAL;
    static AutoPtr<ITypeface> DEFAULT_BOLD_INTERNAL;
    static AutoPtr<ITypeface> SANS_SERIF_INTERNAL;
    static AutoPtr<ITypeface> SERIF_INTERNAL;
    static AutoPtr<ITypeface> MONOSPACE_INTERNAL;

    static const StaticInitializer sInitializer;

    Boolean mShouldUnref;
};

} // namespace Graphics
} // namepsace Droid
} // namespace Elastos

#endif //__ELASTOS_DROID_GRAPHICS_TYPEFACE_H__
