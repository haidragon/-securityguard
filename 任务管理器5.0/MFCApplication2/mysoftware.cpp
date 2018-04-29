// mysoftware.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "mysoftware.h"
#include "afxdialogex.h"

// mysoftware 对话框

IMPLEMENT_DYNAMIC(mysoftware, CDialogEx)

mysoftware::mysoftware(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYSOFTWARE, pParent)
{

}

mysoftware::~mysoftware()
{
}

void mysoftware::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, myclistctrl);
}


BEGIN_MESSAGE_MAP(mysoftware, CDialogEx)
	ON_WM_PAINT()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &mysoftware::OnNMClickList1)
END_MESSAGE_MAP()


// mysoftware 消息处理程序


void mysoftware::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	myclistctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rc;
	myclistctrl.GetClientRect(rc);
	DWORD nwidth = rc.Width();
	//typedef struct tagHEAPLIST32 {
	//	SIZE_T    dwSize;
	//	DWORD     th32ProcessID;
	//	ULONG_PTR th32HeapID;
	//	DWORD     dwFlags;
	//} HEAPLIST32, *PHEAPLIST32;
	//	DWORD th32HeapID;
	myclistctrl.InsertColumn(0, L"软件名", 0, nwidth / 6);
	//	DWORD th32ProcessID;
	myclistctrl.InsertColumn(1, L"软件版本号", 1, nwidth / 6);
	//	DWORD dwSize;
	myclistctrl.InsertColumn(2, L"软件安装目录", 2, nwidth / 6);
	//	DWORD dwFlags;
	myclistctrl.InsertColumn(3, L"软件发布厂商", 3, nwidth / 6);
	myclistctrl.InsertColumn(4, L"安装日期", 4, nwidth / 6);
	myclistctrl.InsertColumn(5, L"卸载exe所在完整路径", 5, nwidth / 6);
	softwaredo();
}

