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

#ifndef __ELASTOS_DROID_SETTINGS_APPLICATIONS_APPLICATIONSSTATE_H__
#define __ELASTOS_DROID_SETTINGS_APPLICATIONS_APPLICATIONSSTATE_H__

#include "Elastos.Droid.App.h"
#include "Elastos.Droid.Graphics.h"
#include "Elastos.CoreLibrary.IO.h"
#include "Elastos.CoreLibrary.Text.h"
#include "Elastos.CoreLibrary.Utility.h"
#include "elastos/droid/settings/applications/InterestingConfigChanges.h"
#include "elastos/droid/content/BroadcastReceiver.h"
#include "elastos/droid/os/Handler.h"
#include "_Elastos.Droid.Settings.h"

using Elastos::Droid::App::IApplication;
using Elastos::Droid::Content::BroadcastReceiver;
using Elastos::Droid::Content::IContext;
using Elastos::Droid::Content::IIntent;
using Elastos::Droid::Content::Pm::IApplicationInfo;
using Elastos::Droid::Content::Pm::IIPackageStatsObserver;
using Elastos::Droid::Content::Pm::IPackageManager;
using Elastos::Droid::Content::Pm::IIPackageManager;
using Elastos::Droid::Content::Pm::IPackageStats;
using Elastos::Droid::Graphics::Drawable::IDrawable;
using Elastos::Droid::Os::Handler;
using Elastos::Droid::Os::ILooper;
using Elastos::Droid::Os::IMessage;
using Elastos::Droid::Os::IHandlerThread;
using Elastos::IO::IFile;
using Elastos::Core::IComparator;
using Elastos::Text::ICollator;
using Elastos::Utility::IArrayList;
using Elastos::Utility::IHashMap;
using Elastos::Utility::IList;
using Elastos::Utility::Regex::IPattern;

