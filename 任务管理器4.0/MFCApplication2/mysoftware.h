#pragma once
#include "afxcmn.h"
#include <vector>
using namespace std;

// mysoftware �Ի���

class mysoftware : public CDialogEx
{
	DECLARE_DYNAMIC(mysoftware)

public:
	mysoftware(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~mysoftware();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYSOFTWARE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl myclistctrl;
	afx_msg void OnPaint();
	void softwaredo();
	typedef struct _SoftInfo
	{
		// �����  
		WCHAR m_strSoftName[50];
		// ����汾��  
		WCHAR m_strSoftVersion[50];
		// �����װĿ¼  
		WCHAR m_strInstallLocation[MAX_PATH];
		// �����������  
		WCHAR m_strPublisher[50];
		// ��������������·��  
		WCHAR m_strMainProPath[MAX_PATH];
		// ж��exe��������·��  
		WCHAR m_strUninstallPth[MAX_PATH];
	}SOFTINFO, *PSOFTINFO;
	vector<SOFTINFO> m_vectSoftInof;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
