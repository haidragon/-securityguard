
// MFCApplication2Dlg.cpp : 实现文件
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
// 如果盾牌没有出现在按钮, 可以加入以下宏.
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCApplication2Dlg 对话框



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


// CMFCApplication2Dlg 消息处理程序

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//MessageBox(L"点击进程号列出当前进程的所有模块!!!!!");

	//root
	// 判断当前是否是以管理员身份运行的进程.
	if (!IsAdmin(GetCurrentProcess())) {

		// 如果不是, 则将一个按钮设置为带盾牌标志的按钮.
		Button_SetElevationRequiredState(this->btnroot, true);
	}
	else {

		// 如果已经以管理员身份运行,则将按钮隐藏
		::ShowWindow(this->btnroot, SW_HIDE);
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	myCpuEdit.SetReadOnly(TRUE);
	//myfileCEdit.SetReadOnly(TRUE);
	myfileCEdit.DragAcceptFiles(TRUE);
	HWND myallen = (HWND)::GetModuleHandle(NULL);
	::RegisterHotKey(this->m_hWnd, 0x1234, MOD_CONTROL, 'G');
	EnumProcess();

	//绑定ip
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication2Dlg::OnPaint()
{
	//查看文件的按扭不可用
	//this->chawenjian.EnableWindow(0);
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


bool CMFCApplication2Dlg::EnumProcess() {
	// 1. 先创建快照
	HANDLE hTool32 = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (INVALID_HANDLE_VALUE == hTool32)
	{
		printf("快照error!\n");
		return false;
	}
	// 2. 开始遍历进程
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
	cclistctrl.InsertColumn(0, L"名称", 0, nwidth / 6);
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
//点击pid遍历模块
void CMFCApplication2Dlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


//获取系统所有线程
void CMFCApplication2Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	ccmythreadmod = new threadmod();
	ccmythreadmod->DoModal();
	delete ccmythreadmod;
	ccmythreadmod = nullptr;
	this->ShowWindow(SW_SHOW);

}


void CMFCApplication2Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
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
		MessageBox(L"输入pid!");
	}
	//	MessageBox(myctr);
}



void CMFCApplication2Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	/*UpdateData(FALSE);
	cpustr += "\n";*/
	//UpdateData(TRUE);
}

//查看cpu信息
void CMFCApplication2Dlg::OnBnClickedButton4()
{
	this->myCpuEdit.Clear();
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	CString str;
	str.Format(L"处理器掩码:%d \r\n", systemInfo.dwActiveProcessorMask);
	cpustr += str;
	str.Format(L"处理器个数:%d \r\n", systemInfo.dwNumberOfProcessors);
	cpustr += str;
	str.Format(L"处理器分页大小:%d\r\n", systemInfo.dwPageSize);
	cpustr += str;
	str.Format(L"处理器类型:%d\r\n", systemInfo.dwProcessorType);
	cpustr += str;
	str.Format(L"最大寻址单元: %d\r\n", systemInfo.lpMaximumApplicationAddress);
	cpustr += str;
	str.Format(L"最小寻址单元: %d\r\n", systemInfo.lpMinimumApplicationAddress);
	cpustr += str;
	str.Format(L"处理器等级: %d\r\n", systemInfo.wProcessorLevel);
	cpustr += str;
	str.Format(L"处理器版本: %d\r\n", systemInfo.wProcessorRevision);
	MEMORYSTATUS stat;
	GlobalMemoryStatus(&stat);
	str.Format(L"内存的使用率: %d\r\n", stat.dwMemoryLoad);
	cpustr += str;
	double neic = stat.dwTotalPhys / 1024.0 / 1024.0 / 1024.0;

	str.Format(L"总的物理内存大小: %f G\r\n", neic);
	cpustr += str;
	str.Format(L"可用的物理内存大小: %f G\r\n", stat.dwAvailPhys / 1024.0 / 1024.0 / 1024.0);
	cpustr += str;
	str.Format(L"虚拟地址空间: %f G\r\n", stat.dwTotalVirtual / 1024.0 / 1024.0 / 1024.0);
	cpustr += str;
	str.Format(L"可用虚拟地址空间: %f G\r\n", stat.dwAvailVirtual / 1024.0 / 1024.0 / 1024.0);

	cpustr += str;
	CWnd* pWnd = GetDlgItem(IDC_EDIT1);
	pWnd->SetWindowText(cpustr);
	cpustr = "";


	//dwLength 　　MEMORYSTATUS结构的大小，在调GlobalMemoryStatus函数前用sizeof()函数求得，用来供函数检测结构的版本。
	//	dwMemoryLoad 　 返回一个介于0～100之间的值，用来指示当前系统内存的使用率。
	//	dwTotalPhys 　　返回总的物理内存大小，以字节(byte)为单位。
	//	dwAvailPhys 　　返回可用的物理内存大小，以字节(byte)为单位。
	//	dwTotalPageFile  显示可以存在页面文件中的字节数。注意这个数值并不表示在页面文件在磁盘上的真实物理大小。
	//	dwAvailPageFile  返回可用的页面文件大小，以字节(byte)为单位。
	//	dwTotalVirtual 　返回调用进程的用户模式部分的全部可用虚拟地址空间，以字节(byte)为单位。
	//	dwAvailVirtual 　返回调用进程的用户模式部分的实际自由可用的虚拟地址空间，以字节(byte)为单位。
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

	// TODO: 在此添加控件通知处理程序代码

	//cout << setw(20) << "处理器掩码: " << systemInfo.dwActiveProcessorMask << endl
	//	<< setw(20) << "处理器个数: " << systemInfo.dwNumberOfProcessors << endl
	//	<< setw(20) << "处理器分页大小: " << systemInfo.dwPageSize << endl
	//	<< setw(20) << "处理器类型: " << systemInfo.dwProcessorType << endl
	//	<< setw(20) << "最大寻址单元: " << systemInfo.lpMaximumApplicationAddress << endl
	//	<< setw(20) << "最小寻址单元: " << systemInfo.lpMinimumApplicationAddress << endl
	//	<< setw(20) << "处理器等级: " << systemInfo.wProcessorLevel << endl
	//	<< setw(20) << "处理器版本: " << systemInfo.wProcessorRevision << endl;
	//GetSystemInfo
}


