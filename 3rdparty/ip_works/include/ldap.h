/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_LDAP_H_
#define _IPWORKS_LDAP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//LDAPAttributeModOps
#define AMO_ADD                                            0
#define AMO_DELETE                                         1
#define AMO_REPLACE                                        2

//AuthMechanisms
#define AM_SIMPLE                                          0
#define AM_DIGEST_MD5                                      1
#define AM_NEGOTIATE                                       2

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TLDAPDerefAliases
#define SDA_NEVER                                          0
#define SDA_IN_SEARCHING                                   1
#define SDA_FINDING_BASE_OBJECT                            2
#define SDA_ALWAYS                                         3

//TLDAPSearchScope
#define SS_BASE_OBJECT                                     0
#define SS_SINGLE_LEVEL                                    1
#define SS_WHOLE_SUBTREE                                   2


extern "C" void* IPWORKS_CALL IPWorks_LDAP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_LDAP_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_LDAP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_LDAP_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} LDAPConnectedEventParams;

typedef struct {
  const char* ConnectionEvent;
  int StatusCode;
  const char* Description;
  int reserved;
} LDAPConnectionStatusEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} LDAPDisconnectedEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} LDAPErrorEventParams;

typedef struct {
  int MessageId;
  const char* DN;
  int ResultCode;
  const char* Description;
  const char* ResponseName;
  const char* ResponseValue;
  int lenResponseValue;
  int reserved;
} LDAPExtendedResponseEventParams;

typedef struct {
  int MessageId;
  const char* DN;
  int ResultCode;
  const char* Description;
  int reserved;
} LDAPResultEventParams;

typedef struct {
  int MessageId;
  const char* DN;
  int ResultCode;
  const char* Description;
  int reserved;
} LDAPSearchCompleteEventParams;

typedef struct {
  int MessageId;
  const char* DN;
  int ResultCode;
  const char* Description;
  int CancelSearch;
  int reserved;
} LDAPSearchPageEventParams;

typedef struct {
  int MessageId;
  const char* DN;
  int reserved;
} LDAPSearchResultEventParams;

typedef struct {
  int MessageId;
  const char* LdapUrl;
  int reserved;
} LDAPSearchResultReferenceEventParams;



class LDAP {
  
  public: //events
  
