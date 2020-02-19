
// YX_TEST1_1View.cpp : CYX_TEST1_1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "YX_TEST1_1.h"
#endif

#include "YX_TEST1_1Doc.h"
#include "YX_TEST1_1View.h"

#include "CalendarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CYX_TEST1_1View

IMPLEMENT_DYNCREATE(CYX_TEST1_1View, CView)

BEGIN_MESSAGE_MAP(CYX_TEST1_1View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CYX_TEST1_1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_SHOW_CALENDAR, &CYX_TEST1_1View::OnShowCalendar)
	ON_COMMAND(ID_CLOCK_RUN, &CYX_TEST1_1View::OnClockRun)
END_MESSAGE_MAP()

// CYX_TEST1_1View ����/����

CYX_TEST1_1View::CYX_TEST1_1View()
{
	// TODO: �ڴ˴���ӹ������
	m_time = false;
}

CYX_TEST1_1View::~CYX_TEST1_1View()
{
}

BOOL CYX_TEST1_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CYX_TEST1_1View ����

void CYX_TEST1_1View::OnDraw(CDC* /*pDC*/)
{
	m_pdc = GetDC();
	m_calendar.init(m_clock.getStartX(), m_clock.getStartY(), m_pdc, m_clock.getR());
	m_clock.init(m_calendar.getDayOfWeek(), m_pdc);
	CYX_TEST1_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CYX_TEST1_1View ��ӡ


void CYX_TEST1_1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CYX_TEST1_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CYX_TEST1_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CYX_TEST1_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CYX_TEST1_1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CYX_TEST1_1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CYX_TEST1_1View ���

#ifdef _DEBUG
void CYX_TEST1_1View::AssertValid() const
{
	CView::AssertValid();
}

void CYX_TEST1_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CYX_TEST1_1Doc* CYX_TEST1_1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CYX_TEST1_1Doc)));
	return (CYX_TEST1_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CYX_TEST1_1View ��Ϣ�������


void CYX_TEST1_1View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_clock.intervalTime();//��ʱִ��ָ��ת������
	Invalidate();//ˢ��
	ReleaseDC(m_pdc);//�ͷ�pdc
	CView::OnTimer(nIDEvent);
}


void CYX_TEST1_1View::OnShowCalendar()
{

	// TODO: �ڴ���������������

	CCalendarDlg dlg;
	dlg.DoModal();


}


void CYX_TEST1_1View::OnClockRun()
{
	if(m_time){
		KillTimer(1);
		m_time = false;
	}else{
		SetTimer(1, 50, NULL);
		m_time = true;
	}
	// TODO: �ڴ���������������
}
