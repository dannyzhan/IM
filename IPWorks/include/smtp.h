/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_SMTP_H_
#define _IPWORKS_SMTP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//AuthMechanisms
#define AM_USER_PASSWORD                                   0
#define AM_CRAMMD5                                         1
#define AM_NTLM                                            2
#define AM_KERBEROS                                        6

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TImportance
#define MI_UNSPECIFIED                                     0
#define MI_HIGH                                            1
#define MI_NORMAL                                          2
#define MI_LOW                                             3

//EmailRecipientTypes
#define RT_TO                                              0
#define RT_CC                                              1
#define RT_BCC                                             2

//TPriority
#define EP_UNSPECIFIED                                     0
#define EP_NORMAL                                          1
#define EP_URGENT                                          2
#define EP_NON_URGENT                                      3

//TSensitivity
#define ES_UNSPECIFIED                                     0
#define ES_PERSONAL                                        1
#define ES_PRIVATE                                         2
#define ES_COMPANY_CONFIDENTIAL                            3


extern "C" void* IPWORKS_CALL IPWorks_SMTP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_SMTP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SMTP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_SMTP_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_SMTP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_SMTP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_SMTP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SMTP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_SMTP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_SMTP_StaticDestroy();

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
} SMTPConnectionStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} SMTPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} SMTPErrorEventParams;

typedef struct {
  const char* Address;
  int reserved;
} SMTPExpandEventParams;

typedef struct {
  int Direction;
  const char* Message;
  int reserved;
} SMTPPITrailEventParams;

typedef struct {
  int Direction;
  int reserved;
} SMTPStartTransferEventParams;

typedef struct {
  int Direction;
  ns_int64 *pBytesTransferred;
  int PercentDone;
  int reserved;
} SMTPTransferEventParams;



class SMTP {
  
  public: //events
  
