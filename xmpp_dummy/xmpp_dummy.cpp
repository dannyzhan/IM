// xmpp_dummy.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "xmpp_dummy.h"

xmpp_dummy::xmpp_dummy() {

}

xmpp_dummy::~xmpp_dummy() {

}

bool xmpp_dummy::Logon(const tstring& jid, const tstring& password, const tstring& server, int port) {
	Buddy buddy;
	buddy.Group = "dummy";
	buddy.Jid = "dummy";
	IMEventSync* ev = new IMEventSync;
	ev->Buddies.push_back(buddy);
	Handler(ev);
	return true;
}

bool xmpp_dummy::Logoff() {
	return true;
}

bool xmpp_dummy::SendFile(const tstring& file, const tstring jid) {
	return false;
}

bool xmpp_dummy::SendMessage(const tstring& msg, const tstring& jid) {
	IMEventMessage* ev = new IMEventMessage;
	ev->Domain="dummy";
	ev->From = "dummy";
	ev->MessageText = "This is a dummy user chat to you";
	Handler(ev);
	return true;
}

bool xmpp_dummy::Handler(IMEvent* event) {
	if (EventHandler()) {
		return EventHandler()->Handler(event);
	}
	return IMEventHandler::Handler(event);
}