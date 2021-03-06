/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_ODATA_H_
#define _IPWORKS_ODATA_H_

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

//AtomTextTypes
#define TT_TEXT                                            0
#define TT_HTML                                            1
#define TT_XHTML                                           2

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//AssociationMultiplicities
#define NM_ZERO_ONE                                        0
#define NM_ONE                                             1
#define NM_MANY                                            2

//AssociationDeleteActions
#define DA_NONE                                            0
#define DA_CASCADE                                         1


extern "C" void* IPWORKS_CALL IPWorks_OData_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_OData_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OData_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_OData_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_OData_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_OData_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_OData_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OData_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_OData_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_OData_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} ODataConnectedEventParams;

typedef struct {
  int StatusCode;
  const char* Description;
  int reserved;
} ODataDisconnectedEventParams;

typedef struct {
  int Direction;
  int reserved;
} ODataEndTransferEventParams;

typedef struct {
  const char* Name;
  int reserved;
} ODataEntityEventParams;

typedef struct {
  const char* Id;
  const char* Title;
  const char* Summary;
  const char* ETag;
  int reserved;
} ODataEntryEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} ODataErrorEventParams;

typedef struct {
  const char* Field;
  const char* Value;
  int reserved;
} ODataHeaderEventParams;

typedef struct {
  const char* Name;
  const char* TypeName;
  int Nullable;
  int reserved;
} ODataPropertyEventParams;

typedef struct {
  const char* Name;
  const char* Value;
  const char* Expires;
  const char* Domain;
  const char* Path;
  int Secure;
  int reserved;
} ODataSetCookieEventParams;

typedef struct {
  int Direction;
  int reserved;
} ODataStartTransferEventParams;

typedef struct {
  const char* HTTPVersion;
  int StatusCode;
  const char* Description;
  int reserved;
} ODataStatusEventParams;

typedef struct {
  int Direction;
  ns_int64 *pBytesTransferred;
  int PercentDone;
  const char* Text;
  int lenText;
  int reserved;
} ODataTransferEventParams;



class OData {
  
  public: //events
  
