// MFCLibrary1.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "MFCLibrary1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//extern "C"  void  Thetest(DWORD64 addr);
//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
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

// CMFCLibrary1App 构造

CMFCLibrary1App::CMFCLibrary1App()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CMFCLibrary1App 对象

CMFCLibrary1App theApp;


// CMFCLibrary1App 初始化
//盗版openpress
HANDLE WINAPI myOpenProcess(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId)
{

	HANDLE handle=NULL;

	if (mypid == NULL)
	{
		MessageBox(NULL, TEXT("被hook"), NULL, MB_OK);
		return handle;
	}
	else if (*mypid == dwProcessId)
	{

		dwDesiredAccess &= ~PROCESS_ALL_ACCESS;  //过虑权限
		
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
	//MessageBox(NULL, TEXT("注入成功！！！"), NULL, MB_OK);
	HMODULE hmodule = GetModuleHandle(_T("kernel32.dll"));
	//获取的原来openpress函数地址
	SIZE_T oldopenpress = (SIZE_T)GetProcAddress(hmodule, "OpenProcess");

	SIZE_T size;
	SIZE_T	dwWrite = 0;
	// 4. 先将盗版openpress路径写入到新开的内存空间中
	//求偏移 
	SIZE_T offset =(SIZE_T)myOpenProcess - (SIZE_T)oldopenpress - 5;
	DWORD oldProtect;
	//先修改属性
	VirtualProtect((void*)oldopenpress, 7, PAGE_EXECUTE_READWRITE, &oldProtect);
	//
	//memset((BYTE*)oldopenpress, 0x90, 6);

	hMap=OpenFileMappingA(FILE_MAP_READ, false, "hook");

	mypid=(DWORD *)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);


	//构造跳转
	newbyte[0] = 0xe9;
	*(DWORD *)(newbyte + 1) = offset;
	//复制函数前5个字节
	memcpy(oldbyte, (void *)oldopenpress, 5);
	//替换前5个字节
	memcpy((void *)oldopenpress, newbyte, 5);

	oldaddr = (void *)oldopenpress;


	return TRUE;
}
