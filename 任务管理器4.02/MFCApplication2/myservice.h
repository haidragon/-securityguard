#pragma once
#include "afxcmn.h"
#include <windows.h>
#include <Winsvc.h>
// myservice �Ի���

class myservice : public CDialogEx
{
	DECLARE_DYNAMIC(myservice)

public:
	myservice(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~myservice();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYSERVICE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mylistctrl;
	afx_msg void OnPaint();
	void myservicedo();
	//// �������ݿ���
	SC_HANDLE hSCM;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
