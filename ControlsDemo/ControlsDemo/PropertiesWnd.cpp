// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "ControlsDemo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	m_nComboHeight = 0;
	m_lChartType = 16;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGE_ACTIVE_TAB, OnTabSetActive)
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers


LRESULT CPropertiesWnd::OnTabSetActive(WPARAM wParam, LPARAM lParam)
{
		
	AdjustLayout();
	return 1;
}
void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;
	int MainWindowHeightReduction = m_nComboHeight + cyTlb + 20;
	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() -(MainWindowHeightReduction), SWP_NOACTIVATE | SWP_NOZORDER);
	m_ChartCtrl.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() - (MainWindowHeightReduction), SWP_NOACTIVATE | SWP_NOZORDER);
	Invalidate();
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create tabs window:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_3D_VS2005, rectDummy, this, 2))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}

	// Create combo:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	const DWORD dwStyle =  WS_CHILD | WS_VISIBLE ;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, &m_wndTabs, 1))
	{
		TRACE0("Failed to create Properties Combo \n");
		return -1;      // fail to create
	}

	m_wndObjectCombo.AddString(_T("Application"));
	m_wndObjectCombo.AddString(_T("Properties Window"));
	m_wndObjectCombo.SetCurSel(0);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect (&rectCombo);

	m_nComboHeight = rectCombo.Height();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, &m_wndTabs, 2))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;      // fail to create
	}

	if (!m_ChartCtrl.Create(_T("Chart Control"),WS_VISIBLE | WS_CHILD, rectDummy, &m_wndTabs, 22))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;      // fail to create
	}
	
	

	InitPropList();

	m_wndToolBar.Create(&m_wndTabs, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* Is locked */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* Locked */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);
		
	m_wndTabs.AddTab(&m_wndPropList, _T("Properties"), (UINT)0);
	m_wndTabs.AddTab(&m_ChartCtrl, _T("Report"), (UINT)1);
	//m_ChartCtrl.series

	int nBound = PopulateChartData();

	//---------------------------------------------
	//	Adding Data to Chart
	//---------------------------------------------

	AddOrUpdateChartData(nBound);

	AdjustLayout();
	
	m_ChartCtrl.put_chartType(m_lChartType);

	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
	m_wndTabs.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: Add your command handler code here
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: Add your command handler code here
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Appearance"));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("3D Look"), (_variant_t) false, _T("Specifies the window's font will be non-bold and controls will have a 3D border")));

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("Border"), _T("Dialog Frame"), _T("One of: None, Thin, Resizable, or Dialog Frame"));
	pProp->AddOption(_T("None"));
	pProp->AddOption(_T("Thin"));
	pProp->AddOption(_T("Resizable"));
	pProp->AddOption(_T("Dialog Frame"));
	pProp->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Caption"), (_variant_t) _T("About"), _T("Specifies the text that will be displayed in the window's title bar")));

	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("Window Size"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("Height"), (_variant_t) 250l, _T("Specifies the window's height"));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("Width"), (_variant_t) 150l, _T("Specifies the window's width"));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("Font"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	_tcscpy_s(lf.lfFaceName, _T("Arial"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("Font"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("Specifies the default font for the window")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Use System Font"), (_variant_t) true, _T("Specifies that the window uses MS Shell Dlg font")));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("Misc"));
	pProp = new CMFCPropertyGridProperty(_T("(Name)"), _T("Application"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("Window Color"), RGB(210, 192, 254), NULL, _T("Specifies the default window color"));
	pColorProp->EnableOtherButton(_T("Other..."));
	pColorProp->EnableAutomaticButton(_T("Default"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	static const TCHAR szFilter[] = _T("Icon Files(*.ico)|*.ico|All Files(*.*)|*.*||");
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("Icon"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("Specifies the window icon")));

	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("Folder"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("Hierarchy"));

	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("First sub-level"));
	pGroup4->AddSubItem(pGroup41);

	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("Second sub-level"));
	pGroup41->AddSubItem(pGroup411);

	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 1"), (_variant_t) _T("Value 1"), _T("This is a description")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 2"), (_variant_t) _T("Value 2"), _T("This is a description")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 3"), (_variant_t) _T("Value 3"), _T("This is a description")));

	pGroup4->Expand(FALSE);
	m_wndPropList.AddProperty(pGroup4);
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}


int CPropertiesWnd::PopulateChartData()
{
	//Forgive me for the bit elaborate list stucture
	// my application needed it to fill from a database query
	//however i am taKing out the complete recordset and database part

	m_filedetails.clear();

	CString csTemp;

	int nBound = 0;
	for (int i = 1;i<11;i++)
	{

		FILEDETAILS filedetailsstruct;

		//below is the rowlabel,it SHOULD NOT be a string 
		//that can be converted to a valid number

		csTemp.Format(_T("John_%d"), i);
		filedetailsstruct.login = csTemp;

		csTemp.Format(_T("%d"), i * 4);
		filedetailsstruct.n9000 = csTemp;

		csTemp.Format(_T("%d"), i * 6);
		filedetailsstruct.n9002 = csTemp;

		csTemp.Format(_T("%d"), i * 8);
		filedetailsstruct.n9004 = csTemp;

		csTemp.Format(_T("%d"), i * 10);
		filedetailsstruct.nCancel = csTemp;

		m_filedetails.insert(m_filedetails.end(), filedetailsstruct);
		nBound++;

	}

	return nBound;
}


int CPropertiesWnd::AddOrUpdateChartData(int  noOfRows)
{
#if true
#if 0
	m_ChartCtrl.put_ShowLegend(TRUE);
	COleSafeArray saRet;

	DWORD numElements[] = { 20, 4 };
	m_ChartCtrl.put_TitleText(_T("Distance Vs Refractive Index "));
	m_ChartCtrl.put_FootnoteText(_T("Distance"));
	
	saRet.Create(VT_R8, 2, numElements);

	long index[2] = { 0 , 0 };

	double value = 0;
	double vx[2] = { 0 , 0 };

	for (long i = 0; i < 20; i++)
	{
		// curve 1
		index[1] = 0;
		vx[0] = i*10;
		vx[1] = i;
		saRet.PutElement(index, &vx);
		index[0]= index[0]+1;
	}

	m_ChartCtrl.put_ChartData(saRet.Detach());
	m_ChartCtrl.put_ColumnCount(1);
	for (long j = 1;j < 21;j++)
	{
		m_ChartCtrl.put_Row(j);
		CString strData;
		strData.Format(_T("%d"), j);
		m_ChartCtrl.put_RowLabel(strData);
	}
	m_ChartCtrl.put_ColumnLabel(_T("Refractive Index"));
	
#else
	COleSafeArray saRet;
	SAFEARRAYBOUND sab[2];

	sab[0].cElements = 4;// give this exact
	sab[1].cElements = 2; //number of columns + 1 (because the first column is where we put 
						  // the row labels - ie in 1.1, 2.1, 3.1, 4,1 etc

	sab[0].lLbound = sab[1].lLbound = 1;

	// Use the chart as the backdrop of the legend.
	
	// Create the safe-array...

	saRet.Create(VT_R8, 2, sab);

	long index[2] = { 0,0 }; //a 2D graph needs a 2D array as index array

	index[0] = 1;
	index[1] = 1;
	double pValue = 1;
	saRet.PutElement(index, &pValue);

	index[0] = 1;
	index[1] = 2;
	pValue = 9.6;
	saRet.PutElement(index, &pValue);

	index[0] = 2;
	index[1] = 1;
	pValue = 2;
	saRet.PutElement(index, &pValue);

	index[0] = 2;
	index[1] = 2;
	pValue = 10.6;
	saRet.PutElement(index, &pValue);

	index[0] = 3;
	index[1] = 1;
	pValue = 3;
	saRet.PutElement(index, &pValue);

	index[0] = 3;
	index[1] = 2;
	pValue = 15.6;
	saRet.PutElement(index, &pValue);
	
	COleSafeArray saRet1= saRet;
	m_ChartCtrl.put_ChartData(saRet1.Detach());
	
	m_ChartCtrl.put_TitleText(_T("X Axis | Distance Vs Refractive Index | Y Axis"));
	m_ChartCtrl.put_ColumnLabel(_T("Refractive Index"));
	m_ChartCtrl.put_RowLabel(_T("Distance"));
	m_ChartCtrl.Refresh();
	
	index[0] = 4;
	index[1] = 1;
	pValue = 4;
	saRet.PutElement(index, &pValue);

	index[0] = 4;
	index[1] = 2;
	pValue = 17.6;
	saRet.PutElement(index, &pValue);

	saRet1 = saRet;
	m_ChartCtrl.put_ChartData(saRet1.Detach());
	m_ChartCtrl.Refresh();

#endif	
#else
	COleSafeArray saRet;

	SAFEARRAYBOUND sab[2];

	sab[0].cElements = noOfRows;// give this exact
	sab[1].cElements = 5; //number of columns + 1 (because the first column is where we put 
						  // the row labels - ie in 1.1, 2.1, 3.1, 4,1 etc

	sab[0].lLbound = sab[1].lLbound = 1;

	// Use the chart as the backdrop of the legend.
	m_ChartCtrl.put_ShowLegend(TRUE);

	// Create the safe-array...

	saRet.Create(VT_BSTR, 2, sab);

	long index[2] = { 0,0 }; //a 2D graph needs a 2D array as index array
	BSTR bstr;
	index[0] = 1;

	FILEDETAILS filedetailsstruct;
	CString cstemp;

	for (i = m_filedetails.begin();i != m_filedetails.end();i++)
	{

		filedetailsstruct = (FILEDETAILS)*i;

		index[1] = 1;
		bstr = filedetailsstruct.login.AllocSysString(); // Row label
		saRet.PutElement(index, bstr);

		index[1] = 2;

		bstr = filedetailsstruct.n9000.AllocSysString(); // Data for column 1
		::SysFreeString(bstr);
		saRet.PutElement(index, bstr);

		index[1] = 3;
		bstr = filedetailsstruct.n9002.AllocSysString(); // Data for column 2
		::SysFreeString(bstr);
		saRet.PutElement(index, bstr);

		index[1] = 4;
		bstr = filedetailsstruct.n9004.AllocSysString(); // Data for column 3
		::SysFreeString(bstr);
		saRet.PutElement(index, bstr);

		index[1] = 5;
		bstr = filedetailsstruct.nCancel.AllocSysString();// Data for column 4
		::SysFreeString(bstr);
		saRet.PutElement(index, bstr);

		index[0]++;

	}

	m_ChartCtrl.put_ChartData(saRet.Detach());

	m_ChartCtrl.put_ColumnLabelCount(4);
	m_ChartCtrl.put_Column(1);
	m_ChartCtrl.put_ColumnLabel(_T("Monday"));
	m_ChartCtrl.put_Column(2);
	m_ChartCtrl.put_ColumnLabel(_T("Wednesday"));
	m_ChartCtrl.put_Column(3);
	m_ChartCtrl.put_ColumnLabel(_T("Friday"));
	m_ChartCtrl.put_Column(4);
	m_ChartCtrl.put_ColumnLabel(_T("Saturday"));
#endif
	return 1;
}