//查看文件信息
void CMFCApplication2Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	//typedef struct _WIN32_FILE_ATTRIBUTE_DATA {
	//	DWORD    dwFileAttributes;
	   //创建时间
	//	FILETIME ftCreationTime;
		//最后进入时间
	//	FILETIME ftLastAccessTime;
		//最后修改时间
	//	FILETIME ftLastWriteTime;
	//	DWORD    nFileSizeHigh;
	//	DWORD    nFileSizeLow;
	//} WIN32_FILE_ATTRIBUTE_DATA, *LPWIN32_FILE_ATTRIBUTE_DATA;
	if (this->ctrpath == _T("")) {
		MessageBox(L"请输入路径！");
		return;
	}
	SYSTEMTIME time;
	WIN32_FILE_ATTRIBUTE_DATA lpinf;
	CString TestDate;
	if (GetFileAttributesEx(ctrpath, GetFileExInfoStandard, &lpinf) == 0) {
		MessageBox(L"路径不对！");
		return;
	}
	//创建时间
	FileTimeToSystemTime(&lpinf.ftCreationTime, &time);
	TestDate.Format(_T("创建时间：%d-%d-%d\r\n"), time.wYear, time.wMonth, time.wDay);
	filestr += TestDate;
	//最后修改时间
	FileTimeToSystemTime(&lpinf.ftLastWriteTime, &time);
	TestDate.Format(_T("最后修改时间：%d-%d-%d\r\n"), time.wYear, time.wMonth, time.wDay);
	filestr += TestDate;
	//最后进入时间
	FileTimeToSystemTime(&lpinf.ftLastAccessTime, &time);
	TestDate.Format(_T("最后访问时间：%d-%d-%d\r\n"), time.wYear, time.wMonth, time.wDay);
	filestr += TestDate;


	double size;
	CFileStatus fileStatus;

	if (CFile::GetStatus(ctrpath, fileStatus))
	{
		size = fileStatus.m_size;
	}
	CString str;
	str.Format(L"大小：%f M\r\n", size / 1024.0 / 1024.0);
	filestr += str;
	str.Format(L"路径：%s\r\n", fileStatus.m_szFullName);
	filestr += str;
	//CString strSource;//宣告CString
	//char* charSource; //宣告char*
	//法1：
	//	charSource = (char*)strSource.GetBuffer(0);
	//法2：
	//	charSource = (char*)strSource.GetBuffer(strSource.GetLength());
	//法3：
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
	str.Format(_T("Md5值：%S\r\n"), charSource2);
	filestr += str;
	CWnd* pWnd = GetDlgItem(IDC_EDIT3);
	pWnd->SetWindowText(filestr);
	filestr = "";

	//CFileStatus是一个结构体，此结构体存储了文件的状态信息。
	//	下面我们来看看其结构体成员：
	//	CTime m_ctime   The date and time the file was created.
	//	表示文件的创建时间
	//	CTime m_mtime   The date and time the file was last modified.
	//	表示文件的修改时间
	//	CTime m_atime   The date and time the file was last accessed for reading.
	//	表示文件的最后访问时间
	//	ULONGLONG m_size   The logical size of the file in bytes, as reported by the DIR command.
	//	表示文件的逻辑大小
	//	BYTE m_attribute   The attribute byte of the file.
	//	表示文件的系统属性
	//	char m_szFullName[_MAX_PATH]   The absolute filename in the Windows character set.
	//	表示文件的绝对路径
}

