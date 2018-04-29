// ccmymodo.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "ccmymodo.h"
#include "afxdialogex.h"
#include<TlHelp32.h>
#include<Windows.h>
#include<Psapi.h>
// ccmymodo 对话框
 DWORD pid = 0;
IMPLEMENT_DYNAMIC(ccmymodo, CDialogEx)

ccmymodo::ccmymodo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

ccmymodo::~ccmymodo()
{
}

void ccmymodo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, myctrl);
}


BEGIN_MESSAGE_MAP(ccmymodo, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// ccmymodo 消息处理程序



bool ccmymodo::EnumModule(DWORD dwPID) {
	// 1. 先创建快照
	HANDLE hTool32 = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	if (INVALID_HANDLE_VALUE == hTool32)
	{
		MessageBox(L"权限太低，看清名称不要瞎点！！！！");
		//printf("快照error!\n");
		return false;
	}
	// 2. 开始遍历进程
	MODULEENTRY32W mi = { sizeof(MODULEENTRY32W) };
	BOOL bRet = Module32First(hTool32, &mi);
	if (!bRet)
	{
		
		printf("Module32First error!\n");
		return false;
	}
	//	printf("baseaddr    size       handle     name:\n");
	//typedef struct tagMODULEENTRY32 {
	//	DWORD   dwSize;
	//	DWORD   th32ModuleID;
	//	DWORD   th32ProcessID;
	//	DWORD   GlblcntUsage;
	//	DWORD   ProccntUsage;
	//	BYTE    *modBaseAddr;
	//	DWORD   modBaseSize;
	//	HMODULE hModule;
	//	TCHAR   szModule[MAX_MODULE_NAME32 + 1];
	//	TCHAR   szExePath[MAX_PATH];
	//} MODULEENTRY32, *PMODULEENTRY32;
	int i = 0;
	myctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rc;
	myctrl.GetClientRect(rc);
	DWORD nwidth = rc.Width();
				 //	TCHAR   szModule[MAX_MODULE_NAME32 + 1];
	myctrl.InsertColumn(0, L"szModule", 0, nwidth / 6);

	//	DWORD   th32ModuleID;
	myctrl.InsertColumn(1, L"th32ModuleID", 1, nwidth / 8);
	//	DWORD   th32ProcessID;
	myctrl.InsertColumn(2, L"th32ProcessID", 2, nwidth / 8);
	//	DWORD   GlblcntUsage;
	myctrl.InsertColumn(3, L"GlblcntUsage", 3, nwidth / 8);
	//	DWORD   ProccntUsage;
	myctrl.InsertColumn(4, L"ProccntUsage", 4, nwidth / 8);
	//	BYTE    *modBaseAddr;
	myctrl.InsertColumn(5, L"modBaseAddr", 5, nwidth / 8);
	//	DWORD   modBaseSize;
	myctrl.InsertColumn(6, L"modBaseSize", 6, nwidth / 8);
	//	HMODULE hModule;
	myctrl.InsertColumn(7, L"hModule", 7, nwidth / 8);
	//	DWORD   dwSize;
	myctrl.InsertColumn(8, L"dwSize", 8, nwidth / 8);
	//	TCHAR   szExePath[MAX_PATH];
	myctrl.InsertColumn(9, L"szExePath", 9, nwidth / 8);
	do
	{
		//	TCHAR   szModule[MAX_MODULE_NAME32 + 1];
		//CString szModule;
		//	szModule.Format(L"%4d", mi.szModule);
		myctrl.InsertItem(i, mi.szModule);
		//	DWORD   th32ModuleID;
		CString th32ModuleID;
		th32ModuleID.Format(L"%4d", mi.th32ModuleID);
		myctrl.SetItemText(i, 1, th32ModuleID);
		//	DWORD     th32ProcessID;
		CString th32ProcessID;
		th32ProcessID.Format(L"%4d", mi.th32ProcessID);
		myctrl.SetItemText(i, 2, th32ProcessID);
		//	DWORD     GlblcntUsage;
		CString GlblcntUsage;
		GlblcntUsage.Format(L"%4d", mi.GlblcntUsage);
		myctrl.SetItemText(i, 3, GlblcntUsage);
		//	DWORD   ProccntUsage;
		CString ProccntUsage;
		ProccntUsage.Format(L"%04d", mi.ProccntUsage);
		myctrl.SetItemText(i, 4, ProccntUsage);
		//	BYTE    *modBaseAddr;
		CString modBaseAddr;
		modBaseAddr.Format(L"%08x", (DWORD)mi.modBaseAddr);
		myctrl.SetItemText(i, 5, modBaseAddr);
		//	DWORD   modBaseSize;
		CString modBaseSize;
		modBaseSize.Format(L"%4d", mi.modBaseSize);
		myctrl.SetItemText(i, 6, modBaseSize);
		//	HMODULE hModule;
		CString hModule;
		hModule.Format(L"%4d", mi.hModule);
		myctrl.SetItemText(i, 7, hModule);
		//	DWORD     dwSize;
		CString dwSize;
		dwSize.Format(L"%4d", mi.dwSize);
		myctrl.SetItemText(i, 8, dwSize);
		//	TCHAR   szExePath[MAX_PATH];
		myctrl.SetItemText(i, 9, mi.szExePath);
		/*	printf("%08x   %08x    %08x   %S\n",
		(DWORD)mi.modBaseAddr,
		mi.modBaseSize,
		mi.hModule,
		mi.szModule);*/



	} while (Module32NextW(hTool32, &mi));
	return true;
}



void ccmymodo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	EnumModule(pid);

}

bool ccmymodo::EnumModule2(DWORD dwPID)
{   //1.枚举进程模块的函数
	/*BOOL WINAPI EnumProcessModulesEx(
		_In_  HANDLE  hProcess,       //进程句柄
		_Out_ HMODULE *lphModule,     //获取到的所有模块句柄的数组    会将所有模块的信息返回 这是个数组的首地址
		_In_  DWORD   cb,			  //模块句柄数组大小
		_Out_ LPDWORD lpcbNeeded,	  //实际需要的数组的大小
		_In_  DWORD   dwFilterFlag    //枚举模块的类型
	);*/
	//2.如果调用这个函数时，如果不知道需要传入多少缓冲区先传0
	//
	DWORD DWszie = 0;
	EnumProcessModulesEx((HANDLE)dwPID, NULL, 0, &DWszie, LIST_MODULES_ALL);
	HMODULE* pmodewhandler = (HMODULE*) new char[DWszie];
	//3.再调用
	EnumProcessModulesEx((HANDLE)dwPID, pmodewhandler, DWszie, &DWszie, LIST_MODULES_ALL);
	//
	TCHAR szModuleName[MAX_PATH];
	for (int i = 0;i < DWszie / sizeof(HMODULE);++i) {
		MODULEINFO stcModuleinfo = { 0 };
		//模块信息
		//GetModuleInformation
		//模块全路径
		//GetModuleBaseName
	}
	return false;
}
