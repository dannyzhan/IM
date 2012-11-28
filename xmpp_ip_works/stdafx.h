// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#ifdef XMPP_IP_WORKS_EXPORTS
#define XMPP_API __declspec(dllexport)
#else
#define XMPP_API __declspec(dllimport)
#endif


// TODO: reference additional headers your program requires here