    virtual int FireConnected(LDAPConnectedEventParams *e) {return 0;}
    virtual int FireConnectionStatus(LDAPConnectionStatusEventParams *e) {return 0;}
    virtual int FireDisconnected(LDAPDisconnectedEventParams *e) {return 0;}
    virtual int FireError(LDAPErrorEventParams *e) {return 0;}
    virtual int FireExtendedResponse(LDAPExtendedResponseEventParams *e) {return 0;}
    virtual int FireResult(LDAPResultEventParams *e) {return 0;}
    virtual int FireSearchComplete(LDAPSearchCompleteEventParams *e) {return 0;}
    virtual int FireSearchPage(LDAPSearchPageEventParams *e) {return 0;}
    virtual int FireSearchResult(LDAPSearchResultEventParams *e) {return 0;}
    virtual int FireSearchResultReference(LDAPSearchResultReferenceEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL LDAPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((LDAP*)lpObj)->LDAPEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            LDAPConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((LDAP*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            LDAPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((LDAP*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 3: {
            LDAPDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((LDAP*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 4: {
            LDAPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((LDAP*)lpObj)->FireError(&e);
            break;
         }
         case 5: {
            LDAPExtendedResponseEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (char*)IPW64CAST(param[5]), (int)IPW64CAST(cbparam[5]),  0};
            ret_code = ((LDAP*)lpObj)->FireExtendedResponse(&e);
            break;
         }
         case 6: {
            LDAPResultEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]),  0};
            ret_code = ((LDAP*)lpObj)->FireResult(&e);
            break;
         }
         case 7: {
            LDAPSearchCompleteEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]),  0};
            ret_code = ((LDAP*)lpObj)->FireSearchComplete(&e);
            break;
         }
         case 8: {
            LDAPSearchPageEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(param[4]),  0};
            ret_code = ((LDAP*)lpObj)->FireSearchPage(&e);
            param[4] = (void*)IPW64CAST(e.CancelSearch);
            break;
         }
         case 9: {
            LDAPSearchResultEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((LDAP*)lpObj)->FireSearchResult(&e);
            break;
         }
         case 10: {
            LDAPSearchResultReferenceEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((LDAP*)lpObj)->FireSearchResultReference(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int LDAPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    LDAP(char *lpOemKey = (char*)IPWORKS_OEMKEY_33) {
      m_pObj = IPWorks_LDAP_Create(LDAPEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~LDAP() {
      IPWorks_LDAP_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_LDAP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_LDAP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_LDAP_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline int GetAcceptData() {
      void* val = IPWorks_LDAP_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetAcceptData(int bAcceptData) {
      void* val = (void*)IPW64CAST(bAcceptData);
      return IPWorks_LDAP_Set(m_pObj, 1, 0, val, 0);
    }
    inline int GetAttrCount() {
      void* val = IPWorks_LDAP_Get(m_pObj, 2, 0, 0);
      return (int)(long)val;
    }
    inline int SetAttrCount(int iAttrCount) {
      void* val = (void*)IPW64CAST(iAttrCount);
      return IPWorks_LDAP_Set(m_pObj, 2, 0, val, 0);
    }
    inline char* GetAttrType(int iAttrIndex) {
      void* val = IPWorks_LDAP_Get(m_pObj, 3, iAttrIndex, 0);
      return (char*)val;
    }

    inline int SetAttrType(int iAttrIndex, const char *lpAttrType) {
      return IPWorks_LDAP_Set(m_pObj, 3, iAttrIndex, (void*)lpAttrType, 0);
    }

    inline int GetAttrModOp(int iAttrIndex) {
      void* val = IPWorks_LDAP_Get(m_pObj, 4, iAttrIndex, 0);
      return (int)(long)val;
    }
    inline int SetAttrModOp(int iAttrIndex, int iAttrModOp) {
      void* val = (void*)IPW64CAST(iAttrModOp);
      return IPWorks_LDAP_Set(m_pObj, 4, iAttrIndex, val, 0);
    }
    inline int GetAttrValue(int iAttrIndex, char *&lpAttrValue, int &lenAttrValue) {
      lpAttrValue = (char*)IPWorks_LDAP_Get(m_pObj, 5, iAttrIndex, &lenAttrValue);
      return lpAttrValue ? 0 : lenAttrValue;
    }

    inline int SetAttrValue(int iAttrIndex, const char *lpAttrValue, int lenAttrValue) {
      return IPWorks_LDAP_Set(m_pObj, 5, iAttrIndex, (void*)lpAttrValue, lenAttrValue);
    }

    inline int GetAuthMechanism() {
      void* val = IPWorks_LDAP_Get(m_pObj, 6, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthMechanism(int iAuthMechanism) {
      void* val = (void*)IPW64CAST(iAuthMechanism);
      return IPWorks_LDAP_Set(m_pObj, 6, 0, val, 0);
    }
    inline int GetConnected() {
      void* val = IPWorks_LDAP_Get(m_pObj, 7, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_LDAP_Set(m_pObj, 7, 0, val, 0);
    }
    inline int GetDeleteOldRDN() {
      void* val = IPWorks_LDAP_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }
    inline int SetDeleteOldRDN(int bDeleteOldRDN) {
      void* val = (void*)IPW64CAST(bDeleteOldRDN);
      return IPWorks_LDAP_Set(m_pObj, 8, 0, val, 0);
    }
    inline char* GetDN() {
      void* val = IPWorks_LDAP_Get(m_pObj, 9, 0, 0);
      return (char*)val;
    }

    inline int SetDN(const char *lpDN) {
      return IPWorks_LDAP_Set(m_pObj, 9, 0, (void*)lpDN, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_LDAP_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_LDAP_Set(m_pObj, 10, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_LDAP_Get(m_pObj, 11, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_LDAP_Set(m_pObj, 11, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_LDAP_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_LDAP_Set(m_pObj, 12, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_LDAP_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_LDAP_Set(m_pObj, 13, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_LDAP_Get(m_pObj, 14, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_LDAP_Set(m_pObj, 14, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_LDAP_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_LDAP_Set(m_pObj, 15, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_LDAP_Get(m_pObj, 16, 0, 0);
      return (int)(long)val;
    }

    inline int GetLDAPVersion() {
      void* val = IPWorks_LDAP_Get(m_pObj, 17, 0, 0);
      return (int)(long)val;
    }
    inline int SetLDAPVersion(int iLDAPVersion) {
      void* val = (void*)IPW64CAST(iLDAPVersion);
      return IPWorks_LDAP_Set(m_pObj, 17, 0, val, 0);
    }
    inline char* GetLocalHost() {
      void* val = IPWorks_LDAP_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_LDAP_Set(m_pObj, 18, 0, (void*)lpLocalHost, 0);
    }

    inline int GetMessageId() {
      void* val = IPWorks_LDAP_Get(m_pObj, 19, 0, 0);
      return (int)(long)val;
    }
    inline int SetMessageId(int iMessageId) {
      void* val = (void*)IPW64CAST(iMessageId);
      return IPWorks_LDAP_Set(m_pObj, 19, 0, val, 0);
    }
    inline int GetPageSize() {
      void* val = IPWorks_LDAP_Get(m_pObj, 20, 0, 0);
      return (int)(long)val;
    }
    inline int SetPageSize(int iPageSize) {
      void* val = (void*)IPW64CAST(iPageSize);
      return IPWorks_LDAP_Set(m_pObj, 20, 0, val, 0);
    }
    inline char* GetPassword() {
      void* val = IPWorks_LDAP_Get(m_pObj, 21, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_LDAP_Set(m_pObj, 21, 0, (void*)lpPassword, 0);
    }

    inline int GetReferenceCount() {
      void* val = IPWorks_LDAP_Get(m_pObj, 22, 0, 0);
      return (int)(long)val;
    }

    inline char* GetReferenceURL(int iReferenceIndex) {
      void* val = IPWorks_LDAP_Get(m_pObj, 23, iReferenceIndex, 0);
      return (char*)val;
    }


    inline int GetResultCode() {
      void* val = IPWorks_LDAP_Get(m_pObj, 24, 0, 0);
      return (int)(long)val;
    }

    inline char* GetResultDescription() {
      void* val = IPWorks_LDAP_Get(m_pObj, 25, 0, 0);
      return (char*)val;
    }


    inline char* GetResultDN() {
      void* val = IPWorks_LDAP_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }


    inline int GetSearchDerefAliases() {
      void* val = IPWorks_LDAP_Get(m_pObj, 27, 0, 0);
      return (int)(long)val;
    }
    inline int SetSearchDerefAliases(int iSearchDerefAliases) {
      void* val = (void*)IPW64CAST(iSearchDerefAliases);
      return IPWorks_LDAP_Set(m_pObj, 27, 0, val, 0);
    }
    inline int GetSearchReturnValues() {
      void* val = IPWorks_LDAP_Get(m_pObj, 28, 0, 0);
      return (int)(long)val;
    }
    inline int SetSearchReturnValues(int bSearchReturnValues) {
      void* val = (void*)IPW64CAST(bSearchReturnValues);
      return IPWorks_LDAP_Set(m_pObj, 28, 0, val, 0);
    }
    inline int GetSearchScope() {
      void* val = IPWorks_LDAP_Get(m_pObj, 29, 0, 0);
      return (int)(long)val;
    }
    inline int SetSearchScope(int iSearchScope) {
      void* val = (void*)IPW64CAST(iSearchScope);
      return IPWorks_LDAP_Set(m_pObj, 29, 0, val, 0);
    }
    inline int GetSearchSizeLimit() {
      void* val = IPWorks_LDAP_Get(m_pObj, 30, 0, 0);
      return (int)(long)val;
    }
    inline int SetSearchSizeLimit(int iSearchSizeLimit) {
      void* val = (void*)IPW64CAST(iSearchSizeLimit);
      return IPWorks_LDAP_Set(m_pObj, 30, 0, val, 0);
    }
    inline int GetSearchTimeLimit() {
      void* val = IPWorks_LDAP_Get(m_pObj, 31, 0, 0);
      return (int)(long)val;
    }
    inline int SetSearchTimeLimit(int iSearchTimeLimit) {
      void* val = (void*)IPW64CAST(iSearchTimeLimit);
      return IPWorks_LDAP_Set(m_pObj, 31, 0, val, 0);
    }
    inline char* GetServerName() {
      void* val = IPWorks_LDAP_Get(m_pObj, 32, 0, 0);
      return (char*)val;
    }

    inline int SetServerName(const char *lpServerName) {
      return IPWorks_LDAP_Set(m_pObj, 32, 0, (void*)lpServerName, 0);
    }

    inline int GetServerPort() {
      void* val = IPWorks_LDAP_Get(m_pObj, 33, 0, 0);
      return (int)(long)val;
    }
    inline int SetServerPort(int lServerPort) {
      void* val = (void*)IPW64CAST(lServerPort);
      return IPWorks_LDAP_Set(m_pObj, 33, 0, val, 0);
    }
    inline char* GetSortAttributes() {
      void* val = IPWorks_LDAP_Get(m_pObj, 34, 0, 0);
      return (char*)val;
    }

    inline int SetSortAttributes(const char *lpSortAttributes) {
      return IPWorks_LDAP_Set(m_pObj, 34, 0, (void*)lpSortAttributes, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_LDAP_Get(m_pObj, 35, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_LDAP_Set(m_pObj, 35, 0, val, 0);
    }

  public: //methods

    inline int Abandon(int iMessageId) {
      void *param[1+1] = {(void*)IPW64CAST(iMessageId), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 2, 1, param, cbparam);
      
      
    }
    inline int Add() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline char* Attr(const char* lpszAttrType) {
      void *param[1+1] = {(void*)IPW64CAST(lpszAttrType), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_LDAP_Do(m_pObj, 4, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Bind() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int Compare() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_LDAP_Do(m_pObj, 7, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Delete() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int ExtendedRequest(const char* lpszRequestName, const char* lpRequestValue, int lenRequestValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszRequestName), (void*)IPW64CAST(lpRequestValue), 0};
      int cbparam[2+1] = {0, lenRequestValue, 0};
      return IPWorks_LDAP_Do(m_pObj, 10, 2, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 11, 0, param, cbparam);
      
      
    }
    inline int Modify() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 12, 0, param, cbparam);
      
      
    }
    inline int ModifyRDN(const char* lpszNewRDN) {
      void *param[1+1] = {(void*)IPW64CAST(lpszNewRDN), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 13, 1, param, cbparam);
      
      
    }
    inline int MoveToDN(const char* lpszNewSuperior) {
      void *param[1+1] = {(void*)IPW64CAST(lpszNewSuperior), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 14, 1, param, cbparam);
      
      
    }
    inline int Search(const char* lpszSearchFilter) {
      void *param[1+1] = {(void*)IPW64CAST(lpszSearchFilter), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 15, 1, param, cbparam);
      
      
    }
    inline int Unbind() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 16, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} LDAPConnectedEventParamsW;

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} LDAPConnectionStatusEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} LDAPDisconnectedEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} LDAPErrorEventParamsW;

typedef struct {
  int MessageId;
  LPWSTR DN;
  int ResultCode;
  LPWSTR Description;
  LPWSTR ResponseName;
  LPWSTR ResponseValue;
  int lenResponseValue;
  int reserved;
} LDAPExtendedResponseEventParamsW;

typedef struct {
  int MessageId;
  LPWSTR DN;
  int ResultCode;
  LPWSTR Description;
  int reserved;
} LDAPResultEventParamsW;

typedef struct {
  int MessageId;
  LPWSTR DN;
  int ResultCode;
  LPWSTR Description;
  int reserved;
} LDAPSearchCompleteEventParamsW;

typedef struct {
  int MessageId;
  LPWSTR DN;
  int ResultCode;
  LPWSTR Description;
  int CancelSearch;
  int reserved;
} LDAPSearchPageEventParamsW;

typedef struct {
  int MessageId;
  LPWSTR DN;
  int reserved;
} LDAPSearchResultEventParamsW;

typedef struct {
  int MessageId;
  LPWSTR LdapUrl;
  int reserved;
} LDAPSearchResultReferenceEventParamsW;



class LDAPW : public LDAP {

  public: //properties
  




    inline LPWSTR GetAttrType(int iAttrIndex) {
      return (LPWSTR)IPWorks_LDAP_Get(m_pObj, 10000+3, iAttrIndex, 0);
    }

    inline int SetAttrType(int iAttrIndex, LPWSTR lpAttrType) {
      return IPWorks_LDAP_Set(m_pObj, 10000+3, iAttrIndex, (void*)lpAttrType, 0);
    }



    inline LPWSTR GetAttrValue(int iAttrIndex) {
      return (LPWSTR)IPWorks_LDAP_Get(m_pObj, 10000+5, iAttrIndex, 0);
    }

    inline int SetAttrValue(int iAttrIndex, LPWSTR lpAttrValue) {
      return IPWorks_LDAP_Set(m_pObj, 10000+5, iAttrIndex, (void*)lpAttrValue, 0);
    }
    inline int GetAttrValueB(int iAttrIndex, char *&lpAttrValue, int &lenAttrValue) {
      lpAttrValue = (char*)IPWorks_LDAP_Get(m_pObj, 5, iAttrIndex, &lenAttrValue);
      return lpAttrValue ? 0 : lenAttrValue;
    }
    inline int SetAttrValueB(int iAttrIndex, const char *lpAttrValue, int lenAttrValue) {
      return IPWorks_LDAP_Set(m_pObj, 5, iAttrIndex, (void*)lpAttrValue, lenAttrValue);
    }






    inline LPWSTR GetDN() {
      return (LPWSTR)IPWorks_LDAP_Get(m_pObj, 10000+9, 0, 0);
    }

    inline int SetDN(LPWSTR lpDN) {
      return IPWorks_LDAP_Set(m_pObj, 10000+9, 0, (void*)lpDN, 0);
    }





    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_LDAP_Get(m_pObj, 10000+12, 0, 0);
    }

    inline int SetFirewallHost(LPWSTR lpFirewallHost) {
      return IPWorks_LDAP_Set(m_pObj, 10000+12, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_LDAP_Get(m_pObj, 10000+13, 0, 0);
    }

    inline int SetFirewallPassword(LPWSTR lpFirewallPassword) {
      return IPWorks_LDAP_Set(m_pObj, 10000+13, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_LDAP_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetFirewallUser(LPWSTR lpFirewallUser) {
      return IPWorks_LDAP_Set(m_pObj, 10000+15, 0, (void*)lpFirewallUser, 0);
    }





    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_LDAP_Get(m_pObj, 10000+18, 0, 0);
    }

    inline int SetLocalHost(LPWSTR lpLocalHost) {
      return IPWorks_LDAP_Set(m_pObj, 10000+18, 0, (void*)lpLocalHost, 0);
    }





    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_LDAP_Get(m_pObj, 10000+21, 0, 0);
    }

    inline int SetPassword(LPWSTR lpPassword) {
      return IPWorks_LDAP_Set(m_pObj, 10000+21, 0, (void*)lpPassword, 0);
    }



    inline LPWSTR GetReferenceURL(int iReferenceIndex) {
      return (LPWSTR)IPWorks_LDAP_Get(m_pObj, 10000+23, iReferenceIndex, 0);
    }





    inline LPWSTR GetResultDescription() {
      return (LPWSTR)IPWorks_LDAP_Get(m_pObj, 10000+25, 0, 0);
    }



    inline LPWSTR GetResultDN() {
      return (LPWSTR)IPWorks_LDAP_Get(m_pObj, 10000+26, 0, 0);
    }













    inline LPWSTR GetServerName() {
      return (LPWSTR)IPWorks_LDAP_Get(m_pObj, 10000+32, 0, 0);
    }

    inline int SetServerName(LPWSTR lpServerName) {
      return IPWorks_LDAP_Set(m_pObj, 10000+32, 0, (void*)lpServerName, 0);
    }



    inline LPWSTR GetSortAttributes() {
      return (LPWSTR)IPWorks_LDAP_Get(m_pObj, 10000+34, 0, 0);
    }

    inline int SetSortAttributes(LPWSTR lpSortAttributes) {
      return IPWorks_LDAP_Set(m_pObj, 10000+34, 0, (void*)lpSortAttributes, 0);
    }





  public: //events
  
    virtual int FireConnected(LDAPConnectedEventParamsW *e) {return 0;}
    virtual int FireConnectionStatus(LDAPConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDisconnected(LDAPDisconnectedEventParamsW *e) {return 0;}
    virtual int FireError(LDAPErrorEventParamsW *e) {return 0;}
    virtual int FireExtendedResponse(LDAPExtendedResponseEventParamsW *e) {return 0;}
    virtual int FireResult(LDAPResultEventParamsW *e) {return 0;}
    virtual int FireSearchComplete(LDAPSearchCompleteEventParamsW *e) {return 0;}
    virtual int FireSearchPage(LDAPSearchPageEventParamsW *e) {return 0;}
    virtual int FireSearchResult(LDAPSearchResultEventParamsW *e) {return 0;}
    virtual int FireSearchResultReference(LDAPSearchResultReferenceEventParamsW *e) {return 0;}


  protected:
  
    virtual int LDAPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            LDAPConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            LDAPConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 3: {
            LDAPDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 4: {
            LDAPErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 5: {
            LDAPExtendedResponseEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (LPWSTR)IPW64CAST(param[5]), (int)IPW64CAST(cbparam[5]),  0};
            ret_code = FireExtendedResponse(&e);
            break;
         }
         case 6: {
            LDAPResultEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]),  0};
            ret_code = FireResult(&e);
            break;
         }
         case 7: {
            LDAPSearchCompleteEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]),  0};
            ret_code = FireSearchComplete(&e);
            break;
         }
         case 8: {
            LDAPSearchPageEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(param[4]),  0};
            ret_code = FireSearchPage(&e);
            param[4] = (void*)(e.CancelSearch);
            break;
         }
         case 9: {
            LDAPSearchResultEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireSearchResult(&e);
            break;
         }
         case 10: {
            LDAPSearchResultReferenceEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireSearchResultReference(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(LDAPConnectedEventParams *e) {return -10000;}
    virtual int FireConnectionStatus(LDAPConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDisconnected(LDAPDisconnectedEventParams *e) {return -10000;}
    virtual int FireError(LDAPErrorEventParams *e) {return -10000;}
    virtual int FireExtendedResponse(LDAPExtendedResponseEventParams *e) {return -10000;}
    virtual int FireResult(LDAPResultEventParams *e) {return -10000;}
    virtual int FireSearchComplete(LDAPSearchCompleteEventParams *e) {return -10000;}
    virtual int FireSearchPage(LDAPSearchPageEventParams *e) {return -10000;}
    virtual int FireSearchResult(LDAPSearchResultEventParams *e) {return -10000;}
    virtual int FireSearchResultReference(LDAPSearchResultReferenceEventParams *e) {return -10000;}

  public: //methods

    inline int Abandon(int iMessageId) {
      void *param[1+1] = {(void*)iMessageId, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 10000+2, 1, param, cbparam);
      
    }
    inline int Add() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline LPWSTR Attr(LPWSTR lpszAttrType) {
      void *param[1+1] = {(void*)lpszAttrType, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_LDAP_Do(m_pObj, 10000+4, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Bind() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int Compare() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_LDAP_Do(m_pObj, 10000+7, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Delete() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int ExtendedRequest(LPWSTR lpszRequestName, LPWSTR lpRequestValue, int lenRequestValue) {
      void *param[2+1] = {(void*)lpszRequestName, (void*)lpRequestValue, 0};
      int cbparam[2+1] = {0, lenRequestValue, 0};
      return IPWorks_LDAP_Do(m_pObj, 10000+10, 2, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 10000+11, 0, param, cbparam);
      
    }
    inline int Modify() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 10000+12, 0, param, cbparam);
      
    }
    inline int ModifyRDN(LPWSTR lpszNewRDN) {
      void *param[1+1] = {(void*)lpszNewRDN, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 10000+13, 1, param, cbparam);
      
    }
    inline int MoveToDN(LPWSTR lpszNewSuperior) {
      void *param[1+1] = {(void*)lpszNewSuperior, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 10000+14, 1, param, cbparam);
      
    }
    inline int Search(LPWSTR lpszSearchFilter) {
      void *param[1+1] = {(void*)lpszSearchFilter, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_LDAP_Do(m_pObj, 10000+15, 1, param, cbparam);
      
    }
    inline int Unbind() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_LDAP_Do(m_pObj, 10000+16, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_LDAP_H_