//选择文件
void CMFCApplication2Dlg::OnBnClickedButton7()
{
	//IDC_EDIT4, ctrpath);
	// TODO: 在此添加控件通知处理程序代码
	CString gReadFilePathName;
	CFileDialog fileDlg(true, _T("c++"), _T("*.cpp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("c Files (*.c)|*.cpp|zip File(*.zip)|*.rar|All File (*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK)    //弹出对话框  
	{
		gReadFilePathName = fileDlg.GetPathName();//得到完整的文件名和目录名拓展名  
		GetDlgItem(IDC_EDIT4)->SetWindowText(gReadFilePathName);//将路径显示  
		ctrpath = gReadFilePathName;
		CStringA strPathA = CW2A(ctrpath.GetBuffer(), CP_THREAD_ACP);
		char*temp = strPathA.GetBuffer();
		char*charSource2 = md5FileValue(temp);
		//保存md5值
		this->md5 = charSource2;
	}
	//设置查看文件的按扭可用
	this->chawenjian.EnableWindow(1);
	//MessageBox(gReadFilePathName);
}


void CMFCApplication2Dlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);

}


void CMFCApplication2Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//线束进程
void CMFCApplication2Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	if (mypidctr != "") {
		DWORD pid = _ttoi(mypidctr);
		//KillProcess(pid);
		if (KillProcess(pid)) {
			MessageBox(L"成功！");
		}
		else {
			MessageBox(L"失败！");
		}

	}
	else {
		MessageBox(L"请输入pid");
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
}

//heap
void CMFCApplication2Dlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
}

//关机
void CMFCApplication2Dlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 0);
}

//重启
void CMFCApplication2Dlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	ExitWindows(EWX_REBOOT | EWX_FORCE, 0);
}

//注销
void CMFCApplication2Dlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	ExitWindows(EWX_LOGOFF | EWX_FORCE, 0);
}

//休眠
void CMFCApplication2Dlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	//SetSuspendState(TRUE, FALSE, FALSE);
}


void CMFCApplication2Dlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

//::RegisterHotKey(myallen, 0x1234, MOD_CONTROL, 'G');
//::RegisterHotKey(myallen, 0x1235, MOD_CONTROL, 'J');

BOOL CMFCApplication2Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
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

//内存优化
void CMFCApplication2Dlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取当前系统前物理内存和虚拟内存的使用

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
	//获取当前的内存状态
	MEMORYSTATUSEX  myMEMORYSTATUSEX = { 0 };
	myMEMORYSTATUSEX.dwLength = sizeof(myMEMORYSTATUSEX);
	GlobalMemoryStatusEx(&myMEMORYSTATUSEX);
	DWORDLONG preUesrMem = myMEMORYSTATUSEX.ullTotalPhys - myMEMORYSTATUSEX.ullAvailPhys;
	//清理内存
	DWORD dwPIDlist[1000] = { 0 };
	DWORD bufSize = sizeof(dwPIDlist);
	DWORD dwNeedSize = 0;
	EnumProcesses(dwPIDlist, bufSize, &dwNeedSize);
	for (DWORD i = 0;i < dwNeedSize / sizeof(DWORD);i++) {
		HANDLE hProcess = OpenProcess(PROCESS_SET_QUOTA, false, dwPIDlist[i]);
		//降低使用
		SetProcessWorkingSetSize(hProcess, -1, -1);
	}
	GlobalMemoryStatusEx(&myMEMORYSTATUSEX);
	DWORDLONG afterUesrMem = myMEMORYSTATUSEX.ullTotalPhys - myMEMORYSTATUSEX.ullAvailPhys;
	CString mystr;
	mystr.Format(_T("优化前%d---优化后%d"), preUesrMem, afterUesrMem);
	MessageBox(mystr, _T("优化前后对比"), IDOK);
}

