/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_NNTP_H_
#define _IPWORKS_NNTP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3


extern "C" void* IPWORKS_CALL IPWorks_NNTP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_NNTP_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_NNTP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_NNTP_StaticDestroy();

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
} NNTPConnectionStatusEventParams;

typedef struct {
  int Direction;
  int reserved;
} NNTPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} NNTPErrorEventParams;

typedef struct {
  const char* Group;
  int FirstArticle;
  int LastArticle;
  int CanPost;
  int reserved;
} NNTPGroupListEventParams;

typedef struct {
  int ArticleNumber;
  const char* Subject;
  const char* From;
  const char* ArticleDate;
  const char* MessageId;
  const char* References;
  int ArticleSize;
  int ArticleLines;
  const char* OtherHeaders;
  int reserved;
} NNTPGroupOverviewEventParams;

typedef struct {
  int ArticleNumber;
  const char* Header;
  int reserved;
} NNTPGroupSearchEventParams;

typedef struct {
  const char* Field;
  const char* Value;
  int reserved;
} NNTPHeaderEventParams;

typedef struct {
  int Direction;
  const char* Message;
  int reserved;
} NNTPPITrailEventParams;

typedef struct {
  int Direction;
  int reserved;
} NNTPStartTransferEventParams;

typedef struct {
  int Direction;
  ns_int64 *pBytesTransferred;
  int PercentDone;
  const char* Text;
  int EOL;
  int lenText;
  int reserved;
} NNTPTransferEventParams;



class NNTP {
  
  public: //events
  
