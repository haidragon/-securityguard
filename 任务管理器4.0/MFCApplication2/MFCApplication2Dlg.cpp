
// MFCApplication2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#include<TlHelp32.h>
#include<Psapi.h>
#include<Windows.h>
#include <shellapi.h>
#include<string>
#include<atlconv.h>
#include<afxpriv.h>
#include<iostream>
#include<fstream>
#include <CString>
#include<ShlObj.h>
#include<Commctrl.h>
using namespace std;
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// �������û�г����ڰ�ť, ���Լ������º�.
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//CString CAboutDlg::ctrpath = L"";

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication2Dlg �Ի���



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
	, cpustr(_T(""))
	, ctrpath(_T(""))
	, filestr(_T(""))
	//, mycleactr(_T(""))
	, myclearctring(_T(""))
	, mypidctr(_T(""))
	, mypidheap(_T(""))
	, killpid(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, cclistctrl);
	//DDX_Text(pDX, IDC_EDIT1, myctr);
	DDX_Text(pDX, IDC_EDIT1, cpustr);
	DDX_Control(pDX, IDC_EDIT1, myCpuEdit);
	DDX_Text(pDX, IDC_EDIT4, ctrpath);
	DDX_Text(pDX, IDC_EDIT3, filestr);
	DDX_Control(pDX, IDC_EDIT3, myfileCEdit);
	DDX_Control(pDX, IDC_EDIT2, myclear);
	//DDX_Text(pDX, IDC_EDIT2, mycleactr);
	DDX_Text(pDX, IDC_EDIT2, myclearctring);
	DDX_Text(pDX, IDC_EDIT5, mypidctr);
	DDX_Text(pDX, IDC_EDIT6, mypidheap);
	DDX_Control(pDX, IDC_BUTTON6, chawenjian);
	DDX_Text(pDX, IDC_EDIT7, killpid);
	DDX_Control(pDX, IDC_BUTTON29, btnroot);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMFCApplication2Dlg::OnNMClickList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CMFCApplication2Dlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication2Dlg::OnBnClickedButton2)
	//ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication2Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication2Dlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication2Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication2Dlg::OnBnClickedButton4)
	//ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication2Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication2Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication2Dlg::OnBnClickedButton7)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCApplication2Dlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CMFCApplication2Dlg::OnEnChangeEdit4)
	//ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication2Dlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication2Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication2Dlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT5, &CMFCApplication2Dlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CMFCApplication2Dlg::OnEnChangeEdit6)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCApplication2Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCApplication2Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMFCApplication2Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CMFCApplication2Dlg::OnBnClickedButton11)
	ON_WM_HOTKEY()

	ON_BN_CLICKED(IDC_BUTTON13, &CMFCApplication2Dlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CMFCApplication2Dlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CMFCApplication2Dlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON17, &CMFCApplication2Dlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CMFCApplication2Dlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CMFCApplication2Dlg::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &CMFCApplication2Dlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, &CMFCApplication2Dlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON16, &CMFCApplication2Dlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON22, &CMFCApplication2Dlg::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON23, &CMFCApplication2Dlg::OnBnClickedButton23)
	ON_EN_CHANGE(IDC_EDIT7, &CMFCApplication2Dlg::OnEnChangeEdit7)
	ON_BN_CLICKED(IDC_BUTTON24, &CMFCApplication2Dlg::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON26, &CMFCApplication2Dlg::OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON25, &CMFCApplication2Dlg::OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON27, &CMFCApplication2Dlg::OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON28, &CMFCApplication2Dlg::OnBnClickedButton28)
	ON_BN_CLICKED(IDC_BUTTON29, &CMFCApplication2Dlg::OnBnClickedButton29)
	ON_BN_CLICKED(IDC_BUTTON30, &CMFCApplication2Dlg::OnBnClickedButton30)
END_MESSAGE_MAP()


// CMFCApplication2Dlg ��Ϣ�������

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//MessageBox(L"������̺��г���ǰ���̵�����ģ��!!!!!");

	//root
	// �жϵ�ǰ�Ƿ����Թ���Ա������еĽ���.
	if (!IsAdmin(GetCurrentProcess())) {

		// �������, ��һ����ť����Ϊ�����Ʊ�־�İ�ť.
		Button_SetElevationRequiredState(this->btnroot, true);
	}
	else {

		// ����Ѿ��Թ���Ա�������,�򽫰�ť����
		::ShowWindow(this->btnroot, SW_HIDE);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	myCpuEdit.SetReadOnly(TRUE);
	//myfileCEdit.SetReadOnly(TRUE);
	myfileCEdit.DragAcceptFiles(TRUE);
	HWND myallen = (HWND)::GetModuleHandle(NULL);
	::RegisterHotKey(this->m_hWnd, 0x1234, MOD_CONTROL, 'G');
	EnumProcess();

	//��ip
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication2Dlg::OnPaint()
{
	//�鿴�ļ��İ�Ť������
	//this->chawenjian.EnableWindow(0);
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


bool CMFCApplication2Dlg::EnumProcess() {
	// 1. �ȴ�������
	HANDLE hTool32 = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (INVALID_HANDLE_VALUE == hTool32)
	{
		printf("����error!\n");
		return false;
	}
	// 2. ��ʼ��������
	PROCESSENTRY32W psi = { sizeof(PROCESSENTRY32W) };
	BOOL bRet = Process32FirstW(hTool32, &psi);
	if (!bRet)
	{
		//printf("Process32FirstW error!\n");
		return false;
	}
	//printf("PID    EXE:\n");
	int i = 0;
	cclistctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	cclistctrl.GetClientRect(rc);
	nwidth = rc.Width();
	cclistctrl.InsertColumn(0, L"����", 0, nwidth / 6);
	cclistctrl.InsertColumn(1, L"dwSize", 1, nwidth / 8);
	cclistctrl.InsertColumn(2, L"cntUsage", 2, nwidth / 8);
	cclistctrl.InsertColumn(3, L"PID", 3, nwidth / 8);
	cclistctrl.InsertColumn(4, L"th32DefaultHeapID", 4, nwidth / 8);
	cclistctrl.InsertColumn(5, L"th32ModuleID", 5, nwidth / 8);
	cclistctrl.InsertColumn(6, L"cntThreads", 6, nwidth / 8);
	cclistctrl.InsertColumn(7, L"th32ParentProcessID", 7, nwidth / 8);
	cclistctrl.InsertColumn(8, L"pcPriClassBase", 8, nwidth / 8);
	cclistctrl.InsertColumn(9, L"dwFlags", 9, nwidth / 8);


	do
	{


		//typedef struct tagPROCESSENTRY32 {
		//	DWORD     dwSize;
		//	DWORD     cntUsage;
		//	DWORD     th32ProcessID;
		//	ULONG_PTR th32DefaultHeapID;
		//	DWORD     th32ModuleID;
		//	DWORD     cntThreads;
		//	DWORD     th32ParentProcessID;
		//	LONG      pcPriClassBase;
		//	DWORD     dwFlags;
		//	TCHAR     szExeFile[MAX_PATH];
		//} PROCESSENTRY32, *PPROCESSENTRY32;
		//printf("%4d   %S\n", psi.th32ProcessID, psi.szExeFile);
		//	TCHAR     szExeFile[MAX_PATH];
		cclistctrl.InsertItem(i, psi.szExeFile);
		//	DWORD     dwSize;
		CString strdwSize;
		strdwSize.Format(L"%4d", psi.dwSize);
		cclistctrl.SetItemText(i, 1, strdwSize);
		//	DWORD     cntUsage;
		CString strcntUsage;
		strcntUsage.Format(L"%4d", psi.cntUsage);
		cclistctrl.SetItemText(i, 2, strcntUsage);
		//	DWORD     th32ProcessID;
		CString strcth32ProcessID;
		strcth32ProcessID.Format(L"%4d", psi.th32ProcessID);
		cclistctrl.SetItemText(i, 3, strcth32ProcessID);
		//	ULONG_PTR th32DefaultHeapID;
		CString strcth32DefaultHeapID;
		strcth32DefaultHeapID.Format(L"%4d", psi.th32DefaultHeapID);
		cclistctrl.SetItemText(i, 4, strcth32DefaultHeapID);
		//	ULONG_PTR th32ModuleID;
		CString strth32ModuleID;
		strth32ModuleID.Format(L"%4d", psi.th32ModuleID);
		cclistctrl.SetItemText(i, 5, strth32ModuleID);
		//	DWORD     cntThreads;
		CString cntThreads;
		cntThreads.Format(L"%4d", psi.cntThreads);
		cclistctrl.SetItemText(i, 6, cntThreads);
		//	DWORD     th32ParentProcessID;
		CString th32ParentProcessID;
		th32ParentProcessID.Format(L"%4d", psi.th32ParentProcessID);
		cclistctrl.SetItemText(i, 7, th32ParentProcessID);
		//	LONG      pcPriClassBase;
		CString pcPriClassBase;
		pcPriClassBase.Format(L"%4d", psi.pcPriClassBase);
		cclistctrl.SetItemText(i, 8, pcPriClassBase);
		//	DWORD     dwFlags;
		CString strcdwFlags;
		strcdwFlags.Format(L"%4d", psi.dwFlags);
		cclistctrl.SetItemText(i, 9, strcdwFlags);

		++i;
	} while (Process32NextW(hTool32, &psi));
	return true;
}
//���pid����ģ��
void CMFCApplication2Dlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ccol = pNMItemActivate->iSubItem;
	int crow = pNMItemActivate->iItem;
	if (ccol == 3) {
		CString str = cclistctrl.GetItemText(crow, ccol);
		this->ShowWindow(SW_HIDE);
		//modo::pid = _ttoi(str);
		pid = _ttoi(str);
		ccmymodo1 = new ccmymodo();
		ccmymodo1->DoModal();
		delete ccmymodo1;
		ccmymodo1 = nullptr;
		this->ShowWindow(SW_SHOW);
	}

	*pResult = 0;
}


void CMFCApplication2Dlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


//��ȡϵͳ�����߳�
void CMFCApplication2Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);
	ccmythreadmod = new threadmod();
	ccmythreadmod->DoModal();
	delete ccmythreadmod;
	ccmythreadmod = nullptr;
	this->ShowWindow(SW_SHOW);

}


