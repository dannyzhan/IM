#include "StdAfx.h"
#include "MsgReactor.h"

#include <boost/bind.hpp>

#include "Event.h"

using namespace Swift;
using namespace boost;

XMPPMsgReactor::XMPPMsgReactor(std::string name, std::string password)
: m_username(name), m_password(password), m_pClient(NULL), m_pEventLoop(NULL), m_pFactories(NULL)
{
}

XMPPMsgReactor::~XMPPMsgReactor(void)
{
    if (m_pEventLoop != NULL)
        delete m_pEventLoop;
    if (m_pFactories != NULL)
        delete m_pFactories;
    if (m_pClient)
        delete m_pClient;
    m_pEventLoop = NULL;
    m_pFactories = NULL;
    m_pClient = NULL;
}

void XMPPMsgReactor::handleDisConnected()
{
    if (m_pEventLoop != NULL)
    {
        m_pEventLoop->stop();
    }
    
    AfxGetApp()->PostThreadMessage(EVT_DISCONNECTED, 0, 0);
}

void XMPPMsgReactor::handleConnected()
{
    // Request the roster
    GetRosterRequest::ref rosterRequest = GetRosterRequest::create(m_pClient->getIQRouter());
    rosterRequest->onResponse.connect(bind(&XMPPMsgReactor::handleRosterReceived, this, _2));
    m_pClient->getRoster()->onJIDAdded.connect(boost::bind(&XMPPMsgReactor::handleOnJIDAdded, this, _1));
    rosterRequest->send();
    m_pClient->requestRoster();

    AfxGetApp()->PostThreadMessage(EVT_CONNECTED, 0, 0);
}

void XMPPMsgReactor::handleRosterReceived(ErrorPayload::ref error) {
    // Send initial available presence
    m_pClient->sendPresence(Presence::create("Send me a message"));
}

void XMPPMsgReactor::handlePresenceReceived(Presence::ref presence) {
    // Automatically approve subscription requests
    if (presence->getType() == Presence::Subscribe) {
        Presence::ref response = Presence::create();
        response->setTo(presence->getFrom());
        response->setType(Presence::Subscribed);
        m_pClient->sendPresence(response);
    }
}

void XMPPMsgReactor::handleOnJIDAdded(const JID& jid) {
    std::vector<std::string> groups = m_pClient->getRoster()->getGroupsForJID(jid); // TDO: handle group
    std::string name = m_pClient->getNickResolver()->jidToNick(jid);

    AfxGetApp()->PostThreadMessage(EVT_ROSTER_ADD_JID, (WPARAM)&jid, (LPARAM)&name);
    boost::this_thread::sleep(boost::posix_time::milliseconds(50));
}

void XMPPMsgReactor::operator()()
{
    m_pEventLoop = new SimpleEventLoop();
    m_pFactories = new BoostNetworkFactories(m_pEventLoop);

    m_pClient = new Client(m_username, m_password, m_pFactories);
    m_pClient->setAlwaysTrustCertificates();
    m_pClient->onConnected.connect(bind(&XMPPMsgReactor::handleConnected, this));
    m_pClient->onDisconnected.connect(bind(&XMPPMsgReactor::handleDisConnected, this));
    m_pClient->onPresenceReceived.connect(bind(&XMPPMsgReactor::handlePresenceReceived, this, _1));

    m_pClient->connect();

    m_pEventLoop->run();
}