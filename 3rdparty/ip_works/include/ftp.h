/******************************************************************
   IP*Works! V9 C++ Edition
   Copyright (c) 2012 /n software inc. - All rights reserved.
*******************************************************************/

#ifndef _IPWORKS_FTP_H_
#define _IPWORKS_FTP_H_

#define IPWORKS_ONLY_TYPES
#include "ipworks.h"
#include "ipworks.key"

//FirewallTypes
#define FW_NONE                                            0
#define FW_TUNNEL                                          1
#define FW_SOCKS4                                          2
#define FW_SOCKS5                                          3

//TFTPTransferModes
#define TM_DEFAULT                                         0
#define TM_ASCII                                           1
#define TM_BINARY                                          2


extern "C" void* IPWORKS_CALL IPWorks_FTP_Create(PIPWORKS_CALLBACK lpSink, void *lpContext, char *lpOemKey);
extern "C" int   IPWORKS_CALL IPWorks_FTP_Destroy(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FTP_CheckIndex(void *lpObj, int propid, int arridx);
extern "C" void* IPWORKS_CALL IPWorks_FTP_Get(void *lpObj, int propid, int arridx, int *lpcbVal);
extern "C" int   IPWORKS_CALL IPWorks_FTP_Set(void *lpObj, int propid, int arridx, const void *val, int cbVal);
extern "C" int   IPWORKS_CALL IPWorks_FTP_Do(void *lpObj, int methid, int cparam, void *param[], int cbparam[]);
extern "C" char* IPWORKS_CALL IPWorks_FTP_GetLastError(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FTP_GetLastErrorCode(void *lpObj);
extern "C" int   IPWORKS_CALL IPWorks_FTP_StaticInit(void *hInst);
extern "C" int   IPWORKS_CALL IPWorks_FTP_StaticDestroy();

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
} FTPConnectionStatusEventParams;

typedef struct {
  const char* DirEntry;
  const char* FileName;
  int IsDir;
  ns_int64 *pFileSize;
  const char* FileTime;
  int reserved;
} FTPDirListEventParams;

typedef struct {
  int Direction;
  int reserved;
} FTPEndTransferEventParams;

typedef struct {
  int ErrorCode;
  const char* Description;
  int reserved;
} FTPErrorEventParams;

typedef struct {
  int Direction;
  const char* Message;
  int reserved;
} FTPPITrailEventParams;

typedef struct {
  int Direction;
  int reserved;
} FTPStartTransferEventParams;

typedef struct {
  int Direction;
  ns_int64 *pBytesTransferred;
  int PercentDone;
  const char* Text;
  int lenText;
  int reserved;
} FTPTransferEventParams;



class FTP {
  
  public: //events
  
    virtual int FireConnectionStatus(FTPConnectionStatusEventParams *e) {return 0;}
    virtual int FireDirList(FTPDirListEventParams *e) {return 0;}
    virtual int FireEndTransfer(FTPEndTransferEventParams *e) {return 0;}
    virtual int FireError(FTPErrorEventParams *e) {return 0;}
    virtual int FirePITrail(FTPPITrailEventParams *e) {return 0;}
    virtual int FireStartTransfer(FTPStartTransferEventParams *e) {return 0;}
    virtual int FireTransfer(FTPTransferEventParams *e) {return 0;}


  protected:

    void *m_pObj;
    
    static int IPWORKS_CALL FTPEventSink(void *lpObj, int event_id, int cparam, void *param[], int cbparam[]) {
      int ret_code = 0;
      if (event_id > 10000) return ((FTP*)lpObj)->FTPEventSinkW(event_id - 10000, cparam, param, cbparam);
      switch (event_id) {
         case 1: {
            FTPConnectionStatusEventParams e = {(char*)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (char*)IPW64CAST(param[2]),  0};
            ret_code = ((FTP*)lpObj)->FireConnectionStatus(&e);
            break;
         }
         case 2: {
            FTPDirListEventParams e = {(char*)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (ns_int64*)IPW64CAST(param[3]), (char*)IPW64CAST(param[4]),  0};
            ret_code = ((FTP*)lpObj)->FireDirList(&e);
            break;
         }
         case 3: {
            FTPEndTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((FTP*)lpObj)->FireEndTransfer(&e);
            break;
         }
         case 4: {
            FTPErrorEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((FTP*)lpObj)->FireError(&e);
            break;
         }
         case 5: {
            FTPPITrailEventParams e = {(int)IPW64CAST(param[0]), (char*)IPW64CAST(param[1]),  0};
            ret_code = ((FTP*)lpObj)->FirePITrail(&e);
            break;
         }
         case 6: {
            FTPStartTransferEventParams e = {(int)IPW64CAST(param[0]),  0};
            ret_code = ((FTP*)lpObj)->FireStartTransfer(&e);
            break;
         }
         case 7: {
            FTPTransferEventParams e = {(int)IPW64CAST(param[0]), (ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (char*)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = ((FTP*)lpObj)->FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }

    virtual int FTPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {return 0;}

  public:

    FTP(char *lpOemKey = (char*)IPWORKS_OEMKEY_17) {
      m_pObj = IPWorks_FTP_Create(FTPEventSink, (void*)this, (char*)lpOemKey);
    }

    virtual ~FTP() {
      IPWorks_FTP_Destroy(m_pObj);
    }

  public:

    inline char *GetLastError() {
      return IPWorks_FTP_GetLastError(m_pObj);
    }
    
    inline int GetLastErrorCode() {
      return IPWorks_FTP_GetLastErrorCode(m_pObj);
    }

    inline char *VERSION() {
      return (char*)IPWorks_FTP_Get(m_pObj, 0, 0, 0);
    }

  public: //properties

    inline char* GetAccount() {
      void* val = IPWorks_FTP_Get(m_pObj, 1, 0, 0);
      return (char*)val;
    }

    inline int SetAccount(const char *lpAccount) {
      return IPWorks_FTP_Set(m_pObj, 1, 0, (void*)lpAccount, 0);
    }


    inline int SetCommand(const char *lpCommand) {
      return IPWorks_FTP_Set(m_pObj, 2, 0, (void*)lpCommand, 0);
    }

    inline int GetConnected() {
      void* val = IPWorks_FTP_Get(m_pObj, 3, 0, 0);
      return (int)(long)val;
    }
    inline int SetConnected(int bConnected) {
      void* val = (void*)IPW64CAST(bConnected);
      return IPWorks_FTP_Set(m_pObj, 3, 0, val, 0);
    }
    inline int GetDirListCount() {
      void* val = IPWorks_FTP_Get(m_pObj, 4, 0, 0);
      return (int)(long)val;
    }

    inline char* GetDirListEntry(int iEntryIndex) {
      void* val = IPWorks_FTP_Get(m_pObj, 5, iEntryIndex, 0);
      return (char*)val;
    }


    inline char* GetDirListFileName(int iEntryIndex) {
      void* val = IPWorks_FTP_Get(m_pObj, 6, iEntryIndex, 0);
      return (char*)val;
    }


    inline ns_int64 GetDirListFileSize(int iEntryIndex) {
      ns_int64 *pval = (ns_int64*)IPWorks_FTP_Get(m_pObj, 7, iEntryIndex, 0);
      return *pval;
    }


    inline char* GetDirListFileTime(int iEntryIndex) {
      void* val = IPWorks_FTP_Get(m_pObj, 8, iEntryIndex, 0);
      return (char*)val;
    }


    inline int GetDirListIsDir(int iEntryIndex) {
      void* val = IPWorks_FTP_Get(m_pObj, 9, iEntryIndex, 0);
      return (int)(long)val;
    }

    inline int GetFileExists() {
      void* val = IPWorks_FTP_Get(m_pObj, 10, 0, 0);
      return (int)(long)val;
    }

    inline ns_int64 GetFileSize() {
      ns_int64 *pval = (ns_int64*)IPWorks_FTP_Get(m_pObj, 11, 0, 0);
      return *pval;
    }


    inline char* GetFileTime() {
      void* val = IPWorks_FTP_Get(m_pObj, 12, 0, 0);
      return (char*)val;
    }


    inline int GetFirewallAutoDetect() {
      void* val = IPWorks_FTP_Get(m_pObj, 13, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallAutoDetect(int bFirewallAutoDetect) {
      void* val = (void*)IPW64CAST(bFirewallAutoDetect);
      return IPWorks_FTP_Set(m_pObj, 13, 0, val, 0);
    }
    inline int GetFirewallType() {
      void* val = IPWorks_FTP_Get(m_pObj, 14, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallType(int iFirewallType) {
      void* val = (void*)IPW64CAST(iFirewallType);
      return IPWorks_FTP_Set(m_pObj, 14, 0, val, 0);
    }
    inline char* GetFirewallHost() {
      void* val = IPWorks_FTP_Get(m_pObj, 15, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallHost(const char *lpFirewallHost) {
      return IPWorks_FTP_Set(m_pObj, 15, 0, (void*)lpFirewallHost, 0);
    }

    inline char* GetFirewallPassword() {
      void* val = IPWorks_FTP_Get(m_pObj, 16, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallPassword(const char *lpFirewallPassword) {
      return IPWorks_FTP_Set(m_pObj, 16, 0, (void*)lpFirewallPassword, 0);
    }

    inline int GetFirewallPort() {
      void* val = IPWorks_FTP_Get(m_pObj, 17, 0, 0);
      return (int)(long)val;
    }
    inline int SetFirewallPort(int lFirewallPort) {
      void* val = (void*)IPW64CAST(lFirewallPort);
      return IPWorks_FTP_Set(m_pObj, 17, 0, val, 0);
    }
    inline char* GetFirewallUser() {
      void* val = IPWorks_FTP_Get(m_pObj, 18, 0, 0);
      return (char*)val;
    }

    inline int SetFirewallUser(const char *lpFirewallUser) {
      return IPWorks_FTP_Set(m_pObj, 18, 0, (void*)lpFirewallUser, 0);
    }

    inline int GetIdle() {
      void* val = IPWorks_FTP_Get(m_pObj, 19, 0, 0);
      return (int)(long)val;
    }

    inline char* GetLastReply() {
      void* val = IPWorks_FTP_Get(m_pObj, 20, 0, 0);
      return (char*)val;
    }


    inline char* GetLocalFile() {
      void* val = IPWorks_FTP_Get(m_pObj, 21, 0, 0);
      return (char*)val;
    }

    inline int SetLocalFile(const char *lpLocalFile) {
      return IPWorks_FTP_Set(m_pObj, 21, 0, (void*)lpLocalFile, 0);
    }

    inline char* GetLocalHost() {
      void* val = IPWorks_FTP_Get(m_pObj, 22, 0, 0);
      return (char*)val;
    }

    inline int SetLocalHost(const char *lpLocalHost) {
      return IPWorks_FTP_Set(m_pObj, 22, 0, (void*)lpLocalHost, 0);
    }

    inline int GetOverwrite() {
      void* val = IPWorks_FTP_Get(m_pObj, 23, 0, 0);
      return (int)(long)val;
    }
    inline int SetOverwrite(int bOverwrite) {
      void* val = (void*)IPW64CAST(bOverwrite);
      return IPWorks_FTP_Set(m_pObj, 23, 0, val, 0);
    }
    inline int GetPassive() {
      void* val = IPWorks_FTP_Get(m_pObj, 24, 0, 0);
      return (int)(long)val;
    }
    inline int SetPassive(int bPassive) {
      void* val = (void*)IPW64CAST(bPassive);
      return IPWorks_FTP_Set(m_pObj, 24, 0, val, 0);
    }
    inline char* GetPassword() {
      void* val = IPWorks_FTP_Get(m_pObj, 25, 0, 0);
      return (char*)val;
    }

    inline int SetPassword(const char *lpPassword) {
      return IPWorks_FTP_Set(m_pObj, 25, 0, (void*)lpPassword, 0);
    }

    inline char* GetRemoteFile() {
      void* val = IPWorks_FTP_Get(m_pObj, 26, 0, 0);
      return (char*)val;
    }

    inline int SetRemoteFile(const char *lpRemoteFile) {
      return IPWorks_FTP_Set(m_pObj, 26, 0, (void*)lpRemoteFile, 0);
    }

    inline char* GetRemoteHost() {
      void* val = IPWorks_FTP_Get(m_pObj, 27, 0, 0);
      return (char*)val;
    }

    inline int SetRemoteHost(const char *lpRemoteHost) {
      return IPWorks_FTP_Set(m_pObj, 27, 0, (void*)lpRemoteHost, 0);
    }

    inline char* GetRemotePath() {
      void* val = IPWorks_FTP_Get(m_pObj, 28, 0, 0);
      return (char*)val;
    }

    inline int SetRemotePath(const char *lpRemotePath) {
      return IPWorks_FTP_Set(m_pObj, 28, 0, (void*)lpRemotePath, 0);
    }

    inline int GetRemotePort() {
      void* val = IPWorks_FTP_Get(m_pObj, 29, 0, 0);
      return (int)(long)val;
    }
    inline int SetRemotePort(int lRemotePort) {
      void* val = (void*)IPW64CAST(lRemotePort);
      return IPWorks_FTP_Set(m_pObj, 29, 0, val, 0);
    }
    inline char* GetStartByte() {
      void* val = IPWorks_FTP_Get(m_pObj, 30, 0, 0);
      return (char*)val;
    }

    inline int SetStartByte(const char *lpStartByte) {
      return IPWorks_FTP_Set(m_pObj, 30, 0, (void*)lpStartByte, 0);
    }

    inline int GetTimeout() {
      void* val = IPWorks_FTP_Get(m_pObj, 31, 0, 0);
      return (int)(long)val;
    }
    inline int SetTimeout(int iTimeout) {
      void* val = (void*)IPW64CAST(iTimeout);
      return IPWorks_FTP_Set(m_pObj, 31, 0, val, 0);
    }
    inline int GetTransferMode() {
      void* val = IPWorks_FTP_Get(m_pObj, 32, 0, 0);
      return (int)(long)val;
    }
    inline int SetTransferMode(int iTransferMode) {
      void* val = (void*)IPW64CAST(iTransferMode);
      return IPWorks_FTP_Set(m_pObj, 32, 0, val, 0);
    }
    inline char* GetUser() {
      void* val = IPWorks_FTP_Get(m_pObj, 33, 0, 0);
      return (char*)val;
    }

    inline int SetUser(const char *lpUser) {
      return IPWorks_FTP_Set(m_pObj, 33, 0, (void*)lpUser, 0);
    }


  public: //methods

    inline int Abort() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 2, 0, param, cbparam);
      
      
    }
    inline int Append() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 3, 0, param, cbparam);
      
      
    }
    inline char* Config(const char* lpszConfigurationString) {
      void *param[1+1] = {(void*)IPW64CAST(lpszConfigurationString), 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_FTP_Do(m_pObj, 4, 1, param, cbparam);
      
      return (char*)IPW64CAST(param[1]);
    }
    inline int DeleteFile(const char* lpszFileName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszFileName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 5, 1, param, cbparam);
      
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 6, 0, param, cbparam);
      
      
    }
    inline int Download() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 7, 0, param, cbparam);
      
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 8, 0, param, cbparam);
      
      
    }
    inline int ListDirectory() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 9, 0, param, cbparam);
      
      
    }
    inline int ListDirectoryLong() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 10, 0, param, cbparam);
      
      
    }
    inline int Logoff() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 11, 0, param, cbparam);
      
      
    }
    inline int Logon() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 12, 0, param, cbparam);
      
      
    }
    inline int MakeDirectory(const char* lpszNewDir) {
      void *param[1+1] = {(void*)IPW64CAST(lpszNewDir), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 13, 1, param, cbparam);
      
      
    }
    inline int RemoveDirectory(const char* lpszDirName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszDirName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 14, 1, param, cbparam);
      
      
    }
    inline int RenameFile(const char* lpszNewName) {
      void *param[1+1] = {(void*)IPW64CAST(lpszNewName), 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 15, 1, param, cbparam);
      
      
    }
    inline int StoreUnique() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 18, 0, param, cbparam);
      
      
    }
    inline int Upload() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 19, 0, param, cbparam);
      
      
    }

};


