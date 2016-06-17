#ifndef  __ELASTOS_DROID_SERVICES_TELEPHONY_GSMCONFERENCECONTROLLER_H__
#define  __ELASTOS_DROID_SERVICES_TELEPHONY_GSMCONFERENCECONTROLLER_H__

#include "_Elastos.Droid.Server.Telephony.h"
#include "elastos/droid/ext/frameworkext.h"

namespace Elastos {
namespace Droid {
namespace Services {
namespace Telephony {

/**
 * Maintains a list of all the known GSM connections and implements GSM-specific conference
 * call functionality.
 */
class GsmConferenceController
    : public Object
{
private:
    class MyConnectionListener
        : public Object
        , public IConnectionListener
    {
    public:
        TO_STRING_IMPL("GsmConferenceController::MyConnectionListener");

        MyConnectionListener(
            /* [in] */ GsmConferenceController* host)
            : mHost(host)
        {}

        //@Override
        CARAPI OnStateChanged(
            /* [in] */ IConnection* c,
            /* [in] */ Int32 state);

        /** ${inheritDoc} */
        //@Override
        CARAPI OnDisconnected(
            /* [in] */ IConnection* c,
            /* [in] */ IDisconnectCause* disconnectCause);

        //@Override
        CARAPI OnDestroyed(
            /* [in] */ IConnection* connection);

    private:
        GsmConferenceController* mHost;
    };

public:
    TO_STRING_IMPL("GsmConferenceController")

    GsmConferenceController(
        /* [in] */ ITelephonyConnectionService* connectionService);

    CARAPI Add(
        /* [in] */ IGsmConnection* connection);

    CARAPI Remove(
        /* [in] */ IGsmConnection* connection);

private:
    CARAPI_(void) Recalculate();

    CARAPI_(Boolean) IsFullConference(
        /* [in] */ IConference* conference);

    CARAPI_(Boolean) ParticipatesInFullConference(
        /* [in] */ IConnection* connection);

    /**
     * Calculates the conference-capable state of all GSM connections in this connection service.
     */
    CARAPI_(void) RecalculateConferenceable();

    CARAPI_(void) RecalculateConference();

private:
    static const Int32 GSM_CONFERENCE_MAX_SIZE;

    AutoPtr<IConnectionListener> mConnectionListener;

    /** The known GSM connections. */
    AutoPtr<IList> mGsmConnections;

    AutoPtr<ITelephonyConnectionService> mConnectionService;

    /** The GSM conference connection object. */
    AutoPtr<IConference> mGsmConference;
};

} // namespace Telephony
} // namespace Services
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_SERVICES_TELEPHONY_GSMCONFERENCECONTROLLER_H__