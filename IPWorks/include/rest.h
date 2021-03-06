/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_REST_H_
#define _IPWORKS_REST_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//AuthSchemes
#define AUTH_BASIC                                         0
#define AUTH_DIGEST                                        1
#define AUTH_PROPRIETARY                                   2
#define AUTH_NONE                                          3
#define AUTH_NTLM                                          4
#define AUTH_NEGOTIATE                                     5
#define AUTH_OAUTH                                         6

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TFollowRedirects
#define FR_NEVER                                           0
#define FR_ALWAYS                                          1
#define FR_SAME_SCHEME                                     2


extern "C" void* IPWORKS_CALL IPWorks_REST_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_REST_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_REST_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_REST_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_REST_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_REST_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_REST_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_REST_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_REST_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_REST_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  const char* Text;
  int lenText;
  int reserved;
} RESTCharactersEventParams;

typedef struct {
  const char* Text;
  int reserved;
} RESTCommentEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} RESTConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} RESTConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} RESTDisconnectedEventParams;

typedef struct {
  const char* Namespace;
  const char* Element;
  const char* QName;
  int IsEmpty;
  int reserved;
} RESTEndElementEventParams;

typedef struct {
  const char* Prefix;
  int reserved;
} RESTEndPrefixMappingEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} RESTErrorEventParams;

typedef struct {
  const char* Entity;
  const char* Value;
  int reserved;
} RESTEvalEntityEventParams;

typedef struct {
  const char* Field;
  const char* Value;
  int reserved;
} RESTHeaderEventParams;

typedef struct {
  const char* Text;
  int reserved;
} RESTIgnorableWhitespaceEventParams;

typedef struct {
  const char* Text;
  int reserved;
} RESTMetaEventParams;

typedef struct {
  const char* Text;
  int reserved;
} RESTPIEventParams;

typedef struct {
  const char* Location;
  int Accept;
  int reserved;
} RESTRedirectEventParams;

typedef struct {
  const char* Name;
  const char* Value;
  const char* Expires;
  const char* Domain;
  const char* Path;
  int Secure;
  int reserved;
} RESTSetCookieEventParams;

typedef struct {
  const char* SectionId;
  const char* Text;
  int reserved;
} RESTSpecialSectionEventParams;

typedef struct {
  const char* Namespace;
  const char* Element;
  const char* QName;
  int IsEmpty;
  int reserved;
} RESTStartElementEventParams;

typedef struct {
  const char* Prefix;
  const char* URI;
  int reserved;
} RESTStartPrefixMappingEventParams;

typedef struct {
  const char* HTTPVersion;
  int StatusCode;
  const char* Description;
  int reserved;
} RESTStatusEventParams;



class REST {
  
  public: //events
  