#ifdef WIN32 //UNICODE

typedef struct {
  LPWSTR ConnectionEvent;
  int StatusCode;
  LPWSTR Description;
  int reserved;
} FTPConnectionStatusEventParamsW;

typedef struct {
  LPWSTR DirEntry;
  LPWSTR FileName;
  int IsDir;
  ns_int64 *pFileSize;
  LPWSTR FileTime;
  int reserved;
} FTPDirListEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} FTPEndTransferEventParamsW;

typedef struct {
  int ErrorCode;
  LPWSTR Description;
  int reserved;
} FTPErrorEventParamsW;

typedef struct {
  int Direction;
  LPWSTR Message;
  int reserved;
} FTPPITrailEventParamsW;

typedef struct {
  int Direction;
  int reserved;
} FTPStartTransferEventParamsW;

typedef struct {
  int Direction;
  ns_int64 *pBytesTransferred;
  int PercentDone;
  LPWSTR Text;
  int lenText;
  int reserved;
} FTPTransferEventParamsW;



class FTPW : public FTP {

  public: //properties
  
    inline LPWSTR GetAccount() {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+1, 0, 0);
    }

    inline int SetAccount(LPWSTR lpAccount) {
      return IPWorks_FTP_Set(m_pObj, 10000+1, 0, (void*)lpAccount, 0);
    }



    inline int SetCommand(LPWSTR lpCommand) {
      return IPWorks_FTP_Set(m_pObj, 10000+2, 0, (void*)lpCommand, 0);
    }





    inline LPWSTR GetDirListEntry(int iEntryIndex) {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+5, iEntryIndex, 0);
    }



    inline LPWSTR GetDirListFileName(int iEntryIndex) {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+6, iEntryIndex, 0);
    }





    inline LPWSTR GetDirListFileTime(int iEntryIndex) {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+8, iEntryIndex, 0);
    }









    inline LPWSTR GetFileTime() {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+12, 0, 0);
    }







    inline LPWSTR GetFirewallHost() {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+15, 0, 0);
    }

    inline int SetFirewallHost(LPWSTR lpFirewallHost) {
      return IPWorks_FTP_Set(m_pObj, 10000+15, 0, (void*)lpFirewallHost, 0);
    }

    inline LPWSTR GetFirewallPassword() {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+16, 0, 0);
    }

    inline int SetFirewallPassword(LPWSTR lpFirewallPassword) {
      return IPWorks_FTP_Set(m_pObj, 10000+16, 0, (void*)lpFirewallPassword, 0);
    }



    inline LPWSTR GetFirewallUser() {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+18, 0, 0);
    }

    inline int SetFirewallUser(LPWSTR lpFirewallUser) {
      return IPWorks_FTP_Set(m_pObj, 10000+18, 0, (void*)lpFirewallUser, 0);
    }



    inline LPWSTR GetLastReply() {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+20, 0, 0);
    }



    inline LPWSTR GetLocalFile() {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+10000+21, 0, 0);
    }

    inline int SetLocalFile(LPWSTR lpLocalFile) {
      return IPWorks_FTP_Set(m_pObj, 10000+10000+21, 0, (void*)lpLocalFile, 0);
    }

    inline LPWSTR GetLocalHost() {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+22, 0, 0);
    }

    inline int SetLocalHost(LPWSTR lpLocalHost) {
      return IPWorks_FTP_Set(m_pObj, 10000+22, 0, (void*)lpLocalHost, 0);
    }





    inline LPWSTR GetPassword() {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+25, 0, 0);
    }

    inline int SetPassword(LPWSTR lpPassword) {
      return IPWorks_FTP_Set(m_pObj, 10000+25, 0, (void*)lpPassword, 0);
    }

    inline LPWSTR GetRemoteFile() {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+26, 0, 0);
    }

    inline int SetRemoteFile(LPWSTR lpRemoteFile) {
      return IPWorks_FTP_Set(m_pObj, 10000+26, 0, (void*)lpRemoteFile, 0);
    }

    inline LPWSTR GetRemoteHost() {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+27, 0, 0);
    }

    inline int SetRemoteHost(LPWSTR lpRemoteHost) {
      return IPWorks_FTP_Set(m_pObj, 10000+27, 0, (void*)lpRemoteHost, 0);
    }

    inline LPWSTR GetRemotePath() {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+28, 0, 0);
    }

    inline int SetRemotePath(LPWSTR lpRemotePath) {
      return IPWorks_FTP_Set(m_pObj, 10000+28, 0, (void*)lpRemotePath, 0);
    }



    inline LPWSTR GetStartByte() {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+30, 0, 0);
    }

    inline int SetStartByte(LPWSTR lpStartByte) {
      return IPWorks_FTP_Set(m_pObj, 10000+30, 0, (void*)lpStartByte, 0);
    }





    inline LPWSTR GetUser() {
      return (LPWSTR)IPWorks_FTP_Get(m_pObj, 10000+33, 0, 0);
    }

    inline int SetUser(LPWSTR lpUser) {
      return IPWorks_FTP_Set(m_pObj, 10000+33, 0, (void*)lpUser, 0);
    }



  public: //events
  
    virtual int FireConnectionStatus(FTPConnectionStatusEventParamsW *e) {return 0;}
    virtual int FireDirList(FTPDirListEventParamsW *e) {return 0;}
    virtual int FireEndTransfer(FTPEndTransferEventParamsW *e) {return 0;}
    virtual int FireError(FTPErrorEventParamsW *e) {return 0;}
    virtual int FirePITrail(FTPPITrailEventParamsW *e) {return 0;}
    virtual int FireStartTransfer(FTPStartTransferEventParamsW *e) {return 0;}
    virtual int FireTransfer(FTPTransferEventParamsW *e) {return 0;}


  protected:
  
    virtual int FTPEventSinkW(int event_id, int cparam, void *param[], int cbparam[]) {
    	int ret_code = 0;
      switch (event_id) {
         case 1: {
            FTPConnectionStatusEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (int)IPW64CAST(param[1]), (LPWSTR)IPW64CAST(param[2]),  0};
            ret_code = FireConnectionStatus(&e);
            break;
         }
         case 2: {
            FTPDirListEventParamsW e = {(LPWSTR)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (ns_int64*)IPW64CAST(param[3]), (LPWSTR)IPW64CAST(param[4]),  0};
            ret_code = FireDirList(&e);
            break;
         }
         case 3: {
            FTPEndTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireEndTransfer(&e);
            break;
         }
         case 4: {
            FTPErrorEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FireError(&e);
            break;
         }
         case 5: {
            FTPPITrailEventParamsW e = {(int)IPW64CAST(param[0]), (LPWSTR)IPW64CAST(param[1]),  0};
            ret_code = FirePITrail(&e);
            break;
         }
         case 6: {
            FTPStartTransferEventParamsW e = {(int)IPW64CAST(param[0]),  0};
            ret_code = FireStartTransfer(&e);
            break;
         }
         case 7: {
            FTPTransferEventParamsW e = {(int)IPW64CAST(param[0]), (ns_int64*)IPW64CAST(param[1]), (int)IPW64CAST(param[2]), (LPWSTR)IPW64CAST(param[3]), (int)IPW64CAST(cbparam[3]),  0};
            ret_code = FireTransfer(&e);
            break;
         }

      }
      return ret_code;
    }
  
  public: //event overrides

    virtual int FireConnectionStatus(FTPConnectionStatusEventParams *e) {return -10000;}
    virtual int FireDirList(FTPDirListEventParams *e) {return -10000;}
    virtual int FireEndTransfer(FTPEndTransferEventParams *e) {return -10000;}
    virtual int FireError(FTPErrorEventParams *e) {return -10000;}
    virtual int FirePITrail(FTPPITrailEventParams *e) {return -10000;}
    virtual int FireStartTransfer(FTPStartTransferEventParams *e) {return -10000;}
    virtual int FireTransfer(FTPTransferEventParams *e) {return -10000;}

  public: //methods

    inline int Abort() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 10000+2, 0, param, cbparam);
      
    }
    inline int Append() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 10000+3, 0, param, cbparam);
      
    }
    inline LPWSTR Config(LPWSTR lpszConfigurationString) {
      void *param[1+1] = {(void*)lpszConfigurationString, 0};
      int cbparam[1+1] = {0, 0};
      IPWorks_FTP_Do(m_pObj, 10000+4, 1, param, cbparam);
      return (LPWSTR)IPW64CAST(param[1]);
    }
    inline int DeleteFile(LPWSTR lpszFileName) {
      void *param[1+1] = {(void*)lpszFileName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 10000+5, 1, param, cbparam);
      
    }
    inline int DoEvents() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 10000+6, 0, param, cbparam);
      
    }
    inline int Download() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 10000+7, 0, param, cbparam);
      
    }
    inline int Interrupt() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 10000+8, 0, param, cbparam);
      
    }
    inline int ListDirectory() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 10000+9, 0, param, cbparam);
      
    }
    inline int ListDirectoryLong() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 10000+10, 0, param, cbparam);
      
    }
    inline int Logoff() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 10000+11, 0, param, cbparam);
      
    }
    inline int Logon() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 10000+12, 0, param, cbparam);
      
    }
    inline int MakeDirectory(LPWSTR lpszNewDir) {
      void *param[1+1] = {(void*)lpszNewDir, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 10000+13, 1, param, cbparam);
      
    }
    inline int RemoveDirectory(LPWSTR lpszDirName) {
      void *param[1+1] = {(void*)lpszDirName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 10000+14, 1, param, cbparam);
      
    }
    inline int RenameFile(LPWSTR lpszNewName) {
      void *param[1+1] = {(void*)lpszNewName, 0};
      int cbparam[1+1] = {0, 0};
      return IPWorks_FTP_Do(m_pObj, 10000+15, 1, param, cbparam);
      
    }
    inline int StoreUnique() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 10000+18, 0, param, cbparam);
      
    }
    inline int Upload() {
      void *param[0+1] = {0};
      int cbparam[0+1] = {0};
      return IPWorks_FTP_Do(m_pObj, 10000+19, 0, param, cbparam);
      
    }

};

#endif //WIN32

#endif //_IPWORKS_FTP_H_