//系统版本信息
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
	mystr.Format(_T(" 系统主版本：%d\n 系统次版本：%d\n 系统构建号：%d\n 系统支持的平台：%d\n 系统补丁包的名称：%s\n 系统补丁包的主版本：%d\n 系统补丁包的次版本：%d\n 标识系统上的程序组：%d\n 标识系统类型：%d\n 保存未使用：%d\n"),
		osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber,
		osvi.dwPlatformId, osvi.szCSDVersion, osvi.wServicePackMajor,
		osvi.wServicePackMinor, osvi.wSuiteMask, osvi.wProductType, osvi.wReserved);
	MessageBox(mystr, _T("系统版本信息"), IDOK);
}

//清理回收站
void CMFCApplication2Dlg::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	//初始化SHQUERYRBINFO结构

	SHQUERYRBINFO RecycleBinInformation;
	ZeroMemory(&RecycleBinInformation, sizeof(RecycleBinInformation));
	RecycleBinInformation.cbSize = sizeof(RecycleBinInformation);
	//查询回收站信息
	if (SHQueryRecycleBin(NULL, &RecycleBinInformation) == S_OK)
		//SHQueryRecycleBin第一参数为要查询回收站的盘符或者文件夹,子文件夹
		//一般其根目录相同指向的回收站也是一样的
		//为NULL则指代所有回收站,和下面的SHEmptyRecycleBin第二参数相同
	{
		CString mystr;
		mystr.Format(_T("回收站大小%ld---回收站文件数量%ld"), RecycleBinInformation.i64Size, RecycleBinInformation.i64NumItems);
		MessageBox(mystr, _T("回收站信息"), IDOK);
	}
	else
	{
		CString mystr;
		MessageBox(mystr, _T("回收站信息"), IDOK);
	}
	//清空回收站
	if (SHEmptyRecycleBin(NULL, NULL, /*SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | */SHERB_NOSOUND) == S_OK)
		//SHEmptyRecycleBin第三参数如果要显示确认删除对话框和声音之类的东西置空既可
	{
		CString mystr = _T("操作成功！");
		MessageBox(mystr, _T("回收站信息"), IDOK);
	}
	else
	{
		CString mystr = _T("清理失败，可能是没有垃圾！");
		MessageBox(mystr, _T("回收站信息"), IDOK);
	}
}

//遍历软件
void CMFCApplication2Dlg::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码
	//mysoftware* ccmysoftware;
	this->ShowWindow(SW_HIDE);
	ccmysoftware = new mysoftware();
	ccmysoftware->DoModal();
	this->ShowWindow(SW_SHOW);
}