void CMFCApplication2Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (mypidheap != "") {
		this->ShowWindow(SW_HIDE);
		ccmyduimodo = new myduimodo();
		ccmyduimodo->pid = _ttoi(mypidheap);
		ccmyduimodo->DoModal();
		delete ccmyduimodo;
		ccmyduimodo = nullptr;
		this->ShowWindow(SW_SHOW);
	}
	else {
		MessageBox(L"����pid!");
	}
	//	MessageBox(myctr);
}



void CMFCApplication2Dlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(L"allen");
	//mywinmodo* ccmywinmodo;
	this->ShowWindow(SW_HIDE);
	ccmywinmodo = new mywinmodo();
	ccmywinmodo->DoModal();
	delete ccmywinmodo;
	ccmyduimodo = nullptr;
	this->ShowWindow(SW_SHOW);
}


void CMFCApplication2Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*UpdateData(FALSE);
	cpustr += "\n";*/
	//UpdateData(TRUE);
}

//�鿴cpu��Ϣ
void CMFCApplication2Dlg::OnBnClickedButton4()
{
	this->myCpuEdit.Clear();
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	CString str;
	str.Format(L"����������:%d \r\n", systemInfo.dwActiveProcessorMask);
	cpustr += str;
	str.Format(L"����������:%d \r\n", systemInfo.dwNumberOfProcessors);
	cpustr += str;
	str.Format(L"��������ҳ��С:%d\r\n", systemInfo.dwPageSize);
	cpustr += str;
	str.Format(L"����������:%d\r\n", systemInfo.dwProcessorType);
	cpustr += str;
	str.Format(L"���Ѱַ��Ԫ: %d\r\n", systemInfo.lpMaximumApplicationAddress);
	cpustr += str;
	str.Format(L"��СѰַ��Ԫ: %d\r\n", systemInfo.lpMinimumApplicationAddress);
	cpustr += str;
	str.Format(L"�������ȼ�: %d\r\n", systemInfo.wProcessorLevel);
	cpustr += str;
	str.Format(L"�������汾: %d\r\n", systemInfo.wProcessorRevision);
	MEMORYSTATUS stat;
	GlobalMemoryStatus(&stat);
	str.Format(L"�ڴ��ʹ����: %d\r\n", stat.dwMemoryLoad);
	cpustr += str;
	double neic = stat.dwTotalPhys / 1024.0 / 1024.0 / 1024.0;

	str.Format(L"�ܵ������ڴ��С: %f G\r\n", neic);
	cpustr += str;
	str.Format(L"���õ������ڴ��С: %f G\r\n", stat.dwAvailPhys / 1024.0 / 1024.0 / 1024.0);
	cpustr += str;
	str.Format(L"�����ַ�ռ�: %f G\r\n", stat.dwTotalVirtual / 1024.0 / 1024.0 / 1024.0);
	cpustr += str;
	str.Format(L"���������ַ�ռ�: %f G\r\n", stat.dwAvailVirtual / 1024.0 / 1024.0 / 1024.0);

	cpustr += str;
	CWnd* pWnd = GetDlgItem(IDC_EDIT1);
	pWnd->SetWindowText(cpustr);
	cpustr = "";


	//dwLength ����MEMORYSTATUS�ṹ�Ĵ�С���ڵ�GlobalMemoryStatus����ǰ��sizeof()������ã��������������ṹ�İ汾��
	//	dwMemoryLoad �� ����һ������0��100֮���ֵ������ָʾ��ǰϵͳ�ڴ��ʹ���ʡ�
	//	dwTotalPhys ���������ܵ������ڴ��С�����ֽ�(byte)Ϊ��λ��
	//	dwAvailPhys �������ؿ��õ������ڴ��С�����ֽ�(byte)Ϊ��λ��
	//	dwTotalPageFile  ��ʾ���Դ���ҳ���ļ��е��ֽ�����ע�������ֵ������ʾ��ҳ���ļ��ڴ����ϵ���ʵ�����С��
	//	dwAvailPageFile  ���ؿ��õ�ҳ���ļ���С�����ֽ�(byte)Ϊ��λ��
	//	dwTotalVirtual �����ص��ý��̵��û�ģʽ���ֵ�ȫ�����������ַ�ռ䣬���ֽ�(byte)Ϊ��λ��
	//	dwAvailVirtual �����ص��ý��̵��û�ģʽ���ֵ�ʵ�����ɿ��õ������ַ�ռ䣬���ֽ�(byte)Ϊ��λ��
/*	typedef struct _MEMORYSTATUS {
		DWORD dwLength;
		DWORD dwMemoryLoad;
		SIZE_T dwTotalPhys;
		SIZE_T dwAvailPhys;
		SIZE_T dwTotalPageFile;
		SIZE_T dwAvailPageFile;
		SIZE_T dwTotalVirtual;
		SIZE_T dwAvailVirtual;
	} MEMORYSTATUS, *LPMEMORYSTATUS;*/

	/*typedef struct _SYSTEM_INFO {
		union {
			DWORD  dwOemId;
			struct {
				WORD wProcessorArchitecture;
				WORD wReserved;
			};
		};
		DWORD     dwPageSize;
		LPVOID    lpMinimumApplicationAddress;
		LPVOID    lpMaximumApplicationAddress;
		DWORD_PTR dwActiveProcessorMask;
		DWORD     dwNumberOfProcessors;
		DWORD     dwProcessorType;
		DWORD     dwAllocationGranularity;
		WORD      wProcessorLevel;
		WORD      wProcessorRevision;
	} SYSTEM_INFO;*/

	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//cout << setw(20) << "����������: " << systemInfo.dwActiveProcessorMask << endl
	//	<< setw(20) << "����������: " << systemInfo.dwNumberOfProcessors << endl
	//	<< setw(20) << "��������ҳ��С: " << systemInfo.dwPageSize << endl
	//	<< setw(20) << "����������: " << systemInfo.dwProcessorType << endl
	//	<< setw(20) << "���Ѱַ��Ԫ: " << systemInfo.lpMaximumApplicationAddress << endl
	//	<< setw(20) << "��СѰַ��Ԫ: " << systemInfo.lpMinimumApplicationAddress << endl
	//	<< setw(20) << "�������ȼ�: " << systemInfo.wProcessorLevel << endl
	//	<< setw(20) << "�������汾: " << systemInfo.wProcessorRevision << endl;
	//GetSystemInfo
}


