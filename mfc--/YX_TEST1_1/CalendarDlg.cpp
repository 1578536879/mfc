// CalendarDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "YX_TEST1_1.h"
#include "CalendarDlg.h"
#include "afxdialogex.h"


// CCalendarDlg 对话框

IMPLEMENT_DYNAMIC(CCalendarDlg, CDialogEx)

CCalendarDlg::CCalendarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCalendarDlg::IDD, pParent)
{

}

CCalendarDlg::~CCalendarDlg()
{
}

void CCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCalendarDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CCalendarDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCalendarDlg 消息处理程序


void CCalendarDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
