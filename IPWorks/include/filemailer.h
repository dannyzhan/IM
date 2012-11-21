/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_FILEMAILER_H_
#define _IPWORKS_FILEMAILER_H_

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


extern "C" void* IPWORKS_CALL IPWorks_FileMailer_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_FileMailer_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FileMailer_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_FileMailer_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_FileMailer_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_FileMailer_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_FileMailer_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FileMailer_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FileMailer_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_FileMailer_StaticDestroy();

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
} FileMailerConnectionStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} FileMailerEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} FileMailerErrorEventParams;

typedef struct {
  int Direction;
  const char* Message;
  int reserved;
} FileMailerPITrailEventParams;

typedef struct {
  int Direction;
  int reserved;
} FileMailerStartTransferEventParams;

typedef struct {
  int Direction;
  ns_int64 *pBytesTransferred;
  int PercentDone;
  int reserved;
} FileMailerTransferEventParams;



class FileMailer {
  
  public: //events
  
    virtual int FireConnectionStatus(FileMailerConnectionStatusEventParams *e) {return 0;}
    virtual int FireEndTransfer(FileMailerEndTransferEventParams *e) {return 0;}
    virtual int FireError(FileMailerErrorEventParams *e) {return 0;}
    virtual int FirePITrail(FileMailerPITrailEventParams *e) {return 0;}
    virtual int FireStartTransfer(FileMailerStartTransferEventParams *e) {return 0;}
    virtual int FireTransfer(FileMailerTransferEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL FileMailerEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((FileMailer*)lpObj)->FileMailerEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            FileMailerConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((FileMailer*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 2: {
            FileMailerEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((FileMailer*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 3: {
            FileMailerErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((FileMailer*)lpObj)->FireError(&e);
            break;
         }
         case 4: {
            FileMailerPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((FileMailer*)lpObj)->FirePITrail(&e);
            break;
         }
         case 5: {
            FileMailerStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((FileMailer*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 6: {
            FileMailerTransferEventParams e = {(int)IPW64CAST(param[0]), (ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = ((FileMailer*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int FileMailerEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    FileMailer(char *lpOemKey = (char*)IPWORKS_OEMKEY_41) {
      m_pObj = IPWorks_FileMailer_Create(FileMailerEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~FileMailer() {
      IPWorks_FileMailer_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_FileMailer_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_FileMailer_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_FileMailer_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline int GetAttachmentCount() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetAttachmentCount(int iAttachmentCount) {
      void* val = (void*)IPW64CAST(iAttachmentCount);
      return IPWorks_FileMailer_Set(m_pObj, 1, 0, val, 0);
    }
    inline char* GetAttachmentFile(int iAttachmentIndex) {
      void* val = IPWorks_FileMailer_Get(m_pObj, 2, iAttachmentIndex, 0);
      return (char*)val;
    }

    inline int SetAttachmentFile(int iAttachmentIndex, const char *lpAttachmentFile) {
      return IPWorks_FileMailer_Set(m_pObj, 2, iAttachmentIndex, (void*)lpAttachmentFile, 0);
    }

    inline char* GetAttachmentName(int iAttachmentIndex) {
      void* val = IPWorks_FileMailer_Get(m_pObj, 3, iAttachmentIndex, 0);
      return (char*)val;
    }

    inline int SetAttachmentName(int iAttachmentIndex, const char *lpAttachmentName) {
      return IPWorks_FileMailer_Set(m_pObj, 3, iAttachmentIndex, (void*)lpAttachmentName, 0);
    }

    inline int GetAuthMechanism() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthMechanism(int iAuthMechanism) {
      void* val = (void*)IPW64CAST(iAuthMechanism);
      return IPWorks_FileMailer_Set(m_pObj, 4, 0, val, 0);
    }
    inline char* GetBCc() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }

    inline int SetBCc(const char *lpBCc) {
      return IPWorks_FileMailer_Set(m_pObj, 5, 0, (void*)lpBCc, 0);
    }

    inline char* GetCc() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }

    inline int SetCc(const char *lpCc) {
      return IPWorks_FileMailer_Set(m_pObj, 6, 0, (void*)lpCc, 0);
    }


    inline int SetCommand(const char *lpCommand) {
      return IPWorks_FileMailer_Set(m_pObj, 7, 0, (void*)lpCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_FileMailer_Set(m_pObj, 8, 0, val, 0);
    }
    inline char* GetDeliveryNotificationTo() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 9, 0, 0);
      return (char*)val;
    }

    inline int SetDeliveryNotificationTo(const char *lpDeliveryNotificationTo) {
      return IPWorks_FileMailer_Set(m_pObj, 9, 0, (void*)lpDeliveryNotificationTo, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_FileMailer_Set(m_pObj, 10, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 11, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_FileMailer_Set(m_pObj, 11, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_FileMailer_Set(m_pObj, 12, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_FileMailer_Set(m_pObj, 13, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 14, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_FileMailer_Set(m_pObj, 14, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_FileMailer_Set(m_pObj, 15, 0, (void*)lpFirewallUser, 0);
    }

    inline char* GetFrom() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetFrom(const char *lpFrom) {
      return IPWorks_FileMailer_Set(m_pObj, 16, 0, (void*)lpFrom, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 17, 0, 0);
      return (int)(long)val;
    }

    inline int GetImportance() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 18, 0, 0);
      return (int)(long)val;
    }
    inline int SetImportance(int iImportance) {
      void* val = (void*)IPW64CAST(iImportance);
      return IPWorks_FileMailer_Set(m_pObj, 18, 0, val, 0);
    }
    inline char* GetLastReply() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }


    inline char* GetLocalHost() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_FileMailer_Set(m_pObj, 20, 0, (void*)lpLocalHost, 0);
    }

    inline int GetMailPort() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 21, 0, 0);
      return (int)(long)val;
    }
    inline int SetMailPort(int lMailPort) {
      void* val = (void*)IPW64CAST(lMailPort);
      return IPWorks_FileMailer_Set(m_pObj, 21, 0, val, 0);
    }
    inline char* GetMailServer() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }

    inline int SetMailServer(const char *lpMailServer) {
      return IPWorks_FileMailer_Set(m_pObj, 22, 0, (void*)lpMailServer, 0);
    }

    inline char* GetMessageDate() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 23, 0, 0);
      return (char*)val;
    }

    inline int SetMessageDate(const char *lpMessageDate) {
      return IPWorks_FileMailer_Set(m_pObj, 23, 0, (void*)lpMessageDate, 0);
    }

    inline char* GetMessageId() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 24, 0, 0);
      return (char*)val;
    }

    inline int SetMessageId(const char *lpMessageId) {
      return IPWorks_FileMailer_Set(m_pObj, 24, 0, (void*)lpMessageId, 0);
    }

    inline int GetMessageRecipientCount() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 25, 0, 0);
      return (int)(long)val;
    }
    inline int SetMessageRecipientCount(int iMessageRecipientCount) {
      void* val = (void*)IPW64CAST(iMessageRecipientCount);
      return IPWorks_FileMailer_Set(m_pObj, 25, 0, val, 0);
    }
    inline char* GetMessageRecipientAddress(int iRecipientIndex) {
      void* val = IPWorks_FileMailer_Get(m_pObj, 26, iRecipientIndex, 0);
      return (char*)val;
    }

    inline int SetMessageRecipientAddress(int iRecipientIndex, const char *lpMessageRecipientAddress) {
      return IPWorks_FileMailer_Set(m_pObj, 26, iRecipientIndex, (void*)lpMessageRecipientAddress, 0);
    }

    inline char* GetMessageRecipientName(int iRecipientIndex) {
      void* val = IPWorks_FileMailer_Get(m_pObj, 27, iRecipientIndex, 0);
      return (char*)val;
    }

    inline int SetMessageRecipientName(int iRecipientIndex, const char *lpMessageRecipientName) {
      return IPWorks_FileMailer_Set(m_pObj, 27, iRecipientIndex, (void*)lpMessageRecipientName, 0);
    }

    inline char* GetMessageRecipientOptions(int iRecipientIndex) {
      void* val = IPWorks_FileMailer_Get(m_pObj, 28, iRecipientIndex, 0);
      return (char*)val;
    }

    inline int SetMessageRecipientOptions(int iRecipientIndex, const char *lpMessageRecipientOptions) {
      return IPWorks_FileMailer_Set(m_pObj, 28, iRecipientIndex, (void*)lpMessageRecipientOptions, 0);
    }

    inline int GetMessageRecipientType(int iRecipientIndex) {
      void* val = IPWorks_FileMailer_Get(m_pObj, 29, iRecipientIndex, 0);
      return (int)(long)val;
    }
    inline int SetMessageRecipientType(int iRecipientIndex, int iMessageRecipientType) {
      void* val = (void*)IPW64CAST(iMessageRecipientType);
      return IPWorks_FileMailer_Set(m_pObj, 29, iRecipientIndex, val, 0);
    }
    inline char* GetMessageText() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 30, 0, 0);
      return (char*)val;
    }

    inline int SetMessageText(const char *lpMessageText) {
      return IPWorks_FileMailer_Set(m_pObj, 30, 0, (void*)lpMessageText, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 31, 0, 0);
      return (char*)val;
    }

    inline int SetOtherHeaders(const char *lpOtherHeaders) {
      return IPWorks_FileMailer_Set(m_pObj, 31, 0, (void*)lpOtherHeaders, 0);
    }

    inline char* GetPassword() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 32, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_FileMailer_Set(m_pObj, 32, 0, (void*)lpPassword, 0);
    }

    inline int GetPriority() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 33, 0, 0);
      return (int)(long)val;
    }
    inline int SetPriority(int iPriority) {
      void* val = (void*)IPW64CAST(iPriority);
      return IPWorks_FileMailer_Set(m_pObj, 33, 0, val, 0);
    }
    inline char* GetReadReceiptTo() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 34, 0, 0);
      return (char*)val;
    }

