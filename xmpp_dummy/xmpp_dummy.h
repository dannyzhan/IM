#pragma once

#include "IMProtocol.h"

class xmpp_dummy : public IMProtocol, IMEventHandler {
public:
	xmpp_dummy();
	virtual ~xmpp_dummy();
	virtual bool Logon(const tstring& jid, const tstring& password, const tstring& server, int port);
	virtual bool Logoff(void);
	virtual bool SendMessage(const tstring& msg, const tstring& jid);
	virtual bool SendFile(const tstring& file, const tstring jid);
	virtual bool Handler(IMEvent* event);
};