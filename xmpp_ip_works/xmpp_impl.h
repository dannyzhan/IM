#pragma once

#include "IMProtocol.h"

class xmpp_ip_works;
class xmpp_impl : public IMProtocol, IMEventHandler {
public:
	xmpp_impl();
	virtual ~xmpp_impl();
	virtual bool Logon(const tstring& jid, const tstring& password, const tstring& server, int port);
	virtual bool Logoff(void);
	virtual bool SendMessage(const tstring& msg, const tstring& jid);
	virtual bool SendFile(const tstring& file, const tstring jid);
	virtual bool Handler(IMEvent* event);
private:
	xmpp_ip_works* xmpp_;
};