//删除系统temp与浏览器缓冲
void CMFCApplication2Dlg::OnBnClickedButton18()
{
	// TODO: 在此添加控件通知处理程序代码
	//typedef struct _SHFILEOPSTRUCT {
	//	2  HWND hwnd;//指向发送消息的窗口
	//	3  UINT wFunc;//执行的操作
	//	4  LPCTSTR pFrom;//源文件名
	//	5  LPCTSTR pTo;//目标文件名
	//	6  FILEOP_FLAGS fFlags;//操作与确认标识
	//	7  BOOL fAnyOperationsAborted;//操作是否终止
	//	8  LPVOID hNameMappings;//文件映射
	//	9  LPCTSTR lpszProgressTitle;//进度条标题
	//	10
	//} SHFILEOPSTRUCT, *LPSHFILEOPSTRUCT;
	/*1.FO_COPY：复制
		2.FO_DELETE：删除
		3.FO_MOVE：移动
		4.FO_RENAME：重命名*/
		//	// 错误的用法
		//2   LPTSTR pszSource = L"C:\\Windows";
		//3
		//	4 // 正确的用法
		//	5 LPTSTR pszSource = L"C:\\Windows\0";
		//1   CString strSource("C:\\Windows");
		//2
		//	3 strSource += '\0';//注意必须是'\0'而不是"\0"!~!!
	CString strSrc("C:\\Users\\Default\\AppData\\Local\\Temp");
	CString strDes("C:\\Users\\allenboy\\Downloads");
	strSrc += '\0';//必须加'\0'
	strDes += '\0';
	SHFILEOPSTRUCT FileOp;
	FileOp.fFlags = FOF_ALLOWUNDO | FOF_MULTIDESTFILES | FOF_SIMPLEPROGRESS;//
	CString str("正在进行中");
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
	if (!FileOp.fAnyOperationsAborted)//终止
	{
		if (bOk)
			MessageBox(_T("操作出现错误！"));
		else
			MessageBox(_T("操作完成！"));
	}
	else
	{
		MessageBox(_T("操作已终止！"));
	}
	FileOp.pFrom = strDes; //  
	bOk = SHFileOperation(&FileOp);
	if (!FileOp.fAnyOperationsAborted)//终止
	{
		if (bOk)
			MessageBox(_T("操作出现错误！"));
		else
			MessageBox(_T("操作完成！"));
	}
	else
	{
		MessageBox(_T("操作已终止！"));
	}
}

//启动项
void CMFCApplication2Dlg::OnBnClickedButton19()
{
		HKEY hKey;
		CString strRegPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";//系统启动键
		    //打开
			if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) 
			{
				TCHAR szModule[_MAX_PATH];
				//GetModuleFileName() 获取当前进程已加载模块的文件的完整路径,
				GetModuleFileName(NULL, szModule, _MAX_PATH);
				//设置键值RegSetValueEx
				MessageBox(szModule);
				//RegSetValueEx(hKey, L"AutoRunByRegistry", 0, REG_SZ, (const BYTE*)(LPCSTR)szModule, sizeof(szModule));
				//释放指定注册键的句柄
				RegCloseKey(hKey); 
				MessageBox(L"设置成功");
			}
			else
			{
				MessageBox(L"设置失败");
			}
		
	// TODO: 在此添加控件通知处理程序代码
	//启动项的位置在
	//	[HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run]
	//[HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\RunOnce]（仅运行一次）
	//	[HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\RunServices]
	//[HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run]
	//[HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\RunOnce]（仅运行一次）
	//	[HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\policies\Explorer\Run]（WIN2000 / XP）
	//	[HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer\Run]（WIN2000 / XP）
	//	[HKEY_CURRENT_USER\Software\Microsoft\Windows NT\CurrentVersion\Windows]（WIN2000 / XP）
	//MFC通过注册表 实现程序开机自动运行
	//	1.创建一个成员函数：

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
	//			//add a child Key,and set a value="AutoRunByRegistry"，it is a program name (remove .exe),of course KeyVaule can set anyone.  
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



	//2.增加函数响应：

	//	以下代码，可以放到初始化函数OnInitDialog()，或则按钮响应函数都可以。

	//	SetAutoRun(true);  //add registrykey value
	//					   //SetAutoRun(false);  //remove registrykey value

	//3.效果可以查看注册表：在运行中输入：regedt32.exe

	//	然后找到路径为：SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run，就可以看到注册的程序。

	//	以上程序实现了开机启动运行自身的程序，如果想开机启动其他的应用程序，只需要在RegSetValueEx函数中把程序的完整路径名字设置OK，就可以了。
 // 
}

