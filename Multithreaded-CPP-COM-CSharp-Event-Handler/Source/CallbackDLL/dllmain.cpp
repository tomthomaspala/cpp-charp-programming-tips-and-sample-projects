// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "CallbackDLL_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CCallbackDLLModule _AtlModule;

class CCallbackDLLApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CCallbackDLLApp, CWinApp)
END_MESSAGE_MAP()

CCallbackDLLApp theApp;

BOOL CCallbackDLLApp::InitInstance()
{
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, NULL))
		return FALSE;
#endif
	return CWinApp::InitInstance();
}

int CCallbackDLLApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
