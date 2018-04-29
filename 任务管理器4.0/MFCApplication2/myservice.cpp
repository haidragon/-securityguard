// myservice.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "myservice.h"
#include "afxdialogex.h"

// myservice 对话框

IMPLEMENT_DYNAMIC(myservice, CDialogEx)

myservice::myservice(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MYSERVICE, pParent)
{

}

myservice::~myservice()
{
}

void myservice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mylistctrl);
}


BEGIN_MESSAGE_MAP(myservice, CDialogEx)
	ON_WM_PAINT()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &myservice::OnNMClickList1)
END_MESSAGE_MAP()


// myservice 消息处理程序


void myservice::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	mylistctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CRect rc;
	mylistctrl.GetClientRect(rc);
	DWORD nwidth = rc.Width();
	//typedef struct tagHEAPLIST32 {
	//	SIZE_T    dwSize;
	//	DWORD     th32ProcessID;
	//	ULONG_PTR th32HeapID;
	//	DWORD     dwFlags;
	//} HEAPLIST32, *PHEAPLIST32;
	//	DWORD th32HeapID;
	mylistctrl.InsertColumn(0, L"DisplayName", 0, nwidth / 10);
	//	DWORD th32ProcessID;
	mylistctrl.InsertColumn(1, L"ServiceName", 1, nwidth / 10);
	//	DWORD dwSize;
	mylistctrl.InsertColumn(2, L"ServiceType", 2, nwidth / 10);
	//	DWORD dwFlags;
	mylistctrl.InsertColumn(3, L"CurrentState", 3, nwidth / 10);
	mylistctrl.InsertColumn(4, L"ControlsAccepted", 4, nwidth / 10);
	mylistctrl.InsertColumn(5, L"Win32ExitCode", 5, nwidth / 10);
	mylistctrl.InsertColumn(6, L"ServiceSpecificExitCode", 6, nwidth / 10);
	mylistctrl.InsertColumn(7, L"CheckPoint", 7, nwidth / 10);
	mylistctrl.InsertColumn(8, L"WaitHint", 8, nwidth / 10);
	mylistctrl.InsertColumn(9, L"Process Id", 9, nwidth / 10);
	mylistctrl.InsertColumn(10, L"ServiceFlags", 10, nwidth / 10);
	myservicedo();

}