//�鿴�ļ���Ϣ
void CMFCApplication2Dlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//typedef struct _WIN32_FILE_ATTRIBUTE_DATA {
	//	DWORD    dwFileAttributes;
	   //����ʱ��
	//	FILETIME ftCreationTime;
		//������ʱ��
	//	FILETIME ftLastAccessTime;
		//����޸�ʱ��
	//	FILETIME ftLastWriteTime;
	//	DWORD    nFileSizeHigh;
	//	DWORD    nFileSizeLow;
	//} WIN32_FILE_ATTRIBUTE_DATA, *LPWIN32_FILE_ATTRIBUTE_DATA;
	if (this->ctrpath == _T("")) {
		MessageBox(L"������·����");
		return;
	}
	SYSTEMTIME time;
	WIN32_FILE_ATTRIBUTE_DATA lpinf;
	CString TestDate;
	if (GetFileAttributesEx(ctrpath, GetFileExInfoStandard, &lpinf) == 0) {
		MessageBox(L"·�����ԣ�");
		return;
	}
	//����ʱ��
	FileTimeToSystemTime(&lpinf.ftCreationTime, &time);
	TestDate.Format(_T("����ʱ�䣺%d-%d-%d\r\n"), time.wYear, time.wMonth, time.wDay);
	filestr += TestDate;
	//����޸�ʱ��
	FileTimeToSystemTime(&lpinf.ftLastWriteTime, &time);
	TestDate.Format(_T("����޸�ʱ�䣺%d-%d-%d\r\n"), time.wYear, time.wMonth, time.wDay);
	filestr += TestDate;
	//������ʱ��
	FileTimeToSystemTime(&lpinf.ftLastAccessTime, &time);
	TestDate.Format(_T("������ʱ�䣺%d-%d-%d\r\n"), time.wYear, time.wMonth, time.wDay);
	filestr += TestDate;


	double size;
	CFileStatus fileStatus;

	if (CFile::GetStatus(ctrpath, fileStatus))
	{
		size = fileStatus.m_size;
	}
	CString str;
	str.Format(L"��С��%f M\r\n", size / 1024.0 / 1024.0);
	filestr += str;
	str.Format(L"·����%s\r\n", fileStatus.m_szFullName);
	filestr += str;
	//CString strSource;//����CString
	//char* charSource; //����char*
	//��1��
	//	charSource = (char*)strSource.GetBuffer(0);
	//��2��
	//	charSource = (char*)strSource.GetBuffer(strSource.GetLength());
	//��3��
	//	charSource = (char*)(LPCTSTR)strSource;
	//CString strmd5 = ctrpath;
	//CString str1 = "123";
	//char *t1 = str1.GetBuffer(str1.GetLength());
	//str1.ReleaseBuffer();
	//char* charSource = (char*)(LPCTSTR)strmd5;
	CStringA strPathA = CW2A(ctrpath.GetBuffer(), CP_THREAD_ACP);
	char*temp=strPathA.GetBuffer();
	char*charSource2 = md5FileValue(temp);
	//char* charSource2 = md5FileValue(charSource);
	str.Format(_T("Md5ֵ��%S\r\n"), charSource2);
	filestr += str;
	CWnd* pWnd = GetDlgItem(IDC_EDIT3);
	pWnd->SetWindowText(filestr);
	filestr = "";

	//CFileStatus��һ���ṹ�壬�˽ṹ��洢���ļ���״̬��Ϣ��
	//	����������������ṹ���Ա��
	//	CTime m_ctime   The date and time the file was created.
	//	��ʾ�ļ��Ĵ���ʱ��
	//	CTime m_mtime   The date and time the file was last modified.
	//	��ʾ�ļ����޸�ʱ��
	//	CTime m_atime   The date and time the file was last accessed for reading.
	//	��ʾ�ļ���������ʱ��
	//	ULONGLONG m_size   The logical size of the file in bytes, as reported by the DIR command.
	//	��ʾ�ļ����߼���С
	//	BYTE m_attribute   The attribute byte of the file.
	//	��ʾ�ļ���ϵͳ����
	//	char m_szFullName[_MAX_PATH]   The absolute filename in the Windows character set.
	//	��ʾ�ļ��ľ���·��
}

//ѡ���ļ�
void CMFCApplication2Dlg::OnBnClickedButton7()
{
	//IDC_EDIT4, ctrpath);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString gReadFilePathName;
	CFileDialog fileDlg(true, _T("c++"), _T("*.cpp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("c Files (*.c)|*.cpp|zip File(*.zip)|*.rar|All File (*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //�����Ի���  
	{
		gReadFilePathName = fileDlg.GetPathName();//�õ��������ļ�����Ŀ¼����չ��  
		GetDlgItem(IDC_EDIT4)->SetWindowText(gReadFilePathName);//��·����ʾ  
		ctrpath = gReadFilePathName;
		CStringA strPathA = CW2A(ctrpath.GetBuffer(), CP_THREAD_ACP);
		char*temp = strPathA.GetBuffer();
		char*charSource2 = md5FileValue(temp);
		//����md5ֵ
		this->md5 = charSource2;
	}
	//���ò鿴�ļ��İ�Ť����
	this->chawenjian.EnableWindow(1);
	//MessageBox(gReadFilePathName);
}


void CMFCApplication2Dlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication2Dlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);

}


void CMFCApplication2Dlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

//��������
void CMFCApplication2Dlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (mypidctr != "") {
		DWORD pid = _ttoi(mypidctr);
		//KillProcess(pid);
		if (KillProcess(pid)) {
			MessageBox(L"�ɹ���");
		}
		else {
			MessageBox(L"ʧ�ܣ�");
		}

	}
	else {
		MessageBox(L"������pid");
	}

}


