#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// PEdump �Ի���

class PEdump : public CDialogEx
{
	DECLARE_DYNAMIC(PEdump)

public:
	PEdump(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PEdump();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEDUMP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl crichedit;
	afx_msg void OnBnClickedOk();
	void _openFile(HWND hWinMain);
	//��ؼ���׷������
	void _appendInfo(TCHAR * _lpsz);
	DWORD dwStop;
	OPENFILENAME stOF;
	HANDLE hFile, hMapFile;
	DWORD totalSize;		//�ļ���С
	LPVOID lpMemory;		//�ڴ�ӳ���ļ����ڴ����ʼλ��

	TCHAR szFileName[MAX_PATH] = { 0 };	//Ҫ�򿪵��ļ�·����������
	TCHAR bufTemp1[10];					//ÿ���ַ���ʮ�������ֽ���
	TCHAR bufTemp2[20];					//��һ��
	TCHAR lpServicesBuffer[100];		//һ�е���������
	TCHAR bufDisplay[50];				//������ASCII���ַ�
	DWORD dwCount;						//��������16�����¼�
	DWORD dwCount1;						//��ַ˳��
	DWORD dwBlanks;						//���һ�пո���
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
