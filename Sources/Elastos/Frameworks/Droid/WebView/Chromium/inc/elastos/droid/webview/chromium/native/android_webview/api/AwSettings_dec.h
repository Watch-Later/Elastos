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
//    AwSettings.java
//put this file at the end of the include list
//so the type definition used in this file will be found
#ifndef ELASTOS_AWSETTINGS_CALLBACK_DEC_HH
#define ELASTOS_AWSETTINGS_CALLBACK_DEC_HH


#ifdef __cplusplus
extern "C"
{
#endif
    extern HANDLE Elastos_AwSettings_nativeInit(IInterface* caller,HANDLE webContentsPtr);
    extern String Elastos_AwSettings_nativeGetDefaultUserAgent();
    extern void Elastos_AwSettings_nativeDestroy(IInterface* caller,HANDLE nativeAwSettings);
    extern void Elastos_AwSettings_nativePopulateWebPreferencesLocked(IInterface* caller,HANDLE nativeAwSettings,HANDLE webPrefsPtr);
    extern void Elastos_AwSettings_nativeResetScrollAndScaleState(IInterface* caller,HANDLE nativeAwSettings);
    extern void Elastos_AwSettings_nativeUpdateEverythingLocked(IInterface* caller,HANDLE nativeAwSettings);
    extern void Elastos_AwSettings_nativeUpdateInitialPageScaleLocked(IInterface* caller,HANDLE nativeAwSettings);
    extern void Elastos_AwSettings_nativeUpdateUserAgentLocked(IInterface* caller,HANDLE nativeAwSettings);
    extern void Elastos_AwSettings_nativeUpdateWebkitPreferencesLocked(IInterface* caller,HANDLE nativeAwSettings);
    extern void Elastos_AwSettings_nativeUpdateFormDataPreferencesLocked(IInterface* caller,HANDLE nativeAwSettings);
    extern void Elastos_AwSettings_nativeUpdateRendererPreferencesLocked(IInterface* caller,HANDLE nativeAwSettings);
    extern void Elastos_AwSettings_InitCallback(HANDLE cb);
#ifdef __cplusplus
}
#endif


