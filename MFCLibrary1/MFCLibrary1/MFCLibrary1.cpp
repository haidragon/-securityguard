// MFCLibrary1.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "MFCLibrary1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//extern "C"  void  Thetest(DWORD64 addr);
//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CMFCLibrary1App

BEGIN_MESSAGE_MAP(CMFCLibrary1App, CWinApp)
END_MESSAGE_MAP()

HANDLE   hMap;
DWORD   *mypid;
unsigned char oldbyte[5];
unsigned char newbyte[5];
void *oldaddr;

using   pFun = HANDLE(WINAPI*)(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId);

// CMFCLibrary1App ����

CMFCLibrary1App::CMFCLibrary1App()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMFCLibrary1App ����

CMFCLibrary1App theApp;


// CMFCLibrary1App ��ʼ��
//����openpress
HANDLE WINAPI myOpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId)
{

	HANDLE handle=NULL;

	if (mypid == NULL)
	{
		MessageBox(NULL, TEXT("��hook"), NULL, MB_OK);
		return handle;
	}
	else if (*mypid == dwProcessId)
	{

		dwDesiredAccess &= ~PROCESS_ALL_ACCESS;  //����Ȩ��
		
	}
	
		memcpy(oldaddr, oldbyte, 5);
		handle=((pFun)(oldaddr))(dwDesiredAccess, bInheritHandle, dwProcessId);
		memcpy(oldaddr, newbyte, 5);
	
	//return OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);



	return  handle;
}

BOOL CMFCLibrary1App::InitInstance()
{
	CWinApp::InitInstance();
	//MessageBox(NULL, TEXT("ע��ɹ�������"), NULL, MB_OK);
	HMODULE hmodule = GetModuleHandle(_T("kernel32.dll"));
	//��ȡ��ԭ��openpress������ַ
	SIZE_T oldopenpress = (SIZE_T)GetProcAddress(hmodule, "OpenProcess");

	SIZE_T size;
	SIZE_T	dwWrite = 0;
	// 4. �Ƚ�����openpress·��д�뵽�¿����ڴ�ռ���
	//��ƫ�� 
	SIZE_T offset =(SIZE_T)myOpenProcess - (SIZE_T)oldopenpress - 5;
	DWORD oldProtect;
	//���޸�����
	VirtualProtect((void*)oldopenpress, 7, PAGE_EXECUTE_READWRITE, &oldProtect);
	//
	//memset((BYTE*)oldopenpress, 0x90, 6);

	hMap=OpenFileMappingA(FILE_MAP_READ, false, "hook");

	mypid=(DWORD *)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);


	//������ת
	newbyte[0] = 0xe9;
	*(DWORD *)(newbyte + 1) = offset;
	//���ƺ���ǰ5���ֽ�
	memcpy(oldbyte, (void *)oldopenpress, 5);
	//�滻ǰ5���ֽ�
	memcpy((void *)oldopenpress, newbyte, 5);

	oldaddr = (void *)oldopenpress;


	return TRUE;
}