    virtual int FireCharacters(RESTCharactersEventParams *e) {return 0;}
    virtual int FireComment(RESTCommentEventParams *e) {return 0;}
    virtual int FireConnected(RESTConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(RESTConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(RESTDisconnectedEventParams *e) {return 0;}
    virtual int FireEndElement(RESTEndElementEventParams *e) {return 0;}
    virtual int FireEndPrefixMapping(RESTEndPrefixMappingEventParams *e) {return 0;}
    virtual int FireError(RESTErrorEventParams *e) {return 0;}
    virtual int FireEvalEntity(RESTEvalEntityEventParams *e) {return 0;}
    virtual int FireHeader(RESTHeaderEventParams *e) {return 0;}
    virtual int FireIgnorableWhitespace(RESTIgnorableWhitespaceEventParams *e) {return 0;}
    virtual int FireMeta(RESTMetaEventParams *e) {return 0;}
    virtual int FirePI(RESTPIEventParams *e) {return 0;}
    virtual int FireRedirect(RESTRedirectEventParams *e) {return 0;}
    virtual int FireSetCookie(RESTSetCookieEventParams *e) {return 0;}
    virtual int FireSpecialSection(RESTSpecialSectionEventParams *e) {return 0;}
    virtual int FireStartElement(RESTStartElementEventParams *e) {return 0;}
    virtual int FireStartPrefixMapping(RESTStartPrefixMappingEventParams *e) {return 0;}
    virtual int FireStatus(RESTStatusEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL RESTEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((REST*)lpObj)->RESTEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            RESTCharactersEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((REST*)lpObj)->FireCharacters(&e);
            break;
         }
         case 2: {
            RESTCommentEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((REST*)lpObj)->FireComment(&e);
            break;
         }
         case 3: {
            RESTConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((REST*)lpObj)->FireConnected(&e);
            break;
         }
         case 4: {
            RESTConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((REST*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 5: {
            RESTDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((REST*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 6: {
            RESTEndElementEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = ((REST*)lpObj)->FireEndElement(&e);
            break;
         }
         case 7: {
            RESTEndPrefixMappingEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((REST*)lpObj)->FireEndPrefixMapping(&e);
            break;
         }
         case 8: {
            RESTErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((REST*)lpObj)->FireError(&e);
            break;
         }
         case 9: {
            RESTEvalEntityEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((REST*)lpObj)->FireEvalEntity(&e);
            param[1] = (void*)IPW64CAST(e.Value);
            break;
         }
         case 10: {
            RESTHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((REST*)lpObj)->FireHeader(&e);
            break;
         }
         case 11: {
            RESTIgnorableWhitespaceEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((REST*)lpObj)->FireIgnorableWhitespace(&e);
            break;
         }
         case 12: {
            RESTMetaEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((REST*)lpObj)->FireMeta(&e);
            break;
         }
         case 13: {
            RESTPIEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((REST*)lpObj)->FirePI(&e);
            break;
         }
         case 14: {
            RESTRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = ((REST*)lpObj)->FireRedirect(&e);
            param[1] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 15: {
            RESTSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = ((REST*)lpObj)->FireSetCookie(&e);
            break;
         }
         case 16: {
            RESTSpecialSectionEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((REST*)lpObj)->FireSpecialSection(&e);
            break;
         }
         case 17: {
            RESTStartElementEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = ((REST*)lpObj)->FireStartElement(&e);
            break;
         }
         case 18: {
            RESTStartPrefixMappingEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((REST*)lpObj)->FireStartPrefixMapping(&e);
            break;
         }
         case 19: {
            RESTStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((REST*)lpObj)->FireStatus(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int RESTEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    REST(char *lpOemKey = (char*)IPWORKS_OEMKEY_34) {
      m_pObj = IPWorks_REST_Create(RESTEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~REST() {
      IPWorks_REST_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_REST_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_REST_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_REST_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline char* GetAccept() {
      void* val = IPWorks_REST_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetAccept(const char *lpAccept) {
      return IPWorks_REST_Set(m_pObj, 1, 0, (void*)lpAccept, 0);
    }

    inline char* GetAuthorization() {
      void* val = IPWorks_REST_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetAuthorization(const char *lpAuthorization) {
      return IPWorks_REST_Set(m_pObj, 2, 0, (void*)lpAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_REST_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_REST_Set(m_pObj, 3, 0, val, 0);
    }
    inline int GetBuildDOM() {
      void* val = IPWorks_REST_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetBuildDOM(int bBuildDOM) {
      void* val = (void*)IPW64CAST(bBuildDOM);
      return IPWorks_REST_Set(m_pObj, 4, 0, val, 0);
    }
    inline int GetConnected() {
      void* val = IPWorks_REST_Get(m_pObj, 5, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_REST_Set(m_pObj, 5, 0, val, 0);
    }
    inline char* GetContentType() {
      void* val = IPWorks_REST_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }

    inline int SetContentType(const char *lpContentType) {
      return IPWorks_REST_Set(m_pObj, 6, 0, (void*)lpContentType, 0);
    }

    inline int GetCookieCount() {
      void* val = IPWorks_REST_Get(m_pObj, 7, 0, 0);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_REST_Set(m_pObj, 7, 0, val, 0);
    }
    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 8, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 9, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 10, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieName(int iCookieIndex, const char *lpCookieName) {
      return IPWorks_REST_Set(m_pObj, 10, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 11, iCookieIndex, 0);
      return (char*)val;
    }


    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 12, iCookieIndex, 0);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 13, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieValue(int iCookieIndex, const char *lpCookieValue) {
      return IPWorks_REST_Set(m_pObj, 13, iCookieIndex, (void*)lpCookieValue, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_REST_Get(m_pObj, 14, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_REST_Set(m_pObj, 14, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_REST_Get(m_pObj, 15, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_REST_Set(m_pObj, 15, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_REST_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_REST_Set(m_pObj, 16, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_REST_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_REST_Set(m_pObj, 17, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_REST_Get(m_pObj, 18, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_REST_Set(m_pObj, 18, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_REST_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_REST_Set(m_pObj, 19, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_REST_Get(m_pObj, 20, 0, 0);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_REST_Set(m_pObj, 20, 0, val, 0);
    }
    inline char* GetFrom() {
      void* val = IPWorks_REST_Get(m_pObj, 21, 0, 0);
      return (char*)val;
    }

    inline int SetFrom(const char *lpFrom) {
      return IPWorks_REST_Set(m_pObj, 21, 0, (void*)lpFrom, 0);
    }

    inline char* GetHTTPMethod() {
      void* val = IPWorks_REST_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }

    inline int SetHTTPMethod(const char *lpHTTPMethod) {
      return IPWorks_REST_Set(m_pObj, 22, 0, (void*)lpHTTPMethod, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_REST_Get(m_pObj, 23, 0, 0);
      return (int)(long)val;
    }

    inline char* GetIfModifiedSince() {
      void* val = IPWorks_REST_Get(m_pObj, 24, 0, 0);
      return (char*)val;
    }

    inline int SetIfModifiedSince(const char *lpIfModifiedSince) {
      return IPWorks_REST_Set(m_pObj, 24, 0, (void*)lpIfModifiedSince, 0);
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_REST_Get(m_pObj, 25, 0, 0);
      return (char*)val;
    }

    inline int SetLocalFile(const char *lpLocalFile) {
      return IPWorks_REST_Set(m_pObj, 25, 0, (void*)lpLocalFile, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_REST_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_REST_Set(m_pObj, 26, 0, (void*)lpLocalHost, 0);
    }

    inline int GetNamespaceCount() {
      void* val = IPWorks_REST_Get(m_pObj, 27, 0, 0);
      return (int)(long)val;
    }

    inline char* GetNamespacePrefix(int iNamespaceIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 28, iNamespaceIndex, 0);
      return (char*)val;
    }


    inline char* GetNamespaceURI(int iNamespaceIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 29, iNamespaceIndex, 0);
      return (char*)val;
    }


    inline char* GetOtherHeaders() {
      void* val = IPWorks_REST_Get(m_pObj, 30, 0, 0);
      return (char*)val;
    }

    inline int SetOtherHeaders(const char *lpOtherHeaders) {
      return IPWorks_REST_Set(m_pObj, 30, 0, (void*)lpOtherHeaders, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_REST_Get(m_pObj, 31, 0, 0);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 32, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 33, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetPassword() {
      void* val = IPWorks_REST_Get(m_pObj, 34, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_REST_Set(m_pObj, 34, 0, (void*)lpPassword, 0);
    }

    inline int GetPostData(char *&lpPostData, int &lenPostData) {
      lpPostData = (char*)IPWorks_REST_Get(m_pObj, 35, 0, &lenPostData);
      return lpPostData ? 0 : lenPostData;
    }

    inline int SetPostData(const char *lpPostData, int lenPostData) {
      return IPWorks_REST_Set(m_pObj, 35, 0, (void*)lpPostData, lenPostData);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_REST_Get(m_pObj, 36, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_REST_Set(m_pObj, 36, 0, val, 0);
    }
    inline int GetProxyAutoDetect() {
      void* val = IPWorks_REST_Get(m_pObj, 37, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_REST_Set(m_pObj, 37, 0, val, 0);
    }
    inline char* GetProxyPassword() {
      void* val = IPWorks_REST_Get(m_pObj, 38, 0, 0);
      return (char*)val;
    }

    inline int SetProxyPassword(const char *lpProxyPassword) {
      return IPWorks_REST_Set(m_pObj, 38, 0, (void*)lpProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_REST_Get(m_pObj, 39, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyPort(int lProxyPort) {
      void* val = (void*)IPW64CAST(lProxyPort);
      return IPWorks_REST_Set(m_pObj, 39, 0, val, 0);
    }
    inline char* GetProxyServer() {
      void* val = IPWorks_REST_Get(m_pObj, 40, 0, 0);
      return (char*)val;
    }

    inline int SetProxyServer(const char *lpProxyServer) {
      return IPWorks_REST_Set(m_pObj, 40, 0, (void*)lpProxyServer, 0);
    }

    inline char* GetProxyUser() {
      void* val = IPWorks_REST_Get(m_pObj, 41, 0, 0);
      return (char*)val;
    }

    inline int SetProxyUser(const char *lpProxyUser) {
      return IPWorks_REST_Set(m_pObj, 41, 0, (void*)lpProxyUser, 0);
    }

    inline char* GetReferer() {
      void* val = IPWorks_REST_Get(m_pObj, 42, 0, 0);
      return (char*)val;
    }

    inline int SetReferer(const char *lpReferer) {
      return IPWorks_REST_Set(m_pObj, 42, 0, (void*)lpReferer, 0);
    }

    inline char* GetStatusLine() {
      void* val = IPWorks_REST_Get(m_pObj, 43, 0, 0);
      return (char*)val;
    }


    inline int GetTimeout() {
      void* val = IPWorks_REST_Get(m_pObj, 44, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_REST_Set(m_pObj, 44, 0, val, 0);
    }
    inline int GetTransferredData(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_REST_Get(m_pObj, 45, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }


    inline ns_int64 GetTransferredDataLimit() {
      ns_int64 *pval = (ns_int64*)IPWorks_REST_Get(m_pObj, 46, 0, 0);
      return *pval;
    }

    inline int SetTransferredDataLimit(ns_int64 lTransferredDataLimit) {
      void* val = (void*)(&lTransferredDataLimit);
      return IPWorks_REST_Set(m_pObj, 46, 0, val, 0);
    }

    inline char* GetTransferredHeaders() {
      void* val = IPWorks_REST_Get(m_pObj, 47, 0, 0);
      return (char*)val;
    }


    inline char* GetURL() {
      void* val = IPWorks_REST_Get(m_pObj, 48, 0, 0);
      return (char*)val;
    }

    inline int SetURL(const char *lpURL) {
      return IPWorks_REST_Set(m_pObj, 48, 0, (void*)lpURL, 0);
    }

    inline char* GetUser() {
      void* val = IPWorks_REST_Get(m_pObj, 49, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_REST_Set(m_pObj, 49, 0, (void*)lpUser, 0);
    }

    inline int GetValidate() {
      void* val = IPWorks_REST_Get(m_pObj, 50, 0, 0);
      return (int)(long)val;
    }
    inline int SetValidate(int bValidate) {
      void* val = (void*)IPW64CAST(bValidate);
      return IPWorks_REST_Set(m_pObj, 50, 0, val, 0);
    }
    inline int GetAttrCount() {
      void* val = IPWorks_REST_Get(m_pObj, 51, 0, 0);
      return (int)(long)val;
    }

    inline char* GetAttrName(int iAttrIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 52, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrNamespace(int iAttrIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 53, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrPrefix(int iAttrIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 54, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrValue(int iAttrIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 55, iAttrIndex, 0);
      return (char*)val;
    }


    inline int GetXChildrenCount() {
      void* val = IPWorks_REST_Get(m_pObj, 56, 0, 0);
      return (int)(long)val;
    }

    inline char* GetXChildName(int iXChildIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 57, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildNamespace(int iXChildIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 58, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildPrefix(int iXChildIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 59, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildXText(int iXChildIndex) {
      void* val = IPWorks_REST_Get(m_pObj, 60, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXElement() {
      void* val = IPWorks_REST_Get(m_pObj, 61, 0, 0);
      return (char*)val;
    }


    inline char* GetXErrorPath() {
      void* val = IPWorks_REST_Get(m_pObj, 62, 0, 0);
      return (char*)val;
    }

    inline int SetXErrorPath(const char *lpXErrorPath) {
      return IPWorks_REST_Set(m_pObj, 62, 0, (void*)lpXErrorPath, 0);
    }

    inline char* GetXNamespace() {
      void* val = IPWorks_REST_Get(m_pObj, 63, 0, 0);
      return (char*)val;
    }


    inline char* GetXParent() {
      void* val = IPWorks_REST_Get(m_pObj, 64, 0, 0);
      return (char*)val;
    }


    inline char* GetXPath() {
      void* val = IPWorks_REST_Get(m_pObj, 65, 0, 0);
      return (char*)val;
    }

    inline int SetXPath(const char *lpXPath) {
      return IPWorks_REST_Set(m_pObj, 65, 0, (void*)lpXPath, 0);
    }

    inline char* GetXPrefix() {
      void* val = IPWorks_REST_Get(m_pObj, 66, 0, 0);
      return (char*)val;
    }


    inline char* GetXSubTree() {
      void* val = IPWorks_REST_Get(m_pObj, 67, 0, 0);
      return (char*)val;
    }


    inline char* GetXText() {
      void* val = IPWorks_REST_Get(m_pObj, 68, 0, 0);
      return (char*)val;
    }



  public: //methods

    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_REST_Do(m_pObj, 2, 2, param, cbparam);
      
      
    }
    inline char* Attr(const char* lpszAttrName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszAttrName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_REST_Do(m_pObj, 3, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_REST_Do(m_pObj, 4, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Delete(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_REST_Do(m_pObj, 5, 1, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_REST_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int Get(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_REST_Do(m_pObj, 7, 1, param, cbparam);
      
      
    }
    inline int HasXPath(const char* lpszxpath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszxpath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_REST_Do(m_pObj, 8, 1, param, cbparam);
      
      return (int)IPW64CAST(param[1]);
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_REST_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int Post(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_REST_Do(m_pObj, 10, 1, param, cbparam);
      
      
    }
    inline int Put(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_REST_Do(m_pObj, 11, 1, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_REST_Do(m_pObj, 12, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR Text;
  int lenText;
  int reserved;
} RESTCharactersEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} RESTCommentEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} RESTConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} RESTConnectionStatusEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} RESTDisconnectedEventParamsW;

typedef struct {
  LPWSTR Namespace;
  LPWSTR Element;
  LPWSTR QName;
  int IsEmpty;
  int reserved;
} RESTEndElementEventParamsW;

typedef struct {
  LPWSTR Prefix;
  int reserved;
} RESTEndPrefixMappingEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} RESTErrorEventParamsW;

typedef struct {
  LPWSTR Entity;
  LPWSTR Value;
  int reserved;
} RESTEvalEntityEventParamsW;

typedef struct {
  LPWSTR Field;
  LPWSTR Value;
  int reserved;
} RESTHeaderEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} RESTIgnorableWhitespaceEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} RESTMetaEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} RESTPIEventParamsW;

typedef struct {
  LPWSTR Location;
  int Accept;
  int reserved;
} RESTRedirectEventParamsW;

typedef struct {
  LPWSTR Name;
  LPWSTR Value;
  LPWSTR Expires;
  LPWSTR Domain;
  LPWSTR Path;
  int Secure;
  int reserved;
} RESTSetCookieEventParamsW;

typedef struct {
  LPWSTR SectionId;
  LPWSTR Text;
  int reserved;
} RESTSpecialSectionEventParamsW;

typedef struct {
  LPWSTR Namespace;
  LPWSTR Element;
  LPWSTR QName;
  int IsEmpty;
  int reserved;
} RESTStartElementEventParamsW;

typedef struct {
  LPWSTR Prefix;
  LPWSTR URI;
  int reserved;
} RESTStartPrefixMappingEventParamsW;

typedef struct {
  LPWSTR HTTPVersion;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} RESTStatusEventParamsW;



class RESTW : public REST {

  public: //properties
  
    inline LPWSTR GetAccept() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetAccept(LPWSTR lpAccept) {
      return IPWorks_REST_Set(m_pObj, 10000+1, 0, (void*)lpAccept, 0);
    }

    inline LPWSTR GetAuthorization() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetAuthorization(LPWSTR lpAuthorization) {
      return IPWorks_REST_Set(m_pObj, 10000+2, 0, (void*)lpAuthorization, 0);
    }







    inline LPWSTR GetContentType() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetContentType(LPWSTR lpContentType) {
      return IPWorks_REST_Set(m_pObj, 10000+6, 0, (void*)lpContentType, 0);
    }



    inline LPWSTR GetCookieDomain(int iCookieIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+8, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieExpiration(int iCookieIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+9, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieName(int iCookieIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+10, iCookieIndex, 0);
    }

    inline int SetCookieName(int iCookieIndex, LPWSTR lpCookieName) {
      return IPWorks_REST_Set(m_pObj, 10000+10, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline LPWSTR GetCookiePath(int iCookieIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+11, iCookieIndex, 0);
    }





    inline LPWSTR GetCookieValue(int iCookieIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+13, iCookieIndex, 0);
    }

    inline int SetCookieValue(int iCookieIndex, LPWSTR lpCookieValue) {
      return IPWorks_REST_Set(m_pObj, 10000+13, iCookieIndex, (void*)lpCookieValue, 0);
    }





    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetFirewallHost(LPWSTR lpFirewallHost) {
      return IPWorks_REST_Set(m_pObj, 10000+16, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetFirewallPassword(LPWSTR lpFirewallPassword) {
      return IPWorks_REST_Set(m_pObj, 10000+17, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+19, 0, 0);
    }

    inline int SetFirewallUser(LPWSTR lpFirewallUser) {
      return IPWorks_REST_Set(m_pObj, 10000+19, 0, (void*)lpFirewallUser, 0);
    }



    inline LPWSTR GetFrom() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+21, 0, 0);
    }

    inline int SetFrom(LPWSTR lpFrom) {
      return IPWorks_REST_Set(m_pObj, 10000+21, 0, (void*)lpFrom, 0);
    }

    inline LPWSTR GetHTTPMethod() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+22, 0, 0);
    }

    inline int SetHTTPMethod(LPWSTR lpHTTPMethod) {
      return IPWorks_REST_Set(m_pObj, 10000+22, 0, (void*)lpHTTPMethod, 0);
    }



    inline LPWSTR GetIfModifiedSince() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+24, 0, 0);
    }

    inline int SetIfModifiedSince(LPWSTR lpIfModifiedSince) {
      return IPWorks_REST_Set(m_pObj, 10000+24, 0, (void*)lpIfModifiedSince, 0);
    }

    inline LPWSTR GetLocalFile() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+10000+25, 0, 0);
    }

    inline int SetLocalFile(LPWSTR lpLocalFile) {
      return IPWorks_REST_Set(m_pObj, 10000+10000+25, 0, (void*)lpLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+26, 0, 0);
    }

    inline int SetLocalHost(LPWSTR lpLocalHost) {
      return IPWorks_REST_Set(m_pObj, 10000+26, 0, (void*)lpLocalHost, 0);
    }



    inline LPWSTR GetNamespacePrefix(int iNamespaceIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+28, iNamespaceIndex, 0);
    }



    inline LPWSTR GetNamespaceURI(int iNamespaceIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+29, iNamespaceIndex, 0);
    }



    inline LPWSTR GetOtherHeaders() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+30, 0, 0);
    }

    inline int SetOtherHeaders(LPWSTR lpOtherHeaders) {
      return IPWorks_REST_Set(m_pObj, 10000+30, 0, (void*)lpOtherHeaders, 0);
    }



    inline LPWSTR GetParsedHeaderField(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+32, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetParsedHeaderValue(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+33, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+34, 0, 0);
    }

    inline int SetPassword(LPWSTR lpPassword) {
      return IPWorks_REST_Set(m_pObj, 10000+34, 0, (void*)lpPassword, 0);
    }

    inline LPWSTR GetPostData() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+35, 0, 0);
    }

    inline int SetPostData(LPWSTR lpPostData) {
      return IPWorks_REST_Set(m_pObj, 10000+35, 0, (void*)lpPostData, 0);
    }
    inline int GetPostDataB(char *&lpPostData, int &lenPostData) {
      lpPostData = (char*)IPWorks_REST_Get(m_pObj, 35, 0, &lenPostData);
      return lpPostData ? 0 : lenPostData;
    }
    inline int SetPostDataB(const char *lpPostData, int lenPostData) {
      return IPWorks_REST_Set(m_pObj, 35, 0, (void*)lpPostData, lenPostData);
    }




    inline LPWSTR GetProxyPassword() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+38, 0, 0);
    }

    inline int SetProxyPassword(LPWSTR lpProxyPassword) {
      return IPWorks_REST_Set(m_pObj, 10000+38, 0, (void*)lpProxyPassword, 0);
    }



    inline LPWSTR GetProxyServer() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+40, 0, 0);
    }

    inline int SetProxyServer(LPWSTR lpProxyServer) {
      return IPWorks_REST_Set(m_pObj, 10000+40, 0, (void*)lpProxyServer, 0);
    }

    inline LPWSTR GetProxyUser() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+41, 0, 0);
    }

    inline int SetProxyUser(LPWSTR lpProxyUser) {
      return IPWorks_REST_Set(m_pObj, 10000+41, 0, (void*)lpProxyUser, 0);
    }

    inline LPWSTR GetReferer() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+42, 0, 0);
    }

    inline int SetReferer(LPWSTR lpReferer) {
      return IPWorks_REST_Set(m_pObj, 10000+42, 0, (void*)lpReferer, 0);
    }

    inline LPWSTR GetStatusLine() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+43, 0, 0);
    }





    inline LPWSTR GetTransferredData() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+45, 0, 0);
    }


    inline int GetTransferredDataB(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_REST_Get(m_pObj, 45, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }



    inline LPWSTR GetTransferredHeaders() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+47, 0, 0);
    }



    inline LPWSTR GetURL() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+48, 0, 0);
    }

    inline int SetURL(LPWSTR lpURL) {
      return IPWorks_REST_Set(m_pObj, 10000+48, 0, (void*)lpURL, 0);
    }

    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+49, 0, 0);
    }

    inline int SetUser(LPWSTR lpUser) {
      return IPWorks_REST_Set(m_pObj, 10000+49, 0, (void*)lpUser, 0);
    }





    inline LPWSTR GetAttrName(int iAttrIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+52, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrNamespace(int iAttrIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+53, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrPrefix(int iAttrIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+54, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrValue(int iAttrIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+55, iAttrIndex, 0);
    }





    inline LPWSTR GetXChildName(int iXChildIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+57, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildNamespace(int iXChildIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+58, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildPrefix(int iXChildIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+59, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildXText(int iXChildIndex) {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+60, iXChildIndex, 0);
    }



    inline LPWSTR GetXElement() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+61, 0, 0);
    }



    inline LPWSTR GetXErrorPath() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+62, 0, 0);
    }

    inline int SetXErrorPath(LPWSTR lpXErrorPath) {
      return IPWorks_REST_Set(m_pObj, 10000+62, 0, (void*)lpXErrorPath, 0);
    }

    inline LPWSTR GetXNamespace() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+63, 0, 0);
    }



    inline LPWSTR GetXParent() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+64, 0, 0);
    }



    inline LPWSTR GetXPath() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+65, 0, 0);
    }

    inline int SetXPath(LPWSTR lpXPath) {
      return IPWorks_REST_Set(m_pObj, 10000+65, 0, (void*)lpXPath, 0);
    }

    inline LPWSTR GetXPrefix() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+66, 0, 0);
    }



    inline LPWSTR GetXSubTree() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+67, 0, 0);
    }



    inline LPWSTR GetXText() {
      return (LPWSTR)IPWorks_REST_Get(m_pObj, 10000+68, 0, 0);
    }





  public: //events
  
    virtual int FireCharacters(RESTCharactersEventParamsW *e) {return 0;}
    virtual int FireComment(RESTCommentEventParamsW *e) {return 0;}
    virtual int FireConnected(RESTConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(RESTConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDisconnected(RESTDisconnectedEventParamsW *e) {return 0;}
    virtual int FireEndElement(RESTEndElementEventParamsW *e) {return 0;}
    virtual int FireEndPrefixMapping(RESTEndPrefixMappingEventParamsW *e) {return 0;}
    virtual int FireError(RESTErrorEventParamsW *e) {return 0;}
    virtual int FireEvalEntity(RESTEvalEntityEventParamsW *e) {return 0;}
    virtual int FireHeader(RESTHeaderEventParamsW *e) {return 0;}
    virtual int FireIgnorableWhitespace(RESTIgnorableWhitespaceEventParamsW *e) {return 0;}
    virtual int FireMeta(RESTMetaEventParamsW *e) {return 0;}
    virtual int FirePI(RESTPIEventParamsW *e) {return 0;}
    virtual int FireRedirect(RESTRedirectEventParamsW *e) {return 0;}
    virtual int FireSetCookie(RESTSetCookieEventParamsW *e) {return 0;}
    virtual int FireSpecialSection(RESTSpecialSectionEventParamsW *e) {return 0;}
    virtual int FireStartElement(RESTStartElementEventParamsW *e) {return 0;}
    virtual int FireStartPrefixMapping(RESTStartPrefixMappingEventParamsW *e) {return 0;}
    virtual int FireStatus(RESTStatusEventParamsW *e) {return 0;}


  protected:
  
    virtual int RESTEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            RESTCharactersEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireCharacters(&e);
            break;
         }
         case 2: {
            RESTCommentEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireComment(&e);
            break;
         }
         case 3: {
            RESTConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 4: {
            RESTConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 5: {
            RESTDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 6: {
            RESTEndElementEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = FireEndElement(&e);
            break;
         }
         case 7: {
            RESTEndPrefixMappingEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireEndPrefixMapping(&e);
            break;
         }
         case 8: {
            RESTErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 9: {
            RESTEvalEntityEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireEvalEntity(&e);
            param[1] = (void*)(e.Value);
            break;
         }
         case 10: {
            RESTHeaderEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireHeader(&e);
            break;
         }
         case 11: {
            RESTIgnorableWhitespaceEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireIgnorableWhitespace(&e);
            break;
         }
         case 12: {
            RESTMetaEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireMeta(&e);
            break;
         }
         case 13: {
            RESTPIEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FirePI(&e);
            break;
         }
         case 14: {
            RESTRedirectEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = FireRedirect(&e);
            param[1] = (void*)(e.Accept);
            break;
         }
         case 15: {
            RESTSetCookieEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = FireSetCookie(&e);
            break;
         }
         case 16: {
            RESTSpecialSectionEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireSpecialSection(&e);
            break;
         }
         case 17: {
            RESTStartElementEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = FireStartElement(&e);
            break;
         }
         case 18: {
            RESTStartPrefixMappingEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireStartPrefixMapping(&e);
            break;
         }
         case 19: {
            RESTStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireStatus(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireCharacters(RESTCharactersEventParams *e) {return -10000;}
    virtual int FireComment(RESTCommentEventParams *e) {return -10000;}
    virtual int FireConnected(RESTConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(RESTConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDisconnected(RESTDisconnectedEventParams *e) {return -10000;}
    virtual int FireEndElement(RESTEndElementEventParams *e) {return -10000;}
    virtual int FireEndPrefixMapping(RESTEndPrefixMappingEventParams *e) {return -10000;}
    virtual int FireError(RESTErrorEventParams *e) {return -10000;}
    virtual int FireEvalEntity(RESTEvalEntityEventParams *e) {return -10000;}
    virtual int FireHeader(RESTHeaderEventParams *e) {return -10000;}
    virtual int FireIgnorableWhitespace(RESTIgnorableWhitespaceEventParams *e) {return -10000;}
    virtual int FireMeta(RESTMetaEventParams *e) {return -10000;}
    virtual int FirePI(RESTPIEventParams *e) {return -10000;}
    virtual int FireRedirect(RESTRedirectEventParams *e) {return -10000;}
    virtual int FireSetCookie(RESTSetCookieEventParams *e) {return -10000;}
    virtual int FireSpecialSection(RESTSpecialSectionEventParams *e) {return -10000;}
    virtual int FireStartElement(RESTStartElementEventParams *e) {return -10000;}
    virtual int FireStartPrefixMapping(RESTStartPrefixMappingEventParams *e) {return -10000;}
    virtual int FireStatus(RESTStatusEventParams *e) {return -10000;}

  public: //methods

    inline int AddCookie(LPWSTR lpszCookieName, LPWSTR lpszCookieValue) {
      void *param[2+1] = {(void*)lpszCookieName, (void*)lpszCookieValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_REST_Do(m_pObj, 10000+2, 2, param, cbparam);
      
    }
    inline LPWSTR Attr(LPWSTR lpszAttrName) {
      void *param[1+1] = {(void*)lpszAttrName, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_REST_Do(m_pObj, 10000+3, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_REST_Do(m_pObj, 10000+4, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Delete(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_REST_Do(m_pObj, 10000+5, 1, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_REST_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int Get(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_REST_Do(m_pObj, 10000+7, 1, param, cbparam);
      
    }
    inline int HasXPath(LPWSTR lpszxpath) {
      void *param[1+1] = {(void*)lpszxpath, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_REST_Do(m_pObj, 10000+8, 1, param, cbparam);
      return (int)IPW64CAST(param[1]);
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_REST_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int Post(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_REST_Do(m_pObj, 10000+10, 1, param, cbparam);
      
    }
    inline int Put(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_REST_Do(m_pObj, 10000+11, 1, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_REST_Do(m_pObj, 10000+12, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_REST_H_




