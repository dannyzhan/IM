#pragma once

#include <string>
#include <Swiften.h>

class CIMDlg; 
class XMPPMsgReactor
{
public:
    XMPPMsgReactor(std::string name, std::string password);
    ~XMPPMsgReactor(void);

    void operator()();

protected:
    void handleConnected();
    void handleDisConnected();
    void handlePresenceReceived(Swift::Presence::ref presence);

    void handleRosterReceived(Swift::ErrorPayload::ref error);
    void handleOnJIDAdded(const Swift::JID& jid); 

private:
    Swift::Client* m_pClient;
    Swift::SimpleEventLoop* m_pEventLoop;
    Swift::BoostNetworkFactories* m_pFactories;

    std::string m_username;
    std::string m_password;
};