    virtual int FireConnectionStatus(SMTPConnectionStatusEventParams *e) {return 0;}
    virtual int FireEndTransfer(SMTPEndTransferEventParams *e) {return 0;}
    virtual int FireError(SMTPErrorEventParams *e) {return 0;}
    virtual int FireExpand(SMTPExpandEventParams *e) {return 0;}
    virtual int FirePITrail(SMTPPITrailEventParams *e) {return 0;}
    virtual int FireStartTransfer(SMTPStartTransferEventParams *e) {return 0;}
    virtual int FireTransfer(SMTPTransferEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL SMTPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((SMTP*)lpObj)->SMTPEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            SMTPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((SMTP*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 2: {
            SMTPEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((SMTP*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 3: {
            SMTPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((SMTP*)lpObj)->FireError(&e);
            break;
         }
         case 4: {
            SMTPExpandEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((SMTP*)lpObj)->FireExpand(&e);
            break;
         }
         case 5: {
            SMTPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((SMTP*)lpObj)->FirePITrail(&e);
            break;
         }
         case 6: {
            SMTPStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((SMTP*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 7: {
            SMTPTransferEventParams e = {(int)IPW64CAST(param[0]), (ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = ((SMTP*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int SMTPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    SMTP(char *lpOemKey = (char*)IPWORKS_OEMKEY_23) {
      m_pObj = IPWorks_SMTP_Create(SMTPEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~SMTP() {
      IPWorks_SMTP_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_SMTP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_SMTP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_SMTP_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline int GetAllowExtensions() {
      void* val = IPWorks_SMTP_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetAllowExtensions(int bAllowExtensions) {
      void* val = (void*)IPW64CAST(bAllowExtensions);
      return IPWorks_SMTP_Set(m_pObj, 1, 0, val, 0);
    }
    inline int GetAuthMechanism() {
      void* val = IPWorks_SMTP_Get(m_pObj, 2, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthMechanism(int iAuthMechanism) {
      void* val = (void*)IPW64CAST(iAuthMechanism);
      return IPWorks_SMTP_Set(m_pObj, 2, 0, val, 0);
    }
    inline char* GetBCc() {
      void* val = IPWorks_SMTP_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }

    inline int SetBCc(const char *lpBCc) {
      return IPWorks_SMTP_Set(m_pObj, 3, 0, (void*)lpBCc, 0);
    }

    inline char* GetCc() {
      void* val = IPWorks_SMTP_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetCc(const char *lpCc) {
      return IPWorks_SMTP_Set(m_pObj, 4, 0, (void*)lpCc, 0);
    }


    inline int SetCommand(const char *lpCommand) {
      return IPWorks_SMTP_Set(m_pObj, 5, 0, (void*)lpCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_SMTP_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_SMTP_Set(m_pObj, 6, 0, val, 0);
    }
    inline char* GetDeliveryNotificationTo() {
      void* val = IPWorks_SMTP_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }

    inline int SetDeliveryNotificationTo(const char *lpDeliveryNotificationTo) {
      return IPWorks_SMTP_Set(m_pObj, 7, 0, (void*)lpDeliveryNotificationTo, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_SMTP_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_SMTP_Set(m_pObj, 8, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_SMTP_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_SMTP_Set(m_pObj, 9, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_SMTP_Get(m_pObj, 10, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_SMTP_Set(m_pObj, 10, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_SMTP_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_SMTP_Set(m_pObj, 11, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_SMTP_Get(m_pObj, 12, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_SMTP_Set(m_pObj, 12, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_SMTP_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_SMTP_Set(m_pObj, 13, 0, (void*)lpFirewallUser, 0);
    }

    inline char* GetFrom() {
      void* val = IPWorks_SMTP_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }

    inline int SetFrom(const char *lpFrom) {
      return IPWorks_SMTP_Set(m_pObj, 14, 0, (void*)lpFrom, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_SMTP_Get(m_pObj, 15, 0, 0);
      return (int)(long)val;
    }

    inline int GetImportance() {
      void* val = IPWorks_SMTP_Get(m_pObj, 16, 0, 0);
      return (int)(long)val;
    }
    inline int SetImportance(int iImportance) {
      void* val = (void*)IPW64CAST(iImportance);
      return IPWorks_SMTP_Set(m_pObj, 16, 0, val, 0);
    }
    inline char* GetLastReply() {
      void* val = IPWorks_SMTP_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }


    inline char* GetLocalHost() {
      void* val = IPWorks_SMTP_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_SMTP_Set(m_pObj, 18, 0, (void*)lpLocalHost, 0);
    }

    inline int GetMailPort() {
      void* val = IPWorks_SMTP_Get(m_pObj, 19, 0, 0);
      return (int)(long)val;
    }
    inline int SetMailPort(int lMailPort) {
      void* val = (void*)IPW64CAST(lMailPort);
      return IPWorks_SMTP_Set(m_pObj, 19, 0, val, 0);
    }
    inline char* GetMailServer() {
      void* val = IPWorks_SMTP_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }

    inline int SetMailServer(const char *lpMailServer) {
      return IPWorks_SMTP_Set(m_pObj, 20, 0, (void*)lpMailServer, 0);
    }

    inline int GetMessage(char *&lpMessage, int &lenMessage) {
      lpMessage = (char*)IPWorks_SMTP_Get(m_pObj, 21, 0, &lenMessage);
      return lpMessage ? 0 : lenMessage;
    }

    inline int SetMessage(const char *lpMessage, int lenMessage) {
      return IPWorks_SMTP_Set(m_pObj, 21, 0, (void*)lpMessage, lenMessage);
    }

    inline char* GetMessageDate() {
      void* val = IPWorks_SMTP_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }

    inline int SetMessageDate(const char *lpMessageDate) {
      return IPWorks_SMTP_Set(m_pObj, 22, 0, (void*)lpMessageDate, 0);
    }

    inline int GetMessageHeaderCount() {
      void* val = IPWorks_SMTP_Get(m_pObj, 23, 0, 0);
      return (int)(long)val;
    }

    inline char* GetMessageHeaderField(int iMessageHeaderIndex) {
      void* val = IPWorks_SMTP_Get(m_pObj, 24, iMessageHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetMessageHeaderValue(int iMessageHeaderIndex) {
      void* val = IPWorks_SMTP_Get(m_pObj, 25, iMessageHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetMessageHeadersString() {
      void* val = IPWorks_SMTP_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }


    inline char* GetMessageId() {
      void* val = IPWorks_SMTP_Get(m_pObj, 27, 0, 0);
      return (char*)val;
    }

    inline int SetMessageId(const char *lpMessageId) {
      return IPWorks_SMTP_Set(m_pObj, 27, 0, (void*)lpMessageId, 0);
    }

    inline int GetMessageRecipientCount() {
      void* val = IPWorks_SMTP_Get(m_pObj, 28, 0, 0);
      return (int)(long)val;
    }
    inline int SetMessageRecipientCount(int iMessageRecipientCount) {
      void* val = (void*)IPW64CAST(iMessageRecipientCount);
      return IPWorks_SMTP_Set(m_pObj, 28, 0, val, 0);
    }
    inline char* GetMessageRecipientAddress(int iRecipientIndex) {
      void* val = IPWorks_SMTP_Get(m_pObj, 29, iRecipientIndex, 0);
      return (char*)val;
    }

    inline int SetMessageRecipientAddress(int iRecipientIndex, const char *lpMessageRecipientAddress) {
      return IPWorks_SMTP_Set(m_pObj, 29, iRecipientIndex, (void*)lpMessageRecipientAddress, 0);
    }

    inline char* GetMessageRecipientName(int iRecipientIndex) {
      void* val = IPWorks_SMTP_Get(m_pObj, 30, iRecipientIndex, 0);
      return (char*)val;
    }

    inline int SetMessageRecipientName(int iRecipientIndex, const char *lpMessageRecipientName) {
      return IPWorks_SMTP_Set(m_pObj, 30, iRecipientIndex, (void*)lpMessageRecipientName, 0);
    }

    inline char* GetMessageRecipientOptions(int iRecipientIndex) {
      void* val = IPWorks_SMTP_Get(m_pObj, 31, iRecipientIndex, 0);
      return (char*)val;
    }

    inline int SetMessageRecipientOptions(int iRecipientIndex, const char *lpMessageRecipientOptions) {
      return IPWorks_SMTP_Set(m_pObj, 31, iRecipientIndex, (void*)lpMessageRecipientOptions, 0);
    }

    inline int GetMessageRecipientType(int iRecipientIndex) {
      void* val = IPWorks_SMTP_Get(m_pObj, 32, iRecipientIndex, 0);
      return (int)(long)val;
    }
    inline int SetMessageRecipientType(int iRecipientIndex, int iMessageRecipientType) {
      void* val = (void*)IPW64CAST(iMessageRecipientType);
      return IPWorks_SMTP_Set(m_pObj, 32, iRecipientIndex, val, 0);
    }
    inline char* GetMessageText() {
      void* val = IPWorks_SMTP_Get(m_pObj, 33, 0, 0);
      return (char*)val;
    }

    inline int SetMessageText(const char *lpMessageText) {
      return IPWorks_SMTP_Set(m_pObj, 33, 0, (void*)lpMessageText, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_SMTP_Get(m_pObj, 34, 0, 0);
      return (char*)val;
    }

    inline int SetOtherHeaders(const char *lpOtherHeaders) {
      return IPWorks_SMTP_Set(m_pObj, 34, 0, (void*)lpOtherHeaders, 0);
    }

    inline char* GetPassword() {
      void* val = IPWorks_SMTP_Get(m_pObj, 35, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_SMTP_Set(m_pObj, 35, 0, (void*)lpPassword, 0);
    }

    inline int GetPriority() {
      void* val = IPWorks_SMTP_Get(m_pObj, 36, 0, 0);
      return (int)(long)val;
    }
    inline int SetPriority(int iPriority) {
      void* val = (void*)IPW64CAST(iPriority);
      return IPWorks_SMTP_Set(m_pObj, 36, 0, val, 0);
    }
    inline char* GetReadReceiptTo() {
      void* val = IPWorks_SMTP_Get(m_pObj, 37, 0, 0);
      return (char*)val;
    }

    inline int SetReadReceiptTo(const char *lpReadReceiptTo) {
      return IPWorks_SMTP_Set(m_pObj, 37, 0, (void*)lpReadReceiptTo, 0);
    }

    inline char* GetReplyTo() {
      void* val = IPWorks_SMTP_Get(m_pObj, 38, 0, 0);
      return (char*)val;
    }

    inline int SetReplyTo(const char *lpReplyTo) {
      return IPWorks_SMTP_Set(m_pObj, 38, 0, (void*)lpReplyTo, 0);
    }

    inline char* GetReturnPath() {
      void* val = IPWorks_SMTP_Get(m_pObj, 39, 0, 0);
      return (char*)val;
    }

    inline int SetReturnPath(const char *lpReturnPath) {
      return IPWorks_SMTP_Set(m_pObj, 39, 0, (void*)lpReturnPath, 0);
    }

    inline char* GetSendTo() {
      void* val = IPWorks_SMTP_Get(m_pObj, 40, 0, 0);
      return (char*)val;
    }

    inline int SetSendTo(const char *lpSendTo) {
      return IPWorks_SMTP_Set(m_pObj, 40, 0, (void*)lpSendTo, 0);
    }

    inline int GetSensitivity() {
      void* val = IPWorks_SMTP_Get(m_pObj, 41, 0, 0);
      return (int)(long)val;
    }
    inline int SetSensitivity(int iSensitivity) {
      void* val = (void*)IPW64CAST(iSensitivity);
      return IPWorks_SMTP_Set(m_pObj, 41, 0, val, 0);
    }
    inline char* GetSubject() {
      void* val = IPWorks_SMTP_Get(m_pObj, 42, 0, 0);
      return (char*)val;
    }

    inline int SetSubject(const char *lpSubject) {
      return IPWorks_SMTP_Set(m_pObj, 42, 0, (void*)lpSubject, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_SMTP_Get(m_pObj, 43, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_SMTP_Set(m_pObj, 43, 0, val, 0);
    }
    inline char* GetUser() {
      void* val = IPWorks_SMTP_Get(m_pObj, 44, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_SMTP_Set(m_pObj, 44, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SMTP_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int Expand(const char* lpszEmailAddress) {
      void *param[1+1] = {(void*)IPW64CAST(lpszEmailAddress), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_SMTP_Do(m_pObj, 6, 1, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int ProcessQueue(const char* lpszQueueDir) {
      void *param[1+1] = {(void*)IPW64CAST(lpszQueueDir), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_SMTP_Do(m_pObj, 8, 1, param, cbparam);
      
      
    }
    inline char* Queue(const char* lpszQueueDir) {
      void *param[1+1] = {(void*)IPW64CAST(lpszQueueDir), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SMTP_Do(m_pObj, 9, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int ResetHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 10, 0, param, cbparam);
      
      
    }
    inline int Send() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 11, 0, param, cbparam);
      
      
    }
    inline int SendToTerminalAndEmail() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 12, 0, param, cbparam);
      
      
    }
    inline int SendToTerminalOnly() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 13, 0, param, cbparam);
      
      
    }
    inline int SendToTerminalOrEmail() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 14, 0, param, cbparam);
      
      
    }
    inline int Verify(const char* lpszEmailAddress) {
      void *param[1+1] = {(void*)IPW64CAST(lpszEmailAddress), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_SMTP_Do(m_pObj, 16, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} SMTPConnectionStatusEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} SMTPEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} SMTPErrorEventParamsW;

typedef struct {
  LPWSTR Address;
  int reserved;
} SMTPExpandEventParamsW;

typedef struct {
  int Direction;
  LPWSTR Message;
  int reserved;
} SMTPPITrailEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} SMTPStartTransferEventParamsW;

typedef struct {
  int Direction;
  ns_int64 *pBytesTransferred;
  int PercentDone;
  int reserved;
} SMTPTransferEventParamsW;



class SMTPW : public SMTP {

  public: //properties
  




    inline LPWSTR GetBCc() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+3, 0, 0);
    }

    inline int SetBCc(LPWSTR lpBCc) {
      return IPWorks_SMTP_Set(m_pObj, 10000+3, 0, (void*)lpBCc, 0);
    }

    inline LPWSTR GetCc() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetCc(LPWSTR lpCc) {
      return IPWorks_SMTP_Set(m_pObj, 10000+4, 0, (void*)lpCc, 0);
    }



    inline int SetCommand(LPWSTR lpCommand) {
      return IPWorks_SMTP_Set(m_pObj, 10000+5, 0, (void*)lpCommand, 0);
    }



    inline LPWSTR GetDeliveryNotificationTo() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+7, 0, 0);
    }

    inline int SetDeliveryNotificationTo(LPWSTR lpDeliveryNotificationTo) {
      return IPWorks_SMTP_Set(m_pObj, 10000+7, 0, (void*)lpDeliveryNotificationTo, 0);
    }





    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+10, 0, 0);
    }

    inline int SetFirewallHost(LPWSTR lpFirewallHost) {
      return IPWorks_SMTP_Set(m_pObj, 10000+10, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+11, 0, 0);
    }

    inline int SetFirewallPassword(LPWSTR lpFirewallPassword) {
      return IPWorks_SMTP_Set(m_pObj, 10000+11, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+13, 0, 0);
    }

    inline int SetFirewallUser(LPWSTR lpFirewallUser) {
      return IPWorks_SMTP_Set(m_pObj, 10000+13, 0, (void*)lpFirewallUser, 0);
    }

    inline LPWSTR GetFrom() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+14, 0, 0);
    }

    inline int SetFrom(LPWSTR lpFrom) {
      return IPWorks_SMTP_Set(m_pObj, 10000+14, 0, (void*)lpFrom, 0);
    }





    inline LPWSTR GetLastReply() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+17, 0, 0);
    }



    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+18, 0, 0);
    }

    inline int SetLocalHost(LPWSTR lpLocalHost) {
      return IPWorks_SMTP_Set(m_pObj, 10000+18, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetMailServer() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+20, 0, 0);
    }

    inline int SetMailServer(LPWSTR lpMailServer) {
      return IPWorks_SMTP_Set(m_pObj, 10000+20, 0, (void*)lpMailServer, 0);
    }

    inline LPWSTR GetMessage() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+21, 0, 0);
    }

    inline int SetMessage(LPWSTR lpMessage) {
      return IPWorks_SMTP_Set(m_pObj, 10000+21, 0, (void*)lpMessage, 0);
    }
    inline int GetMessageB(char *&lpMessage, int &lenMessage) {
      lpMessage = (char*)IPWorks_SMTP_Get(m_pObj, 21, 0, &lenMessage);
      return lpMessage ? 0 : lenMessage;
    }
    inline int SetMessageB(const char *lpMessage, int lenMessage) {
      return IPWorks_SMTP_Set(m_pObj, 21, 0, (void*)lpMessage, lenMessage);
    }
    inline LPWSTR GetMessageDate() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+22, 0, 0);
    }

    inline int SetMessageDate(LPWSTR lpMessageDate) {
      return IPWorks_SMTP_Set(m_pObj, 10000+22, 0, (void*)lpMessageDate, 0);
    }



    inline LPWSTR GetMessageHeaderField(int iMessageHeaderIndex) {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+24, iMessageHeaderIndex, 0);
    }



    inline LPWSTR GetMessageHeaderValue(int iMessageHeaderIndex) {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+25, iMessageHeaderIndex, 0);
    }



    inline LPWSTR GetMessageHeadersString() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+26, 0, 0);
    }



    inline LPWSTR GetMessageId() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+27, 0, 0);
    }

    inline int SetMessageId(LPWSTR lpMessageId) {
      return IPWorks_SMTP_Set(m_pObj, 10000+27, 0, (void*)lpMessageId, 0);
    }



    inline LPWSTR GetMessageRecipientAddress(int iRecipientIndex) {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+29, iRecipientIndex, 0);
    }

    inline int SetMessageRecipientAddress(int iRecipientIndex, LPWSTR lpMessageRecipientAddress) {
      return IPWorks_SMTP_Set(m_pObj, 10000+29, iRecipientIndex, (void*)lpMessageRecipientAddress, 0);
    }

    inline LPWSTR GetMessageRecipientName(int iRecipientIndex) {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+30, iRecipientIndex, 0);
    }

    inline int SetMessageRecipientName(int iRecipientIndex, LPWSTR lpMessageRecipientName) {
      return IPWorks_SMTP_Set(m_pObj, 10000+30, iRecipientIndex, (void*)lpMessageRecipientName, 0);
    }

    inline LPWSTR GetMessageRecipientOptions(int iRecipientIndex) {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+31, iRecipientIndex, 0);
    }

    inline int SetMessageRecipientOptions(int iRecipientIndex, LPWSTR lpMessageRecipientOptions) {
      return IPWorks_SMTP_Set(m_pObj, 10000+31, iRecipientIndex, (void*)lpMessageRecipientOptions, 0);
    }



    inline LPWSTR GetMessageText() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+33, 0, 0);
    }

    inline int SetMessageText(LPWSTR lpMessageText) {
      return IPWorks_SMTP_Set(m_pObj, 10000+33, 0, (void*)lpMessageText, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+34, 0, 0);
    }

    inline int SetOtherHeaders(LPWSTR lpOtherHeaders) {
      return IPWorks_SMTP_Set(m_pObj, 10000+34, 0, (void*)lpOtherHeaders, 0);
    }

    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+35, 0, 0);
    }

    inline int SetPassword(LPWSTR lpPassword) {
      return IPWorks_SMTP_Set(m_pObj, 10000+35, 0, (void*)lpPassword, 0);
    }



    inline LPWSTR GetReadReceiptTo() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+37, 0, 0);
    }

    inline int SetReadReceiptTo(LPWSTR lpReadReceiptTo) {
      return IPWorks_SMTP_Set(m_pObj, 10000+37, 0, (void*)lpReadReceiptTo, 0);
    }

    inline LPWSTR GetReplyTo() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+38, 0, 0);
    }

    inline int SetReplyTo(LPWSTR lpReplyTo) {
      return IPWorks_SMTP_Set(m_pObj, 10000+38, 0, (void*)lpReplyTo, 0);
    }

    inline LPWSTR GetReturnPath() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+39, 0, 0);
    }

    inline int SetReturnPath(LPWSTR lpReturnPath) {
      return IPWorks_SMTP_Set(m_pObj, 10000+39, 0, (void*)lpReturnPath, 0);
    }

    inline LPWSTR GetSendTo() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+40, 0, 0);
    }

    inline int SetSendTo(LPWSTR lpSendTo) {
      return IPWorks_SMTP_Set(m_pObj, 10000+40, 0, (void*)lpSendTo, 0);
    }



    inline LPWSTR GetSubject() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+42, 0, 0);
    }

