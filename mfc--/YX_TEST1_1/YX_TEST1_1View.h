
// YX_TEST1_1View.h : CYX_TEST1_1View 类的接口
//

#pragma once
#include "Calendar.h"
#include "Clock.h"


class CYX_TEST1_1View : public CView
{
	CCalendar m_calendar;
	CClock m_clock;
	CDC * m_pdc;
	bool m_time;
protected: // 仅从序列化创建
	CYX_TEST1_1View();
	DECLARE_DYNCREATE(CYX_TEST1_1View)

// 特性
public:
	CYX_TEST1_1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CYX_TEST1_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowCalendar();
	afx_msg void OnClockRun();
};

#ifndef _DEBUG  // YX_TEST1_1View.cpp 中的调试版本
inline CYX_TEST1_1Doc* CYX_TEST1_1View::GetDocument() const
   { return reinterpret_cast<CYX_TEST1_1Doc*>(m_pDocument); }
#endif