void myservice::myservicedo()
{
	LONG lRet = 0;
	BOOL bRet = FALSE;           
	char *pBuf = NULL;                  // 缓冲区指针
	DWORD dwBufSize = 0;                // 传入的缓冲长度
	DWORD dwBufNeed = 0;                // 需要的缓冲长度
	DWORD dwNumberOfService = 0;        // 返回的服务个数
	ENUM_SERVICE_STATUS_PROCESS *pServiceInfo = NULL;   // 服务信息

														// 建立了一个到服务控制管理器的连接，并打开指定的数据库
	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE | SC_MANAGER_CONNECT);
	if (NULL == hSCM)
	{
		printf("OpenSCManager error.\n");
		return ;
	}

	// 获取需要的缓冲区大小  dwBufSize
	EnumServicesStatusEx(hSCM, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,
		NULL, dwBufSize, &dwBufNeed, &dwNumberOfService, NULL, NULL);

	// 多设置存放1个服务信息的长度
	dwBufSize = dwBufNeed + sizeof(ENUM_SERVICE_STATUS_PROCESS);
	pBuf = (char *)malloc(dwBufSize);
	if (NULL == pBuf)
	{
		printf("malloc error.\n");
		return;
	}
	memset(pBuf, 0, dwBufSize);

	// 获取服务信息
	bRet = EnumServicesStatusEx(hSCM, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,
		(LPBYTE)pBuf, dwBufSize, &dwBufNeed, &dwNumberOfService, NULL, NULL);
	if (bRet == FALSE)
	{
		printf("EnumServicesStatusEx error.\n");
		::CloseServiceHandle(hSCM);
		free(pBuf);
		return ;
	}
	// 关闭打开的服务句柄
	bRet = ::CloseServiceHandle(hSCM);
	if (bRet == FALSE)
	{
		printf("CloseServiceHandle error.\n");
	}
	printf("Service Num:%d\n", dwNumberOfService);

	pServiceInfo = (LPENUM_SERVICE_STATUS_PROCESS)pBuf;
	// 打印取得的服务信息
	for (unsigned int i = 0; i < dwNumberOfService; i++)
	{

		this->mylistctrl.InsertItem(i, NULL);
		//软件名称
		this->mylistctrl.SetItemText(i, 0, pServiceInfo[i].lpDisplayName);
		this->mylistctrl.SetItemText(i, 1, pServiceInfo[i].lpServiceName);
		CString str;
		str.Format(L"%d", pServiceInfo[i].ServiceStatusProcess.dwServiceType);
		this->mylistctrl.SetItemText(i, 2, str);
		str.Format(L"%d", pServiceInfo[i].ServiceStatusProcess.dwCurrentState);
		this->mylistctrl.SetItemText(i, 3, str);
		str.Format(L"%d", pServiceInfo[i].ServiceStatusProcess.dwControlsAccepted);
		this->mylistctrl.SetItemText(i, 4, str);
		str.Format(L"%d", pServiceInfo[i].ServiceStatusProcess.dwWin32ExitCode);
		this->mylistctrl.SetItemText(i, 5,str);
		str.Format(L"%d", pServiceInfo[i].ServiceStatusProcess.dwServiceSpecificExitCode);
		this->mylistctrl.SetItemText(i, 6,str);
		str.Format(L"%d", pServiceInfo[i].ServiceStatusProcess.dwCheckPoint);
		this->mylistctrl.SetItemText(i, 7,str);
		str.Format(L"%d", pServiceInfo[i].ServiceStatusProcess.dwWaitHint);
		this->mylistctrl.SetItemText(i, 8,str);
		str.Format(L"%d", pServiceInfo[i].ServiceStatusProcess.dwProcessId);
		this->mylistctrl.SetItemText(i, 9,str);
		str.Format(L"%d", pServiceInfo[i].ServiceStatusProcess.dwServiceFlags);
		this->mylistctrl.SetItemText(i, 10,str);

	/*	printf("----------%d----------\n", i);
		printf("DisplayName \t\t : %s \n", pServiceInfo[i].lpDisplayName);
		printf("ServiceName \t\t : %s \n", pServiceInfo[i].lpServiceName);
		printf("ServiceType \t\t : %d \n", pServiceInfo[i].ServiceStatusProcess.dwServiceType);
		printf("CurrentState \t\t : %d \n", pServiceInfo[i].ServiceStatusProcess.dwCurrentState);
		printf("ControlsAccepted \t : %d \n", pServiceInfo[i].ServiceStatusProcess.dwControlsAccepted);
		printf("Win32ExitCode \t\t : %d \n", pServiceInfo[i].ServiceStatusProcess.dwWin32ExitCode);
		printf("ServiceSpecificExitCode  : %d \n", pServiceInfo[i].ServiceStatusProcess.dwServiceSpecificExitCode);
		printf("CheckPoint \t\t : %d \n", pServiceInfo[i].ServiceStatusProcess.dwCheckPoint);
		printf("WaitHint \t\t : %d \n", pServiceInfo[i].ServiceStatusProcess.dwWaitHint);
		printf("Process Id \t\t : %d \n", pServiceInfo[i].ServiceStatusProcess.dwProcessId);
		printf("ServiceFlags \t\t : %d \n", pServiceInfo[i].ServiceStatusProcess.dwServiceFlags);*/
	}
}

