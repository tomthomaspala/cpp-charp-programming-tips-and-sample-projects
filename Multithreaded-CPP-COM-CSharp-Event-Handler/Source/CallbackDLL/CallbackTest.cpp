// CallbackTest.cpp : Implementation of CCallbackTest

#include "stdafx.h"
#include "CallbackTest.h"
#include "CallbackParam.h"

// CCallbackTest



STDMETHODIMP CCallbackTest::INIT()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here
	m_pThread = AfxBeginThread(CCallbackTest::StartThread, this);
		
	return S_OK;
}





STDMETHODIMP CCallbackTest::INITEx(ICallbackEvents* EventsMethodsObj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here
	m_pCallbackTestEvents = EventsMethodsObj;
	INIT();
	return S_OK;
}


STDMETHODIMP CCallbackTest::STOP()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here
	m_pThread->SuspendThread();

	m_pThread->ExitInstance();
	m_pThread = NULL;

	return S_OK;
}

STDMETHODIMP CCallbackTest::get_Data(ICallbackParam* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here
	pVal = ParametersObj;
	return S_OK;
}

UINT CCallbackTest::StartThread(LPVOID Param)
{
	CCallbackTest* pObject = (CCallbackTest*)Param;
	long Duration;
	for (int i = 0;i < 30;i++)
	{
		Duration = i * 12;
		pObject->ParametersObj->put_Param1(i);
		CString strData;
		strData.Format(_T("Test data %d : Duration %d Sec"), i, Duration);
		pObject->ParametersObj->put_Param2(strData.AllocSysString());
		if (pObject->m_pCallbackTestEvents != NULL)
		{
			pObject->m_pCallbackTestEvents->OnStatusChangeEx(pObject->ParametersObj);
		}
		else
		{
			pObject->Fire_OnStatusChange(pObject->ParametersObj);
		}
		Sleep(12000);
	}
	
	return 1;
}

