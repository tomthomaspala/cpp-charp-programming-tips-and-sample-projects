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

// ControlsDemoView.cpp : implementation of the CControlsDemoView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ControlsDemo.h"
#endif

#include "ControlsDemoDoc.h"
#include "ControlsDemoView.h"
#include "MainFrm.h"

//The follwing Import directive is needed to import the Interfaces in MS Chart Control to call various interfaces like IVcPlot , IVcAxiz etc
#import <msdatsrc.tlb> no_namespace
#import "Lib\MSCHRT20.OCX"   no_namespace //For convenience I placed the OCX control to My Own Folder

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CControlsDemoView

IMPLEMENT_DYNCREATE(CControlsDemoView, CView)

BEGIN_MESSAGE_MAP(CControlsDemoView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CControlsDemoView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_COMMAND(ID_BUTTON_XY_DEMO, &CControlsDemoView::OnButtonXyDemo)
	ON_COMMAND(ID_COMBO_PLOT_TYPE, &CControlsDemoView::OnComboPlotType)
END_MESSAGE_MAP()

// CControlsDemoView construction/destruction

CControlsDemoView::CControlsDemoView()
{
	// TODO: add construction code here
	m_pChartCtrl = NULL;
}

CControlsDemoView::~CControlsDemoView()
{
	delete m_pChartCtrl;
}

BOOL CControlsDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CControlsDemoView drawing

void CControlsDemoView::OnDraw(CDC* /*pDC*/)
{
	CControlsDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CControlsDemoView printing


void CControlsDemoView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CControlsDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CControlsDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CControlsDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CControlsDemoView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CControlsDemoView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CControlsDemoView diagnostics

#ifdef _DEBUG
void CControlsDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CControlsDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CControlsDemoDoc* CControlsDemoView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CControlsDemoDoc)));
	return (CControlsDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CControlsDemoView message handlers


void CControlsDemoView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CRect rectDummy;
	GetClientRect(&rectDummy);
	m_pChartCtrl = new CMschart();

	if (!m_pChartCtrl->Create(_T("Chart Control"), WS_VISIBLE | WS_CHILD, rectDummy, this, 23))
	{
		TRACE0("Failed to create Properties Grid \n");
	}

	// TODO: Add your specialized code here and/or call the base class
}


void CControlsDemoView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if (m_pChartCtrl)
	{
		m_pChartCtrl->SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	}
	
	// TODO: Add your message handler code here
}


void CControlsDemoView::OnButtonXyDemo()
{
	// TODO: Add your command handler code here
	m_pChartCtrl->put_chartType(CMschart::VtChChartType2dXY);
	COleSafeArray saRet;
	SAFEARRAYBOUND sab[2];

	sab[0].cElements = 5;// give this exact
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

	index[0] = 4;
	index[1] = 1;
	pValue = 4;
	saRet.PutElement(index, &pValue);

	index[0] = 4;
	index[1] = 2;
	pValue = 17.6;
	saRet.PutElement(index, &pValue);

	index[0] = 5;
	index[1] = 1;
	pValue = 5;
	saRet.PutElement(index, &pValue);

	index[0] = 5;
	index[1] = 2;
	pValue = 18;
	saRet.PutElement(index, &pValue);

	COleSafeArray saRet1 = saRet;
	m_pChartCtrl->put_ChartData(saRet1.Detach());

	m_pChartCtrl->put_TitleText(_T("X Axis | Distance Vs Refractive Index | Y Axis"));
	m_pChartCtrl->put_ColumnLabel(_T("Refractive Index"));
	m_pChartCtrl->put_RowLabel(_T("Distance"));

	IVcPlot* pPlot= (IVcPlot*)m_pChartCtrl->get_Plot();
	IVcAxis* pXAxis;
	IVcAxis* pYAxis;
	VARIANT varIndex;
	varIndex.vt = VT_I2;
	pPlot->get_Axis(VtChAxisId::VtChAxisIdX, varIndex,&pXAxis);

	IVcAxisTitlePtr XAxisTile = pXAxis->GetAxisTitle();
	XAxisTile->Text = CString(_T("Distance")).AllocSysString();

	varIndex.vt = VT_I2;
	pPlot->get_Axis(VtChAxisId::VtChAxisIdY, varIndex, &pYAxis);

	IVcAxisTitlePtr YAxisTile = pYAxis->GetAxisTitle();
	YAxisTile->Text = CString(_T("Refractive Index")).AllocSysString();

	m_pChartCtrl->Refresh();

	

}


void CControlsDemoView::OnComboPlotType()
{
	// TODO: Add your command handler code here
	switch (((CMFCRibbonComboBox*)((CMainFrame*)AfxGetMainWnd())->m_wndRibbonBar.FindByID(ID_COMBO_PLOT_TYPE))->GetCurSel())
	{
		case CMschart::VtChChartType3dBar:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType3dBar);
			break;
		case CMschart::VtChChartType2dBar:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType2dBar);
			break;
		case CMschart::VtChChartType3dLine:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType3dLine);
			break;
		case CMschart::VtChChartType2dLine:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType2dLine);
			break;
		case CMschart::VtChChartType3dArea:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType3dArea);
			break;
		case CMschart::VtChChartType2dArea:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType2dArea);
			break;
		case CMschart::VtChChartType3dStep:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType3dStep);
			break;
		case CMschart::VtChChartType2dStep:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType2dStep);
			break;
		case CMschart::VtChChartType3dCombination:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType3dCombination);
			break;
		case CMschart::VtChChartType2dCombination:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType2dCombination);
			break;
		case CMschart::VtChChartType3dHorizontalBar:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType3dHorizontalBar);
			break;
		case CMschart::VtChChartType2dHorizontalBar:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType2dHorizontalBar);
			break;
		case CMschart::VtChChartType3dClusteredBar:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType3dClusteredBar);
			break;
		case CMschart::VtChChartType3dPie:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType3dPie);
			break;
		case CMschart::VtChChartType2dPie:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType2dPie);
			break;
		case CMschart::VtChChartType3dDoughnut:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType3dDoughnut);
			break;
		case CMschart::VtChChartType2dXY:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType2dXY);
			break;
		case CMschart::VtChChartType2dPolar:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType2dPolar);
			break;
		case CMschart::VtChChartType2dRadar:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType2dRadar);
			break;
		case CMschart::VtChChartType2dBubble:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType2dBubble);
			break;
		case CMschart::VtChChartType2dHiLo:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType2dHiLo);
			break;
		case CMschart::VtChChartType2dGantt:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType2dGantt);
			break;
		case CMschart::VtChChartType3dGantt:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType3dGantt);
			break;
		case CMschart::VtChChartType3dSurface:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType3dSurface);
			break;
		case CMschart::VtChChartType2dContour:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType2dContour);
			break;
		case CMschart::VtChChartType3dScatter:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType3dScatter);
			break;
		case CMschart::VtChChartType3dXYZ:
			m_pChartCtrl->put_chartType(CMschart::VtChChartType3dXYZ);
			break;
		case CMschart::VtChChartTypeCount:
			m_pChartCtrl->put_chartType(CMschart::VtChChartTypeCount);
			break;

	}
}