bool CMFCApplication2Dlg::KillProcess(DWORD pid)
{
	// When the all operation fail this function terminate the "winlogon" Process for force exit the system.
	HANDLE hYourTargetProcess = OpenProcess(PROCESS_QUERY_INFORMATION |   // Required by Alpha
		PROCESS_CREATE_THREAD |   // For CreateRemoteThread
		PROCESS_VM_OPERATION |   // For VirtualAllocEx/VirtualFreeEx
		PROCESS_TERMINATE |
		PROCESS_VM_WRITE,             // For WriteProcessMemory
		FALSE, pid);

	if (hYourTargetProcess == NULL)
	{
		return FALSE;
	}

	if (TerminateProcess(hYourTargetProcess, 0) != 0)
	{
		::Sleep(1000);
		return TRUE;
	}
	else
		return FALSE;
}

void CMFCApplication2Dlg::OnEnChangeEdit5()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
}

//heap
void CMFCApplication2Dlg::OnEnChangeEdit6()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}

//�ػ�
void CMFCApplication2Dlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 0);
}

//����
void CMFCApplication2Dlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ExitWindows(EWX_REBOOT | EWX_FORCE, 0);
}

//ע��
void CMFCApplication2Dlg::OnBnClickedButton10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ExitWindows(EWX_LOGOFF | EWX_FORCE, 0);
}

//����
void CMFCApplication2Dlg::OnBnClickedButton11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//SetSuspendState(TRUE, FALSE, FALSE);
}


void CMFCApplication2Dlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

//::RegisterHotKey(myallen, 0x1234, MOD_CONTROL, 'G');
//::RegisterHotKey(myallen, 0x1235, MOD_CONTROL, 'J');

BOOL CMFCApplication2Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if ((pMsg->message == WM_HOTKEY) && (pMsg->wParam == 0x1234))
	{
		//	HWND myallen = (HWND)::GetModuleHandle(NULL);
		if (::IsWindowVisible(m_hWnd) == TRUE) {
			ShowWindow(SW_HIDE);
		}
		else {
			ShowWindow(SW_SHOW);
		}



	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

//�ڴ��Ż�
void CMFCApplication2Dlg::OnBnClickedButton13()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ȡ��ǰϵͳǰ�����ڴ�������ڴ��ʹ��

	//BOOL WINAPI GlobalMemoryStatusEx(
	//	_Inout_ LPMEMORYSTATUSEX lpBuffer
	//);

	//typedef struct _MEMORYSTATUSEX {
	//	DWORD     dwLength;
	//	DWORD     dwMemoryLoad;
	//	DWORDLONG ullTotalPhys;
	//	DWORDLONG ullAvailPhys;
	//	DWORDLONG ullTotalPageFile;
	//	DWORDLONG ullAvailPageFile;
	//	DWORDLONG ullTotalVirtual;
	//	DWORDLONG ullAvailVirtual;
	//	DWORDLONG ullAvailExtendedVirtual;
	//} MEMORYSTATUSEX, *LPMEMORYSTATUSEX;
	//��ȡ��ǰ���ڴ�״̬
	MEMORYSTATUSEX  myMEMORYSTATUSEX = { 0 };
	myMEMORYSTATUSEX.dwLength = sizeof(myMEMORYSTATUSEX);
	GlobalMemoryStatusEx(&myMEMORYSTATUSEX);
	DWORDLONG preUesrMem = myMEMORYSTATUSEX.ullTotalPhys - myMEMORYSTATUSEX.ullAvailPhys;
	//�����ڴ�
	DWORD dwPIDlist[1000] = { 0 };
	DWORD bufSize = sizeof(dwPIDlist);
	DWORD dwNeedSize = 0;
	EnumProcesses(dwPIDlist, bufSize, &dwNeedSize);
	for (DWORD i = 0;i < dwNeedSize / sizeof(DWORD);i++) {
		HANDLE hProcess = OpenProcess(PROCESS_SET_QUOTA, false, dwPIDlist[i]);
		//����ʹ��
		SetProcessWorkingSetSize(hProcess, -1, -1);
	}
	GlobalMemoryStatusEx(&myMEMORYSTATUSEX);
	DWORDLONG afterUesrMem = myMEMORYSTATUSEX.ullTotalPhys - myMEMORYSTATUSEX.ullAvailPhys;
	CString mystr;
	mystr.Format(_T("�Ż�ǰ%d---�Ż���%d"), preUesrMem, afterUesrMem);
	MessageBox(mystr, _T("�Ż�ǰ��Ա�"), IDOK);
}

//ϵͳ�汾��Ϣ
void CMFCApplication2Dlg::OnBnClickedButton14()
{
	/*typedef struct _OSVERSIONINFOEX {
		DWORD dwOSVersionInfoSize;
		DWORD dwMajorVersion;
		DWORD dwMinorVersion;
		DWORD dwBuildNumber;
		DWORD dwPlatformId;
		TCHAR szCSDVersion[128];
		WORD  wServicePackMajor;
		WORD  wServicePackMinor;
		WORD  wSuiteMask;
		BYTE  wProductType;
		BYTE  wReserved;
	} OSVERSIONINFOEX, *POSVERSIONINFOEX, *LPOSVERSIONINFOEX;*/
	OSVERSIONINFOEX osvi;
	BOOL bIsWindowsXPorLater;

	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	GetVersionEx((OSVERSIONINFO*)&osvi);
	bIsWindowsXPorLater = ((osvi.dwMajorVersion > 5) || ((osvi.dwMajorVersion == 5) && (osvi.dwMinorVersion >= 1)));
	if (bIsWindowsXPorLater)
		printf("The system meets the requirements.\n");
	else printf("The system does not meet the requirements.\n");
	CString mystr;
	mystr.Format(_T(" ϵͳ���汾��%d\n ϵͳ�ΰ汾��%d\n ϵͳ�����ţ�%d\n ϵͳ֧�ֵ�ƽ̨��%d\n ϵͳ�����������ƣ�%s\n ϵͳ�����������汾��%d\n ϵͳ�������Ĵΰ汾��%d\n ��ʶϵͳ�ϵĳ����飺%d\n ��ʶϵͳ���ͣ�%d\n ����δʹ�ã�%d\n"),
		osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber,
		osvi.dwPlatformId, osvi.szCSDVersion, osvi.wServicePackMajor,
		osvi.wServicePackMinor, osvi.wSuiteMask, osvi.wProductType, osvi.wReserved);
	MessageBox(mystr, _T("ϵͳ�汾��Ϣ"), IDOK);
}

