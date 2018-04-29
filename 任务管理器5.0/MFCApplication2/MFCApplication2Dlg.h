
// MFCApplication2Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "ccmymodo.h"
#include "threadmod.h"
#include "myduimodo.h"
#include "mywinmodo.h"
#include "afxwin.h"
#include "myCEdit.h"
#include "myclearCE.h"
#include "mysoftware.h"
#include "myservice.h"
#include "Md5.h"
#include "PEdump.h"
#include<vector>
#include<string>
#include <Winsock.h>
// CMFCApplication2Dlg �Ի���
class CMFCApplication2Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CRect rc;
	int nwidth;
	bool EnumProcess();
	CListCtrl cclistctrl;
	ccmymodo* ccmymodo1;
	threadmod* ccmythreadmod;
	myduimodo * ccmyduimodo;
	mywinmodo* ccmywinmodo;
	
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	//CString myctr;
	//afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton4();
	//afx_msg void OnBnClickedButton5();
	CString cpustr;
	CEdit myCpuEdit;
	bool bo = true;
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
    CString ctrpath=_T("");
	CString filestr;
	myCEdit myfileCEdit;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	//afx_msg void OnBnClickedButton5();
	myclearCE myclear;
	//CString mycleactr;
	afx_msg void OnEnChangeEdit2();
	CString myclearctring;
	bool KillProcess(DWORD pid);
	afx_msg void OnBnClickedButton5();
	CString mypidctr;
	afx_msg void OnEnChangeEdit5();
	CString mypidheap;
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton17();
	//��� 
	mysoftware* ccmysoftware;
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton20();
	//����
	myservice*  ccmyservice;
	CButton chawenjian;
	char* CMFCApplication2Dlg::UnicodeToAnsi(const wchar_t szStr);
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton23();
	//ɱ��
	char* md5=NULL;
	static std::vector<std::string> split(std::string str, std::string pattern);
	afx_msg void OnEnChangeEdit7();
	CString killpid;
	afx_msg void OnBnClickedButton24();
	afx_msg void OnBnClickedButton26();
	//PEdump
	PEdump* ccPEdump;
	afx_msg void OnBnClickedButton25();
	//�Ʋ�ɱ
	//Э��
	typedef struct _YUNSHA {
		int a;   //0�����  1������
		int namelen;
		char* name;  //·��
		int md5len;
		char* md5;   //md5ֵ
	} yun;
	yun shuju;
	afx_msg void OnBnClickedButton27();
	SOCKET sClient;
	sockaddr_in addrSer;
	afx_msg void OnBnClickedButton28();
	//ȫ·����ɱ
	void EnumLoad(TCHAR * load);
	afx_msg void OnBnClickedButton29();
	//�ж��Ƿ�Ϊroot
	bool IsAdmin(HANDLE hProcess);
	CButton btnroot;
	afx_msg void OnBnClickedButton30();
	//ע���ע��
	wstring GetParent(const std::wstring& FullPath);
	wstring GetExeDirectory();
	void StartInject();
	bool StartInsert(char *title, char *winclass, char *dllpath);
	HANDLE GetThePidOfTargetProcess(HWND hwnd);
	BOOL DoInjection(char *DllPath, HANDLE hProcess);
};
