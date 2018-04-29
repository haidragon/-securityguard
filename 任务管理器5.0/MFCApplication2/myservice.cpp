// myservice.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "myservice.h"
#include "afxdialogex.h"

// myservice �Ի���

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


// myservice ��Ϣ�������


void myservice::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
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
	char *pBuf = NULL;                  // ������ָ��
	DWORD dwBufSize = 0;                // ����Ļ��峤��
	DWORD dwBufNeed = 0;                // ��Ҫ�Ļ��峤��
	DWORD dwNumberOfService = 0;        // ���صķ������
	ENUM_SERVICE_STATUS_PROCESS *pServiceInfo = NULL;   // ������Ϣ

														// ������һ����������ƹ����������ӣ�����ָ�������ݿ�
	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE | SC_MANAGER_CONNECT);
	if (NULL == hSCM)
	{
		printf("OpenSCManager error.\n");
		return ;
	}

	// ��ȡ��Ҫ�Ļ�������С  dwBufSize
	EnumServicesStatusEx(hSCM, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,
		NULL, dwBufSize, &dwBufNeed, &dwNumberOfService, NULL, NULL);

	// �����ô��1��������Ϣ�ĳ���
	dwBufSize = dwBufNeed + sizeof(ENUM_SERVICE_STATUS_PROCESS);
	pBuf = (char *)malloc(dwBufSize);
	if (NULL == pBuf)
	{
		printf("malloc error.\n");
		return;
	}
	memset(pBuf, 0, dwBufSize);

	// ��ȡ������Ϣ
	bRet = EnumServicesStatusEx(hSCM, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,
		(LPBYTE)pBuf, dwBufSize, &dwBufNeed, &dwNumberOfService, NULL, NULL);
	if (bRet == FALSE)
	{
		printf("EnumServicesStatusEx error.\n");
		::CloseServiceHandle(hSCM);
		free(pBuf);
		return ;
	}
	// �رմ򿪵ķ�����
	bRet = ::CloseServiceHandle(hSCM);
	if (bRet == FALSE)
	{
		printf("CloseServiceHandle error.\n");
	}
	printf("Service Num:%d\n", dwNumberOfService);

	pServiceInfo = (LPENUM_SERVICE_STATUS_PROCESS)pBuf;
	// ��ӡȡ�õķ�����Ϣ
	for (unsigned int i = 0; i < dwNumberOfService; i++)
	{

		this->mylistctrl.InsertItem(i, NULL);
		//�������
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

//����¼�
void myservice::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		DWORD dwSize = 0;                // ����Ļ����С
		CString str = mylistctrl.GetItemText(crow, ccol);
		hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE | SC_MANAGER_CONNECT);
		//�򿪷���
		SC_HANDLE hService = OpenService(hSCM, str, SERVICE_ALL_ACCESS);
		if (hService == NULL) {
			MessageBox(_T("Ȩ�޲���"), _T("������Ϣ"), IDOK);
			this->ShowWindow(SW_SHOW);
			return;
		}
		//��һ�ε��û�ȡ��Ҫ�Ļ�������С
		QueryServiceConfig(hService, NULL, 0, &dwSize);
		//�����ڴ�
		char* pconstruct =new char[dwSize];
		//��Ϣ
		QUERY_SERVICE_CONFIG* myQUERY_SERVICE_CONFIG = (QUERY_SERVICE_CONFIG*)pconstruct;
		//�ڶ��λ�ȡ
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

		MessageBox(str2, _T("������Ϣ"), IDOK);
		free(pconstruct);
		//����Ĵ������ڼ������Ƿ�ֹͣ,���ֹͣ��򿪴˷���     
		SERVICE_STATUS ssStatus;
		SC_HANDLE stService;
		//��ȡ
		if ((QueryServiceStatus(hService, &ssStatus)) == 0)
		{
			AfxMessageBox(_T("�޷�ȷ������״̬"), MB_ICONINFORMATION);
		}
		//���stService��   ���ֹͣ������ֹͣ��򿪴˷���  
		if (ssStatus.dwCurrentState == SERVICE_STOP_PENDING ||ssStatus.dwCurrentState == SERVICE_STOPPED)
		{
			AfxMessageBox(_T("����������"),MB_ICONINFORMATION);
			stService = OpenService(hSCM, str, SERVICE_START | GENERIC_EXECUTE);
			StartService(stService, 0, NULL);
			CloseServiceHandle(stService);
		}
		else if (ssStatus.dwCurrentState == SERVICE_RUNNING|| ssStatus.dwCurrentState == SERVICE_START_PENDING) //������������л�����״̬��ֹͣ  
		{     
		  AfxMessageBox(_T("������ֹͣ"),MB_ICONINFORMATION);     
		  stService=OpenService(hSCM, str,SERVICE_STOP|GENERIC_EXECUTE);
		  ControlService(stService,SERVICE_CONTROL_STOP,&ssStatus);     
		  CloseServiceHandle(stService);     
		}    
		this->ShowWindow(SW_SHOW);
	}
	*pResult = 0;
	
}