//查看服务
void CMFCApplication2Dlg::OnBnClickedButton20()
{
	// TODO: 在此添加控件通知处理程序代码
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

//保存md5值
void CMFCApplication2Dlg::OnBnClickedButton21()
{
	if (md5 == NULL) {
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
	CStringA strPathA = CW2A(ctrpath.GetBuffer(), CP_THREAD_ACP);
	char*temp = strPathA.GetBuffer();
	ofstream out("allen.allen", ios::app);
	out << temp << "###" << md5 << endl;
	MessageBox(L"成功！");
}

//杀毒
void CMFCApplication2Dlg::OnBnClickedButton16()
{
	if (ctrpath == _T("")) {
		return;
	}
	//读文件
	try
	{
		ifstream in("allen.allen");
		//先找有就返回
		string str;
		while (getline(in, str))
		{
			std::vector<std::string> mystr = CMFCApplication2Dlg::split(str, "###");
			//判断是否有
			if (mystr.size() >= 2) {
				//名字
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
					MessageBox(L"没有md5！");
					return;
				}
				string cppstrmd1 = this->md5;
				string cppstrmd2 = ch2;
				if (cppstname1 == cppstname2&&cppstrmd1 == cppstrmd2) {
					MessageBox(L"不是毒！");
					return;
				}
			}
		}
		//没有
		MessageBox(L"是毒！");
	}
	catch (exception)
	{
		MessageBox(L"文件读取错误！！");
		return;
	}
	
	
	//// TODO: 在此添加控件通知处理程序代码
	//CStringA strPathA = CW2A(ctrpath.GetBuffer(), CP_THREAD_ACP);
	//char*temp = strPathA.GetBuffer();
	//char*charSource2 = md5FileValue(temp);
	//CString strmd1;
	//strmd1.Format(_T("%S"), this->md5);
	//CString strmd2;
	//strmd2.Format(_T("%S"), charSource2);
	//if (strmd1 == strmd2) {
	//	MessageBox(L"不是毒！");
	//}
	//else {
	//	MessageBox(L"成功！");
	//}

}

//全路径查杀
void CMFCApplication2Dlg::OnBnClickedButton22()
{
	if (ctrpath == _T("")) {
		MessageBox(L"请输入路径！！！");
		return;
	}
	TCHAR oppoStr[MAX_PATH];
	_stprintf_s(oppoStr, MAX_PATH, L"%s", ctrpath);
	EnumLoad(oppoStr);
	// TODO: 在此添加控件通知处理程序代码
}
//递归遍历文件
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
//云查杀
void CMFCApplication2Dlg::OnBnClickedButton23()
{
	if (ctrpath == _T("")) {
		MessageBox(L"路径为空！！！！", L"提示", MB_OK);
		return;
	}
	if (!(this->sClient)) {
		MessageBox(L"先连接服务器！！！", L"提示", MB_OK);
		return;
	}
	CStringA strPathA = CW2A(this->ctrpath.GetBuffer(), CP_THREAD_ACP);
	char*temp1 = strPathA.GetBuffer();
	char* tempmd5 = md5FileValue(temp1);
	//1代表查
	int a = 1;
	CStringA strMD5;
	strMD5.Format("%d###%s", a,tempmd5);
	// 
	CStringA str =strPathA + "###" + strMD5;
	//先查
	send(this->sClient, str, str.GetLength(),NULL);
	MessageBox(L"正在查找", L"提示", MB_OK);
	char buf[1024] = { 0 };
	recv(this->sClient, buf, 1024, 0);
	CStringA stret;
	stret.Format("%s", buf);
	CString tempstr = CA2W(stret);
	MessageBox(tempstr, L"提示", MB_OK);
	// TODO: 在此添加控件通知处理程序代码
}
//字符串分割函数
std::vector<std::string> CMFCApplication2Dlg::split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//扩展字符串以方便操作
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);

}

//白名单查杀
void CMFCApplication2Dlg::OnBnClickedButton24()
{
	// TODO: 在此添加控件通知处理程序代码
	if (killpid==L"") {
		MessageBox(L"请pid！！！");
	}
	HANDLE h_Process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, _ttoi(killpid));
	wchar_t path[MAX_PATH + 1];
	if (!GetModuleFileNameEx(h_Process, NULL, path, MAX_PATH + 1)) {
		MessageBox(L"pid输入失败！！！");
		return ;
	}
	CString strpid;
	strpid.Format(L"%s", path);
	MessageBox(strpid);
	//读文件
	try
	{
		ifstream in("allen.allen");
		//先找有就返回
		string str;
		while (getline(in, str))
		{
			std::vector<std::string> mystr = CMFCApplication2Dlg::split(str, "###");
			//判断是否有
			if (mystr.size() >= 2) {
				//名字
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
					MessageBox(L"没有md5！");
					return;
				}
				string cppstrmd1 = this->md5;
				string cppstrmd2 = ch2;
				if (cppstname1 == cppstname2&&cppstrmd1 == cppstrmd2) {
					MessageBox(L"pid输入错误！");
					return;
				}
			}
		}
		//没有
		MessageBox(L"已停止！");
	}
	catch (exception)
	{
		MessageBox(L"文件读取错误！！");
		return;
	}
}

