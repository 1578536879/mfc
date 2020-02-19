
// YX_TEST1_1View.cpp : CYX_TEST1_1View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CYX_TEST1_1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_SHOW_CALENDAR, &CYX_TEST1_1View::OnShowCalendar)
	ON_COMMAND(ID_CLOCK_RUN, &CYX_TEST1_1View::OnClockRun)
END_MESSAGE_MAP()

// CYX_TEST1_1View 构造/析构

CYX_TEST1_1View::CYX_TEST1_1View()
{
	// TODO: 在此处添加构造代码
	m_time = false;
}

CYX_TEST1_1View::~CYX_TEST1_1View()
{
}

BOOL CYX_TEST1_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CYX_TEST1_1View 绘制

void CYX_TEST1_1View::OnDraw(CDC* /*pDC*/)
{
	m_pdc = GetDC();
	m_calendar.init(m_clock.getStartX(), m_clock.getStartY(), m_pdc, m_clock.getR());
	m_clock.init(m_calendar.getDayOfWeek(), m_pdc);
	CYX_TEST1_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CYX_TEST1_1View 打印


void CYX_TEST1_1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CYX_TEST1_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CYX_TEST1_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CYX_TEST1_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CYX_TEST1_1View 诊断

#ifdef _DEBUG
void CYX_TEST1_1View::AssertValid() const
{
	CView::AssertValid();
}

void CYX_TEST1_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CYX_TEST1_1Doc* CYX_TEST1_1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CYX_TEST1_1Doc)));
	return (CYX_TEST1_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CYX_TEST1_1View 消息处理程序


void CYX_TEST1_1View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_clock.intervalTime();//定时执行指针转到函数
	Invalidate();//刷新
	ReleaseDC(m_pdc);//释放pdc
	CView::OnTimer(nIDEvent);
}


void CYX_TEST1_1View::OnShowCalendar()
{

	// TODO: 在此添加命令处理程序代码

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
	// TODO: 在此添加命令处理程序代码
}