namespace Elastos {
namespace Droid {
namespace Webkit {
namespace Webview {
namespace Chromium {
namespace AndroidWebview {

struct ElaAwSettingsCallback
{
    void (*elastos_AwSettings_nativeAwSettingsGone)(IInterface* obj, HANDLE nativeAwSettings);
    Double (*elastos_AwSettings_getDIPScaleLocked)(IInterface* obj);
    Float (*elastos_AwSettings_getInitialPageScalePercentLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getSpatialNavigationLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getEnableSupportedHardwareAcceleratedFeaturesLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getFullscreenSupportedLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getSaveFormDataLocked)(IInterface* obj);
    String (*elastos_AwSettings_getUserAgentLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getLoadWithOverviewModeLocked)(IInterface* obj);
    Int32 (*elastos_AwSettings_getTextSizePercentLocked)(IInterface* obj);
    String (*elastos_AwSettings_getStandardFontFamilyLocked)(IInterface* obj);
    String (*elastos_AwSettings_getFixedFontFamilyLocked)(IInterface* obj);
    String (*elastos_AwSettings_getSansSerifFontFamilyLocked)(IInterface* obj);
    String (*elastos_AwSettings_getSerifFontFamilyLocked)(IInterface* obj);
    String (*elastos_AwSettings_getCursiveFontFamilyLocked)(IInterface* obj);
    String (*elastos_AwSettings_getFantasyFontFamilyLocked)(IInterface* obj);
    Int32 (*elastos_AwSettings_getMinimumFontSizeLocked)(IInterface* obj);
    Int32 (*elastos_AwSettings_getMinimumLogicalFontSizeLocked)(IInterface* obj);
    Int32 (*elastos_AwSettings_getDefaultFontSizeLocked)(IInterface* obj);
    Int32 (*elastos_AwSettings_getDefaultFixedFontSizeLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getLoadsImagesAutomaticallyLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getImagesEnabledLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getJavaScriptEnabledLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getAllowUniversalAccessFromFileURLsLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getAllowFileAccessFromFileURLsLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getPluginsDisabledLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getJavaScriptCanOpenWindowsAutomaticallyLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getTextAutosizingEnabledLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getSupportMultipleWindowsLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getSupportLegacyQuirksLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getUseWideViewportLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getZeroLayoutHeightDisablesViewportQuirkLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getForceZeroLayoutHeightLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getPasswordEchoEnabledLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getAppCacheEnabledLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getDomStorageEnabledLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getDatabaseEnabledLocked)(IInterface* obj);
    String (*elastos_AwSettings_getDefaultTextEncodingLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getMediaPlaybackRequiresUserGestureLocked)(IInterface* obj);
    String (*elastos_AwSettings_getDefaultVideoPosterURLLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getAllowRunningInsecureContentLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getAllowDisplayingInsecureContentLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_getVideoOverlayForEmbeddedVideoEnabledLocked)(IInterface* obj);
    Boolean (*elastos_AwSettings_supportsDoubleTapZoomLocked)(IInterface* obj);
    void (*elastos_AwSettings_updateEverything)(IInterface* obj);
    void (*elastos_AwSettings_populateWebPreferences)(IInterface* obj, HANDLE webPrefsPtr);
};

void* AwSettings::ElaAwSettingsCallback_Init()
{
    static ElaAwSettingsCallback sElaAwSettingsCallback;

    sElaAwSettingsCallback.elastos_AwSettings_nativeAwSettingsGone = &AwSettings::NativeAwSettingsGone;
    sElaAwSettingsCallback.elastos_AwSettings_getDIPScaleLocked = &AwSettings::GetDIPScaleLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getInitialPageScalePercentLocked = &AwSettings::GetInitialPageScalePercentLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getSpatialNavigationLocked = &AwSettings::GetSpatialNavigationLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getEnableSupportedHardwareAcceleratedFeaturesLocked = &AwSettings::GetEnableSupportedHardwareAcceleratedFeaturesLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getFullscreenSupportedLocked = &AwSettings::GetFullscreenSupportedLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getSaveFormDataLocked = &AwSettings::GetSaveFormDataLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getUserAgentLocked = &AwSettings::GetUserAgentLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getLoadWithOverviewModeLocked = &AwSettings::GetLoadWithOverviewModeLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getTextSizePercentLocked = &AwSettings::GetTextSizePercentLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getStandardFontFamilyLocked = &AwSettings::GetStandardFontFamilyLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getFixedFontFamilyLocked = &AwSettings::GetFixedFontFamilyLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getSansSerifFontFamilyLocked = &AwSettings::GetSansSerifFontFamilyLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getSerifFontFamilyLocked = &AwSettings::GetSerifFontFamilyLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getCursiveFontFamilyLocked = &AwSettings::GetCursiveFontFamilyLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getFantasyFontFamilyLocked = &AwSettings::GetFantasyFontFamilyLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getMinimumFontSizeLocked = &AwSettings::GetMinimumFontSizeLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getMinimumLogicalFontSizeLocked = &AwSettings::GetMinimumLogicalFontSizeLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getDefaultFontSizeLocked = &AwSettings::GetDefaultFontSizeLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getDefaultFixedFontSizeLocked = &AwSettings::GetDefaultFixedFontSizeLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getLoadsImagesAutomaticallyLocked = &AwSettings::GetLoadsImagesAutomaticallyLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getImagesEnabledLocked = &AwSettings::GetImagesEnabledLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getJavaScriptEnabledLocked = &AwSettings::GetJavaScriptEnabledLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getAllowUniversalAccessFromFileURLsLocked = &AwSettings::GetAllowUniversalAccessFromFileURLsLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getAllowFileAccessFromFileURLsLocked = &AwSettings::GetAllowFileAccessFromFileURLsLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getPluginsDisabledLocked = &AwSettings::GetPluginsDisabledLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getJavaScriptCanOpenWindowsAutomaticallyLocked = &AwSettings::GetJavaScriptCanOpenWindowsAutomaticallyLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getTextAutosizingEnabledLocked = &AwSettings::GetTextAutosizingEnabledLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getSupportMultipleWindowsLocked = &AwSettings::GetSupportMultipleWindowsLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getSupportLegacyQuirksLocked = &AwSettings::GetSupportLegacyQuirksLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getUseWideViewportLocked = &AwSettings::GetUseWideViewportLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getZeroLayoutHeightDisablesViewportQuirkLocked = &AwSettings::GetZeroLayoutHeightDisablesViewportQuirkLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getForceZeroLayoutHeightLocked = &AwSettings::GetForceZeroLayoutHeightLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getPasswordEchoEnabledLocked = &AwSettings::GetPasswordEchoEnabledLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getAppCacheEnabledLocked = &AwSettings::GetAppCacheEnabledLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getDomStorageEnabledLocked = &AwSettings::GetDomStorageEnabledLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getDatabaseEnabledLocked = &AwSettings::GetDatabaseEnabledLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getDefaultTextEncodingLocked = &AwSettings::GetDefaultTextEncodingLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getMediaPlaybackRequiresUserGestureLocked = &AwSettings::GetMediaPlaybackRequiresUserGestureLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getDefaultVideoPosterURLLocked = &AwSettings::GetDefaultVideoPosterURLLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getAllowRunningInsecureContentLocked = &AwSettings::GetAllowRunningInsecureContentLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getAllowDisplayingInsecureContentLocked = &AwSettings::GetAllowDisplayingInsecureContentLocked;
    sElaAwSettingsCallback.elastos_AwSettings_getVideoOverlayForEmbeddedVideoEnabledLocked = &AwSettings::GetVideoOverlayForEmbeddedVideoEnabledLocked;
    sElaAwSettingsCallback.elastos_AwSettings_supportsDoubleTapZoomLocked = &AwSettings::SupportsDoubleTapZoomLocked;
    sElaAwSettingsCallback.elastos_AwSettings_updateEverything = &AwSettings::UpdateEverything;
    sElaAwSettingsCallback.elastos_AwSettings_populateWebPreferences = &AwSettings::PopulateWebPreferences;

    Elastos_AwSettings_InitCallback((HANDLE)&sElaAwSettingsCallback);
    return &sElaAwSettingsCallback;
}

static void* sPElaAwSettingsCallback = AwSettings::ElaAwSettingsCallback_Init();

} // namespace AndroidWebview
} // namespace Chromium
} // namespace Webview
} // namespace Webkit
} // namespace Droid
} // namespace Elastos

#endif //ELASTOS_AWSETTINGS_CALLBACK_DEC_HH