//�������վ
void CMFCApplication2Dlg::OnBnClickedButton15()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ��SHQUERYRBINFO�ṹ

	SHQUERYRBINFO RecycleBinInformation;
	ZeroMemory(&RecycleBinInformation, sizeof(RecycleBinInformation));
	RecycleBinInformation.cbSize = sizeof(RecycleBinInformation);
	//��ѯ����վ��Ϣ
	if (SHQueryRecycleBin(NULL, &RecycleBinInformation) == S_OK)
		//SHQueryRecycleBin��һ����ΪҪ��ѯ����վ���̷������ļ���,���ļ���
		//һ�����Ŀ¼��ָͬ��Ļ���վҲ��һ����
		//ΪNULL��ָ�����л���վ,�������SHEmptyRecycleBin�ڶ�������ͬ
	{
		CString mystr;
		mystr.Format(_T("����վ��С%ld---����վ�ļ�����%ld"), RecycleBinInformation.i64Size, RecycleBinInformation.i64NumItems);
		MessageBox(mystr, _T("����վ��Ϣ"), IDOK);
	}
	else
	{
		CString mystr;
		MessageBox(mystr, _T("����վ��Ϣ"), IDOK);
	}
	//��ջ���վ
	if (SHEmptyRecycleBin(NULL, NULL, /*SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | */SHERB_NOSOUND) == S_OK)
		//SHEmptyRecycleBin�����������Ҫ��ʾȷ��ɾ���Ի��������֮��Ķ����ÿռȿ�
	{
		CString mystr = _T("�����ɹ���");
		MessageBox(mystr, _T("����վ��Ϣ"), IDOK);
	}
	else
	{
		CString mystr = _T("����ʧ�ܣ�������û��������");
		MessageBox(mystr, _T("����վ��Ϣ"), IDOK);
	}
}

//�������
void CMFCApplication2Dlg::OnBnClickedButton17()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//mysoftware* ccmysoftware;
	this->ShowWindow(SW_HIDE);
	ccmysoftware = new mysoftware();
	ccmysoftware->DoModal();
	this->ShowWindow(SW_SHOW);
}

//ɾ��ϵͳtemp�����������
void CMFCApplication2Dlg::OnBnClickedButton18()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//typedef struct _SHFILEOPSTRUCT {
	//	2  HWND hwnd;//ָ������Ϣ�Ĵ���
	//	3  UINT wFunc;//ִ�еĲ���
	//	4  LPCTSTR pFrom;//Դ�ļ���
	//	5  LPCTSTR pTo;//Ŀ���ļ���
	//	6  FILEOP_FLAGS fFlags;//������ȷ�ϱ�ʶ
	//	7  BOOL fAnyOperationsAborted;//�����Ƿ���ֹ
	//	8  LPVOID hNameMappings;//�ļ�ӳ��
	//	9  LPCTSTR lpszProgressTitle;//����������
	//	10
	//} SHFILEOPSTRUCT, *LPSHFILEOPSTRUCT;
	/*1.FO_COPY������
		2.FO_DELETE��ɾ��
		3.FO_MOVE���ƶ�
		4.FO_RENAME��������*/
		//	// ������÷�
		//2   LPTSTR pszSource = L"C:\\Windows";
		//3
		//	4 // ��ȷ���÷�
		//	5 LPTSTR pszSource = L"C:\\Windows\0";
		//1   CString strSource("C:\\Windows");
		//2
		//	3 strSource += '\0';//ע�������'\0'������"\0"!~!!
	CString strSrc("C:\\Users\\Default\\AppData\\Local\\Temp");
	CString strDes("C:\\Users\\allenboy\\Downloads");
	strSrc += '\0';//�����'\0'
	strDes += '\0';
	SHFILEOPSTRUCT FileOp;
	FileOp.fFlags = FOF_ALLOWUNDO | FOF_MULTIDESTFILES | FOF_SIMPLEPROGRESS;//
	CString str("���ڽ�����");
	str += '\0';
	FileOp.lpszProgressTitle = str;
	FileOp.hwnd = m_hWnd;
	FileOp.hNameMappings = NULL;
	FileOp.pFrom = strSrc; //     
	FileOp.pTo = strDes;
	FileOp.wFunc = FO_DELETE;
	//FileOp.wFunc = FO_COPY;
	BOOL bOk;
	bOk = SHFileOperation(&FileOp);
	if (!FileOp.fAnyOperationsAborted)//��ֹ
	{
		if (bOk)
			MessageBox(_T("�������ִ���"));
		else
			MessageBox(_T("������ɣ�"));
	}
	else
	{
		MessageBox(_T("��������ֹ��"));
	}
	FileOp.pFrom = strDes; //  
	bOk = SHFileOperation(&FileOp);
	if (!FileOp.fAnyOperationsAborted)//��ֹ
	{
		if (bOk)
			MessageBox(_T("�������ִ���"));
		else
			MessageBox(_T("������ɣ�"));
	}
	else
	{
		MessageBox(_T("��������ֹ��"));
	}
}

//������
void CMFCApplication2Dlg::OnBnClickedButton19()
{
		HKEY hKey;
		CString strRegPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";//ϵͳ������
		    //��
			if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) 
			{
				TCHAR szModule[_MAX_PATH];
				//GetModuleFileName() ��ȡ��ǰ�����Ѽ���ģ����ļ�������·��,
				GetModuleFileName(NULL, szModule, _MAX_PATH);
				//���ü�ֵRegSetValueEx
				MessageBox(szModule);
				//RegSetValueEx(hKey, L"AutoRunByRegistry", 0, REG_SZ, (const BYTE*)(LPCSTR)szModule, sizeof(szModule));
				//�ͷ�ָ��ע����ľ��
				RegCloseKey(hKey); 
				MessageBox(L"���óɹ�");
			}
			else
			{
				MessageBox(L"����ʧ��");
			}
		
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�������λ����
	//	[HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run]
	//[HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\RunOnce]��������һ�Σ�
	//	[HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\RunServices]
	//[HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run]
	//[HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\RunOnce]��������һ�Σ�
	//	[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\policies\Explorer\Run]��WIN2000 / XP��
	//	[HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer\Run]��WIN2000 / XP��
	//	[HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\Windows]��WIN2000 / XP��
	//MFCͨ��ע��� ʵ�ֳ��򿪻��Զ�����
	//	1.����һ����Ա������

	//	void CAutoRunByRegistryDlg::SetAutoRun(bool bAutoRun)
	//{
	//	HKEY hKey;
	//	CString strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";//find the system's startup
	//	if (bAutoRun)
	//	{
	//		if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) //open running item
	//		{
	//			TCHAR szModule[_MAX_PATH];
	//			GetModuleFileName(NULL, szModule, _MAX_PATH);//Get oneself program's name  
	//			RegSetValueEx(hKey, "AutoRunByRegistry", 0, REG_SZ, (const BYTE*)(LPCSTR)szModule, strlen(szModule));
	//			//add a child Key,and set a value="AutoRunByRegistry"��it is a program name (remove .exe),of course KeyVaule can set anyone.  
	//			RegCloseKey(hKey); //close Registry  
	//		}
	//		else
	//		{
	//			AfxMessageBox("the system parameters error,AutoRun fail!");
	//		}
	//	}
	//	else
	//	{
	//		if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
	//		{
	//			RegDeleteValue(hKey, "AutoRunByRegistry");     //Del KeyVaule="AutoRunByRegistry", so program AutoRunByRegistry.exe will can  AutoRun.
	//			RegCloseKey(hKey);
	//		}
	//	}
	//}



	//2.���Ӻ�����Ӧ��

	//	���´��룬���Էŵ���ʼ������OnInitDialog()������ť��Ӧ���������ԡ�

	//	SetAutoRun(true);  //add registrykey value
	//					   //SetAutoRun(false);  //remove registrykey value

	//3.Ч�����Բ鿴ע��������������룺regedt32.exe

	//	Ȼ���ҵ�·��Ϊ��SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run���Ϳ��Կ���ע��ĳ���

	//	���ϳ���ʵ���˿���������������ĳ�������뿪������������Ӧ�ó���ֻ��Ҫ��RegSetValueEx�����аѳ��������·����������OK���Ϳ����ˡ�
 // 
}

