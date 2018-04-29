#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// PEdump 对话框

class PEdump : public CDialogEx
{
	DECLARE_DYNAMIC(PEdump)

public:
	PEdump(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PEdump();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEDUMP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl crichedit;
	afx_msg void OnBnClickedOk();
	void _openFile(HWND hWinMain);
	//向控件中追加文体
	void _appendInfo(TCHAR * _lpsz);
	DWORD dwStop;
	OPENFILENAME stOF;
	HANDLE hFile, hMapFile;
	DWORD totalSize;		//文件大小
	LPVOID lpMemory;		//内存映像文件在内存的起始位置

	TCHAR szFileName[MAX_PATH] = { 0 };	//要打开的文件路径及名称名
	TCHAR bufTemp1[10];					//每个字符的十六进制字节码
	TCHAR bufTemp2[20];					//第一列
	TCHAR lpServicesBuffer[100];		//一行的所有内容
	TCHAR bufDisplay[50];				//第三列ASCII码字符
	DWORD dwCount;						//计数，逢16则重新计
	DWORD dwCount1;						//地址顺号
	DWORD dwBlanks;						//最后一行空格数
	HWND hWinEdit;
	CRichEditCtrl lordPE;
	void cclordPE(void* pe);
	CEdit jiexipe;
	CString strEdit;
	afx_msg void OnBnClickedButton1();
	//
	void myPE();
	DWORD RVAtoFOA(DWORD dwRVA);
	DWORD VAtoFOA(DWORD dwRVA);
	afx_msg void OnEnChangeEdit1();
};
