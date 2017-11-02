// CallbackEvents.h : Declaration of the CCallbackEvents

#pragma once
#include "resource.h"       // main symbols



#include "CallbackDLL_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CCallbackEvents

class ATL_NO_VTABLE CCallbackEvents :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCallbackEvents, &CLSID_CallbackEvents>,
	public IDispatchImpl<ICallbackEvents, &IID_ICallbackEvents, &LIBID_CallbackDLLLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CCallbackEvents()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CALLBACKEVENTS)


BEGIN_COM_MAP(CCallbackEvents)
	COM_INTERFACE_ENTRY(ICallbackEvents)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(OnStatusChangeEx)(ICallbackParam* Param);
};

OBJECT_ENTRY_AUTO(__uuidof(CallbackEvents), CCallbackEvents)
