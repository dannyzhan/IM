/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_XMLP_H_
#define _IPWORKS_XMLP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"


extern "C" void* IPWORKS_CALL IPWorks_XMLp_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_XMLp_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMLp_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_XMLp_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_XMLp_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_XMLp_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_XMLp_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMLp_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_XMLp_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_XMLp_StaticDestroy();

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4311) 
#pragma warning(disable:4312) 
#endif

typedef struct {
  const char* Text;
  int lenText;
  int reserved;
} XMLpCharactersEventParams;

typedef struct {
  const char* Text;
  int reserved;
} XMLpCommentEventParams;

typedef struct {
  const char* Namespace;
  const char* Element;
  const char* QName;
  int IsEmpty;
  int reserved;
} XMLpEndElementEventParams;

typedef struct {
  const char* Prefix;
  int reserved;
} XMLpEndPrefixMappingEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} XMLpErrorEventParams;

typedef struct {
  const char* Entity;
  const char* Value;
  int reserved;
} XMLpEvalEntityEventParams;

typedef struct {
  const char* Text;
  int reserved;
} XMLpIgnorableWhitespaceEventParams;

typedef struct {
  const char* Text;
  int reserved;
} XMLpMetaEventParams;

typedef struct {
  const char* Text;
  int reserved;
} XMLpPIEventParams;

typedef struct {
  const char* SectionId;
  const char* Text;
  int reserved;
} XMLpSpecialSectionEventParams;

typedef struct {
  const char* Namespace;
  const char* Element;
  const char* QName;
  int IsEmpty;
  int reserved;
} XMLpStartElementEventParams;

typedef struct {
  const char* Prefix;
  const char* URI;
  int reserved;
} XMLpStartPrefixMappingEventParams;



class XMLp {
  
  public: //events
  
