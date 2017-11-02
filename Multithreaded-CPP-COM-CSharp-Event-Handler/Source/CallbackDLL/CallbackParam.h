// CallbackParam.h : Declaration of the CCallbackParam

#pragma once
#include "resource.h"       // main symbols



#include "CallbackDLL_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CCallbackParam

class ATL_NO_VTABLE CCallbackParam :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCallbackParam, &CLSID_CallbackParam>,
	public IDispatchImpl<ICallbackParam, &IID_ICallbackParam, &LIBID_CallbackDLLLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
	LONG m_Param1;
	BSTR m_Param2;
public:
	CCallbackParam()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CALLBACKPARAM)


BEGIN_COM_MAP(CCallbackParam)
	COM_INTERFACE_ENTRY(ICallbackParam)
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



	STDMETHOD(get_Param1)(LONG* pVal);
	STDMETHOD(put_Param1)(LONG newVal);
	STDMETHOD(get_Param2)(BSTR* pVal);
	STDMETHOD(put_Param2)(BSTR newVal);
	
};

OBJECT_ENTRY_AUTO(__uuidof(CallbackParam), CCallbackParam)
