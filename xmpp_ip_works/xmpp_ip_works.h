#pragma once

#include "xmpp.h"

class IMEventHandler;
class xmpp_ip_works : public XMPP {
public:
	xmpp_ip_works(IMEventHandler* handler);
	virtual ~xmpp_ip_works();
	virtual int FirePresence(XMPPPresenceEventParams *e);
	virtual int FireMessageIn(XMPPMessageInEventParams *e);
	virtual int FireSync(XMPPSyncEventParams *e);
	virtual int FirePITrail(XMPPPITrailEventParams *e);
private:
	IMEventHandler* handler_;
};