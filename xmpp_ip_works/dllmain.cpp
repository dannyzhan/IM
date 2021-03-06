// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "xmpp_impl.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

XMPP_API IMProtocol* Create(void) {
	return new xmpp_impl;
}

XMPP_API void Destroy(IMProtocol* protocol) {
	if (protocol) {
		protocol->Logoff();
		delete protocol;
	}
}