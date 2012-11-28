/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_POP_H_
#define _IPWORKS_POP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//AuthMechanisms
#define AM_USER_PASSWORD                                   0
#define AM_CRAMMD5                                         1
#define AM_NTLM                                            2
#define AM_APOP                                            3
#define AM_SASLPLAIN                                       4
#define AM_SASLDIGEST_MD5                                  5
#define AM_KERBEROS                                        6

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//EmailRecipientTypes
#define RT_TO                                              0
#define RT_CC                                              1
#define RT_BCC                                             2


extern "C" void* IPWORKS_CALL IPWorks_POP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_POP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_POP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_POP_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_POP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_POP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_POP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_POP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_POP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_POP_StaticDestroy();

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
} POPConnectionStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} POPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} POPErrorEventParams;

typedef struct {
  const char* Field;
  const char* Value;
  int reserved;
} POPHeaderEventParams;

typedef struct {
  int MessageNumber;
  const char* MessageUID;
  int MessageSize;
  int reserved;
} POPMessageListEventParams;

typedef struct {
  int Direction;
  const char* Message;
  int reserved;
} POPPITrailEventParams;

typedef struct {
  int Direction;
  int reserved;
} POPStartTransferEventParams;

typedef struct {
  int Direction;
  ns_int64 *pBytesTransferred;
  int PercentDone;
  const char* Text;
  int EOL;
  int lenText;
  int reserved;
} POPTransferEventParams;



class POP {
  
  public: //events
  