    virtual int FireCharacters(XMLpCharactersEventParams *e) {return 0;}
    virtual int FireComment(XMLpCommentEventParams *e) {return 0;}
    virtual int FireEndElement(XMLpEndElementEventParams *e) {return 0;}
    virtual int FireEndPrefixMapping(XMLpEndPrefixMappingEventParams *e) {return 0;}
    virtual int FireError(XMLpErrorEventParams *e) {return 0;}
    virtual int FireEvalEntity(XMLpEvalEntityEventParams *e) {return 0;}
    virtual int FireIgnorableWhitespace(XMLpIgnorableWhitespaceEventParams *e) {return 0;}
    virtual int FireMeta(XMLpMetaEventParams *e) {return 0;}
    virtual int FirePI(XMLpPIEventParams *e) {return 0;}
    virtual int FireSpecialSection(XMLpSpecialSectionEventParams *e) {return 0;}
    virtual int FireStartElement(XMLpStartElementEventParams *e) {return 0;}
    virtual int FireStartPrefixMapping(XMLpStartPrefixMappingEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL XMLpEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((XMLp*)lpObj)->XMLpEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            XMLpCharactersEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = ((XMLp*)lpObj)->FireCharacters(&e);
            break;
         }
         case 2: {
            XMLpCommentEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((XMLp*)lpObj)->FireComment(&e);
            break;
         }
         case 3: {
            XMLpEndElementEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = ((XMLp*)lpObj)->FireEndElement(&e);
            break;
         }
         case 4: {
            XMLpEndPrefixMappingEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((XMLp*)lpObj)->FireEndPrefixMapping(&e);
            break;
         }
         case 5: {
            XMLpErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((XMLp*)lpObj)->FireError(&e);
            break;
         }
         case 6: {
            XMLpEvalEntityEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((XMLp*)lpObj)->FireEvalEntity(&e);
            param[1] = (void*)IPW64CAST(e.Value);
            break;
         }
         case 7: {
            XMLpIgnorableWhitespaceEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((XMLp*)lpObj)->FireIgnorableWhitespace(&e);
            break;
         }
         case 8: {
            XMLpMetaEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((XMLp*)lpObj)->FireMeta(&e);
            break;
         }
         case 9: {
            XMLpPIEventParams e = {(char*)IPW64CAST(param[0]),  0};
            ret_code = ((XMLp*)lpObj)->FirePI(&e);
            break;
         }
         case 10: {
            XMLpSpecialSectionEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((XMLp*)lpObj)->FireSpecialSection(&e);
            break;
         }
         case 11: {
            XMLpStartElementEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = ((XMLp*)lpObj)->FireStartElement(&e);
            break;
         }
         case 12: {
            XMLpStartPrefixMappingEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((XMLp*)lpObj)->FireStartPrefixMapping(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int XMLpEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    XMLp(char *lpOemKey = (char*)IPWORKS_OEMKEY_54) {
      m_pObj = IPWorks_XMLp_Create(XMLpEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~XMLp() {
      IPWorks_XMLp_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_XMLp_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_XMLp_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_XMLp_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline int GetBuildDOM() {
      void* val = IPWorks_XMLp_Get(m_pObj, 1, 0, 0);
      return (int)(long)val;
    }
    inline int SetBuildDOM(int bBuildDOM) {
      void* val = (void*)IPW64CAST(bBuildDOM);
      return IPWorks_XMLp_Set(m_pObj, 1, 0, val, 0);
    }
    inline char* GetExtraNameChars() {
      void* val = IPWorks_XMLp_Get(m_pObj, 2, 0, 0);
      return (char*)val;
    }

    inline int SetExtraNameChars(const char *lpExtraNameChars) {
      return IPWorks_XMLp_Set(m_pObj, 2, 0, (void*)lpExtraNameChars, 0);
    }

    inline char* GetExtraSpaceChars() {
      void* val = IPWorks_XMLp_Get(m_pObj, 3, 0, 0);
      return (char*)val;
    }

    inline int SetExtraSpaceChars(const char *lpExtraSpaceChars) {
      return IPWorks_XMLp_Set(m_pObj, 3, 0, (void*)lpExtraSpaceChars, 0);
    }

    inline int GetFlushOnEOL() {
      void* val = IPWorks_XMLp_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }
    inline int SetFlushOnEOL(int bFlushOnEOL) {
      void* val = (void*)IPW64CAST(bFlushOnEOL);
      return IPWorks_XMLp_Set(m_pObj, 4, 0, val, 0);
    }
    inline int GetNamespaceCount() {
      void* val = IPWorks_XMLp_Get(m_pObj, 5, 0, 0);
      return (int)(long)val;
    }

    inline char* GetNamespacePrefix(int iNamespaceIndex) {
      void* val = IPWorks_XMLp_Get(m_pObj, 6, iNamespaceIndex, 0);
      return (char*)val;
    }


    inline char* GetNamespaceURI(int iNamespaceIndex) {
      void* val = IPWorks_XMLp_Get(m_pObj, 7, iNamespaceIndex, 0);
      return (char*)val;
    }


    inline int GetOffset() {
      void* val = IPWorks_XMLp_Get(m_pObj, 8, 0, 0);
      return (int)(long)val;
    }

    inline int GetValidate() {
      void* val = IPWorks_XMLp_Get(m_pObj, 9, 0, 0);
      return (int)(long)val;
    }
    inline int SetValidate(int bValidate) {
      void* val = (void*)IPW64CAST(bValidate);
      return IPWorks_XMLp_Set(m_pObj, 9, 0, val, 0);
    }
    inline int GetAttrCount() {
      void* val = IPWorks_XMLp_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }

    inline char* GetAttrName(int iAttrIndex) {
      void* val = IPWorks_XMLp_Get(m_pObj, 11, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrNamespace(int iAttrIndex) {
      void* val = IPWorks_XMLp_Get(m_pObj, 12, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrPrefix(int iAttrIndex) {
      void* val = IPWorks_XMLp_Get(m_pObj, 13, iAttrIndex, 0);
      return (char*)val;
    }


    inline char* GetAttrValue(int iAttrIndex) {
      void* val = IPWorks_XMLp_Get(m_pObj, 14, iAttrIndex, 0);
      return (char*)val;
    }


    inline int GetXChildrenCount() {
      void* val = IPWorks_XMLp_Get(m_pObj, 15, 0, 0);
      return (int)(long)val;
    }

    inline char* GetXChildName(int iXChildIndex) {
      void* val = IPWorks_XMLp_Get(m_pObj, 16, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildNamespace(int iXChildIndex) {
      void* val = IPWorks_XMLp_Get(m_pObj, 17, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildPrefix(int iXChildIndex) {
      void* val = IPWorks_XMLp_Get(m_pObj, 18, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXChildXText(int iXChildIndex) {
      void* val = IPWorks_XMLp_Get(m_pObj, 19, iXChildIndex, 0);
      return (char*)val;
    }


    inline char* GetXElement() {
      void* val = IPWorks_XMLp_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }


    inline char* GetXNamespace() {
      void* val = IPWorks_XMLp_Get(m_pObj, 21, 0, 0);
      return (char*)val;
    }


    inline char* GetXParent() {
      void* val = IPWorks_XMLp_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }


    inline char* GetXPath() {
      void* val = IPWorks_XMLp_Get(m_pObj, 23, 0, 0);
      return (char*)val;
    }

    inline int SetXPath(const char *lpXPath) {
      return IPWorks_XMLp_Set(m_pObj, 23, 0, (void*)lpXPath, 0);
    }

    inline char* GetXPrefix() {
      void* val = IPWorks_XMLp_Get(m_pObj, 24, 0, 0);
      return (char*)val;
    }


    inline char* GetXSubTree() {
      void* val = IPWorks_XMLp_Get(m_pObj, 25, 0, 0);
      return (char*)val;
    }


    inline char* GetXText() {
      void* val = IPWorks_XMLp_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }



  public: //methods

    inline char* Attr(const char* lpszAttrName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszAttrName), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XMLp_Do(m_pObj, 2, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XMLp_Do(m_pObj, 3, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int Flush() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMLp_Do(m_pObj, 4, 0, param, cbparam);
      
      
    }
    inline int HasXPath(const char* lpszxpath) {
      void *param[1+1] = {(void*)IPW64CAST(lpszxpath), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XMLp_Do(m_pObj, 5, 1, param, cbparam);
      
      return (int)IPW64CAST(param[1]);
    }
    inline int Input(const char* lpszText) {
      void *param[1+1] = {(void*)IPW64CAST(lpszText), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLp_Do(m_pObj, 6, 1, param, cbparam);
      
      
    }
    inline int LoadDOM(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLp_Do(m_pObj, 7, 1, param, cbparam);
      
      
    }
    inline int ParseFile(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLp_Do(m_pObj, 8, 1, param, cbparam);
      
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMLp_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int SaveDOM(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLp_Do(m_pObj, 10, 1, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR Text;
  int lenText;
  int reserved;
} XMLpCharactersEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} XMLpCommentEventParamsW;

typedef struct {
  LPWSTR Namespace;
  LPWSTR Element;
  LPWSTR QName;
  int IsEmpty;
  int reserved;
} XMLpEndElementEventParamsW;

typedef struct {
  LPWSTR Prefix;
  int reserved;
} XMLpEndPrefixMappingEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} XMLpErrorEventParamsW;

typedef struct {
  LPWSTR Entity;
  LPWSTR Value;
  int reserved;
} XMLpEvalEntityEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} XMLpIgnorableWhitespaceEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} XMLpMetaEventParamsW;

typedef struct {
  LPWSTR Text;
  int reserved;
} XMLpPIEventParamsW;

typedef struct {
  LPWSTR SectionId;
  LPWSTR Text;
  int reserved;
} XMLpSpecialSectionEventParamsW;

typedef struct {
  LPWSTR Namespace;
  LPWSTR Element;
  LPWSTR QName;
  int IsEmpty;
  int reserved;
} XMLpStartElementEventParamsW;

typedef struct {
  LPWSTR Prefix;
  LPWSTR URI;
  int reserved;
} XMLpStartPrefixMappingEventParamsW;



class XMLpW : public XMLp {

  public: //properties
  


    inline LPWSTR GetExtraNameChars() {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+2, 0, 0);
    }

    inline int SetExtraNameChars(LPWSTR lpExtraNameChars) {
      return IPWorks_XMLp_Set(m_pObj, 10000+2, 0, (void*)lpExtraNameChars, 0);
    }

    inline LPWSTR GetExtraSpaceChars() {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+3, 0, 0);
    }

    inline int SetExtraSpaceChars(LPWSTR lpExtraSpaceChars) {
      return IPWorks_XMLp_Set(m_pObj, 10000+3, 0, (void*)lpExtraSpaceChars, 0);
    }





    inline LPWSTR GetNamespacePrefix(int iNamespaceIndex) {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+6, iNamespaceIndex, 0);
    }



    inline LPWSTR GetNamespaceURI(int iNamespaceIndex) {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+7, iNamespaceIndex, 0);
    }









    inline LPWSTR GetAttrName(int iAttrIndex) {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+11, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrNamespace(int iAttrIndex) {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+12, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrPrefix(int iAttrIndex) {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+13, iAttrIndex, 0);
    }



    inline LPWSTR GetAttrValue(int iAttrIndex) {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+14, iAttrIndex, 0);
    }





    inline LPWSTR GetXChildName(int iXChildIndex) {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+16, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildNamespace(int iXChildIndex) {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+17, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildPrefix(int iXChildIndex) {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+18, iXChildIndex, 0);
    }



    inline LPWSTR GetXChildXText(int iXChildIndex) {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+19, iXChildIndex, 0);
    }



    inline LPWSTR GetXElement() {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+20, 0, 0);
    }



    inline LPWSTR GetXNamespace() {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+21, 0, 0);
    }



    inline LPWSTR GetXParent() {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+22, 0, 0);
    }



    inline LPWSTR GetXPath() {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+23, 0, 0);
    }

    inline int SetXPath(LPWSTR lpXPath) {
      return IPWorks_XMLp_Set(m_pObj, 10000+23, 0, (void*)lpXPath, 0);
    }

    inline LPWSTR GetXPrefix() {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+24, 0, 0);
    }



    inline LPWSTR GetXSubTree() {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+25, 0, 0);
    }



    inline LPWSTR GetXText() {
      return (LPWSTR)IPWorks_XMLp_Get(m_pObj, 10000+26, 0, 0);
    }





  public: //events
  
    virtual int FireCharacters(XMLpCharactersEventParamsW *e) {return 0;}
    virtual int FireComment(XMLpCommentEventParamsW *e) {return 0;}
    virtual int FireEndElement(XMLpEndElementEventParamsW *e) {return 0;}
    virtual int FireEndPrefixMapping(XMLpEndPrefixMappingEventParamsW *e) {return 0;}
    virtual int FireError(XMLpErrorEventParamsW *e) {return 0;}
    virtual int FireEvalEntity(XMLpEvalEntityEventParamsW *e) {return 0;}
    virtual int FireIgnorableWhitespace(XMLpIgnorableWhitespaceEventParamsW *e) {return 0;}
    virtual int FireMeta(XMLpMetaEventParamsW *e) {return 0;}
    virtual int FirePI(XMLpPIEventParamsW *e) {return 0;}
    virtual int FireSpecialSection(XMLpSpecialSectionEventParamsW *e) {return 0;}
    virtual int FireStartElement(XMLpStartElementEventParamsW *e) {return 0;}
    virtual int FireStartPrefixMapping(XMLpStartPrefixMappingEventParamsW *e) {return 0;}


  protected:
  
    virtual int XMLpEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            XMLpCharactersEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(cbparam[0]),  0};
            ret_code = FireCharacters(&e);
            break;
         }
         case 2: {
            XMLpCommentEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireComment(&e);
            break;
         }
         case 3: {
            XMLpEndElementEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = FireEndElement(&e);
            break;
         }
         case 4: {
            XMLpEndPrefixMappingEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireEndPrefixMapping(&e);
            break;
         }
         case 5: {
            XMLpErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 6: {
            XMLpEvalEntityEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireEvalEntity(&e);
            param[1] = (void*)(e.Value);
            break;
         }
         case 7: {
            XMLpIgnorableWhitespaceEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireIgnorableWhitespace(&e);
            break;
         }
         case 8: {
            XMLpMetaEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FireMeta(&e);
            break;
         }
         case 9: {
            XMLpPIEventParamsW e = {(LPWSTR)IPW64CAST(param[0]),  0};
            ret_code = FirePI(&e);
            break;
         }
         case 10: {
            XMLpSpecialSectionEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireSpecialSection(&e);
            break;
         }
         case 11: {
            XMLpStartElementEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]), (int)IPW64CAST(param[3]),  0};
            ret_code = FireStartElement(&e);
            break;
         }
         case 12: {
            XMLpStartPrefixMappingEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireStartPrefixMapping(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireCharacters(XMLpCharactersEventParams *e) {return -10000;}
    virtual int FireComment(XMLpCommentEventParams *e) {return -10000;}
    virtual int FireEndElement(XMLpEndElementEventParams *e) {return -10000;}
    virtual int FireEndPrefixMapping(XMLpEndPrefixMappingEventParams *e) {return -10000;}
    virtual int FireError(XMLpErrorEventParams *e) {return -10000;}
    virtual int FireEvalEntity(XMLpEvalEntityEventParams *e) {return -10000;}
    virtual int FireIgnorableWhitespace(XMLpIgnorableWhitespaceEventParams *e) {return -10000;}
    virtual int FireMeta(XMLpMetaEventParams *e) {return -10000;}
    virtual int FirePI(XMLpPIEventParams *e) {return -10000;}
    virtual int FireSpecialSection(XMLpSpecialSectionEventParams *e) {return -10000;}
    virtual int FireStartElement(XMLpStartElementEventParams *e) {return -10000;}
    virtual int FireStartPrefixMapping(XMLpStartPrefixMappingEventParams *e) {return -10000;}

  public: //methods

    inline LPWSTR Attr(LPWSTR lpszAttrName) {
      void *param[1+1] = {(void*)lpszAttrName, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XMLp_Do(m_pObj, 10000+2, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XMLp_Do(m_pObj, 10000+3, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int Flush() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMLp_Do(m_pObj, 10000+4, 0, param, cbparam);
      
    }
    inline int HasXPath(LPWSTR lpszxpath) {
      void *param[1+1] = {(void*)lpszxpath, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_XMLp_Do(m_pObj, 10000+5, 1, param, cbparam);
      return (int)IPW64CAST(param[1]);
    }
    inline int Input(LPWSTR lpszText) {
      void *param[1+1] = {(void*)lpszText, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLp_Do(m_pObj, 10000+6, 1, param, cbparam);
      
    }
    inline int LoadDOM(LPWSTR lpszFileName) {
      void *param[1+1] = {(void*)lpszFileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLp_Do(m_pObj, 10000+7, 1, param, cbparam);
      
    }
    inline int ParseFile(LPWSTR lpszFileName) {
      void *param[1+1] = {(void*)lpszFileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLp_Do(m_pObj, 10000+8, 1, param, cbparam);
      
    }
    inline int Reset() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_XMLp_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int SaveDOM(LPWSTR lpszFileName) {
      void *param[1+1] = {(void*)lpszFileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_XMLp_Do(m_pObj, 10000+10, 1, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_XMLP_H_




