#pragma once

#include <string>
#include <vector>
#ifdef _UNICODE 
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

class Buddy {
public:
	tstring RealName;
	tstring NickName;
	tstring Jid;
	tstring Group;
	tstring Subscription;
};

class IMEvent {
public:
	enum {
		kError,
		kBuddyUpdate,
		kMessageIn, 
		kConnected, 
		kDisconnected, 
		kPresence,
		kSync,
		kUserEvent
	};

	IMEvent() {};
	virtual ~IMEvent() {};
	int Type() {return type_;};
	void Type(int type) {type_ = type;};
private:
	int type_;
};

class IMEventMessage : public IMEvent {
public:
	IMEventMessage() {Type(kMessageIn);};
	virtual ~IMEventMessage() {};
	tstring MessageId;
	tstring From;
	tstring Domain;
	tstring Resource;
	tstring Subject;
	tstring MessageThread;
	tstring MessageText;
	tstring MessageHTML;
	tstring Other;
};

class IMEventSync : public IMEvent {
public:
	IMEventSync() {Type(kSync);};
	virtual ~IMEventSync() {};
	std::vector<Buddy> Buddies;
};

class IMEventPresence : public IMEvent {
public:
	enum {kOffline, kChat, kAway, kExtendedAway, kDoNotDisturb};
	IMEventPresence() {Type(kPresence);};
	virtual ~IMEventPresence() {};
	tstring User;  
	tstring Domain;  
	tstring Resource;  
	tstring Status;
	int Availability;  
};

class IMEventHandler {
public:
	IMEventHandler() {};
	virtual ~IMEventHandler() {};
	virtual bool Handler(IMEvent *event)  {return false;};
};

template<typename T>
class EventFactory {
public:
	static T* NEW() {
		return new T;
	}

	static void DEL(T* p) {
		delete p;
	}
private:
	EventFactory() {};
};

class IMProtocol {
public:
	IMProtocol() {};
	virtual ~IMProtocol() {};
	tstring Description(void) const {return desc_;};
	void Description(const tstring& desc) {desc_ = desc;};
	void EventHandler(IMEventHandler* handler) {handler_ = handler;};
	IMEventHandler* EventHandler(void) {return handler_;};
	virtual bool Logon(const tstring& jid, const tstring& password, const tstring& server, int port) = 0;
	virtual bool Logoff(void) = 0;
	virtual bool SendMessage(const tstring& msg, const tstring& jid) = 0;
	virtual bool SendFile(const tstring& file, const tstring jid) = 0;
private:
	tstring desc_;
	IMEventHandler* handler_;
};