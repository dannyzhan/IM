// xmpp_ip_works.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "xmpp_impl.h"
#include "xmpp_ip_works.h"

xmpp_impl::xmpp_impl() {
	xmpp_ = new xmpp_ip_works(this);
}

xmpp_impl::~xmpp_impl() {
	if (xmpp_) {
		delete xmpp_;
	}
}

bool xmpp_impl::Logon(const tstring& jid, const tstring& password, const tstring& server, int port) {
	bool ret = false;
	if (xmpp_) {
		if (xmpp_->SetAuthMethods("AuthIQ/Digest,SASL/PLAIN,AuthIQ/Plaintext") == 0 &&
			xmpp_->SetIMServer(server.c_str()) == 0 &&
			xmpp_->SetIMPort(port) == 0 &&
			xmpp_->Connect(jid.c_str(), password.c_str()) == 0 &&
			xmpp_->ChangePresence(1, "I'm here!") == 0) {
				ret = true;
		}
	}
	return ret;
}

bool xmpp_impl::Logoff() {
	bool ret = false;
	if (xmpp_) {
		xmpp_->Disconnect();
		ret = true;
	}
	return ret;
}

bool xmpp_impl::SendFile(const tstring& file, const tstring jid) {
	return false;
}

bool xmpp_impl::SendMessage(const tstring& msg, const tstring& jid) {
	bool ret = false;
	if (xmpp_) {
		xmpp_->SetMessageOtherData("");
		xmpp_->SetMessageText(msg.c_str());
		xmpp_->SetMessageHTML("");
		xmpp_->SendMessage(jid.c_str());
		ret = true;
	}
	return ret;
}

bool xmpp_impl::Handler(IMEvent* event) {
	if (EventHandler()) {
		return EventHandler()->Handler(event);
	}
	return IMEventHandler::Handler(event);
}