namespace Elastos {
namespace Droid {
namespace Settings {
namespace Applications {

class CanBeOnSdCardChecker
    : public Object
{
public:
    TO_STRING_IMPL("CanBeOnSdCardChecker")

    CanBeOnSdCardChecker();

    virtual CARAPI_(void) Init();

    virtual CARAPI_(Boolean) Check(
        /* [in] */ IApplicationInfo* info);

public:
    AutoPtr<IIPackageManager> mPm;
    Int32 mInstallLocation;
};

/**
 * Keeps track of information about all installed applications, lazy-loading
 * as needed.
 */
class ApplicationsState
    : public Object
    , public IApplicationsState
{
    friend class AppViewHolder;
    friend class CInstalledAppDetails;
    friend class ManageApplications;
public:
    class SizeInfo
        : public Object
    {
    public:
        SizeInfo();

        virtual ~SizeInfo();

        TO_STRING_IMPL("ApplicationsState::SizeInfo")

    public:
        Int64 mCacheSize;
        Int64 mCodeSize;
        Int64 mDataSize;
        Int64 mExternalCodeSize;
        Int64 mExternalDataSize;

        // This is the part of externalDataSize that is in the cache
        // section of external storage.  Note that we don't just combine
        // this with cacheSize because currently the platform can't
        // automatically trim this data when needed, so it is something
        // the user may need to manage.  The externalDataSize also includes
        // this value, since what this is here is really the part of
        // externalDataSize that we can just consider to be "cache" files
        // for purposes of cleaning them up in the app details UI.
        Int64 mExternalCacheSize;
    };

    class AppEntry
        : public SizeInfo
        , public IApplicationsStateAppEntry
    {
    public:
        CAR_INTERFACE_DECL()

        TO_STRING_IMPL("ApplicationsState::AppEntry")

        AppEntry(
            /* [in] */ IContext* context,
            /* [in] */ IApplicationInfo* info,
            /* [in] */ Int64 id);

        virtual ~AppEntry();

        virtual CARAPI_(void) EnsureLabel(
            /* [in] */ IContext* context);

        virtual CARAPI_(Boolean) EnsureIconLocked(
            /* [in] */ IContext* context,
            /* [in] */ IPackageManager* pm);

        virtual CARAPI_(String) GetNormalizedLabel();

    public:
        AutoPtr<IFile> mApkFile;
        Int64 mId;
        String mLabel;
        Int64 mSize;
        Int64 mInternalSize;
        Int64 mExternalSize;

        Boolean mMounted;

        // Need to synchronize on 'this' for the following.
        AutoPtr<IApplicationInfo> mInfo;
        AutoPtr<IDrawable> mIcon;
        String mSizeStr;
        String mInternalSizeStr;
        String mExternalSizeStr;
        Boolean mSizeStale;
        Int64 mSizeLoadStart;

        String mNormalizedLabel;
    };

    class InitComparator
        : public Object
        , public IComparator
    {
    public:
        CAR_INTERFACE_DECL()

        TO_STRING_IMPL("ApplicationsState::InitComparator")

        InitComparator(
            /* [in] */ Int32 id);

        ~InitComparator();

        //@Override
        CARAPI Compare(
            /* [in] */ IInterface* lhs,
            /* [in] */ IInterface* rhs,
            /* [out] */ Int32* result);

    private:
        AutoPtr<ICollator> sCollator;
        Int32 mId;
    };

    class InitAppFilter
        : public Object
        , public IApplicationsStateAppFilter
    {
    public:
        CAR_INTERFACE_DECL()

        TO_STRING_IMPL("ApplicationsState::InitAppFilter")

        InitAppFilter(
            /* [in] */ Int32 id);

        ~InitAppFilter();

        //@Override
        CARAPI Init();

        //@Override
        CARAPI FilterApp(
            /* [in] */ IApplicationInfo* info,
            /* [out] */ Boolean* result);

    private:
        Int32 mId;
    };

    class InitAppFilter1
        : public Object
        , public IApplicationsStateAppFilter
    {
    public:
        CAR_INTERFACE_DECL()

        TO_STRING_IMPL("ApplicationsState::InitAppFilter1")

        InitAppFilter1();

        ~InitAppFilter1();

        //@Override
        CARAPI Init();

        //@Override
        CARAPI FilterApp(
            /* [in] */ IApplicationInfo* info,
            /* [out] */ Boolean* result);

    protected:
        AutoPtr<CanBeOnSdCardChecker> mCanBeOnSdCardChecker;
    };

    class Session
        : public Object
    {
    public:
        TO_STRING_IMPL("ApplicationsState::Session")

        Session(
            /* [in] */ IApplicationsStateCallbacks* callbacks,
            /* [in] */ ApplicationsState* host);

        virtual CARAPI Resume();

        virtual CARAPI Pause();

        virtual CARAPI ReleaseItem();

        CARAPI_(void) HandleRebuildList();

        // Creates a new list of app entries with the given filter and comparator.
        virtual CARAPI_(AutoPtr<IArrayList>) Rebuild(
            /* [in] */ IApplicationsStateAppFilter* filter,
            /* [in] */ IComparator* comparator);

    public:
        AutoPtr<IApplicationsStateCallbacks> mCallbacks;
        Boolean mResumed;
        AutoPtr<IArrayList>/*ArrayList<AppEntry>*/ mLastAppList;

    protected:

        // Rebuilding of app list.  Synchronized on mRebuildSync.
        AutoPtr<Object> mRebuildSync;
        Boolean mRebuildRequested;
        Boolean mRebuildAsync;
        AutoPtr<IApplicationsStateAppFilter> mRebuildFilter;
        AutoPtr<IComparator>/*Comparator<AppEntry>*/ mRebuildComparator;
        AutoPtr<IArrayList>/*ArrayList<AppEntry>*/ mRebuildResult;

    private:
        ApplicationsState* mHost;
    };

    class BackgroundHandler
        : public Handler
    {
    public:
        TO_STRING_IMPL("ApplicationsState::BackgroundHandler")

        BackgroundHandler(
            /* [in] */ ApplicationsState* host);

        CARAPI constructor(
            /* [in] */ ILooper* looper);

        //@Override
        CARAPI HandleMessage(
            /* [in] */ IMessage* msg);

    public:
        static const Int32 MSG_REBUILD_LIST = 1;
        static const Int32 MSG_LOAD_ENTRIES = 2;
        static const Int32 MSG_LOAD_ICONS = 3;
        static const Int32 MSG_LOAD_SIZES = 4;

        Boolean mRunning;

        AutoPtr<IIPackageStatsObserver> mStatsObserver;

    private:
        ApplicationsState* mHost;
    };

    class ApplicationsStatePackageStatsObserver
        : public Object
        , public IIPackageStatsObserver
        , public IBinder
    {
    public:
        CAR_INTERFACE_DECL()

        TO_STRING_IMPL("ApplicationsState::ApplicationsStatePackageStatsObserver")

        ApplicationsStatePackageStatsObserver();

        CARAPI constructor(
            /* [in] */ IApplicationsState* host,
            /* [in] */ IHandler* owner);

        ~ApplicationsStatePackageStatsObserver();

        CARAPI OnGetStatsCompleted(
            /* [in] */ IPackageStats* stats,
            /* [in] */ Boolean succeeded);

    private:
        ApplicationsState* mHost;
        BackgroundHandler* mOwner;
    };

protected:
    class MainHandler
        : public Handler
    {
    public:
        TO_STRING_IMPL("ApplicationsState::MainHandler")

        MainHandler(
            /* [in] */ ApplicationsState* host);

        ~MainHandler();

        //@Override
        CARAPI HandleMessage(
            /* [in] */ IMessage* msg);

    public:
        static const Int32 MSG_REBUILD_COMPLETE = 1;
        static const Int32 MSG_PACKAGE_LIST_CHANGED = 2;
        static const Int32 MSG_PACKAGE_ICON_CHANGED = 3;
        static const Int32 MSG_PACKAGE_SIZE_CHANGED = 4;
        static const Int32 MSG_ALL_SIZES_COMPUTED = 5;
        static const Int32 MSG_RUNNING_STATE_CHANGED = 6;

    private:
        ApplicationsState* mHost;
    };

private:
    /**
     * Receives notifications when applications are added/removed.
     */
    class PackageIntentReceiver
        : public BroadcastReceiver
    {
    public:
        TO_STRING_IMPL("ApplicationsState::PackageIntentReceiver")

        PackageIntentReceiver(
            /* [in] */ ApplicationsState* host);

        ~PackageIntentReceiver();

        //@Override
        CARAPI OnReceive(
            /* [in] */ IContext* context,
            /* [in] */ IIntent* intent);

        virtual CARAPI_(void) RegisterReceiver();

        virtual CARAPI_(void) UnregisterReceiver();

    private:
        ApplicationsState* mHost;
    };

public:
    CAR_INTERFACE_DECL();

    TO_STRING_IMPL("ApplicationsState")

    static CARAPI_(String) Normalize(
        /* [in] */ const String& str);

    virtual CARAPI_(AutoPtr<Session>) NewSession(
        /* [in] */ IApplicationsStateCallbacks* callbacks);

    virtual CARAPI_(Boolean) HaveDisabledApps();

protected:
    virtual CARAPI_(void) RebuildActiveSessions();

    static CARAPI_(AutoPtr<ApplicationsState>) GetInstance(
        /* [in] */ IApplication* app);

    virtual CARAPI_(void) DoResumeIfNeededLocked();

    virtual CARAPI_(void) DoPauseIfNeededLocked();

    virtual CARAPI_(AutoPtr<AppEntry>) GetEntry(
        /* [in] */ const String& packageName);

    virtual CARAPI_(void) EnsureIcon(
        /* [in] */ AppEntry* entry);

    virtual CARAPI_(void) RequestSize(
        /* [in] */ const String& packageName);

    virtual CARAPI_(Int64) SumCacheSizes();

    virtual CARAPI_(Int32) IndexOfApplicationInfoLocked(
        /* [in] */ const String& pkgName);

    virtual CARAPI_(void) AddPackage(
        /* [in] */ const String& pkgName);

    virtual CARAPI_(void) RemovePackage(
        /* [in] */ const String& pkgName);

    virtual CARAPI_(void) InvalidatePackage(
        /* [in] */ const String& pkgName);

    virtual CARAPI_(AutoPtr<AppEntry>) GetEntryLocked(
        /* [in] */ IApplicationInfo* info);

private:
    ApplicationsState(
        /* [in] */ IApplication* app);

    CARAPI_(Int64) GetTotalInternalSize(
        /* [in] */ IPackageStats* ps);

    CARAPI_(Int64) GetTotalExternalSize(
        /* [in] */ IPackageStats* ps);

    CARAPI_(String) GetSizeStr(
        /* [in] */ Int64 size);

public:
    static const AutoPtr<IComparator> ALPHA_COMPARATOR;

    static const AutoPtr<IComparator> SIZE_COMPARATOR;

    static const AutoPtr<IComparator> INTERNAL_SIZE_COMPARATOR;

    static const AutoPtr<IComparator> EXTERNAL_SIZE_COMPARATOR;

    static const AutoPtr<IApplicationsStateAppFilter> THIRD_PARTY_FILTER;

    static const AutoPtr<IApplicationsStateAppFilter> ON_SD_CARD_FILTER;

    static const AutoPtr<IApplicationsStateAppFilter> DISABLED_FILTER;

    static const AutoPtr<IApplicationsStateAppFilter> ALL_ENABLED_FILTER;

protected:
    static const String TAG;
    static const Boolean DEBUG;
    static const Boolean DEBUG_LOCKING;

    static const Int32 SIZE_UNKNOWN;
    static const Int32 SIZE_INVALID;

    static const AutoPtr<IPattern> REMOVE_DIACRITICALS_PATTERN;

    static AutoPtr<Object> sLock;
    static AutoPtr<ApplicationsState> sInstance;

    AutoPtr<IContext> mContext;
    AutoPtr<IPackageManager> mPm;
    Int32 mRetrieveFlags;
    AutoPtr<PackageIntentReceiver> mPackageIntentReceiver;

    Boolean mResumed;
    Boolean mHaveDisabledApps;

    // Information about all applications.  Synchronize on mEntriesMap
    // to protect access to these.
    AutoPtr<IArrayList> /*ArrayList<Session>*/ mSessions;
    AutoPtr<IArrayList> /*ArrayList<Session>*/ mRebuildingSessions;
    AutoPtr<InterestingConfigChanges> mInterestingConfigChanges;
    AutoPtr<IHashMap> /*HashMap<String, AppEntry>*/ mEntriesMap;
    AutoPtr<IArrayList> /*ArrayList<AppEntry>*/ mAppEntries;
    AutoPtr<IList> /*List<ApplicationInfo>*/ mApplications;
    Int64 mCurId;// = 1;
    String mCurComputingSizePkg;
    Boolean mSessionsChanged;

    // Temporary for dispatching session callbacks.  Only touched by main thread.
    AutoPtr<IArrayList> /*ArrayList<Session>*/ mActiveSessions;

    AutoPtr<MainHandler> mMainHandler;

    AutoPtr<IHandlerThread> mThread;
    AutoPtr<BackgroundHandler> mBackgroundHandler;
};

} // namespace Applications
} // namespace Settings
} // namespace Droid
} // namespace Elastos

#endif //__ELASTOS_DROID_SETTINGS_APPLICATIONS_APPLICATIONSSTATE_H__