/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_WEBFORM_H_
#define _IPWORKS_WEBFORM_H_

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

//TWebFormEncoding
#define ENC_URLENCODING                                    0
#define ENC_MULTIPART_FORM_DATA                            1
#define ENC_QUERY_STRING                                   2

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TFollowRedirects
#define FR_NEVER                                           0
#define FR_ALWAYS                                          1
#define FR_SAME_SCHEME                                     2


extern "C" void* IPWORKS_CALL IPWorks_WebForm_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_WebForm_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebForm_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_WebForm_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_WebForm_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_WebForm_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_WebForm_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebForm_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_WebForm_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_WebForm_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} WebFormConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} WebFormConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} WebFormDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} WebFormEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} WebFormErrorEventParams;

typedef struct {
  const char* Field;
  const char* Value;
  int reserved;
} WebFormHeaderEventParams;

typedef struct {
  const char* Location;
  int Accept;
  int reserved;
} WebFormRedirectEventParams;

typedef struct {
  const char* Name;
  const char* Value;
  const char* Expires;
  const char* Domain;
  const char* Path;
  int Secure;
  int reserved;
} WebFormSetCookieEventParams;

typedef struct {
  int Direction;
  int reserved;
} WebFormStartTransferEventParams;

typedef struct {
  const char* HTTPVersion;
  int StatusCode;
  const char* Description;
  int reserved;
} WebFormStatusEventParams;

typedef struct {
  int Direction;
  ns_int64 *pBytesTransferred;
  int PercentDone;
  const char* Text;
  int lenText;
  int reserved;
} WebFormTransferEventParams;



class WebForm {
  
  public: //events
  
