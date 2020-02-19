#pragma once


// CCalendarDlg 对话框

class CCalendarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCalendarDlg)

public:
	CCalendarDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCalendarDlg();

// 对话框数据
	enum { IDD = IDD_SHOWCALENDAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};
