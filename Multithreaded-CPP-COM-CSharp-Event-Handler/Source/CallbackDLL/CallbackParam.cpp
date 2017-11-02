// CallbackParam.cpp : Implementation of CCallbackParam

#include "stdafx.h"
#include "CallbackParam.h"


// CCallbackParam



STDMETHODIMP CCallbackParam::get_Param1(LONG* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here
	*pVal = m_Param1;
	return S_OK;
}


STDMETHODIMP CCallbackParam::put_Param1(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here
	m_Param1 = newVal;
	return S_OK;
}


STDMETHODIMP CCallbackParam::get_Param2(BSTR* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here
	*pVal= m_Param2;
	return S_OK;
}


STDMETHODIMP CCallbackParam::put_Param2(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your implementation code here
	m_Param2= newVal;
	return S_OK;
}