    inline int SetSubject(LPWSTR lpSubject) {
      return IPWorks_SMTP_Set(m_pObj, 10000+42, 0, (void*)lpSubject, 0);
    }



    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_SMTP_Get(m_pObj, 10000+44, 0, 0);
    }

    inline int SetUser(LPWSTR lpUser) {
      return IPWorks_SMTP_Set(m_pObj, 10000+44, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnectionStatus(SMTPConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(SMTPEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(SMTPErrorEventParamsW *e) {return 0;}
    virtual int FireExpand(SMTPExpandEventParamsW *e) {return 0;}
    virtual int FirePITrail(SMTPPITrailEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(SMTPStartTransferEventParamsW *e) {return 0;}
    virtual int FireTransfer(SMTPTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int SMTPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            SMTPConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 2: {
            SMTPEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 3: {
            SMTPErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 4: {
            SMTPExpandEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireExpand(&e);
            break;
         }
         case 5: {
            SMTPPITrailEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FirePITrail(&e);
            break;
         }
         case 6: {
            SMTPStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 7: {
            SMTPTransferEventParamsW e = {(int)IPW64CAST(param[0]), (ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnectionStatus(SMTPConnectionStatusEventParams *e) {return -10000;}
    virtual int FireEndTransfer(SMTPEndTransferEventParams *e) {return -10000;}
    virtual int FireError(SMTPErrorEventParams *e) {return -10000;}
    virtual int FireExpand(SMTPExpandEventParams *e) {return -10000;}
    virtual int FirePITrail(SMTPPITrailEventParams *e) {return -10000;}
    virtual int FireStartTransfer(SMTPStartTransferEventParams *e) {return -10000;}
    virtual int FireTransfer(SMTPTransferEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SMTP_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int Expand(LPWSTR lpszEmailAddress) {
      void *param[1+1] = {(void*)lpszEmailAddress, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_SMTP_Do(m_pObj, 10000+6, 1, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int ProcessQueue(LPWSTR lpszQueueDir) {
      void *param[1+1] = {(void*)lpszQueueDir, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_SMTP_Do(m_pObj, 10000+8, 1, param, cbparam);
      
    }
    inline LPWSTR Queue(LPWSTR lpszQueueDir) {
      void *param[1+1] = {(void*)lpszQueueDir, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_SMTP_Do(m_pObj, 10000+9, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int ResetHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 10000+10, 0, param, cbparam);
      
    }
    inline int Send() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 10000+11, 0, param, cbparam);
      
    }
    inline int SendToTerminalAndEmail() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 10000+12, 0, param, cbparam);
      
    }
    inline int SendToTerminalOnly() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 10000+13, 0, param, cbparam);
      
    }
    inline int SendToTerminalOrEmail() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_SMTP_Do(m_pObj, 10000+14, 0, param, cbparam);
      
    }
    inline int Verify(LPWSTR lpszEmailAddress) {
      void *param[1+1] = {(void*)lpszEmailAddress, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_SMTP_Do(m_pObj, 10000+16, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_SMTP_H_




