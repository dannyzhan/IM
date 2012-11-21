/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_IPPORT_H_
#define _IPWORKS_IPPORT_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3


extern "C" void* IPWORKS_CALL IPWorks_IPPort_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_IPPort_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPPort_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_IPPort_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_IPPort_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_IPPort_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_IPPort_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPPort_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPPort_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_IPPort_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} IPPortConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} IPPortConnectionStatusEventParams;

typedef struct {
  const char* Text;
  int EOL;
  int lenText;
  int reserved;
} IPPortDataInEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} IPPortDisconnectedEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} IPPortErrorEventParams;

typedef struct {
  int reserved;
} IPPortReadyToSendEventParams;



class IPPort {
  
  public: //events
  
    virtual int FireConnected(IPPortConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(IPPortConnectionStatusEventParams *e) {return 0;}
    virtual int FireDataIn(IPPortDataInEventParams *e) {return 0;}
    virtual int FireDisconnected(IPPortDisconnectedEventParams *e) {return 0;}
    virtual int FireError(IPPortErrorEventParams *e) {return 0;}
    virtual int FireReadyToSend(IPPortReadyToSendEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL IPPortEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((IPPort*)lpObj)->IPPortEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            IPPortConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((IPPort*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            IPPortConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((IPPort*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 3: {
            IPPortDataInEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((IPPort*)lpObj)->FireDataIn(&e);
            break;
         }
         case 4: {
            IPPortDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((IPPort*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 5: {
            IPPortErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((IPPort*)lpObj)->FireError(&e);
            break;
         }
         case 6: {
            IPPortReadyToSendEventParams e = { 0};
            ret_code = ((IPPort*)lpObj)->FireReadyToSend(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int IPPortEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    IPPort(char *lpOemKey = (char*)IPWORKS_OEMKEY_11) {
      m_pObj = IPWorks_IPPort_Create(IPPortEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~IPPort() {
      IPWorks_IPPort_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_IPPort_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_IPPort_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_IPPort_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline int GetAcceptData() {
      void* val = IPWorks_IPPort_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetAcceptData(int bAcceptData) {
      void* val = (void*)IPW64CAST(bAcceptData);
      return IPWorks_IPPort_Set(m_pObj, 1, 0, val, 0);
    }
    inline int GetBytesSent() {
      void* val = IPWorks_IPPort_Get(m_pObj, 2, 0, 0);
      return (int)(long)val;
    }

    inline int GetConnected() {
      void* val = IPWorks_IPPort_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_IPPort_Set(m_pObj, 3, 0, val, 0);
    }

    inline int SetDataToSend(const char *lpDataToSend, int lenDataToSend) {
      return IPWorks_IPPort_Set(m_pObj, 4, 0, (void*)lpDataToSend, lenDataToSend);
    }

    inline int GetEOL(char *&lpEOL, int &lenEOL) {
      lpEOL = (char*)IPWorks_IPPort_Get(m_pObj, 5, 0, &lenEOL);
      return lpEOL ? 0 : lenEOL;
    }

    inline int SetEOL(const char *lpEOL, int lenEOL) {
      return IPWorks_IPPort_Set(m_pObj, 5, 0, (void*)lpEOL, lenEOL);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_IPPort_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_IPPort_Set(m_pObj, 6, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_IPPort_Get(m_pObj, 7, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_IPPort_Set(m_pObj, 7, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_IPPort_Get(m_pObj, 8, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_IPPort_Set(m_pObj, 8, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_IPPort_Get(m_pObj, 9, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_IPPort_Set(m_pObj, 9, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_IPPort_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_IPPort_Set(m_pObj, 10, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_IPPort_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_IPPort_Set(m_pObj, 11, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetKeepAlive() {
      void* val = IPWorks_IPPort_Get(m_pObj, 12, 0, 0);
      return (int)(long)val;
    }
    inline int SetKeepAlive(int bKeepAlive) {
      void* val = (void*)IPW64CAST(bKeepAlive);
      return IPWorks_IPPort_Set(m_pObj, 12, 0, val, 0);
    }
    inline int GetLinger() {
      void* val = IPWorks_IPPort_Get(m_pObj, 13, 0, 0);
      return (int)(long)val;
    }
    inline int SetLinger(int bLinger) {
      void* val = (void*)IPW64CAST(bLinger);
      return IPWorks_IPPort_Set(m_pObj, 13, 0, val, 0);
    }
    inline char* GetLocalHost() {
      void* val = IPWorks_IPPort_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_IPPort_Set(m_pObj, 14, 0, (void*)lpLocalHost, 0);
    }

    inline int GetLocalPort() {
      void* val = IPWorks_IPPort_Get(m_pObj, 15, 0, 0);
      return (int)(long)val;
    }
    inline int SetLocalPort(int lLocalPort) {
      void* val = (void*)IPW64CAST(lLocalPort);
      return IPWorks_IPPort_Set(m_pObj, 15, 0, val, 0);
    }
    inline char* GetRemoteHost() {
      void* val = IPWorks_IPPort_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetRemoteHost(const char *lpRemoteHost) {
      return IPWorks_IPPort_Set(m_pObj, 16, 0, (void*)lpRemoteHost, 0);
    }

    inline int GetRemotePort() {
      void* val = IPWorks_IPPort_Get(m_pObj, 17, 0, 0);
      return (int)(long)val;
    }
    inline int SetRemotePort(int lRemotePort) {
      void* val = (void*)IPW64CAST(lRemotePort);
      return IPWorks_IPPort_Set(m_pObj, 17, 0, val, 0);
    }
    inline int GetSingleLineMode() {
      void* val = IPWorks_IPPort_Get(m_pObj, 18, 0, 0);
      return (int)(long)val;
    }
    inline int SetSingleLineMode(int bSingleLineMode) {
      void* val = (void*)IPW64CAST(bSingleLineMode);
      return IPWorks_IPPort_Set(m_pObj, 18, 0, val, 0);
    }
    inline int GetTimeout() {
      void* val = IPWorks_IPPort_Get(m_pObj, 19, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_IPPort_Set(m_pObj, 19, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPPort_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Connect(const char* lpszHost, int lPort) {
      void *param[2+1] = {(void*)IPW64CAST(lpszHost), (void*)IPW64CAST(lPort), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_IPPort_Do(m_pObj, 3, 2, param, cbparam);
      
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPPort_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPPort_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline char* GetLine() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_IPPort_Do(m_pObj, 6, 0, param, cbparam);
      
      return (char*)IPW64CAST(param[0]);
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPPort_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int Send(const char* lpText, int lenText) {
      void *param[1+1] = {(void*)IPW64CAST(lpText), 0};
      int cbparam[1+1] = {lenText, 0};
      return IPWorks_IPPort_Do(m_pObj, 8, 1, param, cbparam);
      
      
    }
    inline int SendFile(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IPPort_Do(m_pObj, 9, 1, param, cbparam);
      
      
    }
    inline int SendLine(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IPPort_Do(m_pObj, 10, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} IPPortConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} IPPortConnectionStatusEventParamsW;

typedef struct {
  LPWSTR Text;
  int EOL;
  int lenText;
  int reserved;
} IPPortDataInEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} IPPortDisconnectedEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} IPPortErrorEventParamsW;

typedef struct {
  int reserved;
} IPPortReadyToSendEventParamsW;



class IPPortW : public IPPort {

  public: //properties
  








    inline int SetDataToSend(LPWSTR lpDataToSend) {
      return IPWorks_IPPort_Set(m_pObj, 10000+4, 0, (void*)lpDataToSend, 0);
    }

    inline int SetDataToSendB(const char *lpDataToSend, int lenDataToSend) {
      return IPWorks_IPPort_Set(m_pObj, 4, 0, (void*)lpDataToSend, lenDataToSend);
    }
    inline LPWSTR GetEOL() {
      return (LPWSTR)IPWorks_IPPort_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetEOL(LPWSTR lpEOL) {
      return IPWorks_IPPort_Set(m_pObj, 10000+5, 0, (void*)lpEOL, 0);
    }
    inline int GetEOLB(char *&lpEOL, int &lenEOL) {
      lpEOL = (char*)IPWorks_IPPort_Get(m_pObj, 5, 0, &lenEOL);
      return lpEOL ? 0 : lenEOL;
    }
    inline int SetEOLB(const char *lpEOL, int lenEOL) {
      return IPWorks_IPPort_Set(m_pObj, 5, 0, (void*)lpEOL, lenEOL);
    }




    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_IPPort_Get(m_pObj, 10000+8, 0, 0);
    }

    inline int SetFirewallHost(LPWSTR lpFirewallHost) {
      return IPWorks_IPPort_Set(m_pObj, 10000+8, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_IPPort_Get(m_pObj, 10000+9, 0, 0);
    }

    inline int SetFirewallPassword(LPWSTR lpFirewallPassword) {
      return IPWorks_IPPort_Set(m_pObj, 10000+9, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_IPPort_Get(m_pObj, 10000+11, 0, 0);
    }

    inline int SetFirewallUser(LPWSTR lpFirewallUser) {
      return IPWorks_IPPort_Set(m_pObj, 10000+11, 0, (void*)lpFirewallUser, 0);
    }





    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_IPPort_Get(m_pObj, 10000+14, 0, 0);
    }

    inline int SetLocalHost(LPWSTR lpLocalHost) {
      return IPWorks_IPPort_Set(m_pObj, 10000+14, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetRemoteHost() {
      return (LPWSTR)IPWorks_IPPort_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetRemoteHost(LPWSTR lpRemoteHost) {
      return IPWorks_IPPort_Set(m_pObj, 10000+16, 0, (void*)lpRemoteHost, 0);
    }









  public: //events
  
    virtual int FireConnected(IPPortConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(IPPortConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDataIn(IPPortDataInEventParamsW *e) {return 0;}
    virtual int FireDisconnected(IPPortDisconnectedEventParamsW *e) {return 0;}
    virtual int FireError(IPPortErrorEventParamsW *e) {return 0;}
    virtual int FireReadyToSend(IPPortReadyToSendEventParamsW *e) {return 0;}


  protected:
  
    virtual int IPPortEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            IPPortConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            IPPortConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 3: {
            IPPortDataInEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireDataIn(&e);
            break;
         }
         case 4: {
            IPPortDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 5: {
            IPPortErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 6: {
            IPPortReadyToSendEventParamsW e = { 0};
            ret_code = FireReadyToSend(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(IPPortConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(IPPortConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDataIn(IPPortDataInEventParams *e) {return -10000;}
    virtual int FireDisconnected(IPPortDisconnectedEventParams *e) {return -10000;}
    virtual int FireError(IPPortErrorEventParams *e) {return -10000;}
    virtual int FireReadyToSend(IPPortReadyToSendEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPPort_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Connect(LPWSTR lpszHost, int lPort) {
      void *param[2+1] = {(void*)lpszHost, (void*)lPort, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_IPPort_Do(m_pObj, 10000+3, 2, param, cbparam);
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPPort_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPPort_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline LPWSTR GetLine() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      IPWorks_IPPort_Do(m_pObj, 10000+6, 0, param, cbparam);
      return (LPWSTR)IPW64CAST(param[0]);
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPPort_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int Send(LPWSTR lpText, int lenText) {
      void *param[1+1] = {(void*)lpText, 0};
      int cbparam[1+1] = {lenText, 0};
      return IPWorks_IPPort_Do(m_pObj, 10000+8, 1, param, cbparam);
      
    }
    inline int SendFile(LPWSTR lpszFileName) {
      void *param[1+1] = {(void*)lpszFileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IPPort_Do(m_pObj, 10000+9, 1, param, cbparam);
      
    }
    inline int SendLine(LPWSTR lpszText) {
      void *param[1+1] = {(void*)lpszText, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IPPort_Do(m_pObj, 10000+10, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_IPPORT_H_