    virtual int FireConnected(ODataConnectedEventParams *e) {return 0;}
    virtual int FireDisconnected(ODataDisconnectedEventParams *e) {return 0;}
    virtual int FireEndTransfer(ODataEndTransferEventParams *e) {return 0;}
    virtual int FireEntity(ODataEntityEventParams *e) {return 0;}
    virtual int FireEntry(ODataEntryEventParams *e) {return 0;}
    virtual int FireError(ODataErrorEventParams *e) {return 0;}
    virtual int FireHeader(ODataHeaderEventParams *e) {return 0;}
    virtual int FireProperty(ODataPropertyEventParams *e) {return 0;}
    virtual int FireSetCookie(ODataSetCookieEventParams *e) {return 0;}
    virtual int FireStartTransfer(ODataStartTransferEventParams *e) {return 0;}
    virtual int FireStatus(ODataStatusEventParams *e) {return 0;}
    virtual int FireTransfer(ODataTransferEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL ODataEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((OData*)lpObj)->ODataEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            ODataConnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((OData*)lpObj)->FireConnected(&e);
            break;
         }
         case 2: {
            ODataDisconnectedEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((OData*)lpObj)->FireDisconnected(&e);
            break;
         }
         case 3: {
            ODataEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((OData*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 4: {
            ODataEntityEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((OData*)lpObj)->FireEntity(&e);
            break;
         }
         case 5: {
            ODataEntryEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]),  0};
            ret_code = ((OData*)lpObj)->FireEntry(&e);
            break;
         }
         case 6: {
            ODataErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((OData*)lpObj)->FireError(&e);
            break;
         }
         case 7: {
            ODataHeaderEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((OData*)lpObj)->FireHeader(&e);
            break;
         }
         case 8: {
            ODataPropertyEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = ((OData*)lpObj)->FireProperty(&e);
            break;
         }
         case 9: {
            ODataSetCookieEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = ((OData*)lpObj)->FireSetCookie(&e);
            break;
         }
         case 10: {
            ODataStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((OData*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 11: {
            ODataStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((OData*)lpObj)->FireStatus(&e);
            break;
         }
         case 12: {
            ODataTransferEventParams e = {(int)IPW64CAST(param[0]), (ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = ((OData*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int ODataEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    OData(char *lpOemKey = (char*)IPWORKS_OEMKEY_81) {
      m_pObj = IPWorks_OData_Create(ODataEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~OData() {
      IPWorks_OData_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_OData_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_OData_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_OData_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline char* GetAuthorization() {
      void* val = IPWorks_OData_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetAuthorization(const char *lpAuthorization) {
      return IPWorks_OData_Set(m_pObj, 1, 0, (void*)lpAuthorization, 0);
    }

    inline int GetAuthScheme() {
      void* val = IPWorks_OData_Get(m_pObj, 2, 0, 0);
      return (int)(long)val;
    }
    inline int SetAuthScheme(int iAuthScheme) {
      void* val = (void*)IPW64CAST(iAuthScheme);
      return IPWorks_OData_Set(m_pObj, 2, 0, val, 0);
    }
    inline char* GetChannelAuthorEmail() {
      void* val = IPWorks_OData_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }

    inline int SetChannelAuthorEmail(const char *lpChannelAuthorEmail) {
      return IPWorks_OData_Set(m_pObj, 3, 0, (void*)lpChannelAuthorEmail, 0);
    }

    inline char* GetChannelAuthorName() {
      void* val = IPWorks_OData_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetChannelAuthorName(const char *lpChannelAuthorName) {
      return IPWorks_OData_Set(m_pObj, 4, 0, (void*)lpChannelAuthorName, 0);
    }

    inline char* GetChannelAuthorUri() {
      void* val = IPWorks_OData_Get(m_pObj, 5, 0, 0);
      return (char*)val;
    }

    inline int SetChannelAuthorUri(const char *lpChannelAuthorUri) {
      return IPWorks_OData_Set(m_pObj, 5, 0, (void*)lpChannelAuthorUri, 0);
    }

    inline char* GetChannelCategoryLabel() {
      void* val = IPWorks_OData_Get(m_pObj, 6, 0, 0);
      return (char*)val;
    }

    inline int SetChannelCategoryLabel(const char *lpChannelCategoryLabel) {
      return IPWorks_OData_Set(m_pObj, 6, 0, (void*)lpChannelCategoryLabel, 0);
    }

    inline char* GetChannelCategoryScheme() {
      void* val = IPWorks_OData_Get(m_pObj, 7, 0, 0);
      return (char*)val;
    }

    inline int SetChannelCategoryScheme(const char *lpChannelCategoryScheme) {
      return IPWorks_OData_Set(m_pObj, 7, 0, (void*)lpChannelCategoryScheme, 0);
    }

    inline char* GetChannelCategoryTerm() {
      void* val = IPWorks_OData_Get(m_pObj, 8, 0, 0);
      return (char*)val;
    }

    inline int SetChannelCategoryTerm(const char *lpChannelCategoryTerm) {
      return IPWorks_OData_Set(m_pObj, 8, 0, (void*)lpChannelCategoryTerm, 0);
    }

    inline char* GetChannelContributorEmail() {
      void* val = IPWorks_OData_Get(m_pObj, 9, 0, 0);
      return (char*)val;
    }

    inline int SetChannelContributorEmail(const char *lpChannelContributorEmail) {
      return IPWorks_OData_Set(m_pObj, 9, 0, (void*)lpChannelContributorEmail, 0);
    }

    inline char* GetChannelContributorName() {
      void* val = IPWorks_OData_Get(m_pObj, 10, 0, 0);
      return (char*)val;
    }

    inline int SetChannelContributorName(const char *lpChannelContributorName) {
      return IPWorks_OData_Set(m_pObj, 10, 0, (void*)lpChannelContributorName, 0);
    }

    inline char* GetChannelContributorUri() {
      void* val = IPWorks_OData_Get(m_pObj, 11, 0, 0);
      return (char*)val;
    }

    inline int SetChannelContributorUri(const char *lpChannelContributorUri) {
      return IPWorks_OData_Set(m_pObj, 11, 0, (void*)lpChannelContributorUri, 0);
    }

    inline char* GetChannelGenerator() {
      void* val = IPWorks_OData_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }

    inline int SetChannelGenerator(const char *lpChannelGenerator) {
      return IPWorks_OData_Set(m_pObj, 12, 0, (void*)lpChannelGenerator, 0);
    }

    inline char* GetChannelIcon() {
      void* val = IPWorks_OData_Get(m_pObj, 13, 0, 0);
      return (char*)val;
    }

    inline int SetChannelIcon(const char *lpChannelIcon) {
      return IPWorks_OData_Set(m_pObj, 13, 0, (void*)lpChannelIcon, 0);
    }

    inline char* GetChannelId() {
      void* val = IPWorks_OData_Get(m_pObj, 14, 0, 0);
      return (char*)val;
    }

    inline int SetChannelId(const char *lpChannelId) {
      return IPWorks_OData_Set(m_pObj, 14, 0, (void*)lpChannelId, 0);
    }

    inline char* GetChannelLinkHref() {
      void* val = IPWorks_OData_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLinkHref(const char *lpChannelLinkHref) {
      return IPWorks_OData_Set(m_pObj, 15, 0, (void*)lpChannelLinkHref, 0);
    }

    inline char* GetChannelLinkHrefLang() {
      void* val = IPWorks_OData_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLinkHrefLang(const char *lpChannelLinkHrefLang) {
      return IPWorks_OData_Set(m_pObj, 16, 0, (void*)lpChannelLinkHrefLang, 0);
    }

    inline char* GetChannelLinkLength() {
      void* val = IPWorks_OData_Get(m_pObj, 17, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLinkLength(const char *lpChannelLinkLength) {
      return IPWorks_OData_Set(m_pObj, 17, 0, (void*)lpChannelLinkLength, 0);
    }

    inline char* GetChannelLinkRel() {
      void* val = IPWorks_OData_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLinkRel(const char *lpChannelLinkRel) {
      return IPWorks_OData_Set(m_pObj, 18, 0, (void*)lpChannelLinkRel, 0);
    }

    inline char* GetChannelLinkTitle() {
      void* val = IPWorks_OData_Get(m_pObj, 19, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLinkTitle(const char *lpChannelLinkTitle) {
      return IPWorks_OData_Set(m_pObj, 19, 0, (void*)lpChannelLinkTitle, 0);
    }

    inline char* GetChannelLinkType() {
      void* val = IPWorks_OData_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLinkType(const char *lpChannelLinkType) {
      return IPWorks_OData_Set(m_pObj, 20, 0, (void*)lpChannelLinkType, 0);
    }

    inline char* GetChannelLogo() {
      void* val = IPWorks_OData_Get(m_pObj, 21, 0, 0);
      return (char*)val;
    }

    inline int SetChannelLogo(const char *lpChannelLogo) {
      return IPWorks_OData_Set(m_pObj, 21, 0, (void*)lpChannelLogo, 0);
    }

    inline char* GetChannelRights() {
      void* val = IPWorks_OData_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }

    inline int SetChannelRights(const char *lpChannelRights) {
      return IPWorks_OData_Set(m_pObj, 22, 0, (void*)lpChannelRights, 0);
    }

    inline int GetChannelRightsTextType() {
      void* val = IPWorks_OData_Get(m_pObj, 23, 0, 0);
      return (int)(long)val;
    }
    inline int SetChannelRightsTextType(int iChannelRightsTextType) {
      void* val = (void*)IPW64CAST(iChannelRightsTextType);
      return IPWorks_OData_Set(m_pObj, 23, 0, val, 0);
    }
    inline char* GetChannelSubtitle() {
      void* val = IPWorks_OData_Get(m_pObj, 24, 0, 0);
      return (char*)val;
    }

    inline int SetChannelSubtitle(const char *lpChannelSubtitle) {
      return IPWorks_OData_Set(m_pObj, 24, 0, (void*)lpChannelSubtitle, 0);
    }

    inline int GetChannelSubtitleTextType() {
      void* val = IPWorks_OData_Get(m_pObj, 25, 0, 0);
      return (int)(long)val;
    }
    inline int SetChannelSubtitleTextType(int iChannelSubtitleTextType) {
      void* val = (void*)IPW64CAST(iChannelSubtitleTextType);
      return IPWorks_OData_Set(m_pObj, 25, 0, val, 0);
    }
    inline char* GetChannelTitle() {
      void* val = IPWorks_OData_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }

    inline int SetChannelTitle(const char *lpChannelTitle) {
      return IPWorks_OData_Set(m_pObj, 26, 0, (void*)lpChannelTitle, 0);
    }

    inline int GetChannelTitleTextType() {
      void* val = IPWorks_OData_Get(m_pObj, 27, 0, 0);
      return (int)(long)val;
    }
    inline int SetChannelTitleTextType(int iChannelTitleTextType) {
      void* val = (void*)IPW64CAST(iChannelTitleTextType);
      return IPWorks_OData_Set(m_pObj, 27, 0, val, 0);
    }
    inline char* GetChannelUpdated() {
      void* val = IPWorks_OData_Get(m_pObj, 28, 0, 0);
      return (char*)val;
    }

    inline int SetChannelUpdated(const char *lpChannelUpdated) {
      return IPWorks_OData_Set(m_pObj, 28, 0, (void*)lpChannelUpdated, 0);
    }

    inline int GetCookieCount() {
      void* val = IPWorks_OData_Get(m_pObj, 29, 0, 0);
      return (int)(long)val;
    }
    inline int SetCookieCount(int iCookieCount) {
      void* val = (void*)IPW64CAST(iCookieCount);
      return IPWorks_OData_Set(m_pObj, 29, 0, val, 0);
    }
    inline char* GetCookieDomain(int iCookieIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 30, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieExpiration(int iCookieIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 31, iCookieIndex, 0);
      return (char*)val;
    }


    inline char* GetCookieName(int iCookieIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 32, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieName(int iCookieIndex, const char *lpCookieName) {
      return IPWorks_OData_Set(m_pObj, 32, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline char* GetCookiePath(int iCookieIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 33, iCookieIndex, 0);
      return (char*)val;
    }


    inline int GetCookieSecure(int iCookieIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 34, iCookieIndex, 0);
      return (int)(long)val;
    }

    inline char* GetCookieValue(int iCookieIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 35, iCookieIndex, 0);
      return (char*)val;
    }

    inline int SetCookieValue(int iCookieIndex, const char *lpCookieValue) {
      return IPWorks_OData_Set(m_pObj, 35, iCookieIndex, (void*)lpCookieValue, 0);
    }

    inline char* GetEntryAuthor() {
      void* val = IPWorks_OData_Get(m_pObj, 36, 0, 0);
      return (char*)val;
    }

    inline int SetEntryAuthor(const char *lpEntryAuthor) {
      return IPWorks_OData_Set(m_pObj, 36, 0, (void*)lpEntryAuthor, 0);
    }

    inline int GetEntryCount() {
      void* val = IPWorks_OData_Get(m_pObj, 37, 0, 0);
      return (int)(long)val;
    }

    inline char* GetEntryETag() {
      void* val = IPWorks_OData_Get(m_pObj, 38, 0, 0);
      return (char*)val;
    }

    inline int SetEntryETag(const char *lpEntryETag) {
      return IPWorks_OData_Set(m_pObj, 38, 0, (void*)lpEntryETag, 0);
    }

    inline char* GetEntryId() {
      void* val = IPWorks_OData_Get(m_pObj, 39, 0, 0);
      return (char*)val;
    }

    inline int SetEntryId(const char *lpEntryId) {
      return IPWorks_OData_Set(m_pObj, 39, 0, (void*)lpEntryId, 0);
    }

    inline int GetEntryIndex() {
      void* val = IPWorks_OData_Get(m_pObj, 40, 0, 0);
      return (int)(long)val;
    }
    inline int SetEntryIndex(int iEntryIndex) {
      void* val = (void*)IPW64CAST(iEntryIndex);
      return IPWorks_OData_Set(m_pObj, 40, 0, val, 0);
    }
    inline int GetEntryLinksCount() {
      void* val = IPWorks_OData_Get(m_pObj, 41, 0, 0);
      return (int)(long)val;
    }
    inline int SetEntryLinksCount(int iEntryLinksCount) {
      void* val = (void*)IPW64CAST(iEntryLinksCount);
      return IPWorks_OData_Set(m_pObj, 41, 0, val, 0);
    }
    inline char* GetEntryLinksResourcePath(int iEntryLinksIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 42, iEntryLinksIndex, 0);
      return (char*)val;
    }


    inline char* GetEntryLinksTitle(int iEntryLinksIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 43, iEntryLinksIndex, 0);
      return (char*)val;
    }


    inline int GetEntryPropertiesCount() {
      void* val = IPWorks_OData_Get(m_pObj, 44, 0, 0);
      return (int)(long)val;
    }
    inline int SetEntryPropertiesCount(int iEntryPropertiesCount) {
      void* val = (void*)IPW64CAST(iEntryPropertiesCount);
      return IPWorks_OData_Set(m_pObj, 44, 0, val, 0);
    }
    inline char* GetEntryPropertiesAttributes(int iEntryPropertiesIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 45, iEntryPropertiesIndex, 0);
      return (char*)val;
    }

    inline int SetEntryPropertiesAttributes(int iEntryPropertiesIndex, const char *lpEntryPropertiesAttributes) {
      return IPWorks_OData_Set(m_pObj, 45, iEntryPropertiesIndex, (void*)lpEntryPropertiesAttributes, 0);
    }

    inline int GetEntryPropertiesIsNull(int iEntryPropertiesIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 46, iEntryPropertiesIndex, 0);
      return (int)(long)val;
    }
    inline int SetEntryPropertiesIsNull(int iEntryPropertiesIndex, int bEntryPropertiesIsNull) {
      void* val = (void*)IPW64CAST(bEntryPropertiesIsNull);
      return IPWorks_OData_Set(m_pObj, 46, iEntryPropertiesIndex, val, 0);
    }
    inline char* GetEntryPropertiesName(int iEntryPropertiesIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 47, iEntryPropertiesIndex, 0);
      return (char*)val;
    }

    inline int SetEntryPropertiesName(int iEntryPropertiesIndex, const char *lpEntryPropertiesName) {
      return IPWorks_OData_Set(m_pObj, 47, iEntryPropertiesIndex, (void*)lpEntryPropertiesName, 0);
    }

    inline char* GetEntryPropertiesType(int iEntryPropertiesIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 48, iEntryPropertiesIndex, 0);
      return (char*)val;
    }

    inline int SetEntryPropertiesType(int iEntryPropertiesIndex, const char *lpEntryPropertiesType) {
      return IPWorks_OData_Set(m_pObj, 48, iEntryPropertiesIndex, (void*)lpEntryPropertiesType, 0);
    }

    inline char* GetEntryPropertiesValue(int iEntryPropertiesIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 49, iEntryPropertiesIndex, 0);
      return (char*)val;
    }

    inline int SetEntryPropertiesValue(int iEntryPropertiesIndex, const char *lpEntryPropertiesValue) {
      return IPWorks_OData_Set(m_pObj, 49, iEntryPropertiesIndex, (void*)lpEntryPropertiesValue, 0);
    }

    inline char* GetEntryPropertiesXPath(int iEntryPropertiesIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 50, iEntryPropertiesIndex, 0);
      return (char*)val;
    }


    inline char* GetEntrySummary() {
      void* val = IPWorks_OData_Get(m_pObj, 51, 0, 0);
      return (char*)val;
    }

    inline int SetEntrySummary(const char *lpEntrySummary) {
      return IPWorks_OData_Set(m_pObj, 51, 0, (void*)lpEntrySummary, 0);
    }

    inline char* GetEntryTitle() {
      void* val = IPWorks_OData_Get(m_pObj, 52, 0, 0);
      return (char*)val;
    }

    inline int SetEntryTitle(const char *lpEntryTitle) {
      return IPWorks_OData_Set(m_pObj, 52, 0, (void*)lpEntryTitle, 0);
    }

    inline char* GetEntryUpdated() {
      void* val = IPWorks_OData_Get(m_pObj, 53, 0, 0);
      return (char*)val;
    }


    inline char* GetEntryXML() {
      void* val = IPWorks_OData_Get(m_pObj, 54, 0, 0);
      return (char*)val;
    }

    inline int SetEntryXML(const char *lpEntryXML) {
      return IPWorks_OData_Set(m_pObj, 54, 0, (void*)lpEntryXML, 0);
    }

    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_OData_Get(m_pObj, 55, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_OData_Set(m_pObj, 55, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_OData_Get(m_pObj, 56, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_OData_Set(m_pObj, 56, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_OData_Get(m_pObj, 57, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_OData_Set(m_pObj, 57, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_OData_Get(m_pObj, 58, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_OData_Set(m_pObj, 58, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_OData_Get(m_pObj, 59, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_OData_Set(m_pObj, 59, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_OData_Get(m_pObj, 60, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_OData_Set(m_pObj, 60, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_OData_Get(m_pObj, 61, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_OData_Get(m_pObj, 62, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_OData_Set(m_pObj, 62, 0, (void*)lpLocalHost, 0);
    }

    inline char* GetOtherHeaders() {
      void* val = IPWorks_OData_Get(m_pObj, 63, 0, 0);
      return (char*)val;
    }

    inline int SetOtherHeaders(const char *lpOtherHeaders) {
      return IPWorks_OData_Set(m_pObj, 63, 0, (void*)lpOtherHeaders, 0);
    }

    inline char* GetOtherQueryOptions() {
      void* val = IPWorks_OData_Get(m_pObj, 64, 0, 0);
      return (char*)val;
    }

    inline int SetOtherQueryOptions(const char *lpOtherQueryOptions) {
      return IPWorks_OData_Set(m_pObj, 64, 0, (void*)lpOtherQueryOptions, 0);
    }

    inline int GetParsedHeaderCount() {
      void* val = IPWorks_OData_Get(m_pObj, 65, 0, 0);
      return (int)(long)val;
    }

    inline char* GetParsedHeaderField(int iParsedHeaderIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 66, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetParsedHeaderValue(int iParsedHeaderIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 67, iParsedHeaderIndex, 0);
      return (char*)val;
    }


    inline char* GetPassword() {
      void* val = IPWorks_OData_Get(m_pObj, 68, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_OData_Set(m_pObj, 68, 0, (void*)lpPassword, 0);
    }

    inline int GetProxyAuthScheme() {
      void* val = IPWorks_OData_Get(m_pObj, 69, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAuthScheme(int iProxyAuthScheme) {
      void* val = (void*)IPW64CAST(iProxyAuthScheme);
      return IPWorks_OData_Set(m_pObj, 69, 0, val, 0);
    }
    inline int GetProxyAutoDetect() {
      void* val = IPWorks_OData_Get(m_pObj, 70, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyAutoDetect(int bProxyAutoDetect) {
      void* val = (void*)IPW64CAST(bProxyAutoDetect);
      return IPWorks_OData_Set(m_pObj, 70, 0, val, 0);
    }
    inline char* GetProxyPassword() {
      void* val = IPWorks_OData_Get(m_pObj, 71, 0, 0);
      return (char*)val;
    }

    inline int SetProxyPassword(const char *lpProxyPassword) {
      return IPWorks_OData_Set(m_pObj, 71, 0, (void*)lpProxyPassword, 0);
    }

    inline int GetProxyPort() {
      void* val = IPWorks_OData_Get(m_pObj, 72, 0, 0);
      return (int)(long)val;
    }
    inline int SetProxyPort(int lProxyPort) {
      void* val = (void*)IPW64CAST(lProxyPort);
      return IPWorks_OData_Set(m_pObj, 72, 0, val, 0);
    }
    inline char* GetProxyServer() {
      void* val = IPWorks_OData_Get(m_pObj, 73, 0, 0);
      return (char*)val;
    }

    inline int SetProxyServer(const char *lpProxyServer) {
      return IPWorks_OData_Set(m_pObj, 73, 0, (void*)lpProxyServer, 0);
    }

    inline char* GetProxyUser() {
      void* val = IPWorks_OData_Get(m_pObj, 74, 0, 0);
      return (char*)val;
    }

    inline int SetProxyUser(const char *lpProxyUser) {
      return IPWorks_OData_Set(m_pObj, 74, 0, (void*)lpProxyUser, 0);
    }

    inline char* GetQueryFilter() {
      void* val = IPWorks_OData_Get(m_pObj, 75, 0, 0);
      return (char*)val;
    }

    inline int SetQueryFilter(const char *lpQueryFilter) {
      return IPWorks_OData_Set(m_pObj, 75, 0, (void*)lpQueryFilter, 0);
    }

    inline char* GetQueryOrderBy() {
      void* val = IPWorks_OData_Get(m_pObj, 76, 0, 0);
      return (char*)val;
    }

    inline int SetQueryOrderBy(const char *lpQueryOrderBy) {
      return IPWorks_OData_Set(m_pObj, 76, 0, (void*)lpQueryOrderBy, 0);
    }

    inline char* GetQuerySelect() {
      void* val = IPWorks_OData_Get(m_pObj, 77, 0, 0);
      return (char*)val;
    }

    inline int SetQuerySelect(const char *lpQuerySelect) {
      return IPWorks_OData_Set(m_pObj, 77, 0, (void*)lpQuerySelect, 0);
    }

    inline char* GetQuerySkip() {
      void* val = IPWorks_OData_Get(m_pObj, 78, 0, 0);
      return (char*)val;
    }

    inline int SetQuerySkip(const char *lpQuerySkip) {
      return IPWorks_OData_Set(m_pObj, 78, 0, (void*)lpQuerySkip, 0);
    }

    inline char* GetQuerySkipToken() {
      void* val = IPWorks_OData_Get(m_pObj, 79, 0, 0);
      return (char*)val;
    }

    inline int SetQuerySkipToken(const char *lpQuerySkipToken) {
      return IPWorks_OData_Set(m_pObj, 79, 0, (void*)lpQuerySkipToken, 0);
    }

    inline char* GetQueryTop() {
      void* val = IPWorks_OData_Get(m_pObj, 80, 0, 0);
      return (char*)val;
    }

    inline int SetQueryTop(const char *lpQueryTop) {
      return IPWorks_OData_Set(m_pObj, 80, 0, (void*)lpQueryTop, 0);
    }

    inline char* GetResourcePath() {
      void* val = IPWorks_OData_Get(m_pObj, 81, 0, 0);
      return (char*)val;
    }

    inline int SetResourcePath(const char *lpResourcePath) {
      return IPWorks_OData_Set(m_pObj, 81, 0, (void*)lpResourcePath, 0);
    }

    inline char* GetSchemaAssociationDescription() {
      void* val = IPWorks_OData_Get(m_pObj, 82, 0, 0);
      return (char*)val;
    }


    inline char* GetSchemaAssociationFromRole() {
      void* val = IPWorks_OData_Get(m_pObj, 83, 0, 0);
      return (char*)val;
    }


    inline char* GetSchemaAssociationFromRoleDescription() {
      void* val = IPWorks_OData_Get(m_pObj, 84, 0, 0);
      return (char*)val;
    }


    inline char* GetSchemaAssociationFromRoleEntity() {
      void* val = IPWorks_OData_Get(m_pObj, 85, 0, 0);
      return (char*)val;
    }


    inline int GetSchemaAssociationFromRoleMultiplicity() {
      void* val = IPWorks_OData_Get(m_pObj, 86, 0, 0);
      return (int)(long)val;
    }

    inline char* GetSchemaAssociationFromRoleSummary() {
      void* val = IPWorks_OData_Get(m_pObj, 87, 0, 0);
      return (char*)val;
    }


    inline char* GetSchemaAssociationName() {
      void* val = IPWorks_OData_Get(m_pObj, 88, 0, 0);
      return (char*)val;
    }


    inline int GetSchemaAssociationOnDelete() {
      void* val = IPWorks_OData_Get(m_pObj, 89, 0, 0);
      return (int)(long)val;
    }

    inline char* GetSchemaAssociationRelationship() {
      void* val = IPWorks_OData_Get(m_pObj, 90, 0, 0);
      return (char*)val;
    }


    inline char* GetSchemaAssociationSummary() {
      void* val = IPWorks_OData_Get(m_pObj, 91, 0, 0);
      return (char*)val;
    }


    inline char* GetSchemaAssociationToRole() {
      void* val = IPWorks_OData_Get(m_pObj, 92, 0, 0);
      return (char*)val;
    }


    inline char* GetSchemaAssociationToRoleDescription() {
      void* val = IPWorks_OData_Get(m_pObj, 93, 0, 0);
      return (char*)val;
    }


    inline char* GetSchemaAssociationToRoleEntity() {
      void* val = IPWorks_OData_Get(m_pObj, 94, 0, 0);
      return (char*)val;
    }


    inline int GetSchemaAssociationToRoleMultiplicity() {
      void* val = IPWorks_OData_Get(m_pObj, 95, 0, 0);
      return (int)(long)val;
    }

    inline char* GetSchemaAssociationToRoleSummary() {
      void* val = IPWorks_OData_Get(m_pObj, 96, 0, 0);
      return (char*)val;
    }


    inline int GetSchemaAssociationCount() {
      void* val = IPWorks_OData_Get(m_pObj, 97, 0, 0);
      return (int)(long)val;
    }

    inline int GetSchemaAssociationIndex() {
      void* val = IPWorks_OData_Get(m_pObj, 98, 0, 0);
      return (int)(long)val;
    }
    inline int SetSchemaAssociationIndex(int iSchemaAssociationIndex) {
      void* val = (void*)IPW64CAST(iSchemaAssociationIndex);
      return IPWorks_OData_Set(m_pObj, 98, 0, val, 0);
    }
    inline char* GetSchemaEntityDescription() {
      void* val = IPWorks_OData_Get(m_pObj, 99, 0, 0);
      return (char*)val;
    }


    inline char* GetSchemaEntityName() {
      void* val = IPWorks_OData_Get(m_pObj, 100, 0, 0);
      return (char*)val;
    }


    inline char* GetSchemaEntitySummary() {
      void* val = IPWorks_OData_Get(m_pObj, 101, 0, 0);
      return (char*)val;
    }


    inline int GetSchemaEntityCount() {
      void* val = IPWorks_OData_Get(m_pObj, 102, 0, 0);
      return (int)(long)val;
    }

    inline int GetSchemaEntityIndex() {
      void* val = IPWorks_OData_Get(m_pObj, 103, 0, 0);
      return (int)(long)val;
    }
    inline int SetSchemaEntityIndex(int iSchemaEntityIndex) {
      void* val = (void*)IPW64CAST(iSchemaEntityIndex);
      return IPWorks_OData_Set(m_pObj, 103, 0, val, 0);
    }
    inline int GetSchemaKeysCount() {
      void* val = IPWorks_OData_Get(m_pObj, 104, 0, 0);
      return (int)(long)val;
    }

    inline char* GetSchemaKeys(int iSchemaKeysIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 105, iSchemaKeysIndex, 0);
      return (char*)val;
    }


    inline char* GetSchemaPropertyAttributes() {
      void* val = IPWorks_OData_Get(m_pObj, 106, 0, 0);
      return (char*)val;
    }


    inline char* GetSchemaPropertyDescription() {
      void* val = IPWorks_OData_Get(m_pObj, 107, 0, 0);
      return (char*)val;
    }


    inline int GetSchemaPropertyIsComplexType() {
      void* val = IPWorks_OData_Get(m_pObj, 108, 0, 0);
      return (int)(long)val;
    }

    inline char* GetSchemaPropertyName() {
      void* val = IPWorks_OData_Get(m_pObj, 109, 0, 0);
      return (char*)val;
    }


    inline int GetSchemaPropertyNullable() {
      void* val = IPWorks_OData_Get(m_pObj, 110, 0, 0);
      return (int)(long)val;
    }

    inline char* GetSchemaPropertySummary() {
      void* val = IPWorks_OData_Get(m_pObj, 111, 0, 0);
      return (char*)val;
    }


    inline char* GetSchemaPropertyType() {
      void* val = IPWorks_OData_Get(m_pObj, 112, 0, 0);
      return (char*)val;
    }


    inline int GetSchemaPropertyCount() {
      void* val = IPWorks_OData_Get(m_pObj, 113, 0, 0);
      return (int)(long)val;
    }

    inline int GetSchemaPropertyIndex() {
      void* val = IPWorks_OData_Get(m_pObj, 114, 0, 0);
      return (int)(long)val;
    }
    inline int SetSchemaPropertyIndex(int iSchemaPropertyIndex) {
      void* val = (void*)IPW64CAST(iSchemaPropertyIndex);
      return IPWorks_OData_Set(m_pObj, 114, 0, val, 0);
    }
    inline char* GetSchemaTypeFieldAttributes() {
      void* val = IPWorks_OData_Get(m_pObj, 115, 0, 0);
      return (char*)val;
    }


    inline char* GetSchemaTypeFieldDescription() {
      void* val = IPWorks_OData_Get(m_pObj, 116, 0, 0);
      return (char*)val;
    }


    inline int GetSchemaTypeFieldIsComplexType() {
      void* val = IPWorks_OData_Get(m_pObj, 117, 0, 0);
      return (int)(long)val;
    }

    inline char* GetSchemaTypeFieldName() {
      void* val = IPWorks_OData_Get(m_pObj, 118, 0, 0);
      return (char*)val;
    }


    inline int GetSchemaTypeFieldNullable() {
      void* val = IPWorks_OData_Get(m_pObj, 119, 0, 0);
      return (int)(long)val;
    }

    inline char* GetSchemaTypeFieldSummary() {
      void* val = IPWorks_OData_Get(m_pObj, 120, 0, 0);
      return (char*)val;
    }


    inline char* GetSchemaTypeFieldType() {
      void* val = IPWorks_OData_Get(m_pObj, 121, 0, 0);
      return (char*)val;
    }


    inline int GetSchemaTypeFieldCount() {
      void* val = IPWorks_OData_Get(m_pObj, 122, 0, 0);
      return (int)(long)val;
    }

    inline int GetSchemaTypeFieldIndex() {
      void* val = IPWorks_OData_Get(m_pObj, 123, 0, 0);
      return (int)(long)val;
    }
    inline int SetSchemaTypeFieldIndex(int iSchemaTypeFieldIndex) {
      void* val = (void*)IPW64CAST(iSchemaTypeFieldIndex);
      return IPWorks_OData_Set(m_pObj, 123, 0, val, 0);
    }
    inline char* GetServiceRootURI() {
      void* val = IPWorks_OData_Get(m_pObj, 124, 0, 0);
      return (char*)val;
    }

    inline int SetServiceRootURI(const char *lpServiceRootURI) {
      return IPWorks_OData_Set(m_pObj, 124, 0, (void*)lpServiceRootURI, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_OData_Get(m_pObj, 125, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_OData_Set(m_pObj, 125, 0, val, 0);
    }
    inline int GetTransferredData(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_OData_Get(m_pObj, 126, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }


    inline char* GetUser() {
      void* val = IPWorks_OData_Get(m_pObj, 127, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_OData_Set(m_pObj, 127, 0, (void*)lpUser, 0);
    }

    inline int GetAttrCount() {
      void* val = IPWorks_OData_Get(m_pObj, 128, 0, 0);
      return (int)(long)val;
    }

    inline char* GetAttrName(int iAttrIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 129, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrNamespace(int iAttrIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 130, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrPrefix(int iAttrIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 131, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrValue(int iAttrIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 132, iAttrIndex, 0);
      return (char*)val;
    }


    inline int GetXChildrenCount() {
      void* val = IPWorks_OData_Get(m_pObj, 133, 0, 0);
      return (int)(long)val;
    }

    inline char* GetXChildName(int iXChildIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 134, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildNamespace(int iXChildIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 135, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildPrefix(int iXChildIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 136, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildXText(int iXChildIndex) {
      void* val = IPWorks_OData_Get(m_pObj, 137, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXElement() {
      void* val = IPWorks_OData_Get(m_pObj, 138, 0, 0);
      return (char*)val;
    }


    inline char* GetXNamespace() {
      void* val = IPWorks_OData_Get(m_pObj, 139, 0, 0);
      return (char*)val;
    }


    inline char* GetXParent() {
      void* val = IPWorks_OData_Get(m_pObj, 140, 0, 0);
      return (char*)val;
    }


    inline char* GetXPath() {
      void* val = IPWorks_OData_Get(m_pObj, 141, 0, 0);
      return (char*)val;
    }

    inline int SetXPath(const char *lpXPath) {
      return IPWorks_OData_Set(m_pObj, 141, 0, (void*)lpXPath, 0);
    }

    inline char* GetXPrefix() {
      void* val = IPWorks_OData_Get(m_pObj, 142, 0, 0);
      return (char*)val;
    }


    inline char* GetXSubTree() {
      void* val = IPWorks_OData_Get(m_pObj, 143, 0, 0);
      return (char*)val;
    }


    inline char* GetXText() {
      void* val = IPWorks_OData_Get(m_pObj, 144, 0, 0);
      return (char*)val;
    }



  public: //methods

    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_OData_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int CreateEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline int CustomRequest(const char* lpszHTTPMethod, const char* lpszURL, const char* lpszPostData) {
      void *param[3+1] = {(void*)IPW64CAST(lpszHTTPMethod), (void*)IPW64CAST(lpszURL), (void*)IPW64CAST(lpszPostData), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_OData_Do(m_pObj, 4, 3, param, cbparam);
      
      
    }
    inline int DeleteEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline char* GetEntryProperty(const char* lpszXPath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszXPath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_OData_Do(m_pObj, 6, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int GetSchema() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int HasXPath(const char* lpszxpath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszxpath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_OData_Do(m_pObj, 8, 1, param, cbparam);
      
      return (int)IPW64CAST(param[1]);
    }
    inline int QueryService() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 10, 0, param, cbparam);
      
      
    }
    inline int SetEntryProperty(const char* lpszXPath, const char* lpszValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszXPath), (void*)IPW64CAST(lpszValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_OData_Do(m_pObj, 11, 2, param, cbparam);
      
      
    }
    inline int SetSchemaEntity(const char* lpszName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_OData_Do(m_pObj, 12, 1, param, cbparam);
      
      
    }
    inline int SetSchemaProperty(const char* lpszName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_OData_Do(m_pObj, 13, 1, param, cbparam);
      
      
    }
    inline int SetSchemaType(const char* lpszName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_OData_Do(m_pObj, 14, 1, param, cbparam);
      
      
    }
    inline int UpdateEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 15, 0, param, cbparam);
      
      
    }
    inline int UpdateProperty(const char* lpszXPath, const char* lpszValue) {
      void *param[2+1] = {(void*)IPW64CAST(lpszXPath), (void*)IPW64CAST(lpszValue), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_OData_Do(m_pObj, 16, 2, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} ODataConnectedEventParamsW;

typedef struct {
  int StatusCode;
  LPWSTR Description;
  int reserved;
} ODataDisconnectedEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} ODataEndTransferEventParamsW;

typedef struct {
  LPWSTR Name;
  int reserved;
} ODataEntityEventParamsW;

typedef struct {
  LPWSTR Id;
  LPWSTR Title;
  LPWSTR Summary;
  LPWSTR ETag;
  int reserved;
} ODataEntryEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} ODataErrorEventParamsW;

typedef struct {
  LPWSTR Field;
  LPWSTR Value;
  int reserved;
} ODataHeaderEventParamsW;

typedef struct {
  LPWSTR Name;
  LPWSTR TypeName;
  int Nullable;
  int reserved;
} ODataPropertyEventParamsW;

typedef struct {
  LPWSTR Name;
  LPWSTR Value;
  LPWSTR Expires;
  LPWSTR Domain;
  LPWSTR Path;
  int Secure;
  int reserved;
} ODataSetCookieEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} ODataStartTransferEventParamsW;

typedef struct {
  LPWSTR HTTPVersion;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} ODataStatusEventParamsW;

typedef struct {
  int Direction;
  ns_int64 *pBytesTransferred;
  int PercentDone;
  LPWSTR Text;
  int lenText;
  int reserved;
} ODataTransferEventParamsW;



class ODataW : public OData {

  public: //properties
  
    inline LPWSTR GetAuthorization() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetAuthorization(LPWSTR lpAuthorization) {
      return IPWorks_OData_Set(m_pObj, 10000+1, 0, (void*)lpAuthorization, 0);
    }



    inline LPWSTR GetChannelAuthorEmail() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+3, 0, 0);
    }

    inline int SetChannelAuthorEmail(LPWSTR lpChannelAuthorEmail) {
      return IPWorks_OData_Set(m_pObj, 10000+3, 0, (void*)lpChannelAuthorEmail, 0);
    }

    inline LPWSTR GetChannelAuthorName() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+4, 0, 0);
    }

    inline int SetChannelAuthorName(LPWSTR lpChannelAuthorName) {
      return IPWorks_OData_Set(m_pObj, 10000+4, 0, (void*)lpChannelAuthorName, 0);
    }

    inline LPWSTR GetChannelAuthorUri() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+5, 0, 0);
    }

    inline int SetChannelAuthorUri(LPWSTR lpChannelAuthorUri) {
      return IPWorks_OData_Set(m_pObj, 10000+5, 0, (void*)lpChannelAuthorUri, 0);
    }

    inline LPWSTR GetChannelCategoryLabel() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+6, 0, 0);
    }

    inline int SetChannelCategoryLabel(LPWSTR lpChannelCategoryLabel) {
      return IPWorks_OData_Set(m_pObj, 10000+6, 0, (void*)lpChannelCategoryLabel, 0);
    }

    inline LPWSTR GetChannelCategoryScheme() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+7, 0, 0);
    }

    inline int SetChannelCategoryScheme(LPWSTR lpChannelCategoryScheme) {
      return IPWorks_OData_Set(m_pObj, 10000+7, 0, (void*)lpChannelCategoryScheme, 0);
    }

    inline LPWSTR GetChannelCategoryTerm() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+8, 0, 0);
    }

    inline int SetChannelCategoryTerm(LPWSTR lpChannelCategoryTerm) {
      return IPWorks_OData_Set(m_pObj, 10000+8, 0, (void*)lpChannelCategoryTerm, 0);
    }

    inline LPWSTR GetChannelContributorEmail() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+9, 0, 0);
    }

    inline int SetChannelContributorEmail(LPWSTR lpChannelContributorEmail) {
      return IPWorks_OData_Set(m_pObj, 10000+9, 0, (void*)lpChannelContributorEmail, 0);
    }

    inline LPWSTR GetChannelContributorName() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+10, 0, 0);
    }

    inline int SetChannelContributorName(LPWSTR lpChannelContributorName) {
      return IPWorks_OData_Set(m_pObj, 10000+10, 0, (void*)lpChannelContributorName, 0);
    }

    inline LPWSTR GetChannelContributorUri() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+11, 0, 0);
    }

    inline int SetChannelContributorUri(LPWSTR lpChannelContributorUri) {
      return IPWorks_OData_Set(m_pObj, 10000+11, 0, (void*)lpChannelContributorUri, 0);
    }

    inline LPWSTR GetChannelGenerator() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+12, 0, 0);
    }

    inline int SetChannelGenerator(LPWSTR lpChannelGenerator) {
      return IPWorks_OData_Set(m_pObj, 10000+12, 0, (void*)lpChannelGenerator, 0);
    }

    inline LPWSTR GetChannelIcon() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+13, 0, 0);
    }

    inline int SetChannelIcon(LPWSTR lpChannelIcon) {
      return IPWorks_OData_Set(m_pObj, 10000+13, 0, (void*)lpChannelIcon, 0);
    }

    inline LPWSTR GetChannelId() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+14, 0, 0);
    }

    inline int SetChannelId(LPWSTR lpChannelId) {
      return IPWorks_OData_Set(m_pObj, 10000+14, 0, (void*)lpChannelId, 0);
    }

    inline LPWSTR GetChannelLinkHref() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetChannelLinkHref(LPWSTR lpChannelLinkHref) {
      return IPWorks_OData_Set(m_pObj, 10000+15, 0, (void*)lpChannelLinkHref, 0);
    }

    inline LPWSTR GetChannelLinkHrefLang() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetChannelLinkHrefLang(LPWSTR lpChannelLinkHrefLang) {
      return IPWorks_OData_Set(m_pObj, 10000+16, 0, (void*)lpChannelLinkHrefLang, 0);
    }

    inline LPWSTR GetChannelLinkLength() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+17, 0, 0);
    }

    inline int SetChannelLinkLength(LPWSTR lpChannelLinkLength) {
      return IPWorks_OData_Set(m_pObj, 10000+17, 0, (void*)lpChannelLinkLength, 0);
    }

    inline LPWSTR GetChannelLinkRel() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+18, 0, 0);
    }

    inline int SetChannelLinkRel(LPWSTR lpChannelLinkRel) {
      return IPWorks_OData_Set(m_pObj, 10000+18, 0, (void*)lpChannelLinkRel, 0);
    }

    inline LPWSTR GetChannelLinkTitle() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+19, 0, 0);
    }

    inline int SetChannelLinkTitle(LPWSTR lpChannelLinkTitle) {
      return IPWorks_OData_Set(m_pObj, 10000+19, 0, (void*)lpChannelLinkTitle, 0);
    }

    inline LPWSTR GetChannelLinkType() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+20, 0, 0);
    }

    inline int SetChannelLinkType(LPWSTR lpChannelLinkType) {
      return IPWorks_OData_Set(m_pObj, 10000+20, 0, (void*)lpChannelLinkType, 0);
    }

    inline LPWSTR GetChannelLogo() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+21, 0, 0);
    }

    inline int SetChannelLogo(LPWSTR lpChannelLogo) {
      return IPWorks_OData_Set(m_pObj, 10000+21, 0, (void*)lpChannelLogo, 0);
    }

    inline LPWSTR GetChannelRights() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+22, 0, 0);
    }

    inline int SetChannelRights(LPWSTR lpChannelRights) {
      return IPWorks_OData_Set(m_pObj, 10000+22, 0, (void*)lpChannelRights, 0);
    }



    inline LPWSTR GetChannelSubtitle() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+24, 0, 0);
    }

    inline int SetChannelSubtitle(LPWSTR lpChannelSubtitle) {
      return IPWorks_OData_Set(m_pObj, 10000+24, 0, (void*)lpChannelSubtitle, 0);
    }



    inline LPWSTR GetChannelTitle() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+26, 0, 0);
    }

