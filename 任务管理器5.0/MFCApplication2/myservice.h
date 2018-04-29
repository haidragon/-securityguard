#pragma once
#include "afxcmn.h"
#include <windows.h>
#include <Winsvc.h>
// myservice 对话框

class myservice : public CDialogEx
{
	DECLARE_DYNAMIC(myservice)

public:
	myservice(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~myservice();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYSERVICE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mylistctrl;
	afx_msg void OnPaint();
	void myservicedo();
	//// 服务数据库句柄
	SC_HANDLE hSCM;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
