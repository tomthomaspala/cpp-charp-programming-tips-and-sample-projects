Multithreaded C++|ATL|COM CSharp Event Handler Sample =====================================================

This Project Sample Demonstrates how to develop a Multithreaded C++|ATL|COM Component Which implements  IConnectionPoint Interface so that It can fire events to COM Component Hosted applications in C#.NET and in C++

The Project Sample Contains 3 Projects

1. CallbackDLL 
===============
In this Project the Multithreaded C++ | ATL | COM components is implemented as a DLL with exposes few Interface Methods to start the activity and to Fire Callback events.

2. CallbacktestApp
==================
This is the C# Form Based application Sample that Hosts the COM Component and Receves the Event Fired form the COM Cmponent.

3. CallbackTestConsoleApp
==========================
This is a C++ based Console Application Sample that also Hosts the COM Cmponent and Receves the Event Fired form the COM Cmponent.

How to Run the Program
======================
1. First Compile the CallbackDLL Project
2. Register the COM Component using Regsvr32.exe 
2. Compile and Run the Two Test App see how the Sample Works  
   






 