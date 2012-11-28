#include "stdafx.h"
#include "IMProtocol.h"
#include "xmpp_ip_works.h"

#pragma comment(lib, "ipworks9.lib")
xmpp_ip_works::xmpp_ip_works(IMEventHandler* handler) {
	handler_ = handler;
}

xmpp_ip_works::~xmpp_ip_works() {

}

int xmpp_ip_works::FirePresence(XMPPPresenceEventParams *e) {
	if (handler_) {
		IMEventPresence* ev = EventFactory<IMEventPresence>::NEW();
		ev->Availability = e->Availability;
		ev->Domain = e->Domain;
		ev->User = e->User;
		ev->Status = e->Status;
		ev->Resource = e->Resource;
		handler_->Handler(ev);
	}
	return 0;
}

int xmpp_ip_works::FireMessageIn(XMPPMessageInEventParams *e) {
	if (handler_) {
		IMEventMessage* ev = EventFactory<IMEventMessage>::NEW();
		ev->Domain = e->Domain;
		ev->From = e->From;
		ev->MessageHTML = e->MessageHTML;
		ev->MessageId = e->MessageId;
		ev->MessageText = e->MessageText;
		ev->MessageThread = e->MessageThread;
		ev->Other = e->Other;
		ev->Resource = e->Resource;
		handler_->Handler(ev);
	}
	return 0;
}

int xmpp_ip_works::FireSync(XMPPSyncEventParams *e) {
	if (handler_) {
		IMEventSync* ev = EventFactory<IMEventSync>::NEW();
		int count = GetBuddyCount();
		for (int i = 0; i < count; ++i) {
			Buddy buddy;
			buddy.Group = GetBuddyGroup(i);
			buddy.Jid = GetBuddyId(i);
			buddy.NickName = GetBuddyNickName(i);
			buddy.RealName = GetBuddyRealName(i);
			buddy.Subscription = GetBuddySubscription(i);
			ev->Buddies.push_back(buddy);
		}
		handler_->Handler(ev);
	}
	return 0;
}

int xmpp_ip_works::FirePITrail(XMPPPITrailEventParams *e) {
	return 0;
}