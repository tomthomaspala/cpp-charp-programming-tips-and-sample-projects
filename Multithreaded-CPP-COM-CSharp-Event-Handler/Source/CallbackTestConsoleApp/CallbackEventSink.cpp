#include "stdafx.h"
#include "CallbackEventSink.h"


CallbackEventSink::CallbackEventSink()
{

}


CallbackEventSink::~CallbackEventSink()
{
}


HRESULT CallbackEventSink::OnEventFiringObjectInvoke
(
	IEventFiringObjectEventHandler* pEventHandler,
	DISPID dispidMember,
	REFIID riid,
	LCID lcid,
	WORD wFlags,
	DISPPARAMS* pdispparams,
	VARIANT* pvarResult,
	EXCEPINFO* pexcepinfo,
	UINT* puArgErr
	)
{
	int i = dispidMember;
	switch (i)
	{
	case 1: // dispid 1 OnStatusChange

		break;

	}
	return S_OK;
}