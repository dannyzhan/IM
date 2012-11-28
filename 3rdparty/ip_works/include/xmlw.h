/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_XMLW_H_
#define _IPWORKS_XMLW_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_XMLw_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_XMLw_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMLw_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_XMLw_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_XMLw_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_XMLw_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_XMLw_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMLw_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMLw_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_XMLw_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} XMLwErrorEventParams;



class XMLw {
  
  public: //events
  
    virtual int FireError(XMLwErrorEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL XMLwEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((XMLw*)lpObj)->XMLwEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            XMLwErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((XMLw*)lpObj)->FireError(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int XMLwEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    XMLw(char *lpOemKey = (char*)IPWORKS_OEMKEY_80) {
      m_pObj = IPWorks_XMLw_Create(XMLwEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~XMLw() {
      IPWorks_XMLw_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_XMLw_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_XMLw_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_XMLw_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline char* GetEOL() {
      void* val = IPWorks_XMLw_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetEOL(const char *lpEOL) {
      return IPWorks_XMLw_Set(m_pObj, 1, 0, (void*)lpEOL, 0);
    }

    inline char* GetIndent() {
      void* val = IPWorks_XMLw_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetIndent(const char *lpIndent) {
      return IPWorks_XMLw_Set(m_pObj, 2, 0, (void*)lpIndent, 0);
    }

    inline int GetOutputData(char *&lpOutputData, int &lenOutputData) {
      lpOutputData = (char*)IPWorks_XMLw_Get(m_pObj, 3, 0, &lenOutputData);
      return lpOutputData ? 0 : lenOutputData;
    }


    inline char* GetOutputFile() {
      void* val = IPWorks_XMLw_Get(m_pObj, 4, 0, 0);
      return (char*)val;
    }

    inline int SetOutputFile(const char *lpOutputFile) {
      return IPWorks_XMLw_Set(m_pObj, 4, 0, (void*)lpOutputFile, 0);
    }


  public: //methods

    inline int Close() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMLw_Do(m_pObj, 2, 0, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XMLw_Do(m_pObj, 3, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int EndElement() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMLw_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMLw_Do(m_pObj, 5, 0, param, cbparam);
      
      
    }
    inline int StartElement(const char* lpszName, const char* lpszNamespaceURI) {
      void *param[2+1] = {(void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszNamespaceURI), 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_XMLw_Do(m_pObj, 7, 2, param, cbparam);
      
      
    }
    inline int WriteAttribute(const char* lpszName, const char* lpszNamespaceURI, const char* lpszValue) {
      void *param[3+1] = {(void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszNamespaceURI), (void*)IPW64CAST(lpszValue), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XMLw_Do(m_pObj, 8, 3, param, cbparam);
      
      
    }
    inline int WriteCData(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLw_Do(m_pObj, 9, 1, param, cbparam);
      
      
    }
    inline int WriteComment(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLw_Do(m_pObj, 10, 1, param, cbparam);
      
      
    }
    inline int WriteElement(const char* lpszName, const char* lpszNamespaceURI, const char* lpszValue) {
      void *param[3+1] = {(void*)IPW64CAST(lpszName), (void*)IPW64CAST(lpszNamespaceURI), (void*)IPW64CAST(lpszValue), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XMLw_Do(m_pObj, 11, 3, param, cbparam);
      
      
    }
    inline int WriteRaw(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLw_Do(m_pObj, 12, 1, param, cbparam);
      
      
    }
    inline int WriteString(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLw_Do(m_pObj, 13, 1, param, cbparam);
      
      
    }
    inline int WriteXMLDeclaration(const char* lpszVersion, int bIncludeEncoding, int bStandalone) {
      void *param[3+1] = {(void*)IPW64CAST(lpszVersion), (void*)IPW64CAST(bIncludeEncoding), (void*)IPW64CAST(bStandalone), 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XMLw_Do(m_pObj, 14, 3, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} XMLwErrorEventParamsW;



class XMLwW : public XMLw {

  public: //properties
  
    inline LPWSTR GetEOL() {
      return (LPWSTR)IPWorks_XMLw_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetEOL(LPWSTR lpEOL) {
      return IPWorks_XMLw_Set(m_pObj, 10000+1, 0, (void*)lpEOL, 0);
    }

    inline LPWSTR GetIndent() {
      return (LPWSTR)IPWorks_XMLw_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetIndent(LPWSTR lpIndent) {
      return IPWorks_XMLw_Set(m_pObj, 10000+2, 0, (void*)lpIndent, 0);
    }

    inline LPWSTR GetOutputData() {
      return (LPWSTR)IPWorks_XMLw_Get(m_pObj, 10000+3, 0, 0);
    }


    inline int GetOutputDataB(char *&lpOutputData, int &lenOutputData) {
      lpOutputData = (char*)IPWorks_XMLw_Get(m_pObj, 3, 0, &lenOutputData);
      return lpOutputData ? 0 : lenOutputData;
    }

    inline LPWSTR GetOutputFile() {
      return (LPWSTR)IPWorks_XMLw_Get(m_pObj, 10000+10000+4, 0, 0);
    }

    inline int SetOutputFile(LPWSTR lpOutputFile) {
      return IPWorks_XMLw_Set(m_pObj, 10000+10000+4, 0, (void*)lpOutputFile, 0);
    }



  public: //events
  
    virtual int FireError(XMLwErrorEventParamsW *e) {return 0;}


  protected:
  
    virtual int XMLwEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            XMLwErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireError(XMLwErrorEventParams *e) {return -10000;}

  public: //methods

    inline int Close() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMLw_Do(m_pObj, 10000+2, 0, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XMLw_Do(m_pObj, 10000+3, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int EndElement() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMLw_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMLw_Do(m_pObj, 10000+5, 0, param, cbparam);
      
    }
    inline int StartElement(LPWSTR lpszName, LPWSTR lpszNamespaceURI) {
      void *param[2+1] = {(void*)lpszName, (void*)lpszNamespaceURI, 0};
      int cbparam[2+1] = {0, 0, 0};
      return IPWorks_XMLw_Do(m_pObj, 10000+7, 2, param, cbparam);
      
    }
    inline int WriteAttribute(LPWSTR lpszName, LPWSTR lpszNamespaceURI, LPWSTR lpszValue) {
      void *param[3+1] = {(void*)lpszName, (void*)lpszNamespaceURI, (void*)lpszValue, 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XMLw_Do(m_pObj, 10000+8, 3, param, cbparam);
      
    }
    inline int WriteCData(LPWSTR lpszText) {
      void *param[1+1] = {(void*)lpszText, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLw_Do(m_pObj, 10000+9, 1, param, cbparam);
      
    }
    inline int WriteComment(LPWSTR lpszText) {
      void *param[1+1] = {(void*)lpszText, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLw_Do(m_pObj, 10000+10, 1, param, cbparam);
      
    }
    inline int WriteElement(LPWSTR lpszName, LPWSTR lpszNamespaceURI, LPWSTR lpszValue) {
      void *param[3+1] = {(void*)lpszName, (void*)lpszNamespaceURI, (void*)lpszValue, 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XMLw_Do(m_pObj, 10000+11, 3, param, cbparam);
      
    }
    inline int WriteRaw(LPWSTR lpszText) {
      void *param[1+1] = {(void*)lpszText, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLw_Do(m_pObj, 10000+12, 1, param, cbparam);
      
    }
    inline int WriteString(LPWSTR lpszText) {
      void *param[1+1] = {(void*)lpszText, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLw_Do(m_pObj, 10000+13, 1, param, cbparam);
      
    }
    inline int WriteXMLDeclaration(LPWSTR lpszVersion, int bIncludeEncoding, int bStandalone) {
      void *param[3+1] = {(void*)lpszVersion, (void*)bIncludeEncoding, (void*)bStandalone, 0};
      int cbparam[3+1] = {0, 0, 0, 0};
      return IPWorks_XMLw_Do(m_pObj, 10000+14, 3, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_XMLW_H_