//�鿴����
void CMFCApplication2Dlg::OnBnClickedButton20()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//EnumServiceStatusEx
	this->ShowWindow(SW_HIDE);
	ccmyservice = new myservice();
	ccmyservice->DoModal();
	this->ShowWindow(SW_SHOW);
}
char* CMFCApplication2Dlg::UnicodeToAnsi(const wchar_t szStr)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, (LPCWCH)szStr, -1, pResult, nLen, NULL, NULL);
	return pResult;
}

//����md5ֵ
void CMFCApplication2Dlg::OnBnClickedButton21()
{
	if (md5 == NULL) {
		return;
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CStringA strPathA = CW2A(ctrpath.GetBuffer(), CP_THREAD_ACP);
	char*temp = strPathA.GetBuffer();
	ofstream out("allen.allen", ios::app);
	out << temp << "###" << md5 << endl;
	MessageBox(L"�ɹ���");
}

//ɱ��
void CMFCApplication2Dlg::OnBnClickedButton16()
{
	if (ctrpath == _T("")) {
		return;
	}
	//���ļ�
	try
	{
		ifstream in("allen.allen");
		//�����оͷ���
		string str;
		while (getline(in, str))
		{
			std::vector<std::string> mystr = CMFCApplication2Dlg::split(str, "###");
			//�ж��Ƿ���
			if (mystr.size() >= 2) {
				//����
				const char* ch1 = mystr[0].c_str();
				CStringA strPathA = CW2A(this->ctrpath.GetBuffer(), CP_THREAD_ACP);
				char*temp1 = strPathA.GetBuffer();
				string cppstname1 = temp1;
				string cppstname2 = ch1;
				//md5
				const char* ch2 = mystr[1].c_str();
				CStringA strP = CW2A(ctrpath.GetBuffer(), CP_THREAD_ACP);
				char*temp = strP.GetBuffer();
				this->md5 = md5FileValue(temp);
				if (this->md5 == NULL) {
					MessageBox(L"û��md5��");
					return;
				}
				string cppstrmd1 = this->md5;
				string cppstrmd2 = ch2;
				if (cppstname1 == cppstname2&&cppstrmd1 == cppstrmd2) {
					MessageBox(L"���Ƕ���");
					return;
				}
			}
		}
		//û��
		MessageBox(L"�Ƕ���");
	}
	catch (exception)
	{
		MessageBox(L"�ļ���ȡ���󣡣�");
		return;
	}
	
	
	//// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CStringA strPathA = CW2A(ctrpath.GetBuffer(), CP_THREAD_ACP);
	//char*temp = strPathA.GetBuffer();
	//char*charSource2 = md5FileValue(temp);
	//CString strmd1;
	//strmd1.Format(_T("%S"), this->md5);
	//CString strmd2;
	//strmd2.Format(_T("%S"), charSource2);
	//if (strmd1 == strmd2) {
	//	MessageBox(L"���Ƕ���");
	//}
	//else {
	//	MessageBox(L"�ɹ���");
	//}

}

//ȫ·����ɱ
void CMFCApplication2Dlg::OnBnClickedButton22()
{
	if (ctrpath == _T("")) {
		MessageBox(L"������·��������");
		return;
	}
	TCHAR oppoStr[MAX_PATH];
	_stprintf_s(oppoStr, MAX_PATH, L"%s", ctrpath);
	EnumLoad(oppoStr);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
//�ݹ�����ļ�
void CMFCApplication2Dlg::EnumLoad(TCHAR * load) {
	BOOL Flag = FALSE;
	TCHAR szSearchPath[MAX_PATH] = {};
	_stprintf_s(szSearchPath, MAX_PATH, L"%s\\*.*", load);
	CString str;
	str.Format(L"%s\r\n", szSearchPath);
	this->myclear.SetSel(-1);
	this->myclear.ReplaceSel(str);
	WIN32_FIND_DATA wsd = {};
	HANDLE hFile = FindFirstFile(szSearchPath, &wsd);
	if (hFile == INVALID_HANDLE_VALUE) {
		return;
	}
	do {
		if (wsd.cFileName[0] == '.') {
			continue;
		}
		if (wsd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) {
			TCHAR oppo[MAX_PATH];
			_stprintf_s(oppo, MAX_PATH, L"%s\\%s", load, wsd.cFileName);
			//wsd.cFileName
			CString str;
			str.Format(L"%s\r\n", wsd.cFileName);
			this->myclear.SetSel(-1);
			this->myclear.ReplaceSel(str);
			if (_tcscmp(L"Debug", wsd.cFileName) == 0 || _tcscmp(L"x64", wsd.cFileName) == 0 || _tcscmp(L"Release", wsd.cFileName) == 0
				|| _tcscmp(L"ipch", wsd.cFileName) == 0) {
				//_stprintf_s(oppo, MAX_PATH, L"%s%s", oppo, "\0");
				//SetWindowText(oppo);
				//deleteFolder(oppo);

				continue;
			}
			EnumLoad(oppo);
		}
		else {
			int Size = _tcslen(wsd.cFileName);
			if (NULL != StrStr(wsd.cFileName, L".db")) {
				TCHAR oppoStr[MAX_PATH];
				_stprintf_s(oppoStr, MAX_PATH, L"%s\\%s", load, wsd.cFileName);
			}

		}
	} while (FindNextFile(hFile, &wsd));

}
//�Ʋ�ɱ
void CMFCApplication2Dlg::OnBnClickedButton23()
{
	if (ctrpath == _T("")) {
		MessageBox(L"·��Ϊ�գ�������", L"��ʾ", MB_OK);
		return;
	}
	if (!(this->sClient)) {
		MessageBox(L"�����ӷ�����������", L"��ʾ", MB_OK);
		return;
	}
	CStringA strPathA = CW2A(this->ctrpath.GetBuffer(), CP_THREAD_ACP);
	char*temp1 = strPathA.GetBuffer();
	char* tempmd5 = md5FileValue(temp1);
	//1�����
	int a = 1;
	CStringA strMD5;
	strMD5.Format("%d###%s", a,tempmd5);
	// 
	CStringA str =strPathA + "###" + strMD5;
	//�Ȳ�
	send(this->sClient, str, str.GetLength(),NULL);
	MessageBox(L"���ڲ���", L"��ʾ", MB_OK);
	char buf[1024] = { 0 };
	recv(this->sClient, buf, 1024, 0);
	CStringA stret;
	stret.Format("%s", buf);
	CString tempstr = CA2W(stret);
	MessageBox(tempstr, L"��ʾ", MB_OK);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
//�ַ����ָ��
std::vector<std::string> CMFCApplication2Dlg::split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//��չ�ַ����Է������
	int size = str.size();

	for (int i = 0; i<size; i++)
	{
		pos = str.find(pattern, i);
		if (pos<size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}


void CMFCApplication2Dlg::OnEnChangeEdit7()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);

}

//��������ɱ
void CMFCApplication2Dlg::OnBnClickedButton24()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (killpid==L"") {
		MessageBox(L"��pid������");
	}
	HANDLE h_Process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, _ttoi(killpid));
	wchar_t path[MAX_PATH + 1];
	if (!GetModuleFileNameEx(h_Process, NULL, path, MAX_PATH + 1)) {
		MessageBox(L"pid����ʧ�ܣ�����");
		return ;
	}
	CString strpid;
	strpid.Format(L"%s", path);
	MessageBox(strpid);
	//���ļ�
	try
	{
		ifstream in("allen.allen");
		//�����оͷ���
		string str;
		while (getline(in, str))
		{
			std::vector<std::string> mystr = CMFCApplication2Dlg::split(str, "###");
			//�ж��Ƿ���
			if (mystr.size() >= 2) {
				//����
				const char* ch1 = mystr[0].c_str();
				CStringA strPathA = CW2A(strpid.GetBuffer(), CP_THREAD_ACP);
				char*temp1 = strPathA.GetBuffer();
				string cppstname1 = temp1;
				string cppstname2 = ch1;
				//md5
				const char* ch2 = mystr[1].c_str();
				CStringA strP = CW2A(strpid.GetBuffer(), CP_THREAD_ACP);
				char*temp = strP.GetBuffer();
				this->md5 = md5FileValue(temp);
				if (this->md5 == NULL) {
					MessageBox(L"û��md5��");
					return;
				}
				string cppstrmd1 = this->md5;
				string cppstrmd2 = ch2;
				if (cppstname1 == cppstname2&&cppstrmd1 == cppstrmd2) {
					MessageBox(L"pid�������");
					return;
				}
			}
		}
		//û��
		MessageBox(L"��ֹͣ��");
	}
	catch (exception)
	{
		MessageBox(L"�ļ���ȡ���󣡣�");
		return;
	}
}

