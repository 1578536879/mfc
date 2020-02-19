
// YX_TEST1_1View.h : CYX_TEST1_1View ��Ľӿ�
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
protected: // �������л�����
	CYX_TEST1_1View();
	DECLARE_DYNCREATE(CYX_TEST1_1View)

// ����
public:
	CYX_TEST1_1Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CYX_TEST1_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // YX_TEST1_1View.cpp �еĵ��԰汾
inline CYX_TEST1_1Doc* CYX_TEST1_1View::GetDocument() const
   { return reinterpret_cast<CYX_TEST1_1Doc*>(m_pDocument); }
#endif

