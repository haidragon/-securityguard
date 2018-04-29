#pragma once
#include "afxcmn.h"
#include <vector>
using namespace std;

// mysoftware 对话框

class mysoftware : public CDialogEx
{
	DECLARE_DYNAMIC(mysoftware)

public:
	mysoftware(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~mysoftware();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYSOFTWARE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl myclistctrl;
	afx_msg void OnPaint();
	void softwaredo();
	typedef struct _SoftInfo
	{
		// 软件名  
		WCHAR m_strSoftName[50];
		// 软件版本号  
		WCHAR m_strSoftVersion[50];
		// 软件安装目录  
		WCHAR m_strInstallLocation[MAX_PATH];
		// 软件发布厂商  
		WCHAR m_strPublisher[50];
		// 主程序所在完整路径  
		WCHAR m_strMainProPath[MAX_PATH];
		// 卸载exe所在完整路径  
		WCHAR m_strUninstallPth[MAX_PATH];
	}SOFTINFO, *PSOFTINFO;
	vector<SOFTINFO> m_vectSoftInof;
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