//PEdump
void CMFCApplication2Dlg::OnBnClickedButton26()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
	ccPEdump = new PEdump();
	ccPEdump->DoModal();
	delete ccPEdump;
	ccPEdump = nullptr;
	this->ShowWindow(SW_SHOW);

}

//保存md5到云端
void CMFCApplication2Dlg::OnBnClickedButton25()
{
	// TODO: 在此添加控件通知处理程序代码
	if (ctrpath == _T("")) {
		MessageBox(L"路径为空！！！！", L"提示", MB_OK);
		return;
	}
	if (!(this->sClient)) {
		MessageBox(L"先连接服务器！！！", L"提示", MB_OK);
		return;
	}
	CStringA strPathA = CW2A(this->ctrpath.GetBuffer(), CP_THREAD_ACP);
	char*temp1 = strPathA.GetBuffer();
	char* tempmd5 = md5FileValue(temp1);
	//0代保存查
	int a = 0;
	CStringA strMD5;
	strMD5.Format("%d###%s", a, tempmd5);
	// 
	CStringA str = strPathA + "###" + strMD5;
	//先查
	send(this->sClient, str, str.GetLength(), NULL);
	MessageBox(L"正在查找", L"提示", MB_OK);
	char buf[1024] = { 0 };
	recv(this->sClient, buf, 1024, 0);
	CStringA stret;
	stret.Format("%s", buf);
	CString tempstr = CA2W(stret);
	MessageBox(tempstr, L"提示", MB_OK);
}

//连接服务器
void CMFCApplication2Dlg::OnBnClickedButton27()
{
	// TODO: 在此添加控件通知处理程序代码
	if (ctrpath == _T("")) {
		MessageBox(L"路径为空！！！！", L"提示", MB_OK);
		return;
	}
	WSADATA wsd = {};
	WSAStartup(MAKEWORD(2, 2), &wsd);
	if (LOBYTE(wsd.wVersion) != 2 || HIBYTE(wsd.wVersion) != 2)
	{
		MessageBox( L"库版本不符合要求", L"提示", MB_OK);
		return ;
	}
	this->sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->sClient == INVALID_SOCKET)
	{
	    MessageBox( L"创建套接字失败", L"提示", MB_OK);
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
		MessageBox(L"connect失败", L"提示", MB_OK);
		closesocket(this->sClient);
		WSACleanup();
		return;
	}
	MessageBox(L"连接成功！！！", L"提示", MB_OK);
}

//断开连接
void CMFCApplication2Dlg::OnBnClickedButton28()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!(this->sClient)) {
		MessageBox(L"服务器没有连接！！！", L"提示", MB_OK);
		return;
	}
	closesocket(this->sClient);
	MessageBox(L"服务器已断开！！！", L"提示", MB_OK);
}

//root启动
void CMFCApplication2Dlg::OnBnClickedButton29()
{
	// TODO: 在此添加控件通知处理程序代码
	// 1. 获取本进程路径
	TCHAR path[MAX_PATH] = { 0 };
	DWORD dwSize = MAX_PATH;
	QueryFullProcessImageName(GetCurrentProcess(), 0, path, &dwSize);

	// 隐藏窗口
	ShowWindow(SW_HIDE);
	//HWND hwin = (HWND)GetModuleHandle(NULL);
	HWND hwin = this->m_hWnd;
	// 2. 以管理员身份运行
	ShellExecute(hwin,
		_T("runas"), /*系统命令，意思以管理运行一个进程*/
		path,
		NULL, NULL, SW_SHOW);

	if (ERROR_SUCCESS == GetLastError()) {
		// 如果创建成功则退出进程.
		ExitProcess(0);
	}
	else {
		// 如果创建进程失败, 则将窗口显示回来
		ShowWindow(SW_SHOW);
	}

}