    virtual int FireConnectionStatus(POPConnectionStatusEventParams *e) {return 0;}
    virtual int FireEndTransfer(POPEndTransferEventParams *e) {return 0;}
    virtual int FireError(POPErrorEventParams *e) {return 0;}
    virtual int FireHeader(POPHeaderEventParams *e) {return 0;}
    virtual int FireMessageList(POPMessageListEventParams *e) {return 0;}
    virtual int FirePITrail(POPPITrailEventParams *e) {return 0;}
    virtual int FireStartTransfer(POPStartTransferEventParams *e) {return 0;}
    virtual int FireTransfer(POPTransferEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL POPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((POP*)lpObj)->POPEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            POPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((POP*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 2: {
            POPEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((POP*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 3: {
            POPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((POP*)lpObj)->FireError(&e);
            break;
         }
         case 4: {
            POPHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((POP*)lpObj)->FireHeader(&e);
            break;
         }
         case 5: {
            POPMessageListEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = ((POP*)lpObj)->FireMessageList(&e);
            break;
         }
         case 6: {
            POPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((POP*)lpObj)->FirePITrail(&e);
            break;
         }
         case 7: {
            POPStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((POP*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 8: {
            POPTransferEventParams e = {(int)IPW64CAST(param[0]), (ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = ((POP*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int POPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    POP(char *lpOemKey = (char*)IPWORKS_OEMKEY_24) {
      m_pObj = IPWorks_POP_Create(POPEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~POP() {
      IPWorks_POP_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_POP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_POP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_POP_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline int GetAuthMechanism() {
      void* val = IPWorks_POP_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthMechanism(int iAuthMechanism) {
      void* val = (void*)IPW64CAST(iAuthMechanism);
      return IPWorks_POP_Set(m_pObj, 1, 0, val, 0);
    }

    inline int SetCommand(const char *lpCommand) {
      return IPWorks_POP_Set(m_pObj, 2, 0, (void*)lpCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_POP_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_POP_Set(m_pObj, 3, 0, val, 0);
    }
    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_POP_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_POP_Set(m_pObj, 4, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_POP_Get(m_pObj, 5, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_POP_Set(m_pObj, 5, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_POP_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_POP_Set(m_pObj, 6, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_POP_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_POP_Set(m_pObj, 7, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_POP_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_POP_Set(m_pObj, 8, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_POP_Get(m_pObj, 9, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_POP_Set(m_pObj, 9, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_POP_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }

    inline int GetIncludeHeaders() {
      void* val = IPWorks_POP_Get(m_pObj, 11, 0, 0);
      return (int)(long)val;
    }
    inline int SetIncludeHeaders(int bIncludeHeaders) {
      void* val = (void*)IPW64CAST(bIncludeHeaders);
      return IPWorks_POP_Set(m_pObj, 11, 0, val, 0);
    }
    inline char* GetLastReply() {
      void* val = IPWorks_POP_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }


    inline char* GetLocalFile() {
      void* val = IPWorks_POP_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetLocalFile(const char *lpLocalFile) {
      return IPWorks_POP_Set(m_pObj, 13, 0, (void*)lpLocalFile, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_POP_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_POP_Set(m_pObj, 14, 0, (void*)lpLocalHost, 0);
    }

    inline int GetMailPort() {
      void* val = IPWorks_POP_Get(m_pObj, 15, 0, 0);
      return (int)(long)val;
    }
    inline int SetMailPort(int lMailPort) {
      void* val = (void*)IPW64CAST(lMailPort);
      return IPWorks_POP_Set(m_pObj, 15, 0, val, 0);
    }
    inline char* GetMailServer() {
      void* val = IPWorks_POP_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetMailServer(const char *lpMailServer) {
      return IPWorks_POP_Set(m_pObj, 16, 0, (void*)lpMailServer, 0);
    }

    inline int GetMaxLines() {
      void* val = IPWorks_POP_Get(m_pObj, 17, 0, 0);
      return (int)(long)val;
    }
    inline int SetMaxLines(int lMaxLines) {
      void* val = (void*)IPW64CAST(lMaxLines);
      return IPWorks_POP_Set(m_pObj, 17, 0, val, 0);
    }
    inline int GetMessage(char *&lpMessage, int &lenMessage) {
      lpMessage = (char*)IPWorks_POP_Get(m_pObj, 18, 0, &lenMessage);
      return lpMessage ? 0 : lenMessage;
    }


    inline char* GetMessageCc() {
      void* val = IPWorks_POP_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }


    inline int GetMessageCount() {
      void* val = IPWorks_POP_Get(m_pObj, 20, 0, 0);
      return (int)(long)val;
    }

    inline char* GetMessageDate() {
      void* val = IPWorks_POP_Get(m_pObj, 21, 0, 0);
      return (char*)val;
    }


    inline char* GetMessageFrom() {
      void* val = IPWorks_POP_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }


    inline int GetMessageHeaderCount() {
      void* val = IPWorks_POP_Get(m_pObj, 23, 0, 0);
      return (int)(long)val;
    }

    inline char* GetMessageHeaderField(int iMessageHeaderIndex) {
      void* val = IPWorks_POP_Get(m_pObj, 24, iMessageHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetMessageHeaderValue(int iMessageHeaderIndex) {
      void* val = IPWorks_POP_Get(m_pObj, 25, iMessageHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetMessageHeadersString() {
      void* val = IPWorks_POP_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }


    inline int GetMessageNumber() {
      void* val = IPWorks_POP_Get(m_pObj, 27, 0, 0);
      return (int)(long)val;
    }
    inline int SetMessageNumber(int lMessageNumber) {
      void* val = (void*)IPW64CAST(lMessageNumber);
      return IPWorks_POP_Set(m_pObj, 27, 0, val, 0);
    }
    inline int GetMessageRecipientCount() {
      void* val = IPWorks_POP_Get(m_pObj, 28, 0, 0);
      return (int)(long)val;
    }

    inline char* GetMessageRecipientAddress(int iRecipientIndex) {
      void* val = IPWorks_POP_Get(m_pObj, 29, iRecipientIndex, 0);
      return (char*)val;
    }


    inline char* GetMessageRecipientName(int iRecipientIndex) {
      void* val = IPWorks_POP_Get(m_pObj, 30, iRecipientIndex, 0);
      return (char*)val;
    }


    inline char* GetMessageRecipientOptions(int iRecipientIndex) {
      void* val = IPWorks_POP_Get(m_pObj, 31, iRecipientIndex, 0);
      return (char*)val;
    }


    inline int GetMessageRecipientType(int iRecipientIndex) {
      void* val = IPWorks_POP_Get(m_pObj, 32, iRecipientIndex, 0);
      return (int)(long)val;
    }

    inline char* GetMessageReplyTo() {
      void* val = IPWorks_POP_Get(m_pObj, 33, 0, 0);
      return (char*)val;
    }


    inline int GetMessageSize() {
      void* val = IPWorks_POP_Get(m_pObj, 34, 0, 0);
      return (int)(long)val;
    }

    inline char* GetMessageSubject() {
      void* val = IPWorks_POP_Get(m_pObj, 35, 0, 0);
      return (char*)val;
    }


    inline char* GetMessageText() {
      void* val = IPWorks_POP_Get(m_pObj, 36, 0, 0);
      return (char*)val;
    }


    inline char* GetMessageTo() {
      void* val = IPWorks_POP_Get(m_pObj, 37, 0, 0);
      return (char*)val;
    }


    inline char* GetMessageUID() {
      void* val = IPWorks_POP_Get(m_pObj, 38, 0, 0);
      return (char*)val;
    }


    inline char* GetPassword() {
      void* val = IPWorks_POP_Get(m_pObj, 39, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_POP_Set(m_pObj, 39, 0, (void*)lpPassword, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_POP_Get(m_pObj, 40, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_POP_Set(m_pObj, 40, 0, val, 0);
    }
    inline ns_int64 GetTotalSize() {
      ns_int64 *pval = (ns_int64*)IPWorks_POP_Get(m_pObj, 41, 0, 0);
      return *pval;
    }


    inline char* GetUser() {
      void* val = IPWorks_POP_Get(m_pObj, 42, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_POP_Set(m_pObj, 42, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_POP_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int Delete() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int ListMessageSizes() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }
    inline int ListMessageUIDs() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline char* LocalizeDate(const char* lpszDateTime) {
      void *param[1+1] = {(void*)IPW64CAST(lpszDateTime), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_POP_Do(m_pObj, 10, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 11, 0, param, cbparam);
      
      
    }
    inline int Retrieve() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 12, 0, param, cbparam);
      
      
    }
    inline int RetrieveHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 13, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} POPConnectionStatusEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} POPEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} POPErrorEventParamsW;

typedef struct {
  LPWSTR Field;
  LPWSTR Value;
  int reserved;
} POPHeaderEventParamsW;

typedef struct {
  int MessageNumber;
  LPWSTR MessageUID;
  int MessageSize;
  int reserved;
} POPMessageListEventParamsW;

typedef struct {
  int Direction;
  LPWSTR Message;
  int reserved;
} POPPITrailEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} POPStartTransferEventParamsW;

typedef struct {
  int Direction;
  ns_int64 *pBytesTransferred;
  int PercentDone;
  LPWSTR Text;
  int EOL;
  int lenText;
  int reserved;
} POPTransferEventParamsW;



class POPW : public POP {

  public: //properties
  




    inline int SetCommand(LPWSTR lpCommand) {
      return IPWorks_POP_Set(m_pObj, 10000+2, 0, (void*)lpCommand, 0);
    }







    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetFirewallHost(LPWSTR lpFirewallHost) {
      return IPWorks_POP_Set(m_pObj, 10000+6, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+7, 0, 0);
    }

    inline int SetFirewallPassword(LPWSTR lpFirewallPassword) {
      return IPWorks_POP_Set(m_pObj, 10000+7, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+9, 0, 0);
    }

    inline int SetFirewallUser(LPWSTR lpFirewallUser) {
      return IPWorks_POP_Set(m_pObj, 10000+9, 0, (void*)lpFirewallUser, 0);
    }





    inline LPWSTR GetLastReply() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+12, 0, 0);
    }



    inline LPWSTR GetLocalFile() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+10000+13, 0, 0);
    }

    inline int SetLocalFile(LPWSTR lpLocalFile) {
      return IPWorks_POP_Set(m_pObj, 10000+10000+13, 0, (void*)lpLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+14, 0, 0);
    }

    inline int SetLocalHost(LPWSTR lpLocalHost) {
      return IPWorks_POP_Set(m_pObj, 10000+14, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetMailServer() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetMailServer(LPWSTR lpMailServer) {
      return IPWorks_POP_Set(m_pObj, 10000+16, 0, (void*)lpMailServer, 0);
    }



    inline LPWSTR GetMessage() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+18, 0, 0);
    }


    inline int GetMessageB(char *&lpMessage, int &lenMessage) {
      lpMessage = (char*)IPWorks_POP_Get(m_pObj, 18, 0, &lenMessage);
      return lpMessage ? 0 : lenMessage;
    }

    inline LPWSTR GetMessageCc() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+19, 0, 0);
    }





    inline LPWSTR GetMessageDate() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+21, 0, 0);
    }



    inline LPWSTR GetMessageFrom() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+22, 0, 0);
    }





    inline LPWSTR GetMessageHeaderField(int iMessageHeaderIndex) {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+24, iMessageHeaderIndex, 0);
    }



    inline LPWSTR GetMessageHeaderValue(int iMessageHeaderIndex) {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+25, iMessageHeaderIndex, 0);
    }



    inline LPWSTR GetMessageHeadersString() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+26, 0, 0);
    }







    inline LPWSTR GetMessageRecipientAddress(int iRecipientIndex) {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+29, iRecipientIndex, 0);
    }



    inline LPWSTR GetMessageRecipientName(int iRecipientIndex) {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+30, iRecipientIndex, 0);
    }



    inline LPWSTR GetMessageRecipientOptions(int iRecipientIndex) {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+31, iRecipientIndex, 0);
    }





    inline LPWSTR GetMessageReplyTo() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+33, 0, 0);
    }





    inline LPWSTR GetMessageSubject() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+35, 0, 0);
    }



    inline LPWSTR GetMessageText() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+36, 0, 0);
    }



    inline LPWSTR GetMessageTo() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+37, 0, 0);
    }



    inline LPWSTR GetMessageUID() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+38, 0, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+39, 0, 0);
    }

    inline int SetPassword(LPWSTR lpPassword) {
      return IPWorks_POP_Set(m_pObj, 10000+39, 0, (void*)lpPassword, 0);
    }





    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_POP_Get(m_pObj, 10000+42, 0, 0);
    }

    inline int SetUser(LPWSTR lpUser) {
      return IPWorks_POP_Set(m_pObj, 10000+42, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnectionStatus(POPConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(POPEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(POPErrorEventParamsW *e) {return 0;}
    virtual int FireHeader(POPHeaderEventParamsW *e) {return 0;}
    virtual int FireMessageList(POPMessageListEventParamsW *e) {return 0;}
    virtual int FirePITrail(POPPITrailEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(POPStartTransferEventParamsW *e) {return 0;}
    virtual int FireTransfer(POPTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int POPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            POPConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 2: {
            POPEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 3: {
            POPErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 4: {
            POPHeaderEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireHeader(&e);
            break;
         }
         case 5: {
            POPMessageListEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = FireMessageList(&e);
            break;
         }
         case 6: {
            POPPITrailEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FirePITrail(&e);
            break;
         }
         case 7: {
            POPStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 8: {
            POPTransferEventParamsW e = {(int)IPW64CAST(param[0]), (ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnectionStatus(POPConnectionStatusEventParams *e) {return -10000;}
    virtual int FireEndTransfer(POPEndTransferEventParams *e) {return -10000;}
    virtual int FireError(POPErrorEventParams *e) {return -10000;}
    virtual int FireHeader(POPHeaderEventParams *e) {return -10000;}
    virtual int FireMessageList(POPMessageListEventParams *e) {return -10000;}
    virtual int FirePITrail(POPPITrailEventParams *e) {return -10000;}
    virtual int FireStartTransfer(POPStartTransferEventParams *e) {return -10000;}
    virtual int FireTransfer(POPTransferEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_POP_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int Delete() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int ListMessageSizes() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }
    inline int ListMessageUIDs() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline LPWSTR LocalizeDate(LPWSTR lpszDateTime) {
      void *param[1+1] = {(void*)lpszDateTime, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_POP_Do(m_pObj, 10000+10, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 10000+11, 0, param, cbparam);
      
    }
    inline int Retrieve() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 10000+12, 0, param, cbparam);
      
    }
    inline int RetrieveHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_POP_Do(m_pObj, 10000+13, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_POP_H_