    inline int SetReadReceiptTo(const char *lpReadReceiptTo) {
      return IPWorks_FileMailer_Set(m_pObj, 34, 0, (void*)lpReadReceiptTo, 0);
    }

    inline char* GetReplyTo() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 35, 0, 0);
      return (char*)val;
    }

    inline int SetReplyTo(const char *lpReplyTo) {
      return IPWorks_FileMailer_Set(m_pObj, 35, 0, (void*)lpReplyTo, 0);
    }

    inline char* GetSendTo() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 36, 0, 0);
      return (char*)val;
    }

    inline int SetSendTo(const char *lpSendTo) {
      return IPWorks_FileMailer_Set(m_pObj, 36, 0, (void*)lpSendTo, 0);
    }

    inline int GetSensitivity() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 37, 0, 0);
      return (int)(long)val;
    }
    inline int SetSensitivity(int iSensitivity) {
      void* val = (void*)IPW64CAST(iSensitivity);
      return IPWorks_FileMailer_Set(m_pObj, 37, 0, val, 0);
    }
    inline char* GetSubject() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 38, 0, 0);
      return (char*)val;
    }

    inline int SetSubject(const char *lpSubject) {
      return IPWorks_FileMailer_Set(m_pObj, 38, 0, (void*)lpSubject, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 39, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_FileMailer_Set(m_pObj, 39, 0, val, 0);
    }
    inline char* GetUser() {
      void* val = IPWorks_FileMailer_Get(m_pObj, 40, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_FileMailer_Set(m_pObj, 40, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline int AddAttachment(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FileMailer_Do(m_pObj, 2, 1, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_FileMailer_Do(m_pObj, 3, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FileMailer_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FileMailer_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FileMailer_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FileMailer_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int ProcessQueue(const char* lpszQueueDir) {
      void *param[1+1] = {(void*)IPW64CAST(lpszQueueDir), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FileMailer_Do(m_pObj, 8, 1, param, cbparam);
      
      
    }
    inline char* Queue(const char* lpszQueueDir) {
      void *param[1+1] = {(void*)IPW64CAST(lpszQueueDir), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_FileMailer_Do(m_pObj, 9, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int ResetHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FileMailer_Do(m_pObj, 10, 0, param, cbparam);
      
      
    }
    inline int Send() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FileMailer_Do(m_pObj, 11, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} FileMailerConnectionStatusEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} FileMailerEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} FileMailerErrorEventParamsW;

typedef struct {
  int Direction;
  LPWSTR Message;
  int reserved;
} FileMailerPITrailEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} FileMailerStartTransferEventParamsW;

typedef struct {
  int Direction;
  ns_int64 *pBytesTransferred;
  int PercentDone;
  int reserved;
} FileMailerTransferEventParamsW;



class FileMailerW : public FileMailer {

  public: //properties
  


    inline LPWSTR GetAttachmentFile(int iAttachmentIndex) {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+2, iAttachmentIndex, 0);
    }

    inline int SetAttachmentFile(int iAttachmentIndex, LPWSTR lpAttachmentFile) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+2, iAttachmentIndex, (void*)lpAttachmentFile, 0);
    }

    inline LPWSTR GetAttachmentName(int iAttachmentIndex) {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+3, iAttachmentIndex, 0);
    }

    inline int SetAttachmentName(int iAttachmentIndex, LPWSTR lpAttachmentName) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+3, iAttachmentIndex, (void*)lpAttachmentName, 0);
    }



    inline LPWSTR GetBCc() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetBCc(LPWSTR lpBCc) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+5, 0, (void*)lpBCc, 0);
    }

    inline LPWSTR GetCc() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetCc(LPWSTR lpCc) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+6, 0, (void*)lpCc, 0);
    }



    inline int SetCommand(LPWSTR lpCommand) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+7, 0, (void*)lpCommand, 0);
    }



    inline LPWSTR GetDeliveryNotificationTo() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+9, 0, 0);
    }

    inline int SetDeliveryNotificationTo(LPWSTR lpDeliveryNotificationTo) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+9, 0, (void*)lpDeliveryNotificationTo, 0);
    }





    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+12, 0, 0);
    }

    inline int SetFirewallHost(LPWSTR lpFirewallHost) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+12, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+13, 0, 0);
    }

    inline int SetFirewallPassword(LPWSTR lpFirewallPassword) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+13, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetFirewallUser(LPWSTR lpFirewallUser) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+15, 0, (void*)lpFirewallUser, 0);
    }

    inline LPWSTR GetFrom() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetFrom(LPWSTR lpFrom) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+16, 0, (void*)lpFrom, 0);
    }





    inline LPWSTR GetLastReply() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+19, 0, 0);
    }



    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+20, 0, 0);
    }

    inline int SetLocalHost(LPWSTR lpLocalHost) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+20, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetMailServer() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+22, 0, 0);
    }

    inline int SetMailServer(LPWSTR lpMailServer) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+22, 0, (void*)lpMailServer, 0);
    }

    inline LPWSTR GetMessageDate() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+23, 0, 0);
    }

    inline int SetMessageDate(LPWSTR lpMessageDate) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+23, 0, (void*)lpMessageDate, 0);
    }

    inline LPWSTR GetMessageId() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+24, 0, 0);
    }

    inline int SetMessageId(LPWSTR lpMessageId) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+24, 0, (void*)lpMessageId, 0);
    }



    inline LPWSTR GetMessageRecipientAddress(int iRecipientIndex) {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+26, iRecipientIndex, 0);
    }

    inline int SetMessageRecipientAddress(int iRecipientIndex, LPWSTR lpMessageRecipientAddress) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+26, iRecipientIndex, (void*)lpMessageRecipientAddress, 0);
    }

    inline LPWSTR GetMessageRecipientName(int iRecipientIndex) {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+27, iRecipientIndex, 0);
    }

    inline int SetMessageRecipientName(int iRecipientIndex, LPWSTR lpMessageRecipientName) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+27, iRecipientIndex, (void*)lpMessageRecipientName, 0);
    }

    inline LPWSTR GetMessageRecipientOptions(int iRecipientIndex) {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+28, iRecipientIndex, 0);
    }

    inline int SetMessageRecipientOptions(int iRecipientIndex, LPWSTR lpMessageRecipientOptions) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+28, iRecipientIndex, (void*)lpMessageRecipientOptions, 0);
    }



    inline LPWSTR GetMessageText() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+30, 0, 0);
    }

    inline int SetMessageText(LPWSTR lpMessageText) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+30, 0, (void*)lpMessageText, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+31, 0, 0);
    }

    inline int SetOtherHeaders(LPWSTR lpOtherHeaders) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+31, 0, (void*)lpOtherHeaders, 0);
    }

    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+32, 0, 0);
    }

    inline int SetPassword(LPWSTR lpPassword) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+32, 0, (void*)lpPassword, 0);
    }



    inline LPWSTR GetReadReceiptTo() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+34, 0, 0);
    }

    inline int SetReadReceiptTo(LPWSTR lpReadReceiptTo) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+34, 0, (void*)lpReadReceiptTo, 0);
    }

    inline LPWSTR GetReplyTo() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+35, 0, 0);
    }

    inline int SetReplyTo(LPWSTR lpReplyTo) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+35, 0, (void*)lpReplyTo, 0);
    }

    inline LPWSTR GetSendTo() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+36, 0, 0);
    }

    inline int SetSendTo(LPWSTR lpSendTo) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+36, 0, (void*)lpSendTo, 0);
    }



    inline LPWSTR GetSubject() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+38, 0, 0);
    }

    inline int SetSubject(LPWSTR lpSubject) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+38, 0, (void*)lpSubject, 0);
    }



    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_FileMailer_Get(m_pObj, 10000+40, 0, 0);
    }

    inline int SetUser(LPWSTR lpUser) {
      return IPWorks_FileMailer_Set(m_pObj, 10000+40, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnectionStatus(FileMailerConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(FileMailerEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(FileMailerErrorEventParamsW *e) {return 0;}
    virtual int FirePITrail(FileMailerPITrailEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(FileMailerStartTransferEventParamsW *e) {return 0;}
    virtual int FireTransfer(FileMailerTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int FileMailerEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            FileMailerConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 2: {
            FileMailerEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 3: {
            FileMailerErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 4: {
            FileMailerPITrailEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FirePITrail(&e);
            break;
         }
         case 5: {
            FileMailerStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 6: {
            FileMailerTransferEventParamsW e = {(int)IPW64CAST(param[0]), (ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnectionStatus(FileMailerConnectionStatusEventParams *e) {return -10000;}
    virtual int FireEndTransfer(FileMailerEndTransferEventParams *e) {return -10000;}
    virtual int FireError(FileMailerErrorEventParams *e) {return -10000;}
    virtual int FirePITrail(FileMailerPITrailEventParams *e) {return -10000;}
    virtual int FireStartTransfer(FileMailerStartTransferEventParams *e) {return -10000;}
    virtual int FireTransfer(FileMailerTransferEventParams *e) {return -10000;}

  public: //methods

    inline int AddAttachment(LPWSTR lpszFileName) {
      void *param[1+1] = {(void*)lpszFileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FileMailer_Do(m_pObj, 10000+2, 1, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_FileMailer_Do(m_pObj, 10000+3, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FileMailer_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FileMailer_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FileMailer_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FileMailer_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int ProcessQueue(LPWSTR lpszQueueDir) {
      void *param[1+1] = {(void*)lpszQueueDir, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FileMailer_Do(m_pObj, 10000+8, 1, param, cbparam);
      
    }
    inline LPWSTR Queue(LPWSTR lpszQueueDir) {
      void *param[1+1] = {(void*)lpszQueueDir, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_FileMailer_Do(m_pObj, 10000+9, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int ResetHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FileMailer_Do(m_pObj, 10000+10, 0, param, cbparam);
      
    }
    inline int Send() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FileMailer_Do(m_pObj, 10000+11, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_FILEMAILER_H_




