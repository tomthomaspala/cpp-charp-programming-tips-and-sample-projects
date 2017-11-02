// dllmain.h : Declaration of module class.

class CCallbackDLLModule : public ATL::CAtlDllModuleT< CCallbackDLLModule >
{
public :
	DECLARE_LIBID(LIBID_CallbackDLLLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CALLBACKDLL, "{6C3F7CD7-DFA3-4C1B-B927-A276A00149A9}")
};

extern class CCallbackDLLModule _AtlModule;