    virtual int FireConnectionStatus(NNTPConnectionStatusEventParams *e) {return 0;}
    virtual int FireEndTransfer(NNTPEndTransferEventParams *e) {return 0;}
    virtual int FireError(NNTPErrorEventParams *e) {return 0;}
    virtual int FireGroupList(NNTPGroupListEventParams *e) {return 0;}
    virtual int FireGroupOverview(NNTPGroupOverviewEventParams *e) {return 0;}
    virtual int FireGroupSearch(NNTPGroupSearchEventParams *e) {return 0;}
    virtual int FireHeader(NNTPHeaderEventParams *e) {return 0;}
    virtual int FirePITrail(NNTPPITrailEventParams *e) {return 0;}
    virtual int FireStartTransfer(NNTPStartTransferEventParams *e) {return 0;}
    virtual int FireTransfer(NNTPTransferEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL NNTPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((NNTP*)lpObj)->NNTPEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            NNTPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((NNTP*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 2: {
            NNTPEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((NNTP*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 3: {
            NNTPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((NNTP*)lpObj)->FireError(&e);
            break;
         }
         case 4: {
            NNTPGroupListEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = ((NNTP*)lpObj)->FireGroupList(&e);
            break;
         }
         case 5: {
            NNTPGroupOverviewEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (int)IPW64CAST(param[6]), (int)IPW64CAST(param[7]), (char*)IPW64CAST(param[8]),  0};
            ret_code = ((NNTP*)lpObj)->FireGroupOverview(&e);
            break;
         }
         case 6: {
            NNTPGroupSearchEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((NNTP*)lpObj)->FireGroupSearch(&e);
            break;
         }
         case 7: {
            NNTPHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((NNTP*)lpObj)->FireHeader(&e);
            break;
         }
         case 8: {
            NNTPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((NNTP*)lpObj)->FirePITrail(&e);
            break;
         }
         case 9: {
            NNTPStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((NNTP*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 10: {
            NNTPTransferEventParams e = {(int)IPW64CAST(param[0]), (ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = ((NNTP*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int NNTPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    NNTP(char *lpOemKey = (char*)IPWORKS_OEMKEY_25) {
      m_pObj = IPWorks_NNTP_Create(NNTPEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~NNTP() {
      IPWorks_NNTP_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_NNTP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_NNTP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_NNTP_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline int GetArticleCount() {
      void* val = IPWorks_NNTP_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }

    inline char* GetArticleDate() {
      void* val = IPWorks_NNTP_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }


    inline char* GetArticleFrom() {
      void* val = IPWorks_NNTP_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }

    inline int SetArticleFrom(const char *lpArticleFrom) {
      return IPWorks_NNTP_Set(m_pObj, 3, 0, (void*)lpArticleFrom, 0);
    }

    inline char* GetArticleHeaders() {
      void* val = IPWorks_NNTP_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }


    inline char* GetArticleId() {
      void* val = IPWorks_NNTP_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }


    inline int GetGroupOverviewCount() {
      void* val = IPWorks_NNTP_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }

    inline int GetGroupOverviewArticleLines(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 7, iGroupOverviewIndex, 0);
      return (int)(long)val;
    }

    inline int GetGroupOverviewArticleNumber(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 8, iGroupOverviewIndex, 0);
      return (int)(long)val;
    }

    inline int GetGroupOverviewArticleSize(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 9, iGroupOverviewIndex, 0);
      return (int)(long)val;
    }

    inline char* GetGroupOverviewDate(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 10, iGroupOverviewIndex, 0);
      return (char*)val;
    }


    inline char* GetGroupOverviewFrom(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 11, iGroupOverviewIndex, 0);
      return (char*)val;
    }


    inline char* GetGroupOverviewMessageId(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 12, iGroupOverviewIndex, 0);
      return (char*)val;
    }


    inline char* GetGroupOverviewOtherHeaders(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 13, iGroupOverviewIndex, 0);
      return (char*)val;
    }


    inline char* GetGroupOverviewReferences(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 14, iGroupOverviewIndex, 0);
      return (char*)val;
    }


    inline char* GetGroupOverviewSubject(int iGroupOverviewIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 15, iGroupOverviewIndex, 0);
      return (char*)val;
    }


    inline char* GetArticleReferences() {
      void* val = IPWorks_NNTP_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetArticleReferences(const char *lpArticleReferences) {
      return IPWorks_NNTP_Set(m_pObj, 16, 0, (void*)lpArticleReferences, 0);
    }

    inline char* GetArticleReplyTo() {
      void* val = IPWorks_NNTP_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }

    inline int SetArticleReplyTo(const char *lpArticleReplyTo) {
      return IPWorks_NNTP_Set(m_pObj, 17, 0, (void*)lpArticleReplyTo, 0);
    }

    inline char* GetArticleSubject() {
      void* val = IPWorks_NNTP_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }

    inline int SetArticleSubject(const char *lpArticleSubject) {
      return IPWorks_NNTP_Set(m_pObj, 18, 0, (void*)lpArticleSubject, 0);
    }

    inline char* GetArticleText() {
      void* val = IPWorks_NNTP_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }

    inline int SetArticleText(const char *lpArticleText) {
      return IPWorks_NNTP_Set(m_pObj, 19, 0, (void*)lpArticleText, 0);
    }

    inline char* GetAttachedFile() {
      void* val = IPWorks_NNTP_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }

    inline int SetAttachedFile(const char *lpAttachedFile) {
      return IPWorks_NNTP_Set(m_pObj, 20, 0, (void*)lpAttachedFile, 0);
    }

    inline char* GetCheckDate() {
      void* val = IPWorks_NNTP_Get(m_pObj, 21, 0, 0);
      return (char*)val;
    }

    inline int SetCheckDate(const char *lpCheckDate) {
      return IPWorks_NNTP_Set(m_pObj, 21, 0, (void*)lpCheckDate, 0);
    }


    inline int SetCommand(const char *lpCommand) {
      return IPWorks_NNTP_Set(m_pObj, 22, 0, (void*)lpCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_NNTP_Get(m_pObj, 23, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_NNTP_Set(m_pObj, 23, 0, val, 0);
    }
    inline char* GetCurrentArticle() {
      void* val = IPWorks_NNTP_Get(m_pObj, 24, 0, 0);
      return (char*)val;
    }

    inline int SetCurrentArticle(const char *lpCurrentArticle) {
      return IPWorks_NNTP_Set(m_pObj, 24, 0, (void*)lpCurrentArticle, 0);
    }

    inline char* GetCurrentGroup() {
      void* val = IPWorks_NNTP_Get(m_pObj, 25, 0, 0);
      return (char*)val;
    }

    inline int SetCurrentGroup(const char *lpCurrentGroup) {
      return IPWorks_NNTP_Set(m_pObj, 25, 0, (void*)lpCurrentGroup, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_NNTP_Get(m_pObj, 26, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_NNTP_Set(m_pObj, 26, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_NNTP_Get(m_pObj, 27, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_NNTP_Set(m_pObj, 27, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_NNTP_Get(m_pObj, 28, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_NNTP_Set(m_pObj, 28, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_NNTP_Get(m_pObj, 29, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_NNTP_Set(m_pObj, 29, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_NNTP_Get(m_pObj, 30, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_NNTP_Set(m_pObj, 30, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_NNTP_Get(m_pObj, 31, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_NNTP_Set(m_pObj, 31, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetFirstArticle() {
      void* val = IPWorks_NNTP_Get(m_pObj, 32, 0, 0);
      return (int)(long)val;
    }

    inline int GetGroupListCount() {
      void* val = IPWorks_NNTP_Get(m_pObj, 33, 0, 0);
      return (int)(long)val;
    }

    inline int GetGroupListCanPost(int iGroupListIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 34, iGroupListIndex, 0);
      return (int)(long)val;
    }

    inline int GetGroupListFirstArticle(int iGroupListIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 35, iGroupListIndex, 0);
      return (int)(long)val;
    }

    inline char* GetGroupListGroup(int iGroupListIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 36, iGroupListIndex, 0);
      return (char*)val;
    }


    inline int GetGroupListLastArticle(int iGroupListIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 37, iGroupListIndex, 0);
      return (int)(long)val;
    }

    inline int GetIdle() {
      void* val = IPWorks_NNTP_Get(m_pObj, 38, 0, 0);
      return (int)(long)val;
    }

    inline int GetLastArticle() {
      void* val = IPWorks_NNTP_Get(m_pObj, 39, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLastReply() {
      void* val = IPWorks_NNTP_Get(m_pObj, 40, 0, 0);
      return (char*)val;
    }


    inline char* GetLocalFile() {
      void* val = IPWorks_NNTP_Get(m_pObj, 41, 0, 0);
      return (char*)val;
    }

    inline int SetLocalFile(const char *lpLocalFile) {
      return IPWorks_NNTP_Set(m_pObj, 41, 0, (void*)lpLocalFile, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_NNTP_Get(m_pObj, 42, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_NNTP_Set(m_pObj, 42, 0, (void*)lpLocalHost, 0);
    }

    inline int GetMaxLines() {
      void* val = IPWorks_NNTP_Get(m_pObj, 43, 0, 0);
      return (int)(long)val;
    }
    inline int SetMaxLines(int lMaxLines) {
      void* val = (void*)IPW64CAST(lMaxLines);
      return IPWorks_NNTP_Set(m_pObj, 43, 0, val, 0);
    }
    inline char* GetNewsgroups() {
      void* val = IPWorks_NNTP_Get(m_pObj, 44, 0, 0);
      return (char*)val;
    }

    inline int SetNewsgroups(const char *lpNewsgroups) {
      return IPWorks_NNTP_Set(m_pObj, 44, 0, (void*)lpNewsgroups, 0);
    }

    inline int GetNewsPort() {
      void* val = IPWorks_NNTP_Get(m_pObj, 45, 0, 0);
      return (int)(long)val;
    }
    inline int SetNewsPort(int lNewsPort) {
      void* val = (void*)IPW64CAST(lNewsPort);
      return IPWorks_NNTP_Set(m_pObj, 45, 0, val, 0);
    }
    inline char* GetNewsServer() {
      void* val = IPWorks_NNTP_Get(m_pObj, 46, 0, 0);
      return (char*)val;
    }

    inline int SetNewsServer(const char *lpNewsServer) {
      return IPWorks_NNTP_Set(m_pObj, 46, 0, (void*)lpNewsServer, 0);
    }

    inline char* GetOrganization() {
      void* val = IPWorks_NNTP_Get(m_pObj, 47, 0, 0);
      return (char*)val;
    }

    inline int SetOrganization(const char *lpOrganization) {
      return IPWorks_NNTP_Set(m_pObj, 47, 0, (void*)lpOrganization, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_NNTP_Get(m_pObj, 48, 0, 0);
      return (char*)val;
    }

    inline int SetOtherHeaders(const char *lpOtherHeaders) {
      return IPWorks_NNTP_Set(m_pObj, 48, 0, (void*)lpOtherHeaders, 0);
    }

    inline char* GetOverviewRange() {
      void* val = IPWorks_NNTP_Get(m_pObj, 49, 0, 0);
      return (char*)val;
    }

    inline int SetOverviewRange(const char *lpOverviewRange) {
      return IPWorks_NNTP_Set(m_pObj, 49, 0, (void*)lpOverviewRange, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_NNTP_Get(m_pObj, 50, 0, 0);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 51, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_NNTP_Get(m_pObj, 52, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetPassword() {
      void* val = IPWorks_NNTP_Get(m_pObj, 53, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_NNTP_Set(m_pObj, 53, 0, (void*)lpPassword, 0);
    }

    inline char* GetSearchHeader() {
      void* val = IPWorks_NNTP_Get(m_pObj, 54, 0, 0);
      return (char*)val;
    }

    inline int SetSearchHeader(const char *lpSearchHeader) {
      return IPWorks_NNTP_Set(m_pObj, 54, 0, (void*)lpSearchHeader, 0);
    }

    inline char* GetSearchPattern() {
      void* val = IPWorks_NNTP_Get(m_pObj, 55, 0, 0);
      return (char*)val;
    }

    inline int SetSearchPattern(const char *lpSearchPattern) {
      return IPWorks_NNTP_Set(m_pObj, 55, 0, (void*)lpSearchPattern, 0);
    }

    inline char* GetSearchRange() {
      void* val = IPWorks_NNTP_Get(m_pObj, 56, 0, 0);
      return (char*)val;
    }

    inline int SetSearchRange(const char *lpSearchRange) {
      return IPWorks_NNTP_Set(m_pObj, 56, 0, (void*)lpSearchRange, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_NNTP_Get(m_pObj, 57, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_NNTP_Set(m_pObj, 57, 0, val, 0);
    }
    inline char* GetUser() {
      void* val = IPWorks_NNTP_Get(m_pObj, 58, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_NNTP_Set(m_pObj, 58, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NNTP_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int FetchArticle() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int FetchArticleBody() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int FetchArticleHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }
    inline int GroupOverview() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int GroupSearch() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 11, 0, param, cbparam);
      
      
    }
    inline int ListGroups() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 12, 0, param, cbparam);
      
      
    }
    inline int ListNewGroups() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 13, 0, param, cbparam);
      
      
    }
    inline char* LocalizeDate(const char* lpszDateTime) {
      void *param[1+1] = {(void*)IPW64CAST(lpszDateTime), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NNTP_Do(m_pObj, 14, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int PostArticle() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 15, 0, param, cbparam);
      
      
    }
    inline int ResetHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 16, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} NNTPConnectionStatusEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} NNTPEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} NNTPErrorEventParamsW;

typedef struct {
  LPWSTR Group;
  int FirstArticle;
  int LastArticle;
  int CanPost;
  int reserved;
} NNTPGroupListEventParamsW;

typedef struct {
  int ArticleNumber;
  LPWSTR Subject;
  LPWSTR From;
  LPWSTR ArticleDate;
  LPWSTR MessageId;
  LPWSTR References;
  int ArticleSize;
  int ArticleLines;
  LPWSTR OtherHeaders;
  int reserved;
} NNTPGroupOverviewEventParamsW;

typedef struct {
  int ArticleNumber;
  LPWSTR Header;
  int reserved;
} NNTPGroupSearchEventParamsW;

typedef struct {
  LPWSTR Field;
  LPWSTR Value;
  int reserved;
} NNTPHeaderEventParamsW;

typedef struct {
  int Direction;
  LPWSTR Message;
  int reserved;
} NNTPPITrailEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} NNTPStartTransferEventParamsW;

typedef struct {
  int Direction;
  ns_int64 *pBytesTransferred;
  int PercentDone;
  LPWSTR Text;
  int EOL;
  int lenText;
  int reserved;
} NNTPTransferEventParamsW;



class NNTPW : public NNTP {

  public: //properties
  


    inline LPWSTR GetArticleDate() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+2, 0, 0);
    }



    inline LPWSTR GetArticleFrom() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+3, 0, 0);
    }

    inline int SetArticleFrom(LPWSTR lpArticleFrom) {
      return IPWorks_NNTP_Set(m_pObj, 10000+3, 0, (void*)lpArticleFrom, 0);
    }

    inline LPWSTR GetArticleHeaders() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+4, 0, 0);
    }



    inline LPWSTR GetArticleId() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+5, 0, 0);
    }











    inline LPWSTR GetGroupOverviewDate(int iGroupOverviewIndex) {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+10, iGroupOverviewIndex, 0);
    }



    inline LPWSTR GetGroupOverviewFrom(int iGroupOverviewIndex) {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+11, iGroupOverviewIndex, 0);
    }



    inline LPWSTR GetGroupOverviewMessageId(int iGroupOverviewIndex) {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+12, iGroupOverviewIndex, 0);
    }



    inline LPWSTR GetGroupOverviewOtherHeaders(int iGroupOverviewIndex) {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+13, iGroupOverviewIndex, 0);
    }



    inline LPWSTR GetGroupOverviewReferences(int iGroupOverviewIndex) {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+14, iGroupOverviewIndex, 0);
    }



    inline LPWSTR GetGroupOverviewSubject(int iGroupOverviewIndex) {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+15, iGroupOverviewIndex, 0);
    }



    inline LPWSTR GetArticleReferences() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetArticleReferences(LPWSTR lpArticleReferences) {
      return IPWorks_NNTP_Set(m_pObj, 10000+16, 0, (void*)lpArticleReferences, 0);
    }

    inline LPWSTR GetArticleReplyTo() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetArticleReplyTo(LPWSTR lpArticleReplyTo) {
      return IPWorks_NNTP_Set(m_pObj, 10000+17, 0, (void*)lpArticleReplyTo, 0);
    }

    inline LPWSTR GetArticleSubject() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+18, 0, 0);
    }

    inline int SetArticleSubject(LPWSTR lpArticleSubject) {
      return IPWorks_NNTP_Set(m_pObj, 10000+18, 0, (void*)lpArticleSubject, 0);
    }

    inline LPWSTR GetArticleText() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+19, 0, 0);
    }

    inline int SetArticleText(LPWSTR lpArticleText) {
      return IPWorks_NNTP_Set(m_pObj, 10000+19, 0, (void*)lpArticleText, 0);
    }

    inline LPWSTR GetAttachedFile() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+20, 0, 0);
    }

    inline int SetAttachedFile(LPWSTR lpAttachedFile) {
      return IPWorks_NNTP_Set(m_pObj, 10000+20, 0, (void*)lpAttachedFile, 0);
    }

    inline LPWSTR GetCheckDate() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+21, 0, 0);
    }

    inline int SetCheckDate(LPWSTR lpCheckDate) {
      return IPWorks_NNTP_Set(m_pObj, 10000+21, 0, (void*)lpCheckDate, 0);
    }



    inline int SetCommand(LPWSTR lpCommand) {
      return IPWorks_NNTP_Set(m_pObj, 10000+22, 0, (void*)lpCommand, 0);
    }



    inline LPWSTR GetCurrentArticle() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+24, 0, 0);
    }

    inline int SetCurrentArticle(LPWSTR lpCurrentArticle) {
      return IPWorks_NNTP_Set(m_pObj, 10000+24, 0, (void*)lpCurrentArticle, 0);
    }

    inline LPWSTR GetCurrentGroup() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+25, 0, 0);
    }

    inline int SetCurrentGroup(LPWSTR lpCurrentGroup) {
      return IPWorks_NNTP_Set(m_pObj, 10000+25, 0, (void*)lpCurrentGroup, 0);
    }





    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+28, 0, 0);
    }

    inline int SetFirewallHost(LPWSTR lpFirewallHost) {
      return IPWorks_NNTP_Set(m_pObj, 10000+28, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+29, 0, 0);
    }

    inline int SetFirewallPassword(LPWSTR lpFirewallPassword) {
      return IPWorks_NNTP_Set(m_pObj, 10000+29, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+31, 0, 0);
    }

    inline int SetFirewallUser(LPWSTR lpFirewallUser) {
      return IPWorks_NNTP_Set(m_pObj, 10000+31, 0, (void*)lpFirewallUser, 0);
    }









    inline LPWSTR GetGroupListGroup(int iGroupListIndex) {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+36, iGroupListIndex, 0);
    }









    inline LPWSTR GetLastReply() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+40, 0, 0);
    }



    inline LPWSTR GetLocalFile() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+10000+41, 0, 0);
    }

    inline int SetLocalFile(LPWSTR lpLocalFile) {
      return IPWorks_NNTP_Set(m_pObj, 10000+10000+41, 0, (void*)lpLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+42, 0, 0);
    }

    inline int SetLocalHost(LPWSTR lpLocalHost) {
      return IPWorks_NNTP_Set(m_pObj, 10000+42, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetNewsgroups() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+44, 0, 0);
    }

    inline int SetNewsgroups(LPWSTR lpNewsgroups) {
      return IPWorks_NNTP_Set(m_pObj, 10000+44, 0, (void*)lpNewsgroups, 0);
    }



    inline LPWSTR GetNewsServer() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+46, 0, 0);
    }

    inline int SetNewsServer(LPWSTR lpNewsServer) {
      return IPWorks_NNTP_Set(m_pObj, 10000+46, 0, (void*)lpNewsServer, 0);
    }

    inline LPWSTR GetOrganization() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+47, 0, 0);
    }

    inline int SetOrganization(LPWSTR lpOrganization) {
      return IPWorks_NNTP_Set(m_pObj, 10000+47, 0, (void*)lpOrganization, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+48, 0, 0);
    }

    inline int SetOtherHeaders(LPWSTR lpOtherHeaders) {
      return IPWorks_NNTP_Set(m_pObj, 10000+48, 0, (void*)lpOtherHeaders, 0);
    }

    inline LPWSTR GetOverviewRange() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+49, 0, 0);
    }

    inline int SetOverviewRange(LPWSTR lpOverviewRange) {
      return IPWorks_NNTP_Set(m_pObj, 10000+49, 0, (void*)lpOverviewRange, 0);
    }



    inline LPWSTR GetParsedHeaderField(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+51, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetParsedHeaderValue(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+52, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+53, 0, 0);
    }

    inline int SetPassword(LPWSTR lpPassword) {
      return IPWorks_NNTP_Set(m_pObj, 10000+53, 0, (void*)lpPassword, 0);
    }

    inline LPWSTR GetSearchHeader() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+54, 0, 0);
    }

    inline int SetSearchHeader(LPWSTR lpSearchHeader) {
      return IPWorks_NNTP_Set(m_pObj, 10000+54, 0, (void*)lpSearchHeader, 0);
    }

    inline LPWSTR GetSearchPattern() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+55, 0, 0);
    }

    inline int SetSearchPattern(LPWSTR lpSearchPattern) {
      return IPWorks_NNTP_Set(m_pObj, 10000+55, 0, (void*)lpSearchPattern, 0);
    }

    inline LPWSTR GetSearchRange() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+56, 0, 0);
    }

    inline int SetSearchRange(LPWSTR lpSearchRange) {
      return IPWorks_NNTP_Set(m_pObj, 10000+56, 0, (void*)lpSearchRange, 0);
    }



    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_NNTP_Get(m_pObj, 10000+58, 0, 0);
    }

    inline int SetUser(LPWSTR lpUser) {
      return IPWorks_NNTP_Set(m_pObj, 10000+58, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnectionStatus(NNTPConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(NNTPEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(NNTPErrorEventParamsW *e) {return 0;}
    virtual int FireGroupList(NNTPGroupListEventParamsW *e) {return 0;}
    virtual int FireGroupOverview(NNTPGroupOverviewEventParamsW *e) {return 0;}
    virtual int FireGroupSearch(NNTPGroupSearchEventParamsW *e) {return 0;}
    virtual int FireHeader(NNTPHeaderEventParamsW *e) {return 0;}
    virtual int FirePITrail(NNTPPITrailEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(NNTPStartTransferEventParamsW *e) {return 0;}
    virtual int FireTransfer(NNTPTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int NNTPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            NNTPConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 2: {
            NNTPEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 3: {
            NNTPErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 4: {
            NNTPGroupListEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = FireGroupList(&e);
            break;
         }
         case 5: {
            NNTPGroupOverviewEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (LPWSTR)IPW64CAST(param[5]), (int)IPW64CAST(param[6]), (int)IPW64CAST(param[7]), (LPWSTR)IPW64CAST(param[8]),  0};
            ret_code = FireGroupOverview(&e);
            break;
         }
         case 6: {
            NNTPGroupSearchEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireGroupSearch(&e);
            break;
         }
         case 7: {
            NNTPHeaderEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireHeader(&e);
            break;
         }
         case 8: {
            NNTPPITrailEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FirePITrail(&e);
            break;
         }
         case 9: {
            NNTPStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 10: {
            NNTPTransferEventParamsW e = {(int)IPW64CAST(param[0]), (ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnectionStatus(NNTPConnectionStatusEventParams *e) {return -10000;}
    virtual int FireEndTransfer(NNTPEndTransferEventParams *e) {return -10000;}
    virtual int FireError(NNTPErrorEventParams *e) {return -10000;}
    virtual int FireGroupList(NNTPGroupListEventParams *e) {return -10000;}
    virtual int FireGroupOverview(NNTPGroupOverviewEventParams *e) {return -10000;}
    virtual int FireGroupSearch(NNTPGroupSearchEventParams *e) {return -10000;}
    virtual int FireHeader(NNTPHeaderEventParams *e) {return -10000;}
    virtual int FirePITrail(NNTPPITrailEventParams *e) {return -10000;}
    virtual int FireStartTransfer(NNTPStartTransferEventParams *e) {return -10000;}
    virtual int FireTransfer(NNTPTransferEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NNTP_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Connect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int Disconnect() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int FetchArticle() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int FetchArticleBody() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int FetchArticleHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }
    inline int GroupOverview() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int GroupSearch() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10000+10, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10000+11, 0, param, cbparam);
      
    }
    inline int ListGroups() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10000+12, 0, param, cbparam);
      
    }
    inline int ListNewGroups() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10000+13, 0, param, cbparam);
      
    }
    inline LPWSTR LocalizeDate(LPWSTR lpszDateTime) {
      void *param[1+1] = {(void*)lpszDateTime, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_NNTP_Do(m_pObj, 10000+14, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int PostArticle() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10000+15, 0, param, cbparam);
      
    }
    inline int ResetHeaders() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_NNTP_Do(m_pObj, 10000+16, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_NNTP_H_




