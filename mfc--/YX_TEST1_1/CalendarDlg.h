#pragma once


// CCalendarDlg �Ի���

class CCalendarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCalendarDlg)

public:
	CCalendarDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCalendarDlg();

// �Ի�������
	enum { IDD = IDD_SHOWCALENDAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};
