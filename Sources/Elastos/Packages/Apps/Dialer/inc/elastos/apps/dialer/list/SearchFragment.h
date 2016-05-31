#ifndef __ELASTOS_APPS_DIALER_LIST_SEARCHFRAGMENT_H__
#define __ELASTOS_APPS_DIALER_LIST_SEARCHFRAGMENT_H__

#include "PhoneNumberPickerFragment.h"

namespace Elastos{
namespace Apps{
namespace Dialer {
namespace List {

class SearchFragment
    : public PhoneNumberPickerFragment
    , public ISearchFragment
{
private:
    class MyOnScrollListener
        : public Object
        , public IListViewOnScrollListener
    {
    public:
        CAR_INTERFACE_DECL()

        MyOnScrollListener(
            /* [in] */ SearchFragment* host);

        // @Override
        CARAPI OnScrollStateChanged(
            /* [in] */ IAbsListView* view,
            /* [in] */ Int32 scrollState);

        // @Override
        CARAPI OnScroll(
            /* [in] */ IAbsListView* view,
            /* [in] */ Int32 firstVisibleItem,
            /* [in] */ Int32 visibleItemCount,
            /* [in] */ Int32 totalItemCount);

    private:
        SearchFragment* mHost;
    };

public:
    CAR_INTERFACE_DECL()

    // @Override
    CARAPI OnAttach(
        /* [in] */ IActivity* activity);

    // @Override
    CARAPI OnStart();

    // @Override
    CARAPI OnViewCreated(
        /* [in] */ IView* view,
        /* [in] */ IBundle* savedInstanceState);

    CARAPI SetAddToContactNumber(
        /* [in] */ const String& addToContactNumber);

    /**
     * Updates the position and padding of the search fragment, depending on whether the dialpad is
     * shown. This can be optionally animated.
     * @param animate
     */
    CARAPI UpdatePosition(
        /* [in] */ Boolean animate);

protected:
    // @Override
    CARAPI SetSearchMode(
        /* [in] */ Boolean flag);

    // @Override
    CARAPI CreateListAdapter(
        /* [out] */ IContactEntryListAdapter** adapter);

    // @Override
    CARAPI OnItemClick(
        /* [in] */ Int32 position,
        /* [in] */ Int64 id);

private:
    AutoPtr<IOnListFragmentScrolledListener> mActivityScrollListener;

    /*
     * Stores the untouched user-entered string that is used to populate the add to contacts
     * intent.
     */
    String mAddToContactNumber;
    Int32 mActionBarHeight;
    Int32 mShadowHeight;
    Int32 mPaddingTop;
    Int32 mShowDialpadDuration;
    Int32 mHideDialpadDuration;

    AutoPtr<ISearchFragmentHostInterface> mActivity;
}

} // List
} // Dialer
} // Apps
} // Elastos

#endif //__ELASTOS_APPS_DIALER_LIST_SEARCHFRAGMENT_H__