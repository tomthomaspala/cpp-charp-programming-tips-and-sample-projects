// CallbackTest.h : Declaration of the CCallbackTest

#pragma once
#include "resource.h"       // main symbols



#include "CallbackDLL_i.h"
#include "_ICallbackTestEvents_CP.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CCallbackTest

class ATL_NO_VTABLE CCallbackTest :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCallbackTest, &CLSID_CallbackTest>,
	public IConnectionPointContainerImpl<CCallbackTest>,
	public CProxy_ICallbackTestEvents<CCallbackTest>,
	public IDispatchImpl<ICallbackTest, &IID_ICallbackTest, &LIBID_CallbackDLLLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
	CComPtr<ICallbackParam> ParametersObj;
	ICallbackEvents * m_pCallbackTestEvents;
	CWinThread* m_pThread;
public:
	
	CCallbackTest()
	{
		m_pCallbackTestEvents = NULL;
		ParametersObj.CoCreateInstance(CLSID_CallbackParam);

	}
	static UINT StartThread(LPVOID Param);
DECLARE_REGISTRY_RESOURCEID(IDR_CALLBACKTEST)


BEGIN_COM_MAP(CCallbackTest)
	COM_INTERFACE_ENTRY(ICallbackTest)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CCallbackTest)
	CONNECTION_POINT_ENTRY(__uuidof(_ICallbackTestEvents))
END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(INIT)();
	
	STDMETHOD(INITEx)(ICallbackEvents* EventsMethods);
	STDMETHOD(STOP)();
	
	STDMETHOD(get_Data)(ICallbackParam* pVal);
	
};

OBJECT_ENTRY_AUTO(__uuidof(CallbackTest), CCallbackTest)
