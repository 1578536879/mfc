// CalendarDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "YX_TEST1_1.h"
#include "CalendarDlg.h"
#include "afxdialogex.h"


// CCalendarDlg �Ի���

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


// CCalendarDlg ��Ϣ�������


void CCalendarDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