    inline int SetChannelTitle(LPWSTR lpChannelTitle) {
      return IPWorks_OData_Set(m_pObj, 10000+26, 0, (void*)lpChannelTitle, 0);
    }



    inline LPWSTR GetChannelUpdated() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+28, 0, 0);
    }

    inline int SetChannelUpdated(LPWSTR lpChannelUpdated) {
      return IPWorks_OData_Set(m_pObj, 10000+28, 0, (void*)lpChannelUpdated, 0);
    }



    inline LPWSTR GetCookieDomain(int iCookieIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+30, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieExpiration(int iCookieIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+31, iCookieIndex, 0);
    }



    inline LPWSTR GetCookieName(int iCookieIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+32, iCookieIndex, 0);
    }

    inline int SetCookieName(int iCookieIndex, LPWSTR lpCookieName) {
      return IPWorks_OData_Set(m_pObj, 10000+32, iCookieIndex, (void*)lpCookieName, 0);
    }

    inline LPWSTR GetCookiePath(int iCookieIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+33, iCookieIndex, 0);
    }





    inline LPWSTR GetCookieValue(int iCookieIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+35, iCookieIndex, 0);
    }

    inline int SetCookieValue(int iCookieIndex, LPWSTR lpCookieValue) {
      return IPWorks_OData_Set(m_pObj, 10000+35, iCookieIndex, (void*)lpCookieValue, 0);
    }

    inline LPWSTR GetEntryAuthor() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+36, 0, 0);
    }

    inline int SetEntryAuthor(LPWSTR lpEntryAuthor) {
      return IPWorks_OData_Set(m_pObj, 10000+36, 0, (void*)lpEntryAuthor, 0);
    }



    inline LPWSTR GetEntryETag() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+38, 0, 0);
    }

    inline int SetEntryETag(LPWSTR lpEntryETag) {
      return IPWorks_OData_Set(m_pObj, 10000+38, 0, (void*)lpEntryETag, 0);
    }

    inline LPWSTR GetEntryId() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+39, 0, 0);
    }

    inline int SetEntryId(LPWSTR lpEntryId) {
      return IPWorks_OData_Set(m_pObj, 10000+39, 0, (void*)lpEntryId, 0);
    }





    inline LPWSTR GetEntryLinksResourcePath(int iEntryLinksIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+42, iEntryLinksIndex, 0);
    }



    inline LPWSTR GetEntryLinksTitle(int iEntryLinksIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+43, iEntryLinksIndex, 0);
    }





    inline LPWSTR GetEntryPropertiesAttributes(int iEntryPropertiesIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+45, iEntryPropertiesIndex, 0);
    }

    inline int SetEntryPropertiesAttributes(int iEntryPropertiesIndex, LPWSTR lpEntryPropertiesAttributes) {
      return IPWorks_OData_Set(m_pObj, 10000+45, iEntryPropertiesIndex, (void*)lpEntryPropertiesAttributes, 0);
    }



    inline LPWSTR GetEntryPropertiesName(int iEntryPropertiesIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+47, iEntryPropertiesIndex, 0);
    }

    inline int SetEntryPropertiesName(int iEntryPropertiesIndex, LPWSTR lpEntryPropertiesName) {
      return IPWorks_OData_Set(m_pObj, 10000+47, iEntryPropertiesIndex, (void*)lpEntryPropertiesName, 0);
    }

    inline LPWSTR GetEntryPropertiesType(int iEntryPropertiesIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+48, iEntryPropertiesIndex, 0);
    }

    inline int SetEntryPropertiesType(int iEntryPropertiesIndex, LPWSTR lpEntryPropertiesType) {
      return IPWorks_OData_Set(m_pObj, 10000+48, iEntryPropertiesIndex, (void*)lpEntryPropertiesType, 0);
    }

    inline LPWSTR GetEntryPropertiesValue(int iEntryPropertiesIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+49, iEntryPropertiesIndex, 0);
    }

    inline int SetEntryPropertiesValue(int iEntryPropertiesIndex, LPWSTR lpEntryPropertiesValue) {
      return IPWorks_OData_Set(m_pObj, 10000+49, iEntryPropertiesIndex, (void*)lpEntryPropertiesValue, 0);
    }

    inline LPWSTR GetEntryPropertiesXPath(int iEntryPropertiesIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+50, iEntryPropertiesIndex, 0);
    }



    inline LPWSTR GetEntrySummary() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+51, 0, 0);
    }

    inline int SetEntrySummary(LPWSTR lpEntrySummary) {
      return IPWorks_OData_Set(m_pObj, 10000+51, 0, (void*)lpEntrySummary, 0);
    }

    inline LPWSTR GetEntryTitle() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+52, 0, 0);
    }

    inline int SetEntryTitle(LPWSTR lpEntryTitle) {
      return IPWorks_OData_Set(m_pObj, 10000+52, 0, (void*)lpEntryTitle, 0);
    }

    inline LPWSTR GetEntryUpdated() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+53, 0, 0);
    }



    inline LPWSTR GetEntryXML() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+54, 0, 0);
    }

    inline int SetEntryXML(LPWSTR lpEntryXML) {
      return IPWorks_OData_Set(m_pObj, 10000+54, 0, (void*)lpEntryXML, 0);
    }





    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+57, 0, 0);
    }

    inline int SetFirewallHost(LPWSTR lpFirewallHost) {
      return IPWorks_OData_Set(m_pObj, 10000+57, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+58, 0, 0);
    }

    inline int SetFirewallPassword(LPWSTR lpFirewallPassword) {
      return IPWorks_OData_Set(m_pObj, 10000+58, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+60, 0, 0);
    }

    inline int SetFirewallUser(LPWSTR lpFirewallUser) {
      return IPWorks_OData_Set(m_pObj, 10000+60, 0, (void*)lpFirewallUser, 0);
    }



    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+62, 0, 0);
    }

    inline int SetLocalHost(LPWSTR lpLocalHost) {
      return IPWorks_OData_Set(m_pObj, 10000+62, 0, (void*)lpLocalHost, 0);
    }

    inline LPWSTR GetOtherHeaders() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+63, 0, 0);
    }

    inline int SetOtherHeaders(LPWSTR lpOtherHeaders) {
      return IPWorks_OData_Set(m_pObj, 10000+63, 0, (void*)lpOtherHeaders, 0);
    }

    inline LPWSTR GetOtherQueryOptions() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+64, 0, 0);
    }

    inline int SetOtherQueryOptions(LPWSTR lpOtherQueryOptions) {
      return IPWorks_OData_Set(m_pObj, 10000+64, 0, (void*)lpOtherQueryOptions, 0);
    }



    inline LPWSTR GetParsedHeaderField(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+66, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetParsedHeaderValue(int iParsedHeaderIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+67, iParsedHeaderIndex, 0);
    }



    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+68, 0, 0);
    }

    inline int SetPassword(LPWSTR lpPassword) {
      return IPWorks_OData_Set(m_pObj, 10000+68, 0, (void*)lpPassword, 0);
    }





    inline LPWSTR GetProxyPassword() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+71, 0, 0);
    }

    inline int SetProxyPassword(LPWSTR lpProxyPassword) {
      return IPWorks_OData_Set(m_pObj, 10000+71, 0, (void*)lpProxyPassword, 0);
    }



    inline LPWSTR GetProxyServer() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+73, 0, 0);
    }

    inline int SetProxyServer(LPWSTR lpProxyServer) {
      return IPWorks_OData_Set(m_pObj, 10000+73, 0, (void*)lpProxyServer, 0);
    }

    inline LPWSTR GetProxyUser() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+74, 0, 0);
    }

    inline int SetProxyUser(LPWSTR lpProxyUser) {
      return IPWorks_OData_Set(m_pObj, 10000+74, 0, (void*)lpProxyUser, 0);
    }

    inline LPWSTR GetQueryFilter() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+75, 0, 0);
    }

    inline int SetQueryFilter(LPWSTR lpQueryFilter) {
      return IPWorks_OData_Set(m_pObj, 10000+75, 0, (void*)lpQueryFilter, 0);
    }

    inline LPWSTR GetQueryOrderBy() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+76, 0, 0);
    }

    inline int SetQueryOrderBy(LPWSTR lpQueryOrderBy) {
      return IPWorks_OData_Set(m_pObj, 10000+76, 0, (void*)lpQueryOrderBy, 0);
    }

    inline LPWSTR GetQuerySelect() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+77, 0, 0);
    }

    inline int SetQuerySelect(LPWSTR lpQuerySelect) {
      return IPWorks_OData_Set(m_pObj, 10000+77, 0, (void*)lpQuerySelect, 0);
    }

    inline LPWSTR GetQuerySkip() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+78, 0, 0);
    }

    inline int SetQuerySkip(LPWSTR lpQuerySkip) {
      return IPWorks_OData_Set(m_pObj, 10000+78, 0, (void*)lpQuerySkip, 0);
    }

    inline LPWSTR GetQuerySkipToken() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+79, 0, 0);
    }

    inline int SetQuerySkipToken(LPWSTR lpQuerySkipToken) {
      return IPWorks_OData_Set(m_pObj, 10000+79, 0, (void*)lpQuerySkipToken, 0);
    }

    inline LPWSTR GetQueryTop() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+80, 0, 0);
    }

    inline int SetQueryTop(LPWSTR lpQueryTop) {
      return IPWorks_OData_Set(m_pObj, 10000+80, 0, (void*)lpQueryTop, 0);
    }

    inline LPWSTR GetResourcePath() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+81, 0, 0);
    }

    inline int SetResourcePath(LPWSTR lpResourcePath) {
      return IPWorks_OData_Set(m_pObj, 10000+81, 0, (void*)lpResourcePath, 0);
    }

    inline LPWSTR GetSchemaAssociationDescription() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+82, 0, 0);
    }



    inline LPWSTR GetSchemaAssociationFromRole() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+83, 0, 0);
    }



    inline LPWSTR GetSchemaAssociationFromRoleDescription() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+84, 0, 0);
    }



    inline LPWSTR GetSchemaAssociationFromRoleEntity() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+85, 0, 0);
    }





    inline LPWSTR GetSchemaAssociationFromRoleSummary() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+87, 0, 0);
    }



    inline LPWSTR GetSchemaAssociationName() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+88, 0, 0);
    }





    inline LPWSTR GetSchemaAssociationRelationship() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+90, 0, 0);
    }



    inline LPWSTR GetSchemaAssociationSummary() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+91, 0, 0);
    }



    inline LPWSTR GetSchemaAssociationToRole() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+92, 0, 0);
    }



    inline LPWSTR GetSchemaAssociationToRoleDescription() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+93, 0, 0);
    }



    inline LPWSTR GetSchemaAssociationToRoleEntity() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+94, 0, 0);
    }





    inline LPWSTR GetSchemaAssociationToRoleSummary() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+96, 0, 0);
    }







    inline LPWSTR GetSchemaEntityDescription() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+99, 0, 0);
    }



    inline LPWSTR GetSchemaEntityName() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+100, 0, 0);
    }



    inline LPWSTR GetSchemaEntitySummary() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+101, 0, 0);
    }









    inline LPWSTR GetSchemaKeys(int iSchemaKeysIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+105, iSchemaKeysIndex, 0);
    }



    inline LPWSTR GetSchemaPropertyAttributes() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+106, 0, 0);
    }



    inline LPWSTR GetSchemaPropertyDescription() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+107, 0, 0);
    }





    inline LPWSTR GetSchemaPropertyName() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+109, 0, 0);
    }





    inline LPWSTR GetSchemaPropertySummary() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+111, 0, 0);
    }



    inline LPWSTR GetSchemaPropertyType() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+112, 0, 0);
    }







    inline LPWSTR GetSchemaTypeFieldAttributes() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+115, 0, 0);
    }



    inline LPWSTR GetSchemaTypeFieldDescription() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+116, 0, 0);
    }





    inline LPWSTR GetSchemaTypeFieldName() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+118, 0, 0);
    }





    inline LPWSTR GetSchemaTypeFieldSummary() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+120, 0, 0);
    }



    inline LPWSTR GetSchemaTypeFieldType() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+121, 0, 0);
    }







    inline LPWSTR GetServiceRootURI() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+124, 0, 0);
    }

    inline int SetServiceRootURI(LPWSTR lpServiceRootURI) {
      return IPWorks_OData_Set(m_pObj, 10000+124, 0, (void*)lpServiceRootURI, 0);
    }



    inline LPWSTR GetTransferredData() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+126, 0, 0);
    }


    inline int GetTransferredDataB(char *&lpTransferredData, int &lenTransferredData) {
      lpTransferredData = (char*)IPWorks_OData_Get(m_pObj, 126, 0, &lenTransferredData);
      return lpTransferredData ? 0 : lenTransferredData;
    }

    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+127, 0, 0);
    }

    inline int SetUser(LPWSTR lpUser) {
      return IPWorks_OData_Set(m_pObj, 10000+127, 0, (void*)lpUser, 0);
    }



    inline LPWSTR GetAttrName(int iAttrIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+129, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrNamespace(int iAttrIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+130, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrPrefix(int iAttrIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+131, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrValue(int iAttrIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+132, iAttrIndex, 0);
    }





    inline LPWSTR GetXChildName(int iXChildIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+134, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildNamespace(int iXChildIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+135, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildPrefix(int iXChildIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+136, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildXText(int iXChildIndex) {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+137, iXChildIndex, 0);
    }



    inline LPWSTR GetXElement() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+138, 0, 0);
    }



    inline LPWSTR GetXNamespace() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+139, 0, 0);
    }



    inline LPWSTR GetXParent() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+140, 0, 0);
    }



    inline LPWSTR GetXPath() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+141, 0, 0);
    }

    inline int SetXPath(LPWSTR lpXPath) {
      return IPWorks_OData_Set(m_pObj, 10000+141, 0, (void*)lpXPath, 0);
    }

    inline LPWSTR GetXPrefix() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+142, 0, 0);
    }



    inline LPWSTR GetXSubTree() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+143, 0, 0);
    }



    inline LPWSTR GetXText() {
      return (LPWSTR)IPWorks_OData_Get(m_pObj, 10000+144, 0, 0);
    }





  public: //events
  
    virtual int FireConnected(ODataConnectedEventParamsW *e) {return 0;}
    virtual int FireDisconnected(ODataDisconnectedEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(ODataEndTransferEventParamsW *e) {return 0;}
    virtual int FireEntity(ODataEntityEventParamsW *e) {return 0;}
    virtual int FireEntry(ODataEntryEventParamsW *e) {return 0;}
    virtual int FireError(ODataErrorEventParamsW *e) {return 0;}
    virtual int FireHeader(ODataHeaderEventParamsW *e) {return 0;}
    virtual int FireProperty(ODataPropertyEventParamsW *e) {return 0;}
    virtual int FireSetCookie(ODataSetCookieEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(ODataStartTransferEventParamsW *e) {return 0;}
    virtual int FireStatus(ODataStatusEventParamsW *e) {return 0;}
    virtual int FireTransfer(ODataTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int ODataEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            ODataConnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireConnected(&e);
            break;
         }
         case 2: {
            ODataDisconnectedEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireDisconnected(&e);
            break;
         }
         case 3: {
            ODataEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 4: {
            ODataEntityEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireEntity(&e);
            break;
         }
         case 5: {
            ODataEntryEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]),  0};
            ret_code = FireEntry(&e);
            break;
         }
         case 6: {
            ODataErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 7: {
            ODataHeaderEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireHeader(&e);
            break;
         }
         case 8: {
            ODataPropertyEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]),  0};
            ret_code = FireProperty(&e);
            break;
         }
         case 9: {
            ODataSetCookieEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]), (int)IPW64CAST(param[5]),  0};
            ret_code = FireSetCookie(&e);
            break;
         }
         case 10: {
            ODataStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 11: {
            ODataStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireStatus(&e);
            break;
         }
         case 12: {
            ODataTransferEventParamsW e = {(int)IPW64CAST(param[0]), (ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnected(ODataConnectedEventParams *e) {return -10000;}
    virtual int FireDisconnected(ODataDisconnectedEventParams *e) {return -10000;}
    virtual int FireEndTransfer(ODataEndTransferEventParams *e) {return -10000;}
    virtual int FireEntity(ODataEntityEventParams *e) {return -10000;}
    virtual int FireEntry(ODataEntryEventParams *e) {return -10000;}
    virtual int FireError(ODataErrorEventParams *e) {return -10000;}
    virtual int FireHeader(ODataHeaderEventParams *e) {return -10000;}
    virtual int FireProperty(ODataPropertyEventParams *e) {return -10000;}
    virtual int FireSetCookie(ODataSetCookieEventParams *e) {return -10000;}
    virtual int FireStartTransfer(ODataStartTransferEventParams *e) {return -10000;}
    virtual int FireStatus(ODataStatusEventParams *e) {return -10000;}
    virtual int FireTransfer(ODataTransferEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_OData_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int CreateEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline int CustomRequest(LPWSTR lpszHTTPMethod, LPWSTR lpszURL, LPWSTR lpszPostData) {
      void *param[3+1] = {(void*)lpszHTTPMethod, (void*)lpszURL, (void*)lpszPostData, 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_OData_Do(m_pObj, 10000+4, 3, param, cbparam);
      
    }
    inline int DeleteEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline LPWSTR GetEntryProperty(LPWSTR lpszXPath) {
      void *param[1+1] = {(void*)lpszXPath, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_OData_Do(m_pObj, 10000+6, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int GetSchema() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int HasXPath(LPWSTR lpszxpath) {
      void *param[1+1] = {(void*)lpszxpath, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_OData_Do(m_pObj, 10000+8, 1, param, cbparam);
      return (int)IPW64CAST(param[1]);
    }
    inline int QueryService() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 10000+10, 0, param, cbparam);
      
    }
    inline int SetEntryProperty(LPWSTR lpszXPath, LPWSTR lpszValue) {
      void *param[2+1] = {(void*)lpszXPath, (void*)lpszValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_OData_Do(m_pObj, 10000+11, 2, param, cbparam);
      
    }
    inline int SetSchemaEntity(LPWSTR lpszName) {
      void *param[1+1] = {(void*)lpszName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_OData_Do(m_pObj, 10000+12, 1, param, cbparam);
      
    }
    inline int SetSchemaProperty(LPWSTR lpszName) {
      void *param[1+1] = {(void*)lpszName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_OData_Do(m_pObj, 10000+13, 1, param, cbparam);
      
    }
    inline int SetSchemaType(LPWSTR lpszName) {
      void *param[1+1] = {(void*)lpszName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_OData_Do(m_pObj, 10000+14, 1, param, cbparam);
      
    }
    inline int UpdateEntry() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_OData_Do(m_pObj, 10000+15, 0, param, cbparam);
      
    }
    inline int UpdateProperty(LPWSTR lpszXPath, LPWSTR lpszValue) {
      void *param[2+1] = {(void*)lpszXPath, (void*)lpszValue, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_OData_Do(m_pObj, 10000+16, 2, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_ODATA_H_




