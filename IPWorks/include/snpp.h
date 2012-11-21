/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_SNPP_H_
#define _IPWORKS_SNPP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3


extern "C" void* IPWORKS_CALL IPWorks_SNPP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_SNPP_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_SNPP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_SNPP_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} SNPPConnectionStatusEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} SNPPErrorEventParams;

typedef struct {
  int Direction;
  const char* Message;
  int reserved;
} SNPPPITrailEventParams;



class SNPP {
  
  public: //events
  
    virtual int FireConnectionStatus(SNPPConnectionStatusEventParams *e) {return 0;}
    virtual int FireError(SNPPErrorEventParams *e) {return 0;}
    virtual int FirePITrail(SNPPPITrailEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL SNPPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((SNPP*)lpObj)->SNPPEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            SNPPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((SNPP*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 2: {
            SNPPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((SNPP*)lpObj)->FireError(&e);
            break;
         }
         case 3: {
            SNPPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((SNPP*)lpObj)->FirePITrail(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int SNPPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    SNPP(char *lpOemKey = (char*)IPWORKS_OEMKEY_32) {
      m_pObj = IPWorks_SNPP_Create(SNPPEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~SNPP() {
      IPWorks_SNPP_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_SNPP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_SNPP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_SNPP_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline char* GetCallerId() {
      void* val = IPWorks_SNPP_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetCallerId(const char *lpCallerId) {
      return IPWorks_SNPP_Set(m_pObj, 1, 0, (void*)lpCallerId, 0);
    }


    inline int SetCommand(const char *lpCommand) {
      return IPWorks_SNPP_Set(m_pObj, 2, 0, (void*)lpCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_SNPP_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_SNPP_Set(m_pObj, 3, 0, val, 0);
    }
    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_SNPP_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_SNPP_Set(m_pObj, 4, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_SNPP_Get(m_pObj, 5, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_SNPP_Set(m_pObj, 5, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_SNPP_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_SNPP_Set(m_pObj, 6, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_SNPP_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_SNPP_Set(m_pObj, 7, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_SNPP_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_SNPP_Set(m_pObj, 8, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_SNPP_Get(m_pObj, 9, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_SNPP_Set(m_pObj, 9, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_SNPP_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLastReply() {
      void* val = IPWorks_SNPP_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }


    inline char* GetLocalHost() {
      void* val = IPWorks_SNPP_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_SNPP_Set(m_pObj, 12, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetMessage() {
      void* val = IPWorks_SNPP_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetMessage(const char *lpMessage) {
      return IPWorks_SNPP_Set(m_pObj, 13, 0, (void*)lpMessage, 0);
    }

    inline char* GetPagerId() {
      void* val = IPWorks_SNPP_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }

    inline int SetPagerId(const char *lpPagerId) {
      return IPWorks_SNPP_Set(m_pObj, 14, 0, (void*)lpPagerId, 0);
    }

    inline char* GetServerName() {
      void* val = IPWorks_SNPP_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetServerName(const char *lpServerName) {
      return IPWorks_SNPP_Set(m_pObj, 15, 0, (void*)lpServerName, 0);
    }

    inline int GetServerPort() {
      void* val = IPWorks_SNPP_Get(m_pObj, 16, 0, 0);
      return (int)(long)val;
    }
    inline int SetServerPort(int lServerPort) {
      void* val = (void*)IPW64CAST(lServerPort);
      return IPWorks_SNPP_Set(m_pObj, 16, 0, val, 0);
    }
    inline int GetTimeout() {
      void* val = IPWorks_SNPP_Get(m_pObj, 17, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_SNPP_Set(m_pObj, 17, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SNPP_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int Send() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} SNPPConnectionStatusEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} SNPPErrorEventParamsW;

typedef struct {
  int Direction;
  LPWSTR Message;
  int reserved;
} SNPPPITrailEventParamsW;



class SNPPW : public SNPP {

  public: //properties
  
    inline LPWSTR GetCallerId() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetCallerId(LPWSTR lpCallerId) {
      return IPWorks_SNPP_Set(m_pObj, 10000+1, 0, (void*)lpCallerId, 0);
    }



    inline int SetCommand(LPWSTR lpCommand) {
      return IPWorks_SNPP_Set(m_pObj, 10000+2, 0, (void*)lpCommand, 0);
    }







    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetFirewallHost(LPWSTR lpFirewallHost) {
      return IPWorks_SNPP_Set(m_pObj, 10000+6, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+7, 0, 0);
    }

    inline int SetFirewallPassword(LPWSTR lpFirewallPassword) {
      return IPWorks_SNPP_Set(m_pObj, 10000+7, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+9, 0, 0);
    }

    inline int SetFirewallUser(LPWSTR lpFirewallUser) {
      return IPWorks_SNPP_Set(m_pObj, 10000+9, 0, (void*)lpFirewallUser, 0);
    }



    inline LPWSTR GetLastReply() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+11, 0, 0);
    }



    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+12, 0, 0);
    }

    inline int SetLocalHost(LPWSTR lpLocalHost) {
      return IPWorks_SNPP_Set(m_pObj, 10000+12, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetMessage() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+13, 0, 0);
    }

    inline int SetMessage(LPWSTR lpMessage) {
      return IPWorks_SNPP_Set(m_pObj, 10000+13, 0, (void*)lpMessage, 0);
    }

    inline LPWSTR GetPagerId() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+14, 0, 0);
    }

    inline int SetPagerId(LPWSTR lpPagerId) {
      return IPWorks_SNPP_Set(m_pObj, 10000+14, 0, (void*)lpPagerId, 0);
    }

    inline LPWSTR GetServerName() {
      return (LPWSTR)IPWorks_SNPP_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetServerName(LPWSTR lpServerName) {
      return IPWorks_SNPP_Set(m_pObj, 10000+15, 0, (void*)lpServerName, 0);
    }







  public: //events
  
    virtual int FireConnectionStatus(SNPPConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireError(SNPPErrorEventParamsW *e) {return 0;}
    virtual int FirePITrail(SNPPPITrailEventParamsW *e) {return 0;}


  protected:
  
    virtual int SNPPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            SNPPConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 2: {
            SNPPErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 3: {
            SNPPPITrailEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FirePITrail(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnectionStatus(SNPPConnectionStatusEventParams *e) {return -10000;}
    virtual int FireError(SNPPErrorEventParams *e) {return -10000;}
    virtual int FirePITrail(SNPPPITrailEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SNPP_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int Send() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SNPP_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_SNPP_H_




