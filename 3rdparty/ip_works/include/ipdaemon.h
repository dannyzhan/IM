/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_IPDAEMON_H_
#define _IPWORKS_IPDAEMON_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_IPDaemon_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_IPDaemon_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_IPDaemon_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_IPDaemon_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  int ConnectionId;
  int StatusCode;
  const char* Description;
  int reserved;
} IPDaemonConnectedEventParams;

typedef struct {
  const char* Address;
  int Port;
  int Accept;
  int reserved;
} IPDaemonConnectionRequestEventParams;

typedef struct {
  int ConnectionId;
  const char* Text;
  int EOL;
  int lenText;
  int reserved;
} IPDaemonDataInEventParams;

typedef struct {
  int ConnectionId;
  int StatusCode;
  const char* Description;
  int reserved;
} IPDaemonDisconnectedEventParams;

typedef struct {
  int ConnectionId;
  int ErrorCode;
  const char* Description;
  int reserved;
} IPDaemonErrorEventParams;

typedef struct {
  int ConnectionId;
  int reserved;
} IPDaemonReadyToSendEventParams;



class IPDaemon {
  
  public: //events
  
    virtual int FireConnected(IPDaemonConnectedEventParams *e) {return 0;}
    virtual int FireConnectionRequest(IPDaemonConnectionRequestEventParams *e) {return 0;}
    virtual int FireDataIn(IPDaemonDataInEventParams *e) {return 0;}
    virtual int FireDisconnected(IPDaemonDisconnectedEventParams *e) {return 0;}
    virtual int FireError(IPDaemonErrorEventParams *e) {return 0;}
    virtual int FireReadyToSend(IPDaemonReadyToSendEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL IPDaemonEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((IPDaemon*)lpObj)->IPDaemonEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            IPDaemonConnectedEventParams e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((IPDaemon*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            IPDaemonConnectionRequestEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = ((IPDaemon*)lpObj)->FireConnectionRequest(&e);
            param[2] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 3: {
            IPDaemonDataInEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (int)IPW64CAST(cbparam[1]),  0};
            ret_code = ((IPDaemon*)lpObj)->FireDataIn(&e);
            break;
         }
         case 4: {
            IPDaemonDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((IPDaemon*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 5: {
            IPDaemonErrorEventParams e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((IPDaemon*)lpObj)->FireError(&e);
            break;
         }
         case 6: {
            IPDaemonReadyToSendEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((IPDaemon*)lpObj)->FireReadyToSend(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int IPDaemonEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    IPDaemon(char *lpOemKey = (char*)IPWORKS_OEMKEY_12) {
      m_pObj = IPWorks_IPDaemon_Create(IPDaemonEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~IPDaemon() {
      IPWorks_IPDaemon_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_IPDaemon_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_IPDaemon_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_IPDaemon_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline int GetConnectionBacklog() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnectionBacklog(int iConnectionBacklog) {
      void* val = (void*)IPW64CAST(iConnectionBacklog);
      return IPWorks_IPDaemon_Set(m_pObj, 1, 0, val, 0);
    }
    inline int GetConnectionCount() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 2, 0, 0);
      return (int)(long)val;
    }

    inline int GetAcceptData(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 3, iConnectionId, 0);
      return (int)(long)val;
    }
    inline int SetAcceptData(int iConnectionId, int bAcceptData) {
      void* val = (void*)IPW64CAST(bAcceptData);
      return IPWorks_IPDaemon_Set(m_pObj, 3, iConnectionId, val, 0);
    }
    inline int GetBytesSent(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 4, iConnectionId, 0);
      return (int)(long)val;
    }

    inline int GetConnected(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 5, iConnectionId, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int iConnectionId, int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_IPDaemon_Set(m_pObj, 5, iConnectionId, val, 0);
    }
    inline char* GetConnectionId(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 6, iConnectionId, 0);
      return (char*)val;
    }



    inline int SetDataToSend(int iConnectionId, const char *lpDataToSend, int lenDataToSend) {
      return IPWorks_IPDaemon_Set(m_pObj, 7, iConnectionId, (void*)lpDataToSend, lenDataToSend);
    }

    inline int GetEOL(int iConnectionId, char *&lpEOL, int &lenEOL) {
      lpEOL = (char*)IPWorks_IPDaemon_Get(m_pObj, 8, iConnectionId, &lenEOL);
      return lpEOL ? 0 : lenEOL;
    }

    inline int SetEOL(int iConnectionId, const char *lpEOL, int lenEOL) {
      return IPWorks_IPDaemon_Set(m_pObj, 8, iConnectionId, (void*)lpEOL, lenEOL);
    }

    inline char* GetLocalAddress(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 9, iConnectionId, 0);
      return (char*)val;
    }


    inline char* GetRemoteHost(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 10, iConnectionId, 0);
      return (char*)val;
    }


    inline int GetRemotePort(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 11, iConnectionId, 0);
      return (int)(long)val;
    }

    inline int GetSingleLineMode(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 12, iConnectionId, 0);
      return (int)(long)val;
    }
    inline int SetSingleLineMode(int iConnectionId, int bSingleLineMode) {
      void* val = (void*)IPW64CAST(bSingleLineMode);
      return IPWorks_IPDaemon_Set(m_pObj, 12, iConnectionId, val, 0);
    }
    inline int GetTimeout(int iConnectionId) {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 13, iConnectionId, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iConnectionId, int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_IPDaemon_Set(m_pObj, 13, iConnectionId, val, 0);
    }
    inline int GetDefaultEOL(char *&lpDefaultEOL, int &lenDefaultEOL) {
      lpDefaultEOL = (char*)IPWorks_IPDaemon_Get(m_pObj, 14, 0, &lenDefaultEOL);
      return lpDefaultEOL ? 0 : lenDefaultEOL;
    }

    inline int SetDefaultEOL(const char *lpDefaultEOL, int lenDefaultEOL) {
      return IPWorks_IPDaemon_Set(m_pObj, 14, 0, (void*)lpDefaultEOL, lenDefaultEOL);
    }

    inline int GetDefaultMaxLineLength() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 15, 0, 0);
      return (int)(long)val;
    }
    inline int SetDefaultMaxLineLength(int iDefaultMaxLineLength) {
      void* val = (void*)IPW64CAST(iDefaultMaxLineLength);
      return IPWorks_IPDaemon_Set(m_pObj, 15, 0, val, 0);
    }
    inline int GetDefaultSingleLineMode() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 16, 0, 0);
      return (int)(long)val;
    }
    inline int SetDefaultSingleLineMode(int bDefaultSingleLineMode) {
      void* val = (void*)IPW64CAST(bDefaultSingleLineMode);
      return IPWorks_IPDaemon_Set(m_pObj, 16, 0, val, 0);
    }
    inline int GetDefaultTimeout() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 17, 0, 0);
      return (int)(long)val;
    }
    inline int SetDefaultTimeout(int iDefaultTimeout) {
      void* val = (void*)IPW64CAST(iDefaultTimeout);
      return IPWorks_IPDaemon_Set(m_pObj, 17, 0, val, 0);
    }
    inline int GetKeepAlive() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 18, 0, 0);
      return (int)(long)val;
    }
    inline int SetKeepAlive(int bKeepAlive) {
      void* val = (void*)IPW64CAST(bKeepAlive);
      return IPWorks_IPDaemon_Set(m_pObj, 18, 0, val, 0);
    }
    inline int GetLinger() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 19, 0, 0);
      return (int)(long)val;
    }
    inline int SetLinger(int bLinger) {
      void* val = (void*)IPW64CAST(bLinger);
      return IPWorks_IPDaemon_Set(m_pObj, 19, 0, val, 0);
    }
    inline int GetListening() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 20, 0, 0);
      return (int)(long)val;
    }
    inline int SetListening(int bListening) {
      void* val = (void*)IPW64CAST(bListening);
      return IPWorks_IPDaemon_Set(m_pObj, 20, 0, val, 0);
    }
    inline char* GetLocalHost() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 21, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_IPDaemon_Set(m_pObj, 21, 0, (void*)lpLocalHost, 0);
    }

    inline int GetLocalPort() {
      void* val = IPWorks_IPDaemon_Get(m_pObj, 22, 0, 0);
      return (int)(long)val;
    }
    inline int SetLocalPort(int lLocalPort) {
      void* val = (void*)IPW64CAST(lLocalPort);
      return IPWorks_IPDaemon_Set(m_pObj, 22, 0, val, 0);
    }

  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPDaemon_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Disconnect(int iConnectionId) {
      void *param[1+1] = {(void*)IPW64CAST(iConnectionId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 3, 1, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPDaemon_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int Interrupt(int iConnectionId) {
      void *param[1+1] = {(void*)IPW64CAST(iConnectionId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 5, 1, param, cbparam);
      
      
    }
    inline int Send(int iConnectionId, const char* lpText, int lenText) {
      void *param[2+1] = {(void*)IPW64CAST(iConnectionId), (void*)IPW64CAST(lpText), 0};
      int cbparam[2+1] = {0, lenText, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 6, 2, param, cbparam);
      
      
    }
    inline int SendFile(int iConnectionId, const char* lpszFileName) {
      void *param[2+1] = {(void*)IPW64CAST(iConnectionId), (void*)IPW64CAST(lpszFileName), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 7, 2, param, cbparam);
      
      
    }
    inline int SendLine(int iConnectionId, const char* lpszText) {
      void *param[2+1] = {(void*)IPW64CAST(iConnectionId), (void*)IPW64CAST(lpszText), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 8, 2, param, cbparam);
      
      
    }
    inline int Shutdown() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPDaemon_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int ConnectionId;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} IPDaemonConnectedEventParamsW;

typedef struct {
  LPWSTR Address;
  int Port;
  int Accept;
  int reserved;
} IPDaemonConnectionRequestEventParamsW;

typedef struct {
  int ConnectionId;
  LPWSTR Text;
  int EOL;
  int lenText;
  int reserved;
} IPDaemonDataInEventParamsW;

typedef struct {
  int ConnectionId;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} IPDaemonDisconnectedEventParamsW;

typedef struct {
  int ConnectionId;
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} IPDaemonErrorEventParamsW;

typedef struct {
  int ConnectionId;
  int reserved;
} IPDaemonReadyToSendEventParamsW;



class IPDaemonW : public IPDaemon {

  public: //properties
  










    inline LPWSTR GetConnectionId(int iConnectionId) {
      return (LPWSTR)IPWorks_IPDaemon_Get(m_pObj, 10000+6, iConnectionId, 0);
    }





    inline int SetDataToSend(int iConnectionId, LPWSTR lpDataToSend) {
      return IPWorks_IPDaemon_Set(m_pObj, 10000+7, iConnectionId, (void*)lpDataToSend, 0);
    }

    inline int SetDataToSendB(int iConnectionId, const char *lpDataToSend, int lenDataToSend) {
      return IPWorks_IPDaemon_Set(m_pObj, 7, iConnectionId, (void*)lpDataToSend, lenDataToSend);
    }
    inline LPWSTR GetEOL(int iConnectionId) {
      return (LPWSTR)IPWorks_IPDaemon_Get(m_pObj, 10000+8, iConnectionId, 0);
    }

    inline int SetEOL(int iConnectionId, LPWSTR lpEOL) {
      return IPWorks_IPDaemon_Set(m_pObj, 10000+8, iConnectionId, (void*)lpEOL, 0);
    }
    inline int GetEOLB(int iConnectionId, char *&lpEOL, int &lenEOL) {
      lpEOL = (char*)IPWorks_IPDaemon_Get(m_pObj, 8, iConnectionId, &lenEOL);
      return lpEOL ? 0 : lenEOL;
    }
    inline int SetEOLB(int iConnectionId, const char *lpEOL, int lenEOL) {
      return IPWorks_IPDaemon_Set(m_pObj, 8, iConnectionId, (void*)lpEOL, lenEOL);
    }
    inline LPWSTR GetLocalAddress(int iConnectionId) {
      return (LPWSTR)IPWorks_IPDaemon_Get(m_pObj, 10000+9, iConnectionId, 0);
    }



    inline LPWSTR GetRemoteHost(int iConnectionId) {
      return (LPWSTR)IPWorks_IPDaemon_Get(m_pObj, 10000+10, iConnectionId, 0);
    }









    inline LPWSTR GetDefaultEOL() {
      return (LPWSTR)IPWorks_IPDaemon_Get(m_pObj, 10000+14, 0, 0);
    }

    inline int SetDefaultEOL(LPWSTR lpDefaultEOL) {
      return IPWorks_IPDaemon_Set(m_pObj, 10000+14, 0, (void*)lpDefaultEOL, 0);
    }
    inline int GetDefaultEOLB(char *&lpDefaultEOL, int &lenDefaultEOL) {
      lpDefaultEOL = (char*)IPWorks_IPDaemon_Get(m_pObj, 14, 0, &lenDefaultEOL);
      return lpDefaultEOL ? 0 : lenDefaultEOL;
    }
    inline int SetDefaultEOLB(const char *lpDefaultEOL, int lenDefaultEOL) {
      return IPWorks_IPDaemon_Set(m_pObj, 14, 0, (void*)lpDefaultEOL, lenDefaultEOL);
    }












    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_IPDaemon_Get(m_pObj, 10000+21, 0, 0);
    }

    inline int SetLocalHost(LPWSTR lpLocalHost) {
      return IPWorks_IPDaemon_Set(m_pObj, 10000+21, 0, (void*)lpLocalHost, 0);
    }





  public: //events
  
    virtual int FireConnected(IPDaemonConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionRequest(IPDaemonConnectionRequestEventParamsW *e) {return 0;}
    virtual int FireDataIn(IPDaemonDataInEventParamsW *e) {return 0;}
    virtual int FireDisconnected(IPDaemonDisconnectedEventParamsW *e) {return 0;}
    virtual int FireError(IPDaemonErrorEventParamsW *e) {return 0;}
    virtual int FireReadyToSend(IPDaemonReadyToSendEventParamsW *e) {return 0;}


  protected:
  
    virtual int IPDaemonEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            IPDaemonConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            IPDaemonConnectionRequestEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionRequest(&e);
            param[2] = (void*)(e.Accept);
            break;
         }
         case 3: {
            IPDaemonDataInEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (int)IPW64CAST(cbparam[1]),  0};
            ret_code = FireDataIn(&e);
            break;
         }
         case 4: {
            IPDaemonDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 5: {
            IPDaemonErrorEventParamsW e = {(int)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 6: {
            IPDaemonReadyToSendEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireReadyToSend(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(IPDaemonConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionRequest(IPDaemonConnectionRequestEventParams *e) {return -10000;}
    virtual int FireDataIn(IPDaemonDataInEventParams *e) {return -10000;}
    virtual int FireDisconnected(IPDaemonDisconnectedEventParams *e) {return -10000;}
    virtual int FireError(IPDaemonErrorEventParams *e) {return -10000;}
    virtual int FireReadyToSend(IPDaemonReadyToSendEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_IPDaemon_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Disconnect(int iConnectionId) {
      void *param[1+1] = {(void*)iConnectionId, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 10000+3, 1, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPDaemon_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int Interrupt(int iConnectionId) {
      void *param[1+1] = {(void*)iConnectionId, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 10000+5, 1, param, cbparam);
      
    }
    inline int Send(int iConnectionId, LPWSTR lpText, int lenText) {
      void *param[2+1] = {(void*)iConnectionId, (void*)lpText, 0};
      int cbparam[2+1] = {0, lenText, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 10000+6, 2, param, cbparam);
      
    }
    inline int SendFile(int iConnectionId, LPWSTR lpszFileName) {
      void *param[2+1] = {(void*)iConnectionId, (void*)lpszFileName, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 10000+7, 2, param, cbparam);
      
    }
    inline int SendLine(int iConnectionId, LPWSTR lpszText) {
      void *param[2+1] = {(void*)iConnectionId, (void*)lpszText, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_IPDaemon_Do(m_pObj, 10000+8, 2, param, cbparam);
      
    }
    inline int Shutdown() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_IPDaemon_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_IPDAEMON_H_