//点击事件
void myservice::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int ccol = pNMItemActivate->iSubItem;
	int crow = pNMItemActivate->iItem;
	if (ccol == 1) {
		/*typedef struct _QUERY_SERVICE_CONFIG {
			DWORD  dwServiceType;
			DWORD  dwStartType;
			DWORD  dwErrorControl;
			LPTSTR lpBinaryPathName;
			LPTSTR lpLoadOrderGroup;
			DWORD  dwTagId;
			LPTSTR lpDependencies;
			LPTSTR lpServiceStartName;
			LPTSTR lpDisplayName;
		} QUERY_SERVICE_CONFIG, *LPQUERY_SERVICE_CONFIG;*/
		this->ShowWindow(SW_HIDE);
		DWORD dwSize = 0;                // 传入的缓冲大小
		CString str = mylistctrl.GetItemText(crow, ccol);
		hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE | SC_MANAGER_CONNECT);
		//打开服务
		SC_HANDLE hService = OpenService(hSCM, str, SERVICE_ALL_ACCESS);
		if (hService == NULL) {
			MessageBox(_T("权限不够"), _T("服务信息"), IDOK);
			this->ShowWindow(SW_SHOW);
			return;
		}
		//第一次调用获取需要的缓冲区大小
		QueryServiceConfig(hService, NULL, 0, &dwSize);
		//分配内存
		char* pconstruct =new char[dwSize];
		//信息
		QUERY_SERVICE_CONFIG* myQUERY_SERVICE_CONFIG = (QUERY_SERVICE_CONFIG*)pconstruct;
		//第二次获取
		QueryServiceConfig(hService, myQUERY_SERVICE_CONFIG, dwSize, &dwSize);
		CString str2;
		/*DWORD  dwServiceType;
		DWORD  dwStartType;
		DWORD  dwErrorControl;
		LPTSTR lpBinaryPathName;
		LPTSTR lpLoadOrderGroup;
		DWORD  dwTagId;
		LPTSTR lpDependencies;
		LPTSTR lpServiceStartName;
		LPTSTR lpDisplayName;*/
		str2.Format(L"dwServiceType: %d \n dwStartType: %d \n dwErrorControl: %d \n lpBinaryPathName: %s \n lpLoadOrderGroup: %s\n dwTagId: %d\n lpDependencies: %s \n lpServiceStartName: %s\n lpDisplayName:%s \n",
			myQUERY_SERVICE_CONFIG->dwServiceType, myQUERY_SERVICE_CONFIG->dwStartType,
			myQUERY_SERVICE_CONFIG->dwErrorControl, myQUERY_SERVICE_CONFIG->lpBinaryPathName,
			myQUERY_SERVICE_CONFIG->lpLoadOrderGroup, myQUERY_SERVICE_CONFIG->dwTagId,
			myQUERY_SERVICE_CONFIG->lpDependencies, myQUERY_SERVICE_CONFIG->lpServiceStartName,
			myQUERY_SERVICE_CONFIG->lpDisplayName);

		MessageBox(str2, _T("服务信息"), IDOK);
		free(pconstruct);
		//下面的代码用于检查服务是否被停止,如果停止则打开此服务     
		SERVICE_STATUS ssStatus;
		SC_HANDLE stService;
		//获取
		if ((QueryServiceStatus(hService, &ssStatus)) == 0)
		{
			AfxMessageBox(_T("无法确定服务状态"), MB_ICONINFORMATION);
		}
		//如果stService打开   如果停止或正在停止则打开此服务  
		if (ssStatus.dwCurrentState == SERVICE_STOP_PENDING ||ssStatus.dwCurrentState == SERVICE_STOPPED)
		{
			AfxMessageBox(_T("服务已启动"),MB_ICONINFORMATION);
			stService = OpenService(hSCM, str, SERVICE_START | GENERIC_EXECUTE);
			StartService(stService, 0, NULL);
			CloseServiceHandle(stService);
		}
		else if (ssStatus.dwCurrentState == SERVICE_RUNNING|| ssStatus.dwCurrentState == SERVICE_START_PENDING) //如果是正在运行或启动状态就停止  
		{     
		  AfxMessageBox(_T("服务已停止"),MB_ICONINFORMATION);     
		  stService=OpenService(hSCM, str,SERVICE_STOP|GENERIC_EXECUTE);
		  ControlService(stService,SERVICE_CONTROL_STOP,&ssStatus);     
		  CloseServiceHandle(stService);     
		}    
		this->ShowWindow(SW_SHOW);
	}
	*pResult = 0;
	
}