//判断是否以管理员身份运行
bool CMFCApplication2Dlg::IsAdmin(HANDLE hProcess)
{
	HANDLE hToken = NULL;
	OpenProcessToken(hProcess, TOKEN_QUERY, &hToken);

	TOKEN_ELEVATION_TYPE tokenType = TokenElevationTypeDefault; // 用于接收令牌类型

	DWORD dwRetSize = 0; // 用于接收函数输出信息的字节数
						 // 2. 查询进程令牌中的权限提升值.( 这个值会记录当前的令牌是何种类型( 细节将17_权限管理_令牌的获取.cpp ) )
	GetTokenInformation(hToken,
		TokenElevationType,// 获取令牌的当前提升等级
		&tokenType,
		sizeof(tokenType),
		&dwRetSize // 所需缓冲区的字节数
	);

	// 根据令牌的类型来输出相应的信息
	if (TokenElevationTypeFull == tokenType) {
		// 3. 如果令牌是TokenElevationTypeFull , 则拥有至高无上的能力,可以给令牌添加任何特权,返回第0步执行代码.
		return true;
	}
	// 4. 如果是其他的, 则需要以管理员身份重新运行本进程. 这样就能以第三步的方法解决剩下的问题.
	else if (TokenElevationTypeDefault == tokenType) {

		// 默认用户可能是一个没有权限的标准用户
		// 也可能是UAC被关闭.
		// 直接调用系统的函数IsUserAnAdmin 来判断用户是否是管理员.
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
		MessageBox(NULL, L"提示", 0,0);
	}
}
//进程保护
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
		"来自shellcode\0"
		"shellcode!!!"
	};

	// 将MessageBoxA函数的地址写入到shellcode中.
	*(DWORD*)(shellcode + 19) = (DWORD)&myMessageBoxA;
	// TODO: 在此添加控件通知处理程序代码
	//将Dll注入到目标进程
	//打开目标进程
	//获取目标进程pid
	const WCHAR* szDllName = L"Win32Project6.dll";
	HWND hwnd;
	while (true)
	{
		hwnd = ::FindWindow(0, L"任务管理器");
		if (hwnd)
			break;
		Sleep(100);
	}
	DWORD pid = 0;
	//通过窗口句柄获得进程ID
	GetWindowThreadProcessId(hwnd, &pid);

	//获得进程句柄
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	//2.在目标进程中申请使用空间
	LPVOID pszDllName = VirtualAllocEx(hProcess, NULL, 64*4096, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	//3.向目标进程中写入数据(要注入的Dll名称）
	SIZE_T size;
	SIZE_T	dwWrite = 0;
	// 2. 将shellcode路径写入到新开的内存空间中
	WriteProcessMemory(
		hProcess,
		pszDllName,			  /* 要写入的地址 */
		shellcode,		      /* 要写入的内容的地址 */
		sizeof(shellcode),				  /* 写入的字节数 */
		&dwWrite				  /* 输出:函数实际写入的字节数 */
	);
	//WriteProcessMemory(hProcess, pszDllName, szDllName, MAX_PATH, &size);
	//4.在目标进程中创建远程线程
	//LPTHREAD_START_ROUTINE lpaddr=(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"),"LoadLibraryA");
	HANDLE hRemoteThread = CreateRemoteThread(
		hProcess,
		0, 0,
		(LPTHREAD_START_ROUTINE)pszDllName,  /* 线程回调函数  就是shellcode */
		0,							           /* 回调函数参数 */
		0, 0);
	//HANDLE hInJectThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, pszDllName, NULL, NULL);
	//5.等待线程函数结束(加载dll结束)
	WaitForSingleObject(hRemoteThread, -1);
	//获取Dll加载地址
	DWORD eCode;
	GetExitCodeThread(hRemoteThread, &eCode);
	HMODULE hMod = (HMODULE)eCode;
	//释放空间
	VirtualFreeEx(hProcess, pszDllName, 4096, MEM_DECOMMIT);
	CloseHandle(hProcess);






	//////注册表注入
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
	//打开键值  
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

	//查询键值  
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
	//是否dll名称已经在内容中  
	wstring strCmpBuff(szReadBuff);
	//strCmpBuff = szReadBuff;
	int a = strCmpBuff.find(InjectFileFullPath);
	if (strCmpBuff.find(InjectFileFullPath))
	{
		return ;
	}

	//有字符串就加入空格  
	if (wcscmp(szReadBuff, L" ") != 0)
	{
		wcscat_s(szReadBuff, L" ");
	}

	wcscat_s(szReadBuff, InjectFileFullPath.c_str());

	//把dll路径设置到注册表中  
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