//PEdump
void CMFCApplication2Dlg::OnBnClickedButton26()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);
	ccPEdump = new PEdump();
	ccPEdump->DoModal();
	delete ccPEdump;
	ccPEdump = nullptr;
	this->ShowWindow(SW_SHOW);

}

//����md5���ƶ�
void CMFCApplication2Dlg::OnBnClickedButton25()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (ctrpath == _T("")) {
		MessageBox(L"·��Ϊ�գ�������", L"��ʾ", MB_OK);
		return;
	}
	if (!(this->sClient)) {
		MessageBox(L"�����ӷ�����������", L"��ʾ", MB_OK);
		return;
	}
	CStringA strPathA = CW2A(this->ctrpath.GetBuffer(), CP_THREAD_ACP);
	char*temp1 = strPathA.GetBuffer();
	char* tempmd5 = md5FileValue(temp1);
	//0�������
	int a = 0;
	CStringA strMD5;
	strMD5.Format("%d###%s", a, tempmd5);
	// 
	CStringA str = strPathA + "###" + strMD5;
	//�Ȳ�
	send(this->sClient, str, str.GetLength(), NULL);
	MessageBox(L"���ڲ���", L"��ʾ", MB_OK);
	char buf[1024] = { 0 };
	recv(this->sClient, buf, 1024, 0);
	CStringA stret;
	stret.Format("%s", buf);
	CString tempstr = CA2W(stret);
	MessageBox(tempstr, L"��ʾ", MB_OK);
}

//���ӷ�����
void CMFCApplication2Dlg::OnBnClickedButton27()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (ctrpath == _T("")) {
		MessageBox(L"·��Ϊ�գ�������", L"��ʾ", MB_OK);
		return;
	}
	WSADATA wsd = {};
	WSAStartup(MAKEWORD(2, 2), &wsd);
	if (LOBYTE(wsd.wVersion) != 2 || HIBYTE(wsd.wVersion) != 2)
	{
		MessageBox( L"��汾������Ҫ��", L"��ʾ", MB_OK);
		return ;
	}
	this->sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->sClient == INVALID_SOCKET)
	{
	    MessageBox( L"�����׽���ʧ��", L"��ʾ", MB_OK);
		WSACleanup();
		return ;
	}
    addrSer = {};
	addrSer.sin_family = AF_INET;
	addrSer.sin_addr.S_un.S_addr = inet_addr("192.168.1.192");
	addrSer.sin_port = htons(1234);
	int nRet = connect(this->sClient, (sockaddr*)&addrSer, sizeof(sockaddr_in));
	if (nRet == SOCKET_ERROR)
	{
		MessageBox(L"connectʧ��", L"��ʾ", MB_OK);
		closesocket(this->sClient);
		WSACleanup();
		return;
	}
	MessageBox(L"���ӳɹ�������", L"��ʾ", MB_OK);
}

//�Ͽ�����
void CMFCApplication2Dlg::OnBnClickedButton28()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!(this->sClient)) {
		MessageBox(L"������û�����ӣ�����", L"��ʾ", MB_OK);
		return;
	}
	closesocket(this->sClient);
	MessageBox(L"�������ѶϿ�������", L"��ʾ", MB_OK);
}

//root����
void CMFCApplication2Dlg::OnBnClickedButton29()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// 1. ��ȡ������·��
	TCHAR path[MAX_PATH] = { 0 };
	DWORD dwSize = MAX_PATH;
	QueryFullProcessImageName(GetCurrentProcess(), 0, path, &dwSize);

	// ���ش���
	ShowWindow(SW_HIDE);
	//HWND hwin = (HWND)GetModuleHandle(NULL);
	HWND hwin = this->m_hWnd;
	// 2. �Թ���Ա�������
	ShellExecute(hwin,
		_T("runas"), /*ϵͳ�����˼�Թ�������һ������*/
		path,
		NULL, NULL, SW_SHOW);

	if (ERROR_SUCCESS == GetLastError()) {
		// ��������ɹ����˳�����.
		ExitProcess(0);
	}
	else {
		// �����������ʧ��, �򽫴�����ʾ����
		ShowWindow(SW_SHOW);
	}

}

