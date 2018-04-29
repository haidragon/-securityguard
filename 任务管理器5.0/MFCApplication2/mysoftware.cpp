// mysoftware.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "mysoftware.h"
#include "afxdialogex.h"

// mysoftware �Ի���

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


// mysoftware ��Ϣ�������


void mysoftware::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
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
	myclistctrl.InsertColumn(0, L"�����", 0, nwidth / 6);
	//	DWORD th32ProcessID;
	myclistctrl.InsertColumn(1, L"����汾��", 1, nwidth / 6);
	//	DWORD dwSize;
	myclistctrl.InsertColumn(2, L"�����װĿ¼", 2, nwidth / 6);
	//	DWORD dwFlags;
	myclistctrl.InsertColumn(3, L"�����������", 3, nwidth / 6);
	myclistctrl.InsertColumn(4, L"��װ����", 4, nwidth / 6);
	myclistctrl.InsertColumn(5, L"ж��exe��������·��", 5, nwidth / 6);
	softwaredo();
}

void mysoftware::softwaredo()
{

	struct _SoftInfo
	{
		// �����  
		WCHAR m_strSoftName[50];
		// ����汾��  
		WCHAR m_strSoftVersion[50];
		// �����װĿ¼  
		WCHAR m_strInstallLocation[MAX_PATH];
		// �����������  
		WCHAR m_strPublisher[50];
		// �����װ���� 
		WCHAR time[MAX_PATH];
		// ж��exe��������·��  
		WCHAR m_strUninstallPth[MAX_PATH];
	}SoftInfo = { 0 };
	HKEY hkPesult = 0;
	// ����  
	HKEY RootKey = HKEY_LOCAL_MACHINE; //����
	// �Ӽ�����  
	LPCTSTR lpSubKey = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall"; 
	// ��Ҫ�򿪼��ľ��   
	HKEY hkResult;
	// ��¼��ȡע����Ƿ�ɹ�  
	LONG lReturn;
	CString strBuffer;
	CString strMidReg;
	int i = 0;
	DWORD index = 0;
	TCHAR szKeyName[255] = { 0 };        // ע���������  
	TCHAR szBuffer[255] = { 0 };
	DWORD dwKeyLen = 255;
	DWORD dwNameLen = 255;
	DWORD dwType = REG_BINARY | REG_DWORD | REG_EXPAND_SZ | REG_MULTI_SZ | REG_NONE | REG_SZ;
	CString *name = new CString;
	//1.��һ���Ѿ����ڵ�ע����
	LONG lPeturn = RegOpenKeyEx(RootKey,//����
		lpSubKey,//�Ӽ�·��
		0, //����  ����Ϊ0
		KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE, //Ȩ��
		&hkPesult   //�ӽ����
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

		//if (SoftInfo.m_strSoftName == name[0])//ȥ���ظ�  
		//{
		//	dwIndex++;
		//	continue;
		//}
		//// �����  
		//WCHAR m_strSoftName[50];
		//// ����汾��  
		//WCHAR m_strSoftVersion[50];
		//// �����װĿ¼  
		//WCHAR m_strInstallLocation[MAX_PATH];
		//// �����������  
		//WCHAR m_strPublisher[50];
		//// ��������������·��  
		//WCHAR m_strMainProPath[MAX_PATH];
		//// ж��exe��������·��  
		//WCHAR m_strUninstallPth[MAX_PATH];
		name[0] = SoftInfo.m_strSoftName;

		this->myclistctrl.InsertItem(i, NULL);
		//�������
		this->myclistctrl.SetItemText(i, 0, SoftInfo.m_strSoftName);
		//����汾��

		
		RegQueryValueEx(hkValueKey, L"DisplayVersion", 0, &dwType, (LPBYTE)SoftInfo.m_strSoftVersion, &dwNameLen);
		dwNameLen = 255;
		CString srtT;
		srtT.Format(L"%s", SoftInfo.m_strSoftVersion);
		this->myclistctrl.SetItemText(i, 1, srtT);
		//�����װĿ¼ 
		RegQueryValueEx(hkValueKey, L"InstallLocation", 0, &dwType, (LPBYTE)SoftInfo.m_strInstallLocation, &dwNameLen);
		dwNameLen = 255;
		srtT.Format(L"%s", SoftInfo.m_strInstallLocation);
		this->myclistctrl.SetItemText(i, 2, srtT);
		//�����������
		RegQueryValueEx(hkValueKey, L"Publisher", 0, &dwType, (LPBYTE)SoftInfo.m_strPublisher, &dwNameLen);
		dwNameLen = 255;
		srtT.Format(L"%s", SoftInfo.m_strPublisher);
		this->myclistctrl.SetItemText(i, 3, srtT);
		//��������
		RegQueryValueEx(hkValueKey, L"InstallDate", 0, &dwType, (LPBYTE)SoftInfo.time, &dwNameLen);
		dwNameLen = 255;
		srtT.Format(L"%s", SoftInfo.time);
		this->myclistctrl.SetItemText(i, 4, srtT);
		//ж��exe��������·�� 
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


	//1.�����ж����Ϣ
	//����  HKEY_LOCAL_MACHINE
	//32λ�£� �Ӽ�  SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall
	//64λ�£�SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall
	//lpSubKey = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
	//lpSubKey = _T("SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall");  
	//m_vectSoftInof

	//DWORD dwType;// = REG_BINARY | REG_DWORD | REG_EXPAND_SZ | REG_MULTI_SZ | REG_NONE | REG_SZ;

	//ѭ������UninstallĿ¼�µ��ӽ�
	//DWORD dwIndex = 0;
	//while (true)
	//{
	//	DWORD dwKeyLen = 255;
	//	WCHAR szNewKeyName[MAX_PATH] = {};  //ע���������
	//	LONG lReturn = RegEnumKeyEx(hkPesult,//�ӽ����
	//		dwIndex,//ָ����ö�ټ����Ӽ�����������0��ʼ
	//		szNewKeyName, //ָ��һ���ڴ汣���ӽ�������
	//		&dwKeyLen,//ָ���ڴ��С
	//		0,//��������Ϊ0
	//		NULL,//���ڻ�ȡ�ӽ�ֵ������
	//		NULL,//ָ��һ���ڴ棬���ڻ�ȡ�Ӽ�ֵ������
	//		NULL);//��һ����������Ļ��ڴ��С
	//	//ͨ���õ����Ӽ�����������ϳ��µ��Ӽ�·��
	//	WCHAR strMidReg[MAX_PATH] = {};
	//	swprintf_s(strMidReg, L"%s%s%s", lpSubKey, L"\\", szNewKeyName);
	//	//���µ��Ӽ�����ȡ����
	//	HKEY hkValueKey = 0;   //�Ӽ����
	//	RegOpenKeyEx(RootKey,//����
	//		strMidReg,//�Ӽ�·��
	//		0, //����  ����Ϊ0
	//	    KEY_QUERY_VALUE, //Ȩ��
	//		&hkValueKey   //�ӽ����
	//	);
	//	//��ȡ��ֵ 
	//	DWORD dwNameLen = 255;   //
	//	//��ȡ�������
	//	RegQueryValueEx(hkValueKey, L"DisplayName", 0, &dwType, (LPBYTE)SoftInfo.m_strSoftName, &dwNameLen);
	//    dwNameLen = 255;   //���û�����¸�ֵ��һ�ν���ȡ������Ϣ
	//	//��ж·��
	//	RegQueryValueEx(hkValueKey, L"UninstallString", 0, &dwType, (LPBYTE)SoftInfo.m_strUninstallPth, &dwNameLen);
	//    dwNameLen = 255;   //
	//	//���û��
	//	if (lReturn == ERROR_NO_MORE_ITEMS)
	//	{
	//		break;
	//	}
	//	dwIndex++;
	//}

	
}

//����¼�
void mysoftware::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ccol = pNMItemActivate->iSubItem;
	int crow = pNMItemActivate->iItem;
	if (ccol == 5) {
		CString str = myclistctrl.GetItemText(crow, ccol);
		this->ShowWindow(SW_HIDE);
		MessageBox(str, _T("��Ϣ"), IDOK);
		LPOFSTRUCT lpReOpenBuff;
		//ж��
		//OpenFile((LPCSTR)LPCTSTR(str), lpReOpenBuff, NULL);
		OFSTRUCT myOFSTRUCT = { 0 };
		//OpenFile((LPCSTR)str,&myOFSTRUCT,OF_READ);
		this->ShowWindow(SW_SHOW);
	}
	*pResult = 0;
	
}