    virtual int FireConnected(WebFormConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(WebFormConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(WebFormDisconnectedEventParams *e) {return 0;}
    virtual int FireEndTransfer(WebFormEndTransferEventParams *e) {return 0;}
    virtual int FireError(WebFormErrorEventParams *e) {return 0;}
    virtual int FireHeader(WebFormHeaderEventParams *e) {return 0;}
    virtual int FireRedirect(WebFormRedirectEventParams *e) {return 0;}
    virtual int FireSetCookie(WebFormSetCookieEventParams *e) {return 0;}
    virtual int FireStartTransfer(WebFormStartTransferEventParams *e) {return 0;}
    virtual int FireStatus(WebFormStatusEventParams *e) {return 0;}
    virtual int FireTransfer(WebFormTransferEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL WebFormEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((WebForm*)lpObj)->WebFormEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            WebFormConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((WebForm*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            WebFormConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((WebForm*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 3: {
            WebFormDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((WebForm*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 4: {
            WebFormEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((WebForm*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 5: {
            WebFormErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((WebForm*)lpObj)->FireError(&e);
            break;
         }
         case 6: {
            WebFormHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((WebForm*)lpObj)->FireHeader(&e);
            break;
         }
         case 7: {
            WebFormRedirectEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = ((WebForm*)lpObj)->FireRedirect(&e);
            param[1] = (void*)IPW64CAST(e.Accept);
            break;
         }
         case 8: {
            WebFormSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = ((WebForm*)lpObj)->FireSetCookie(&e);
            break;
         }
         case 9: {
            WebFormStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((WebForm*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 10: {
            WebFormStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((WebForm*)lpObj)->FireStatus(&e);
            break;
         }
         case 11: {
            WebFormTransferEventParams e = {(int)IPW64CAST(param[0]), (ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = ((WebForm*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int WebFormEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    WebForm(char *lpOemKey = (char*)IPWORKS_OEMKEY_49) {
      m_pObj = IPWorks_WebForm_Create(WebFormEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~WebForm() {
      IPWorks_WebForm_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_WebForm_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_WebForm_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_WebForm_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline char* GetAccept() {
      void* val = IPWorks_WebForm_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetAccept(const char *lpAccept) {
      return IPWorks_WebForm_Set(m_pObj, 1, 0, (void*)lpAccept, 0);
    }

    inline char* GetAuthorization() {
      void* val = IPWorks_WebForm_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetAuthorization(const char *lpAuthorization) {
      return IPWorks_WebForm_Set(m_pObj, 2, 0, (void*)lpAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_WebForm_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_WebForm_Set(m_pObj, 3, 0, val, 0);
    }
    inline int GetConnected() {
      void* val = IPWorks_WebForm_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_WebForm_Set(m_pObj, 4, 0, val, 0);
    }
    inline char* GetContentType() {
      void* val = IPWorks_WebForm_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }

    inline int SetContentType(const char *lpContentType) {
      return IPWorks_WebForm_Set(m_pObj, 5, 0, (void*)lpContentType, 0);
    }

    inline int GetCookieCount() {
      void* val = IPWorks_WebForm_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_WebForm_Set(m_pObj, 6, 0, val, 0);
    }
    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_WebForm_Get(m_pObj, 7, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_WebForm_Get(m_pObj, 8, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_WebForm_Get(m_pObj, 9, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieName(int iCookieIndex, const char *lpCookieName) {
      return IPWorks_WebForm_Set(m_pObj, 9, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_WebForm_Get(m_pObj, 10, iCookieIndex, 0);
      return (char*)val;
    }


    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_WebForm_Get(m_pObj, 11, iCookieIndex, 0);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_WebForm_Get(m_pObj, 12, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieValue(int iCookieIndex, const char *lpCookieValue) {
      return IPWorks_WebForm_Set(m_pObj, 12, iCookieIndex, (void*)lpCookieValue, 0);
    }

    inline int GetEncoding() {
      void* val = IPWorks_WebForm_Get(m_pObj, 13, 0, 0);
      return (int)(long)val;
    }
    inline int SetEncoding(int iEncoding) {
      void* val = (void*)IPW64CAST(iEncoding);
      return IPWorks_WebForm_Set(m_pObj, 13, 0, val, 0);
    }
    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_WebForm_Get(m_pObj, 14, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_WebForm_Set(m_pObj, 14, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_WebForm_Get(m_pObj, 15, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_WebForm_Set(m_pObj, 15, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_WebForm_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_WebForm_Set(m_pObj, 16, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_WebForm_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_WebForm_Set(m_pObj, 17, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_WebForm_Get(m_pObj, 18, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_WebForm_Set(m_pObj, 18, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_WebForm_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_WebForm_Set(m_pObj, 19, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetFollowRedirects() {
      void* val = IPWorks_WebForm_Get(m_pObj, 20, 0, 0);
      return (int)(long)val;
    }
    inline int SetFollowRedirects(int iFollowRedirects) {
      void* val = (void*)IPW64CAST(iFollowRedirects);
      return IPWorks_WebForm_Set(m_pObj, 20, 0, val, 0);
    }
    inline int GetFormVarCount() {
      void* val = IPWorks_WebForm_Get(m_pObj, 21, 0, 0);
      return (int)(long)val;
    }
    inline int SetFormVarCount(int iFormVarCount) {
      void* val = (void*)IPW64CAST(iFormVarCount);
      return IPWorks_WebForm_Set(m_pObj, 21, 0, val, 0);
    }
    inline char* GetFormVarName(int iVarIndex) {
      void* val = IPWorks_WebForm_Get(m_pObj, 22, iVarIndex, 0);
      return (char*)val;
    }

    inline int SetFormVarName(int iVarIndex, const char *lpFormVarName) {
      return IPWorks_WebForm_Set(m_pObj, 22, iVarIndex, (void*)lpFormVarName, 0);
    }

    inline char* GetFormVarValue(int iVarIndex) {
      void* val = IPWorks_WebForm_Get(m_pObj, 23, iVarIndex, 0);
      return (char*)val;
    }

    inline int SetFormVarValue(int iVarIndex, const char *lpFormVarValue) {
      return IPWorks_WebForm_Set(m_pObj, 23, iVarIndex, (void*)lpFormVarValue, 0);
    }

    inline char* GetFrom() {
      void* val = IPWorks_WebForm_Get(m_pObj, 24, 0, 0);
      return (char*)val;
    }

    inline int SetFrom(const char *lpFrom) {
      return IPWorks_WebForm_Set(m_pObj, 24, 0, (void*)lpFrom, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_WebForm_Get(m_pObj, 25, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLocalFile() {
      void* val = IPWorks_WebForm_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }

    inline int SetLocalFile(const char *lpLocalFile) {
      return IPWorks_WebForm_Set(m_pObj, 26, 0, (void*)lpLocalFile, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_WebForm_Get(m_pObj, 27, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_WebForm_Set(m_pObj, 27, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_WebForm_Get(m_pObj, 28, 0, 0);
      return (char*)val;
    }

    inline int SetOtherHeaders(const char *lpOtherHeaders) {
      return IPWorks_WebForm_Set(m_pObj, 28, 0, (void*)lpOtherHeaders, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_WebForm_Get(m_pObj, 29, 0, 0);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_WebForm_Get(m_pObj, 30, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_WebForm_Get(m_pObj, 31, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetPassword() {
      void* val = IPWorks_WebForm_Get(m_pObj, 32, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_WebForm_Set(m_pObj, 32, 0, (void*)lpPassword, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_WebForm_Get(m_pObj, 33, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_WebForm_Set(m_pObj, 33, 0, val, 0);
    }
    inline int GetProxyAutoDetect() {
      void* val = IPWorks_WebForm_Get(m_pObj, 34, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_WebForm_Set(m_pObj, 34, 0, val, 0);
    }
    inline char* GetProxyPassword() {
      void* val = IPWorks_WebForm_Get(m_pObj, 35, 0, 0);
      return (char*)val;
    }

    inline int SetProxyPassword(const char *lpProxyPassword) {
      return IPWorks_WebForm_Set(m_pObj, 35, 0, (void*)lpProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_WebForm_Get(m_pObj, 36, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyPort(int lProxyPort) {
      void* val = (void*)IPW64CAST(lProxyPort);
      return IPWorks_WebForm_Set(m_pObj, 36, 0, val, 0);
    }
    inline char* GetProxyServer() {
      void* val = IPWorks_WebForm_Get(m_pObj, 37, 0, 0);
      return (char*)val;
    }

    inline int SetProxyServer(const char *lpProxyServer) {
      return IPWorks_WebForm_Set(m_pObj, 37, 0, (void*)lpProxyServer, 0);
    }

    inline char* GetProxyUser() {
      void* val = IPWorks_WebForm_Get(m_pObj, 38, 0, 0);
      return (char*)val;
    }

    inline int SetProxyUser(const char *lpProxyUser) {
      return IPWorks_WebForm_Set(m_pObj, 38, 0, (void*)lpProxyUser, 0);
    }

    inline char* GetReferer() {
      void* val = IPWorks_WebForm_Get(m_pObj, 39, 0, 0);
      return (char*)val;
    }

    inline int SetReferer(const char *lpReferer) {
      return IPWorks_WebForm_Set(m_pObj, 39, 0, (void*)lpReferer, 0);
    }

    inline char* GetStatusLine() {
      void* val = IPWorks_WebForm_Get(m_pObj, 40, 0, 0);
      return (char*)val;
    }


    inline int GetTimeout() {
      void* val = IPWorks_WebForm_Get(m_pObj, 41, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_WebForm_Set(m_pObj, 41, 0, val, 0);
    }
    inline int GetTransferredData(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_WebForm_Get(m_pObj, 42, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }


    inline ns_int64 GetTransferredDataLimit() {
      ns_int64 *pval = (ns_int64*)IPWorks_WebForm_Get(m_pObj, 43, 0, 0);
      return *pval;
    }

    inline int SetTransferredDataLimit(ns_int64 lTransferredDataLimit) {
      void* val = (void*)(&lTransferredDataLimit);
      return IPWorks_WebForm_Set(m_pObj, 43, 0, val, 0);
    }

    inline char* GetTransferredHeaders() {
      void* val = IPWorks_WebForm_Get(m_pObj, 44, 0, 0);
      return (char*)val;
    }


    inline char* GetURL() {
      void* val = IPWorks_WebForm_Get(m_pObj, 45, 0, 0);
      return (char*)val;
    }

    inline int SetURL(const char *lpURL) {
      return IPWorks_WebForm_Set(m_pObj, 45, 0, (void*)lpURL, 0);
    }

    inline char* GetUser() {
      void* val = IPWorks_WebForm_Get(m_pObj, 46, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_WebForm_Set(m_pObj, 46, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline int AddCookie(const char* lpszCookieName, const char* lpszCookieValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszCookieName), (void*)IPW64CAST(lpszCookieValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebForm_Do(m_pObj, 2, 2, param, cbparam);
      
      
    }
    inline int AddFormVar(const char* lpszVarName, const char* lpszVarValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszVarName), (void*)IPW64CAST(lpszVarValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebForm_Do(m_pObj, 3, 2, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_WebForm_Do(m_pObj, 4, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebForm_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebForm_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebForm_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int Submit() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebForm_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }
    inline int SubmitTo(const char* lpszURL) {
      void *param[1+1] = {(void*)IPW64CAST(lpszURL), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebForm_Do(m_pObj, 9, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} WebFormConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} WebFormConnectionStatusEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} WebFormDisconnectedEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} WebFormEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} WebFormErrorEventParamsW;

typedef struct {
  LPWSTR Field;
  LPWSTR Value;
  int reserved;
} WebFormHeaderEventParamsW;

typedef struct {
  LPWSTR Location;
  int Accept;
  int reserved;
} WebFormRedirectEventParamsW;

typedef struct {
  LPWSTR Name;
  LPWSTR Value;
  LPWSTR Expires;
  LPWSTR Domain;
  LPWSTR Path;
  int Secure;
  int reserved;
} WebFormSetCookieEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} WebFormStartTransferEventParamsW;

typedef struct {
  LPWSTR HTTPVersion;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} WebFormStatusEventParamsW;

typedef struct {
  int Direction;
  ns_int64 *pBytesTransferred;
  int PercentDone;
  LPWSTR Text;
  int lenText;
  int reserved;
} WebFormTransferEventParamsW;



class WebFormW : public WebForm {

  public: //properties
  
    inline LPWSTR GetAccept() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetAccept(LPWSTR lpAccept) {
      return IPWorks_WebForm_Set(m_pObj, 10000+1, 0, (void*)lpAccept, 0);
    }

    inline LPWSTR GetAuthorization() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetAuthorization(LPWSTR lpAuthorization) {
      return IPWorks_WebForm_Set(m_pObj, 10000+2, 0, (void*)lpAuthorization, 0);
    }





    inline LPWSTR GetContentType() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetContentType(LPWSTR lpContentType) {
      return IPWorks_WebForm_Set(m_pObj, 10000+5, 0, (void*)lpContentType, 0);
    }



    inline LPWSTR GetCookieDomain(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+7, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieExpiration(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+8, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieName(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+9, iCookieIndex, 0);
    }

    inline int SetCookieName(int iCookieIndex, LPWSTR lpCookieName) {
      return IPWorks_WebForm_Set(m_pObj, 10000+9, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline LPWSTR GetCookiePath(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+10, iCookieIndex, 0);
    }





    inline LPWSTR GetCookieValue(int iCookieIndex) {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+12, iCookieIndex, 0);
    }

    inline int SetCookieValue(int iCookieIndex, LPWSTR lpCookieValue) {
      return IPWorks_WebForm_Set(m_pObj, 10000+12, iCookieIndex, (void*)lpCookieValue, 0);
    }







    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetFirewallHost(LPWSTR lpFirewallHost) {
      return IPWorks_WebForm_Set(m_pObj, 10000+16, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetFirewallPassword(LPWSTR lpFirewallPassword) {
      return IPWorks_WebForm_Set(m_pObj, 10000+17, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+19, 0, 0);
    }

    inline int SetFirewallUser(LPWSTR lpFirewallUser) {
      return IPWorks_WebForm_Set(m_pObj, 10000+19, 0, (void*)lpFirewallUser, 0);
    }





    inline LPWSTR GetFormVarName(int iVarIndex) {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+22, iVarIndex, 0);
    }

    inline int SetFormVarName(int iVarIndex, LPWSTR lpFormVarName) {
      return IPWorks_WebForm_Set(m_pObj, 10000+22, iVarIndex, (void*)lpFormVarName, 0);
    }

    inline LPWSTR GetFormVarValue(int iVarIndex) {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+23, iVarIndex, 0);
    }

    inline int SetFormVarValue(int iVarIndex, LPWSTR lpFormVarValue) {
      return IPWorks_WebForm_Set(m_pObj, 10000+23, iVarIndex, (void*)lpFormVarValue, 0);
    }

    inline LPWSTR GetFrom() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+24, 0, 0);
    }

    inline int SetFrom(LPWSTR lpFrom) {
      return IPWorks_WebForm_Set(m_pObj, 10000+24, 0, (void*)lpFrom, 0);
    }



    inline LPWSTR GetLocalFile() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+10000+26, 0, 0);
    }

    inline int SetLocalFile(LPWSTR lpLocalFile) {
      return IPWorks_WebForm_Set(m_pObj, 10000+10000+26, 0, (void*)lpLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+27, 0, 0);
    }

    inline int SetLocalHost(LPWSTR lpLocalHost) {
      return IPWorks_WebForm_Set(m_pObj, 10000+27, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+28, 0, 0);
    }

    inline int SetOtherHeaders(LPWSTR lpOtherHeaders) {
      return IPWorks_WebForm_Set(m_pObj, 10000+28, 0, (void*)lpOtherHeaders, 0);
    }



    inline LPWSTR GetParsedHeaderField(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+30, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetParsedHeaderValue(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+31, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+32, 0, 0);
    }

    inline int SetPassword(LPWSTR lpPassword) {
      return IPWorks_WebForm_Set(m_pObj, 10000+32, 0, (void*)lpPassword, 0);
    }





    inline LPWSTR GetProxyPassword() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+35, 0, 0);
    }

    inline int SetProxyPassword(LPWSTR lpProxyPassword) {
      return IPWorks_WebForm_Set(m_pObj, 10000+35, 0, (void*)lpProxyPassword, 0);
    }



    inline LPWSTR GetProxyServer() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+37, 0, 0);
    }

    inline int SetProxyServer(LPWSTR lpProxyServer) {
      return IPWorks_WebForm_Set(m_pObj, 10000+37, 0, (void*)lpProxyServer, 0);
    }

    inline LPWSTR GetProxyUser() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+38, 0, 0);
    }

    inline int SetProxyUser(LPWSTR lpProxyUser) {
      return IPWorks_WebForm_Set(m_pObj, 10000+38, 0, (void*)lpProxyUser, 0);
    }

    inline LPWSTR GetReferer() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+39, 0, 0);
    }

    inline int SetReferer(LPWSTR lpReferer) {
      return IPWorks_WebForm_Set(m_pObj, 10000+39, 0, (void*)lpReferer, 0);
    }

    inline LPWSTR GetStatusLine() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+40, 0, 0);
    }





    inline LPWSTR GetTransferredData() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+42, 0, 0);
    }


    inline int GetTransferredDataB(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_WebForm_Get(m_pObj, 42, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }



    inline LPWSTR GetTransferredHeaders() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+44, 0, 0);
    }



    inline LPWSTR GetURL() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+45, 0, 0);
    }

    inline int SetURL(LPWSTR lpURL) {
      return IPWorks_WebForm_Set(m_pObj, 10000+45, 0, (void*)lpURL, 0);
    }

    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_WebForm_Get(m_pObj, 10000+46, 0, 0);
    }

    inline int SetUser(LPWSTR lpUser) {
      return IPWorks_WebForm_Set(m_pObj, 10000+46, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnected(WebFormConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(WebFormConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDisconnected(WebFormDisconnectedEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(WebFormEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(WebFormErrorEventParamsW *e) {return 0;}
    virtual int FireHeader(WebFormHeaderEventParamsW *e) {return 0;}
    virtual int FireRedirect(WebFormRedirectEventParamsW *e) {return 0;}
    virtual int FireSetCookie(WebFormSetCookieEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(WebFormStartTransferEventParamsW *e) {return 0;}
    virtual int FireStatus(WebFormStatusEventParamsW *e) {return 0;}
    virtual int FireTransfer(WebFormTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int WebFormEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            WebFormConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            WebFormConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 3: {
            WebFormDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 4: {
            WebFormEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 5: {
            WebFormErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 6: {
            WebFormHeaderEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireHeader(&e);
            break;
         }
         case 7: {
            WebFormRedirectEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]),  0};
            ret_code = FireRedirect(&e);
            param[1] = (void*)(e.Accept);
            break;
         }
         case 8: {
            WebFormSetCookieEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = FireSetCookie(&e);
            break;
         }
         case 9: {
            WebFormStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 10: {
            WebFormStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireStatus(&e);
            break;
         }
         case 11: {
            WebFormTransferEventParamsW e = {(int)IPW64CAST(param[0]), (ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(WebFormConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(WebFormConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDisconnected(WebFormDisconnectedEventParams *e) {return -10000;}
    virtual int FireEndTransfer(WebFormEndTransferEventParams *e) {return -10000;}
    virtual int FireError(WebFormErrorEventParams *e) {return -10000;}
    virtual int FireHeader(WebFormHeaderEventParams *e) {return -10000;}
    virtual int FireRedirect(WebFormRedirectEventParams *e) {return -10000;}
    virtual int FireSetCookie(WebFormSetCookieEventParams *e) {return -10000;}
    virtual int FireStartTransfer(WebFormStartTransferEventParams *e) {return -10000;}
    virtual int FireStatus(WebFormStatusEventParams *e) {return -10000;}
    virtual int FireTransfer(WebFormTransferEventParams *e) {return -10000;}

  public: //methods

    inline int AddCookie(LPWSTR lpszCookieName, LPWSTR lpszCookieValue) {
      void *param[2+1] = {(void*)lpszCookieName, (void*)lpszCookieValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebForm_Do(m_pObj, 10000+2, 2, param, cbparam);
      
    }
    inline int AddFormVar(LPWSTR lpszVarName, LPWSTR lpszVarValue) {
      void *param[2+1] = {(void*)lpszVarName, (void*)lpszVarValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_WebForm_Do(m_pObj, 10000+3, 2, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_WebForm_Do(m_pObj, 10000+4, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebForm_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebForm_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebForm_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int Submit() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_WebForm_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }
    inline int SubmitTo(LPWSTR lpszURL) {
      void *param[1+1] = {(void*)lpszURL, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_WebForm_Do(m_pObj, 10000+9, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_WEBFORM_H_