void mysoftware::softwaredo()
{

	struct _SoftInfo
	{
		// 软件名  
		WCHAR m_strSoftName[50];
		// 软件版本号  
		WCHAR m_strSoftVersion[50];
		// 软件安装目录  
		WCHAR m_strInstallLocation[MAX_PATH];
		// 软件发布厂商  
		WCHAR m_strPublisher[50];
		// 软件安装日期 
		WCHAR time[MAX_PATH];
		// 卸载exe所在完整路径  
		WCHAR m_strUninstallPth[MAX_PATH];
	}SoftInfo = { 0 };
	HKEY hkPesult = 0;
	// 主键  
	HKEY RootKey = HKEY_LOCAL_MACHINE; //主键
	// 子键名称  
	LPCTSTR lpSubKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"; 
	// 将要打开键的句柄   
	HKEY hkResult;
	// 记录读取注册表是否成功  
	LONG lReturn;
	CString strBuffer;
	CString strMidReg;
	int i = 0;
	DWORD index = 0;
	TCHAR szKeyName[255] = { 0 };        // 注册表项名称  
	TCHAR szBuffer[255] = { 0 };
	DWORD dwKeyLen = 255;
	DWORD dwNameLen = 255;
	DWORD dwType = REG_BINARY | REG_DWORD | REG_EXPAND_SZ | REG_MULTI_SZ | REG_NONE | REG_SZ;
	CString *name = new CString;
	//1.打开一个已经存在的注册表键
	LONG lPeturn = RegOpenKeyEx(RootKey,//主键
		lpSubKey,//子键路径
		0, //保留  必须为0
		KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE, //权限
		&hkPesult   //子健句柄
	);
	//lpSubKey = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
	////lpSubKey = _T("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall");  
	bool isOK = false;
	DWORD dwIndex = 0;
	while (true)
	{
		DWORD dwKeyLen = 255;
		WCHAR szNewKeyName[MAX_PATH] = {};
		LONG lReturn = RegEnumKeyEx(hkPesult, dwIndex, szNewKeyName, &dwKeyLen, 0, NULL, NULL, NULL);
		OutputDebugString(szNewKeyName);
		WCHAR strMidReg[MAX_PATH] = {};
		swprintf_s(strMidReg, L"%s%s%s", lpSubKey, L"\\", szNewKeyName);
		HKEY hkValueKey = 0;
		RegOpenKeyEx(RootKey, strMidReg, 0, KEY_QUERY_VALUE, &hkValueKey);
		DWORD dwNameLen = 255;
		RegQueryValueEx(hkValueKey, L"DisplayName", 0, &dwType, (LPBYTE)SoftInfo.m_strSoftName, &dwNameLen);
		dwNameLen = 255;

		//if (SoftInfo.m_strSoftName == name[0])//去除重复  
		//{
		//	dwIndex++;
		//	continue;
		//}
		//// 软件名  
		//WCHAR m_strSoftName[50];
		//// 软件版本号  
		//WCHAR m_strSoftVersion[50];
		//// 软件安装目录  
		//WCHAR m_strInstallLocation[MAX_PATH];
		//// 软件发布厂商  
		//WCHAR m_strPublisher[50];
		//// 主程序所在完整路径  
		//WCHAR m_strMainProPath[MAX_PATH];
		//// 卸载exe所在完整路径  
		//WCHAR m_strUninstallPth[MAX_PATH];
		name[0] = SoftInfo.m_strSoftName;

		this->myclistctrl.InsertItem(i, NULL);
		//软件名称
		this->myclistctrl.SetItemText(i, 0, SoftInfo.m_strSoftName);
		//软件版本号

		
		RegQueryValueEx(hkValueKey, L"DisplayVersion", 0, &dwType, (LPBYTE)SoftInfo.m_strSoftVersion, &dwNameLen);
		dwNameLen = 255;
		CString srtT;
		srtT.Format(L"%s", SoftInfo.m_strSoftVersion);
		this->myclistctrl.SetItemText(i, 1, srtT);
		//软件安装目录 
		RegQueryValueEx(hkValueKey, L"InstallLocation", 0, &dwType, (LPBYTE)SoftInfo.m_strInstallLocation, &dwNameLen);
		dwNameLen = 255;
		srtT.Format(L"%s", SoftInfo.m_strInstallLocation);
		this->myclistctrl.SetItemText(i, 2, srtT);
		//软件发布厂商
		RegQueryValueEx(hkValueKey, L"Publisher", 0, &dwType, (LPBYTE)SoftInfo.m_strPublisher, &dwNameLen);
		dwNameLen = 255;
		srtT.Format(L"%s", SoftInfo.m_strPublisher);
		this->myclistctrl.SetItemText(i, 3, srtT);
		//主程日期
		RegQueryValueEx(hkValueKey, L"InstallDate", 0, &dwType, (LPBYTE)SoftInfo.time, &dwNameLen);
		dwNameLen = 255;
		srtT.Format(L"%s", SoftInfo.time);
		this->myclistctrl.SetItemText(i, 4, srtT);
		//卸载exe所在完整路径 
		RegQueryValueEx(hkValueKey, L"UninstallString", 0, &dwType, (LPBYTE)SoftInfo.m_strUninstallPth, &dwNameLen);
		dwNameLen = 255;
		srtT.Format(L"%s", SoftInfo.m_strUninstallPth);
		this->myclistctrl.SetItemText(i, 5, srtT);
		i++;
		dwIndex++;
		if (lReturn == ERROR_NO_MORE_ITEMS)
		{
			break;
		}
	}


	//1.找软件卸载信息
	//主键  HKEY_LOCAL_MACHINE
	//32位下： 子键  SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall
	//64位下：SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall
	//lpSubKey = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
	//lpSubKey = _T("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall");  
	//m_vectSoftInof

	//DWORD dwType;// = REG_BINARY | REG_DWORD | REG_EXPAND_SZ | REG_MULTI_SZ | REG_NONE | REG_SZ;

	//循环遍历Uninstall目录下的子健
	//DWORD dwIndex = 0;
	//while (true)
	//{
	//	DWORD dwKeyLen = 255;
	//	WCHAR szNewKeyName[MAX_PATH] = {};  //注册表项名称
	//	LONG lReturn = RegEnumKeyEx(hkPesult,//子健句柄
	//		dwIndex,//指定被枚举键下子键的索引，从0开始
	//		szNewKeyName, //指向一块内存保存子健的名称
	//		&dwKeyLen,//指向内存大小
	//		0,//保留必须为0
	//		NULL,//用于获取子健值的类型
	//		NULL,//指向一块内存，用于获取子键值的数据
	//		NULL);//上一个参数所向的会内存大小
	//	//通过得到的子键名称重新组合成新的子键路径
	//	WCHAR strMidReg[MAX_PATH] = {};
	//	swprintf_s(strMidReg, L"%s%s%s", lpSubKey, L"\\", szNewKeyName);
	//	//打开新的子键，获取其句柄
	//	HKEY hkValueKey = 0;   //子键句柄
	//	RegOpenKeyEx(RootKey,//主键
	//		strMidReg,//子键路径
	//		0, //保留  必须为0
	//	    KEY_QUERY_VALUE, //权限
	//		&hkValueKey   //子健句柄
	//	);
	//	//获取键值 
	//	DWORD dwNameLen = 255;   //
	//	//获取软件名称
	//	RegQueryValueEx(hkValueKey, L"DisplayName", 0, &dwType, (LPBYTE)SoftInfo.m_strSoftName, &dwNameLen);
	//    dwNameLen = 255;   //如果没有重新赋值下一次将获取不到信息
	//	//拆卸路径
	//	RegQueryValueEx(hkValueKey, L"UninstallString", 0, &dwType, (LPBYTE)SoftInfo.m_strUninstallPth, &dwNameLen);
	//    dwNameLen = 255;   //
	//	//如果没有
	//	if (lReturn == ERROR_NO_MORE_ITEMS)
	//	{
	//		break;
	//	}
	//	dwIndex++;
	//}

	
}

//点击事件
void mysoftware::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int ccol = pNMItemActivate->iSubItem;
	int crow = pNMItemActivate->iItem;
	if (ccol == 5) {
		CString str = myclistctrl.GetItemText(crow, ccol);
		this->ShowWindow(SW_HIDE);
		MessageBox(str, _T("信息"), IDOK);
		LPOFSTRUCT lpReOpenBuff;
		//卸载
		//OpenFile((LPCSTR)LPCTSTR(str), lpReOpenBuff, NULL);
		OFSTRUCT myOFSTRUCT = { 0 };
		//OpenFile((LPCSTR)str,&myOFSTRUCT,OF_READ);
		this->ShowWindow(SW_SHOW);
	}
	*pResult = 0;
	
}
