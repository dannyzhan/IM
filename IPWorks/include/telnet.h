/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_TELNET_H_
#define _IPWORKS_TELNET_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3


extern "C" void* IPWORKS_CALL IPWorks_Telnet_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_Telnet_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_Telnet_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_Telnet_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  int CommandCode;
  int reserved;
} TelnetCommandEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} TelnetConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} TelnetConnectionStatusEventParams;

typedef struct {
  const char* Text;
  int lenText;
  int reserved;
} TelnetDataInEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} TelnetDisconnectedEventParams;

typedef struct {
  int OptionCode;
  int reserved;
} TelnetDoEventParams;

typedef struct {
  int OptionCode;
  int reserved;
} TelnetDontEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} TelnetErrorEventParams;

typedef struct {
  int reserved;
} TelnetReadyToSendEventParams;

typedef struct {
  const char* SubOption;
  int lenSubOption;
  int reserved;
} TelnetSubOptionEventParams;

typedef struct {
  int OptionCode;
  int reserved;
} TelnetWillEventParams;

typedef struct {
  int OptionCode;
  int reserved;
} TelnetWontEventParams;



class Telnet {
  
  public: //events
  
    virtual int FireCommand(TelnetCommandEventParams *e) {return 0;}
    virtual int FireConnected(TelnetConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(TelnetConnectionStatusEventParams *e) {return 0;}
    virtual int FireDataIn(TelnetDataInEventParams *e) {return 0;}
    virtual int FireDisconnected(TelnetDisconnectedEventParams *e) {return 0;}
    virtual int FireDo(TelnetDoEventParams *e) {return 0;}
    virtual int FireDont(TelnetDontEventParams *e) {return 0;}
    virtual int FireError(TelnetErrorEventParams *e) {return 0;}
    virtual int FireReadyToSend(TelnetReadyToSendEventParams *e) {return 0;}
    virtual int FireSubOption(TelnetSubOptionEventParams *e) {return 0;}
    virtual int FireWill(TelnetWillEventParams *e) {return 0;}
    virtual int FireWont(TelnetWontEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL TelnetEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((Telnet*)lpObj)->TelnetEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            TelnetCommandEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((Telnet*)lpObj)->FireCommand(&e);
            break;
         }
         case 2: {
            TelnetConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((Telnet*)lpObj)->FireConnected(&e);
            break;
         }
         case 3: {
            TelnetConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((Telnet*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 4: {
            TelnetDataInEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((Telnet*)lpObj)->FireDataIn(&e);
            break;
         }
         case 5: {
            TelnetDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((Telnet*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 6: {
            TelnetDoEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((Telnet*)lpObj)->FireDo(&e);
            break;
         }
         case 7: {
            TelnetDontEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((Telnet*)lpObj)->FireDont(&e);
            break;
         }
         case 8: {
            TelnetErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((Telnet*)lpObj)->FireError(&e);
            break;
         }
         case 9: {
            TelnetReadyToSendEventParams e = { 0};
            ret_code = ((Telnet*)lpObj)->FireReadyToSend(&e);
            break;
         }
         case 10: {
            TelnetSubOptionEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((Telnet*)lpObj)->FireSubOption(&e);
            break;
         }
         case 11: {
            TelnetWillEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((Telnet*)lpObj)->FireWill(&e);
            break;
         }
         case 12: {
            TelnetWontEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((Telnet*)lpObj)->FireWont(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int TelnetEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    Telnet(char *lpOemKey = (char*)IPWORKS_OEMKEY_19) {
      m_pObj = IPWorks_Telnet_Create(TelnetEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~Telnet() {
      IPWorks_Telnet_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_Telnet_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_Telnet_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_Telnet_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline int GetAcceptData() {
      void* val = IPWorks_Telnet_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetAcceptData(int bAcceptData) {
      void* val = (void*)IPW64CAST(bAcceptData);
      return IPWorks_Telnet_Set(m_pObj, 1, 0, val, 0);
    }
    inline int GetBytesSent() {
      void* val = IPWorks_Telnet_Get(m_pObj, 2, 0, 0);
      return (int)(long)val;
    }


    inline int SetCommand(int iCommand) {
      void* val = (void*)IPW64CAST(iCommand);
      return IPWorks_Telnet_Set(m_pObj, 3, 0, val, 0);
    }
    inline int GetConnected() {
      void* val = IPWorks_Telnet_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_Telnet_Set(m_pObj, 4, 0, val, 0);
    }

    inline int SetDataToSend(const char *lpDataToSend, int lenDataToSend) {
      return IPWorks_Telnet_Set(m_pObj, 5, 0, (void*)lpDataToSend, lenDataToSend);
    }


    inline int SetDontOption(int iDontOption) {
      void* val = (void*)IPW64CAST(iDontOption);
      return IPWorks_Telnet_Set(m_pObj, 6, 0, val, 0);
    }

    inline int SetDoOption(int iDoOption) {
      void* val = (void*)IPW64CAST(iDoOption);
      return IPWorks_Telnet_Set(m_pObj, 7, 0, val, 0);
    }

    inline int SetDoSubOption(const char *lpDoSubOption, int lenDoSubOption) {
      return IPWorks_Telnet_Set(m_pObj, 8, 0, (void*)lpDoSubOption, lenDoSubOption);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_Telnet_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_Telnet_Set(m_pObj, 9, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_Telnet_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_Telnet_Set(m_pObj, 10, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_Telnet_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_Telnet_Set(m_pObj, 11, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_Telnet_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_Telnet_Set(m_pObj, 12, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_Telnet_Get(m_pObj, 13, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_Telnet_Set(m_pObj, 13, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_Telnet_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_Telnet_Set(m_pObj, 14, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetKeepAlive() {
      void* val = IPWorks_Telnet_Get(m_pObj, 15, 0, 0);
      return (int)(long)val;
    }
    inline int SetKeepAlive(int bKeepAlive) {
      void* val = (void*)IPW64CAST(bKeepAlive);
      return IPWorks_Telnet_Set(m_pObj, 15, 0, val, 0);
    }
    inline int GetLinger() {
      void* val = IPWorks_Telnet_Get(m_pObj, 16, 0, 0);
      return (int)(long)val;
    }
    inline int SetLinger(int bLinger) {
      void* val = (void*)IPW64CAST(bLinger);
      return IPWorks_Telnet_Set(m_pObj, 16, 0, val, 0);
    }
    inline char* GetLocalHost() {
      void* val = IPWorks_Telnet_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_Telnet_Set(m_pObj, 17, 0, (void*)lpLocalHost, 0);
    }

    inline int GetLocalPort() {
      void* val = IPWorks_Telnet_Get(m_pObj, 18, 0, 0);
      return (int)(long)val;
    }
    inline int SetLocalPort(int lLocalPort) {
      void* val = (void*)IPW64CAST(lLocalPort);
      return IPWorks_Telnet_Set(m_pObj, 18, 0, val, 0);
    }
    inline char* GetRemoteHost() {
      void* val = IPWorks_Telnet_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }

    inline int SetRemoteHost(const char *lpRemoteHost) {
      return IPWorks_Telnet_Set(m_pObj, 19, 0, (void*)lpRemoteHost, 0);
    }

    inline int GetRemotePort() {
      void* val = IPWorks_Telnet_Get(m_pObj, 20, 0, 0);
      return (int)(long)val;
    }
    inline int SetRemotePort(int lRemotePort) {
      void* val = (void*)IPW64CAST(lRemotePort);
      return IPWorks_Telnet_Set(m_pObj, 20, 0, val, 0);
    }
    inline int GetTimeout() {
      void* val = IPWorks_Telnet_Get(m_pObj, 21, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_Telnet_Set(m_pObj, 21, 0, val, 0);
    }
    inline int GetTransparent() {
      void* val = IPWorks_Telnet_Get(m_pObj, 22, 0, 0);
      return (int)(long)val;
    }
    inline int SetTransparent(int bTransparent) {
      void* val = (void*)IPW64CAST(bTransparent);
      return IPWorks_Telnet_Set(m_pObj, 22, 0, val, 0);
    }

    inline int SetUrgentData(const char *lpUrgentData, int lenUrgentData) {
      return IPWorks_Telnet_Set(m_pObj, 23, 0, (void*)lpUrgentData, lenUrgentData);
    }


    inline int SetWillOption(int iWillOption) {
      void* val = (void*)IPW64CAST(iWillOption);
      return IPWorks_Telnet_Set(m_pObj, 24, 0, val, 0);
    }

    inline int SetWontOption(int iWontOption) {
      void* val = (void*)IPW64CAST(iWontOption);
      return IPWorks_Telnet_Set(m_pObj, 25, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Telnet_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Connect(const char* lpszHost) {
      void *param[1+1] = {(void*)IPW64CAST(lpszHost), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Telnet_Do(m_pObj, 3, 1, param, cbparam);
      
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Telnet_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Telnet_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int Send(const char* lpText, int lenText) {
      void *param[1+1] = {(void*)IPW64CAST(lpText), 0};
      int cbparam[1+1] = {lenText, 0};
      return IPWorks_Telnet_Do(m_pObj, 6, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int CommandCode;
  int reserved;
} TelnetCommandEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} TelnetConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} TelnetConnectionStatusEventParamsW;

typedef struct {
  LPWSTR Text;
  int lenText;
  int reserved;
} TelnetDataInEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} TelnetDisconnectedEventParamsW;

typedef struct {
  int OptionCode;
  int reserved;
} TelnetDoEventParamsW;

typedef struct {
  int OptionCode;
  int reserved;
} TelnetDontEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} TelnetErrorEventParamsW;

typedef struct {
  int reserved;
} TelnetReadyToSendEventParamsW;

typedef struct {
  LPWSTR SubOption;
  int lenSubOption;
  int reserved;
} TelnetSubOptionEventParamsW;

typedef struct {
  int OptionCode;
  int reserved;
} TelnetWillEventParamsW;

typedef struct {
  int OptionCode;
  int reserved;
} TelnetWontEventParamsW;



class TelnetW : public Telnet {

  public: //properties
  










    inline int SetDataToSend(LPWSTR lpDataToSend) {
      return IPWorks_Telnet_Set(m_pObj, 10000+5, 0, (void*)lpDataToSend, 0);
    }

    inline int SetDataToSendB(const char *lpDataToSend, int lenDataToSend) {
      return IPWorks_Telnet_Set(m_pObj, 5, 0, (void*)lpDataToSend, lenDataToSend);
    }






    inline int SetDoSubOption(LPWSTR lpDoSubOption) {
      return IPWorks_Telnet_Set(m_pObj, 10000+8, 0, (void*)lpDoSubOption, 0);
    }

    inline int SetDoSubOptionB(const char *lpDoSubOption, int lenDoSubOption) {
      return IPWorks_Telnet_Set(m_pObj, 8, 0, (void*)lpDoSubOption, lenDoSubOption);
    }




    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_Telnet_Get(m_pObj, 10000+11, 0, 0);
    }

    inline int SetFirewallHost(LPWSTR lpFirewallHost) {
      return IPWorks_Telnet_Set(m_pObj, 10000+11, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_Telnet_Get(m_pObj, 10000+12, 0, 0);
    }

    inline int SetFirewallPassword(LPWSTR lpFirewallPassword) {
      return IPWorks_Telnet_Set(m_pObj, 10000+12, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_Telnet_Get(m_pObj, 10000+14, 0, 0);
    }

    inline int SetFirewallUser(LPWSTR lpFirewallUser) {
      return IPWorks_Telnet_Set(m_pObj, 10000+14, 0, (void*)lpFirewallUser, 0);
    }





    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_Telnet_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetLocalHost(LPWSTR lpLocalHost) {
      return IPWorks_Telnet_Set(m_pObj, 10000+17, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetRemoteHost() {
      return (LPWSTR)IPWorks_Telnet_Get(m_pObj, 10000+19, 0, 0);
    }

    inline int SetRemoteHost(LPWSTR lpRemoteHost) {
      return IPWorks_Telnet_Set(m_pObj, 10000+19, 0, (void*)lpRemoteHost, 0);
    }









    inline int SetUrgentData(LPWSTR lpUrgentData) {
      return IPWorks_Telnet_Set(m_pObj, 10000+23, 0, (void*)lpUrgentData, 0);
    }

    inline int SetUrgentDataB(const char *lpUrgentData, int lenUrgentData) {
      return IPWorks_Telnet_Set(m_pObj, 23, 0, (void*)lpUrgentData, lenUrgentData);
    }






  public: //events
  
    virtual int FireCommand(TelnetCommandEventParamsW *e) {return 0;}
    virtual int FireConnected(TelnetConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(TelnetConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDataIn(TelnetDataInEventParamsW *e) {return 0;}
    virtual int FireDisconnected(TelnetDisconnectedEventParamsW *e) {return 0;}
    virtual int FireDo(TelnetDoEventParamsW *e) {return 0;}
    virtual int FireDont(TelnetDontEventParamsW *e) {return 0;}
    virtual int FireError(TelnetErrorEventParamsW *e) {return 0;}
    virtual int FireReadyToSend(TelnetReadyToSendEventParamsW *e) {return 0;}
    virtual int FireSubOption(TelnetSubOptionEventParamsW *e) {return 0;}
    virtual int FireWill(TelnetWillEventParamsW *e) {return 0;}
    virtual int FireWont(TelnetWontEventParamsW *e) {return 0;}


  protected:
  
    virtual int TelnetEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            TelnetCommandEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireCommand(&e);
            break;
         }
         case 2: {
            TelnetConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 3: {
            TelnetConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 4: {
            TelnetDataInEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireDataIn(&e);
            break;
         }
         case 5: {
            TelnetDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 6: {
            TelnetDoEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireDo(&e);
            break;
         }
         case 7: {
            TelnetDontEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireDont(&e);
            break;
         }
         case 8: {
            TelnetErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 9: {
            TelnetReadyToSendEventParamsW e = { 0};
            ret_code = FireReadyToSend(&e);
            break;
         }
         case 10: {
            TelnetSubOptionEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireSubOption(&e);
            break;
         }
         case 11: {
            TelnetWillEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireWill(&e);
            break;
         }
         case 12: {
            TelnetWontEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireWont(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireCommand(TelnetCommandEventParams *e) {return -10000;}
    virtual int FireConnected(TelnetConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(TelnetConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDataIn(TelnetDataInEventParams *e) {return -10000;}
    virtual int FireDisconnected(TelnetDisconnectedEventParams *e) {return -10000;}
    virtual int FireDo(TelnetDoEventParams *e) {return -10000;}
    virtual int FireDont(TelnetDontEventParams *e) {return -10000;}
    virtual int FireError(TelnetErrorEventParams *e) {return -10000;}
    virtual int FireReadyToSend(TelnetReadyToSendEventParams *e) {return -10000;}
    virtual int FireSubOption(TelnetSubOptionEventParams *e) {return -10000;}
    virtual int FireWill(TelnetWillEventParams *e) {return -10000;}
    virtual int FireWont(TelnetWontEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_Telnet_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Connect(LPWSTR lpszHost) {
      void *param[1+1] = {(void*)lpszHost, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_Telnet_Do(m_pObj, 10000+3, 1, param, cbparam);
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Telnet_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_Telnet_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int Send(LPWSTR lpText, int lenText) {
      void *param[1+1] = {(void*)lpText, 0};
      int cbparam[1+1] = {lenText, 0};
      return IPWorks_Telnet_Do(m_pObj, 10000+6, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_TELNET_H_