//�ж��Ƿ��Թ���Ա�������
bool CMFCApplication2Dlg::IsAdmin(HANDLE hProcess)
{
	HANDLE hToken = NULL;
	OpenProcessToken(hProcess, TOKEN_QUERY, &hToken);

	TOKEN_ELEVATION_TYPE tokenType = TokenElevationTypeDefault; // ���ڽ�����������

	DWORD dwRetSize = 0; // ���ڽ��պ��������Ϣ���ֽ���
						 // 2. ��ѯ���������е�Ȩ������ֵ.( ���ֵ���¼��ǰ�������Ǻ�������( ϸ�ڽ�17_Ȩ�޹���_���ƵĻ�ȡ.cpp ) )
	GetTokenInformation(hToken,
		TokenElevationType,// ��ȡ���Ƶĵ�ǰ�����ȼ�
		&tokenType,
		sizeof(tokenType),
		&dwRetSize // ���軺�������ֽ���
	);

	// �������Ƶ������������Ӧ����Ϣ
	if (TokenElevationTypeFull == tokenType) {
		// 3. ���������TokenElevationTypeFull , ��ӵ���������ϵ�����,���Ը���������κ���Ȩ,���ص�0��ִ�д���.
		return true;
	}
	// 4. �����������, ����Ҫ�Թ���Ա����������б�����. ���������Ե������ķ������ʣ�µ�����.
	else if (TokenElevationTypeDefault == tokenType) {

		// Ĭ���û�������һ��û��Ȩ�޵ı�׼�û�
		// Ҳ������UAC���ر�.
		// ֱ�ӵ���ϵͳ�ĺ���IsUserAnAdmin ���ж��û��Ƿ��ǹ���Ա.
		return IsUserAnAdmin();
	}
	else if (TokenElevationTypeLimited == tokenType) {

		return false;
	}

	return false;
}
int WINAPI myMessageBoxA(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType) {
	while (1)
	{
		MessageBox(NULL, L"��ʾ", 0,0);
	}
}
//���̱���
void CMFCApplication2Dlg::OnBnClickedButton30()
{

	BYTE shellcode[] =
	{
		"\xE8\x00\x00\x00\x00"	// call $+5
		"\x58"					// pop	eax
		"\x6A\x00"				// push	0
		"\x83\xC0\x17"			// add eax,0x17
		"\x50"					// push eax
		"\x83\xC0\x14"			// add eax,0x14
		"\x50"					// push eax
		"\x6A\x00"				// push 0
		"\xB8\x30\x88\x20\x74"	// mov eax,MessageBoxA
		"\xFF\xD0"				// call eax
		"\xC2\x04\x00"			// ret 0x04
		"����shellcode\0"
		"shellcode!!!"
	};

	// ��MessageBoxA�����ĵ�ַд�뵽shellcode��.
	*(DWORD*)(shellcode + 19) = (DWORD)&myMessageBoxA;
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��Dllע�뵽Ŀ�����
	//��Ŀ�����
	//��ȡĿ�����pid
	const WCHAR* szDllName = L"Win32Project6.dll";
	HWND hwnd;
	while (true)
	{
		hwnd = ::FindWindow(0, L"���������");
		if (hwnd)
			break;
		Sleep(100);
	}
	DWORD pid = 0;
	//ͨ�����ھ����ý���ID
	GetWindowThreadProcessId(hwnd, &pid);

	//��ý��̾��
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	//2.��Ŀ�����������ʹ�ÿռ�
	LPVOID pszDllName = VirtualAllocEx(hProcess, NULL, 64*4096, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	//3.��Ŀ�������д������(Ҫע���Dll���ƣ�
	SIZE_T size;
	SIZE_T	dwWrite = 0;
	// 2. ��shellcode·��д�뵽�¿����ڴ�ռ���
	WriteProcessMemory(
		hProcess,
		pszDllName,			  /* Ҫд��ĵ�ַ */
		shellcode,		      /* Ҫд������ݵĵ�ַ */
		sizeof(shellcode),				  /* д����ֽ��� */
		&dwWrite				  /* ���:����ʵ��д����ֽ��� */
	);
	//WriteProcessMemory(hProcess, pszDllName, szDllName, MAX_PATH, &size);
	//4.��Ŀ������д���Զ���߳�
	//LPTHREAD_START_ROUTINE lpaddr=(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"),"LoadLibraryA");
	HANDLE hRemoteThread = CreateRemoteThread(
		hProcess,
		0, 0,
		(LPTHREAD_START_ROUTINE)pszDllName,  /* �̻߳ص�����  ����shellcode */
		0,							           /* �ص��������� */
		0, 0);
	//HANDLE hInJectThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, pszDllName, NULL, NULL);
	//5.�ȴ��̺߳�������(����dll����)
	WaitForSingleObject(hRemoteThread, -1);
	//��ȡDll���ص�ַ
	DWORD eCode;
	GetExitCodeThread(hRemoteThread, &eCode);
	HMODULE hMod = (HMODULE)eCode;
	//�ͷſռ�
	VirtualFreeEx(hProcess, pszDllName, 4096, MEM_DECOMMIT);
	CloseHandle(hProcess);






	//////ע���ע��
	wchar_t ProcessFullPath[MAX_PATH] = { 0 };
	DWORD ProcessFullPathLength = ARRAYSIZE(ProcessFullPath);
	GetModuleFileName(NULL, ProcessFullPath, ProcessFullPathLength);
	LONG ReturnValue = 0;
	HKEY hKey;
	WCHAR  RegPath[] = L"SOFTWARE\\Microsoft\\Windows\ NT\\CurrentVersion\\Windows";
	const wchar_t* DllName = L"Win32Project6.dll";
	wstring InjectFileFullPath;
	InjectFileFullPath = GetExeDirectory() +
		L"\\" + DllName;
	RegEnableReflectionKey(HKEY_LOCAL_MACHINE);
	//�򿪼�ֵ  
	ReturnValue = RegOpenKeyEx(
		HKEY_LOCAL_MACHINE,
		RegPath,
		0,
		KEY_ALL_ACCESS,
		&hKey);

	if (ReturnValue != ERROR_SUCCESS)
	{
		return ;
	}

	//��ѯ��ֵ  
	DWORD dwReadType;
	DWORD dwReadCount;
	WCHAR szReadBuff[1000] = { 0 };
	ReturnValue = RegQueryValueEx(hKey,
		L"AppInit_DLLs",
		NULL,
		&dwReadType,
		(BYTE*)&szReadBuff,
		&dwReadCount);

	if (ReturnValue != ERROR_SUCCESS)
	{
		return ;
	}
	//�Ƿ�dll�����Ѿ���������  
	wstring strCmpBuff(szReadBuff);
	//strCmpBuff = szReadBuff;
	int a = strCmpBuff.find(InjectFileFullPath);
	if (strCmpBuff.find(InjectFileFullPath))
	{
		return ;
	}

	//���ַ����ͼ���ո�  
	if (wcscmp(szReadBuff, L" ") != 0)
	{
		wcscat_s(szReadBuff, L" ");
	}

	wcscat_s(szReadBuff, InjectFileFullPath.c_str());

	//��dll·�����õ�ע�����  
	ReturnValue = RegSetValueEx(hKey,
		L"AppInit_DLLs",
		0,
		REG_SZ,
		(CONST BYTE*)szReadBuff,
		(_tcslen(szReadBuff) + 1) * sizeof(TCHAR));
	DWORD v1 = 0;
	ReturnValue = RegSetValueEx(hKey,
		L"LoadAppInit_DLLs",
		0,
		REG_DWORD,
		(CONST BYTE*)&v1,
		sizeof(DWORD));
}

wstring CMFCApplication2Dlg::GetExeDirectory()
{
	wchar_t ProcessFullPath[MAX_PATH] = { 0 };
	DWORD ProcessFullPathLength = ARRAYSIZE(ProcessFullPath);
	GetModuleFileName(NULL, ProcessFullPath, ProcessFullPathLength);

	return GetParent(ProcessFullPath);
}

wstring CMFCApplication2Dlg::GetParent(const std::wstring& FullPath)
{
	if (FullPath.empty())
	{
		return FullPath;
	}
	auto v1 = FullPath.rfind(L"\\");
	if (v1 == FullPath.npos)
	{
		v1 = FullPath.rfind(L'/');
	}
	if (v1 != FullPath.npos)
	{
		return FullPath.substr(0, v1);
	}
	else
	{
		return FullPath;
	}
}