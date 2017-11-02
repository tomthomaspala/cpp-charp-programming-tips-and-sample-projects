// CallbackTestConsoleApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CallbackEventSink.h"
#include<stdio.h>

int main()
{
	printf("Callback Console Application Test\n");
	CoInitialize(NULL);

	CallbackEventSink EventSink;
	HRESULT hr= EventSink.CallbackTest.CoCreateInstance(CLSID_CallbackTest);
	EventSink.m_pIEventFiringObjectEventHandler = new IEventFiringObjectEventHandler(EventSink, EventSink.CallbackTest, &CallbackEventSink::OnEventFiringObjectInvoke);
	EventSink.CallbackTest->INIT();
	int i = 0;
	scanf_s("%d",i);

    return 0;
}

