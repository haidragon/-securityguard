// PEdump.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "PEdump.h"
#include "afxdialogex.h"
#include <windows.h>
#include <Richedit.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<commdlg.h>
using namespace std;
DWORD dwFileSize;
BYTE* g_pFileImageBase = 0;
PIMAGE_NT_HEADERS g_pNt = 0;
// PEdump 对话框

IMPLEMENT_DYNAMIC(PEdump, CDialogEx)

PEdump::PEdump(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PEDUMP, pParent)
	, strEdit(_T(""))
{

}

PEdump::~PEdump()
{
}

void PEdump::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, crichedit);
	DDX_Control(pDX, IDC_RICHEDIT22, lordPE);
	DDX_Control(pDX, IDC_EDIT1, jiexipe);
	DDX_Text(pDX, IDC_EDIT1, strEdit);
}


BEGIN_MESSAGE_MAP(PEdump, CDialogEx)
	ON_BN_CLICKED(IDOK, &PEdump::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &PEdump::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &PEdump::OnEnChangeEdit1)
END_MESSAGE_MAP()


// PEdump 消息处理程序

//打开文件
void PEdump::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CDialogEx::OnOK();*/
	hWinEdit = this->crichedit;
	_openFile(this->m_hWnd);
}

void PEdump::_openFile(HWND hWinMain)
{
	//OPENFILENAME stOF;
	//HANDLE hFile, hMapFile;
	//DWORD totalSize;		//文件大小
	//LPVOID lpMemory;		//内存映像文件在内存的起始位置

	//TCHAR szFileName[MAX_PATH] = { 0 };	//要打开的文件路径及名称名
	//TCHAR bufTemp1[10];					//每个字符的十六进制字节码
	//TCHAR bufTemp2[20];					//第一列
	//TCHAR lpServicesBuffer[100];		//一行的所有内容
	//TCHAR bufDisplay[50];				//第三列ASCII码字符
	//DWORD dwCount;						//计数，逢16则重新计
	//DWORD dwCount1;						//地址顺号
	//DWORD dwBlanks;						//最后一行空格数

	TCHAR szExtPe[] = TEXT("PE Files\0*.exe;*.dll;*.scr;*.fon;*.drv\0All Files(*.*)\0*.*\0\0");


	RtlZeroMemory(&stOF, sizeof(stOF));
	stOF.lStructSize = sizeof(stOF);
	stOF.hwndOwner = hWinMain;
	stOF.lpstrFilter = szExtPe;
	stOF.lpstrFile = szFileName;
	stOF.nMaxFile = MAX_PATH;
	stOF.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&stOF))		//让用户选择打开的文件
	{
		hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			totalSize = GetFileSize(hFile, NULL);//获取文件大小
			if (totalSize)
			{
				hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);//内存映射文件
				if (hMapFile)
				{
					lpMemory = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);//获得文件在内存的映象起始位置
					if (lpMemory)
					{
						//开始处理文件

						//缓冲区初始化
						RtlZeroMemory(bufTemp1, 10);
						RtlZeroMemory(bufTemp2, 20);
						RtlZeroMemory(lpServicesBuffer, 100);
						RtlZeroMemory(bufDisplay, 50);

						dwCount = 1;

						//将第一列写入lpServicesBuffer
						dwCount1 = 0;
						wsprintf(bufTemp2, TEXT("%08x  "), dwCount1);
						lstrcat(lpServicesBuffer, bufTemp2);    //函数功能：该函数将一个字符串附加在另一个字符串后面。

						dwBlanks = (16 - totalSize % 16) * 3;//求最后一行的空格数

						while (TRUE)
						{
							if (totalSize == 0)//最后一行
							{
								while (dwBlanks)//填充空格
								{
									lstrcat(lpServicesBuffer, TEXT("#"));
									--dwBlanks;
								}

								lstrcat(lpServicesBuffer, TEXT("  "));//第二列与第三列中间的空格							
								lstrcat(lpServicesBuffer, bufDisplay);//第三列内容							
								lstrcat(lpServicesBuffer, TEXT("\n"));//回车换行符号
								break;
							}

							//翻译成可以显示的ascii码字,写入第三列的值
							if (*(char *)lpMemory > 0x20 && *(char *)lpMemory < 0x7e)
							{
								bufDisplay[dwCount - 1] = (TCHAR)*(char *)lpMemory;
							}
							else
							{
								bufDisplay[dwCount - 1] = (TCHAR)0x2e;//如果不是ASCII码值，则显示“.”
							}
							wsprintf(bufTemp1, TEXT("%02X   "), *(BYTE *)lpMemory);//字节的十六进制字符串到@bufTemp1中							
							lstrcat(lpServicesBuffer, bufTemp1);//将第二列写入lpServicesBuffer

							if (dwCount == 16)//已到16个字节，
							{
								lstrcat(lpServicesBuffer, TEXT("  "));//第二列与第三列中间的空格
								lstrcat(lpServicesBuffer, bufDisplay);//显示第三列字符 
								lstrcat(lpServicesBuffer, TEXT("\n"));//回车换行

								_appendInfo(lpServicesBuffer);//写入内容
								CString str;
								str.Format(_T("%s"), lpServicesBuffer);
								//MessageBox(str);
								RtlZeroMemory(lpServicesBuffer, 100);

								if (dwStop == 1)
								{
									break;
								}

								wsprintf(bufTemp2, TEXT("%08X  "), (++dwCount1) * 16); // 显示下一行的地址
								lstrcat(lpServicesBuffer, bufTemp2);
								dwCount = 0;
								RtlZeroMemory(bufDisplay, 50);
							}
							--totalSize;
							++dwCount;
							//++(TCHAR *)lpMemory;
							lpMemory = (char *)lpMemory + 1;

						}

						_appendInfo(lpServicesBuffer); //添加最后一行
						UnmapViewOfFile(lpMemory);
					}
					CloseHandle(hMapFile);
				}
			}
			CloseHandle(hFile);
		}
	}
}
//追加到最后
void PEdump::_appendInfo(TCHAR * _lpsz)
{
	CHARRANGE stCR;
	int iTextLength;

	iTextLength = ::GetWindowTextLength(hWinEdit);
	stCR.cpMin = iTextLength;
	stCR.cpMax = iTextLength;

	::SendMessage(hWinEdit, EM_EXSETSEL, 0, (LPARAM)&stCR);
	::SendMessage(hWinEdit, EM_REPLACESEL, FALSE, (LPARAM)_lpsz);
}
//解析pe
void PEdump::cclordPE(void * pe)
{

}

//rva转foa
DWORD PEdump::RVAtoFOA(DWORD dwRVA)
{
	//此RVA落在哪个区段中
	//找到所在区段后，
	//减去所在区段的起始位置，加上在文件中的起始位置
	//大文件头中找区段数
	int nCountOfSection = g_pNt->FileHeader.NumberOfSections;
	//区段表头
	PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(g_pNt);
	//在扩展头中找到块对齐数
	DWORD dwSecAligment = g_pNt->OptionalHeader.SectionAlignment;
	//循环
	for (int i = 0; i < nCountOfSection; i++)
	{
		//求在内存中的真实大小
		//Misc.VirtualSize % dwSecAligment如果是0代表刚好对齐否则就先对齐（非0就是真）
		//Misc.VirtualSize / dwSecAligment * dwSecAligment   + dwSecAligment     //最后加上余数的对齐
		DWORD dwRealVirSize = pSec->Misc.VirtualSize % dwSecAligment ?
			pSec->Misc.VirtualSize / dwSecAligment * dwSecAligment + dwSecAligment
			: pSec->Misc.VirtualSize;
		//区段中的相对虚拟地址转文件偏移  思路是 用要转换的地址与各个区
		//段起始地址做比较如果落在一个区段中（大于起始地址小于起始地址加区段最大偏移和），
		//就用要转换的相对虚拟地址减去区段的起始地址的相对虚拟地址，
		//得到了这个地址相对这个区段偏移，再用得到的这个偏移加上区段在文件中的偏移的起始位置
		//（pointerToRawData字段)就是他在文件中的文件偏移
		if (dwRVA >= pSec->VirtualAddress &&
			dwRVA < pSec->VirtualAddress + dwRealVirSize)
		{
			//FOA = RVA - 内存中区段的起始位置 + 在文件中区段的起始位置 
			return dwRVA - pSec->VirtualAddress + pSec->PointerToRawData;
		}
		//下一个区段地址
		pSec++;
	}
}
DWORD PEdump::VAtoFOA(DWORD dwVA) {
	//此RVA落在哪个区段中
	//找到所在区段后，
	//减去所在区段的起始位置，加上在文件中的起始位置
	//大文件头中找区段数
	int nCountOfSection = g_pNt->FileHeader.NumberOfSections;
	//区段表头
	PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(g_pNt);
	//在扩展头中找到块对齐数
	DWORD dwSecAligment = g_pNt->OptionalHeader.SectionAlignment;
	//循环
	for (int i = 0; i < nCountOfSection; i++)
	{
		//求在内存中的真实大小
		//Misc.VirtualSize % dwSecAligment如果是0代表刚好对齐否则就先对齐（非0就是真）
		//Misc.VirtualSize / dwSecAligment * dwSecAligment   + dwSecAligment     //最后加上余数的对齐
		DWORD dwRealVirSize = pSec->Misc.VirtualSize % dwSecAligment ?
			pSec->Misc.VirtualSize / dwSecAligment * dwSecAligment + dwSecAligment
			: pSec->Misc.VirtualSize;
		//区段中的相对虚拟地址转文件偏移  思路是 用要转换的地址与各个区
		//段起始地址做比较如果落在一个区段中（大于起始地址小于起始地址加区段最大偏移和），
		//就用要转换的相对虚拟地址减去区段的起始地址的相对虚拟地址，
		//得到了这个地址相对这个区段偏移，再用得到的这个偏移加上区段在文件中的偏移的起始位置
		//（pointerToRawData字段)就是他在文件中的文件偏移
		if (dwVA >= pSec->VirtualAddress &&
			dwVA <= pSec->VirtualAddress + dwRealVirSize)
		{
			//FOA = RVA - 内存中区段的起始位置 + 在文件中区段的起始位置 
			return dwVA - pSec->VirtualAddress + pSec->PointerToRawData;
		}
		//下一个区段地址
		pSec++;
	}
}
void PEdump::myPE() {
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
	TCHAR szExtPe[] = TEXT("PE Files\0*.exe;*.dll;*.scr;*.fon;*.drv\0All Files(*.*)\0*.*\0\0");
	RtlZeroMemory(&stOF, sizeof(stOF));
	stOF.lStructSize = sizeof(stOF);
//	stOF.hwndOwner = hWinMain;
	stOF.lpstrFilter = szExtPe;
	stOF.lpstrFile = szFileName;
	stOF.nMaxFile = MAX_PATH;
	stOF.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&stOF))		//让用户选择打开的文件
	{
		hFile = CreateFile((LPCWSTR)szFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
		//如果是无效的句柄
		if (hFile == INVALID_HANDLE_VALUE) {
			printf("文件打开失败\n");
			return;
		}
		//获取文件大小
		dwFileSize = GetFileSize(hFile, NULL);
		g_pFileImageBase = new BYTE[dwFileSize]{};
		DWORD dwRead;
		//将文件读取到内存中
		bool bRet = ReadFile(hFile, g_pFileImageBase, dwFileSize, &dwRead, NULL);
		//如果读取失败就返回
		if (!bRet)
		{
			delete[] g_pFileImageBase;
		}
		//关闭句柄
		CloseHandle(hFile);
		/////////////////////////////////dos头///////////////////////////////////////////////
		//typedef struct _IMAGE_DOS_HEADER {      // DOS .EXE header
		//	WORD   e_magic;                     // Magic number
		//	WORD   e_cblp;                      // Bytes on last page of file
		//	WORD   e_cp;                        // Pages in file
		//	WORD   e_crlc;                      // Relocations
		//	WORD   e_cparhdr;                   // Size of header in paragraphs
		//	WORD   e_minalloc;                  // Minimum extra paragraphs needed
		//	WORD   e_maxalloc;                  // Maximum extra paragraphs needed
		//	WORD   e_ss;                        // Initial (relative) SS value
		//	WORD   e_sp;                        // Initial SP value
		//	WORD   e_csum;                      // Checksum
		//	WORD   e_ip;                        // Initial IP value
		//	WORD   e_cs;                        // Initial (relative) CS value
		//	WORD   e_lfarlc;                    // File address of relocation table
		//	WORD   e_ovno;                      // Overlay number
		//	WORD   e_res[4];                    // Reserved words
		//	WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
		//	WORD   e_oeminfo;                   // OEM information; e_oemid specific
		//	WORD   e_res2[10];                  // Reserved words
		//	LONG   e_lfanew;                    // File address of new exe header
		//} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;
		/////////////////////////////////dos头///////////////////////////////////////////////
		//使用PIMAGE_DOS_HEADER（占64字节）解释前64个字节
		PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)g_pFileImageBase;
		//判断PE文件的标识是否正确，有一个不对，那么它就不是PE文件
		if (pDos->e_magic != IMAGE_DOS_SIGNATURE)//0x5A4D('MZ')
		{
			return;
		}
		CString str;
		str.Format(L"---------------------------DOS头（_IMAGE_DOS_HEADER）------------------------------- \r\n");
		//this->strEdit = str;
		this->jiexipe.SetSel(-1,-1);
		this->jiexipe.ReplaceSel(str);
		//str.Format(L"WORD   e_magic:     %2X\r\n", pDos->e_magic);
		////this->strEdit = str;
		//this->jiexipe.SetSel(-1,-1);
		//this->jiexipe.ReplaceSel(str);
		//str.Format(L"WORD   e_cblp:      %2X\r\n", pDos->e_cblp); 
		//this->jiexipe.SetSel(-1);
		//this->jiexipe.ReplaceSel(str);
		cout << hex << "WORD   e_cp:        " << pDos->e_cp << endl;
		cout << hex << "WORD   e_cblp:      " << pDos->e_cblp << endl;
		cout << hex << "WORD   e_cparhdr:   " << pDos->e_cparhdr << endl;
		cout << hex << "WORD   e_minalloc:  " << pDos->e_minalloc << endl;
		cout << hex << "WORD   e_ss:        " << pDos->e_ss << endl;
		cout << hex << "WORD   e_sp:        " << pDos->e_sp << endl;
		cout << hex << "WORD   e_csum:      " << pDos->e_csum << endl;
		cout << hex << "WORD   e_ip:        " << pDos->e_ip << endl;
		cout << hex << "WORD   e_cs:        " << pDos->e_cs << endl;
		cout << hex << "WORD   e_lfarlc:    " << pDos->e_lfarlc << endl;
		cout << hex << "WORD   e_ovno:      " << pDos->e_ovno << endl;
		cout << hex << "WORD   e_res[4]:    " << *(pDos->e_res) << endl;
		cout << hex << "WORD   e_oemid:     " << pDos->e_oemid << endl;
		cout << hex << "WORD   e_oeminfo:   " << pDos->e_oeminfo << endl;
		cout << hex << "WORD   e_res2[10]:  " << *(pDos->e_res2) << endl;
		cout << hex << "WORD   e_lfanew:    " << pDos->e_lfanew << endl;

		/////////////////////////////////NT头///////////////////////////////////////////////

		/*typedef struct _IMAGE_NT_HEADERS {
		DWORD Signature;
		IMAGE_FILE_HEADER FileHeader;
		IMAGE_OPTIONAL_HEADER32 OptionalHeader;
		} IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;*/
		g_pNt = (PIMAGE_NT_HEADERS)(pDos->e_lfanew + g_pFileImageBase);
		if (g_pNt->Signature != IMAGE_NT_SIGNATURE)//0x00004550('PE')
		{
			return;
		}
		TCHAR szMsg[] = TEXT("文件名：%s\r\n"
			"-----------------------------------------\n\n\r\n"
			"运行平台：      0x%04x  (014c:Intel 386   014dh:Intel 486  014eh:Intel 586)\r\n"
			"节的数量：      %d\r\n"
			"文件属性：      0x%04x  (大尾-禁止多处理器-DLL-系统文件-禁止网络运行-禁止优盘运行-无调试-32位-小尾-X-X-X-无符号-无行-可执行-无重定位)\r\n"
			"建议装入基地址：  0x%08x\n"
			"文件执行入口(RVA地址)：  0x%04x\n\r\n");
		TCHAR szBuffer[1024];
		PIMAGE_NT_HEADERS pImageNtHeaders = (PIMAGE_NT_HEADERS)g_pNt;
		wsprintf(szBuffer, szMsg, szFileName, pImageNtHeaders->FileHeader.Machine,
			pImageNtHeaders->FileHeader.NumberOfSections, pImageNtHeaders->FileHeader.Characteristics,
			pImageNtHeaders->OptionalHeader.ImageBase, pImageNtHeaders->OptionalHeader.AddressOfEntryPoint);
		str.Format(L"%s\r\n", szBuffer);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		PIMAGE_FILE_HEADER mytmf = &(g_pNt->FileHeader);
		str.Format(_T("---------------------------FILE头（IMAGE_FILE_HEADER ）----------------------------- "));
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		cout << hex << "WORD    Machine;                              " << mytmf->Machine << endl;
		cout << hex << "WORD    NumberOfSections;                     " << mytmf->NumberOfSections << endl;
		cout << hex << "DWORD   TimeDateStamp;                        " << mytmf->TimeDateStamp << endl;
		cout << hex << "DWORD   PointerToSymbolTable;                 " << mytmf->PointerToSymbolTable << endl;
		cout << hex << "DWORD   NumberOfSymbols;                      " << mytmf->NumberOfSymbols << endl;
		cout << hex << "WORD    SizeOfOptionalHeader;                 " << mytmf->SizeOfOptionalHeader << endl;
		cout << hex << "WORD    Characteristics;                      " << mytmf->Characteristics << endl;
	
		PIMAGE_OPTIONAL_HEADER myoption = &(g_pNt->OptionalHeader);
		cout << "----------------------------扩展头（PIMAGE_OPTIONAL_HEADER32 ）----------------------------------------------------- " << endl;

		cout << "---------------------------------------Standard fields.------------------------------------------------------------- " << endl;
		cout << hex << "WORD    Magic;                                     " << myoption->Magic << endl;
		cout << hex << "BYTE    MajorLinkerVersion;                        " << myoption->MajorLinkerVersion << endl;
		cout << hex << "BYTE    MinorLinkerVersion;                        " << myoption->MinorLinkerVersion << endl;
		cout << hex << "DWORD   SizeOfCode;                                " << myoption->SizeOfCode << endl;
		cout << hex << "DWORD   SizeOfInitializedData;                     " << myoption->SizeOfInitializedData << endl;
		cout << hex << "DWORD   SizeOfUninitializedData;                   " << myoption->SizeOfUninitializedData << endl;
		cout << hex << "DWORD   AddressOfEntryPoint;                       " << myoption->AddressOfEntryPoint << endl;
		str.Format(_T("入口点（OEP）;               %8X\r\n"), myoption->AddressOfEntryPoint);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		cout << hex << "DWORD   BaseOfCode;                                " << myoption->BaseOfCode << endl;
		str.Format(_T("起始代码基址（RVA);                    %8X\r\n"), myoption->BaseOfCode);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
	/*	cout << hex << "DWORD   BaseOfData;                                " << myoption->BaseOfData << endl;
		str.Format(_T("起始数据基址（RVA);                    %8X\r\n"), myoption->BaseOfData);*/
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		cout << "----------------------------------------- NT additional fields.----------------------------------------------------- " << endl;
		cout << hex << "DWORD   ImageBase;                                 " << myoption->ImageBase << endl;
		str.Format(_T("镜像基址;                               %8X\r\n"), myoption->ImageBase);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		cout << hex << "DWORD   SectionAlignment;                          " << myoption->SectionAlignment << endl;
		cout << hex << "DWORD   FileAlignment;                             " << myoption->FileAlignment << endl;
		cout << hex << "WORD    MajorOperatingSystemVersion;               " << myoption->MajorOperatingSystemVersion << endl;
		cout << hex << "WORD    MinorOperatingSystemVersion;               " << myoption->MinorOperatingSystemVersion << endl;
		cout << hex << "WORD    MajorImageVersion;                         " << myoption->MajorImageVersion << endl;
		cout << hex << "DWORD   SectionAlignment;                          " << myoption->SectionAlignment << endl;
		cout << hex << "WORD    MinorImageVersion;                         " << myoption->MinorImageVersion << endl;
		cout << hex << "WORD    MajorSubsystemVersion;                     " << myoption->MajorSubsystemVersion << endl;
		cout << hex << "WORD    MinorSubsystemVersion;                     " << myoption->MinorSubsystemVersion << endl;
		cout << hex << "DWORD   Win32VersionValue;                         " << myoption->Win32VersionValue << endl;
		cout << hex << "DWORD   SizeOfImage;                               " << myoption->SizeOfImage << endl;
		cout << hex << "DWORD   SizeOfHeaders;                             " << myoption->SizeOfHeaders << endl;
		cout << hex << "DWORD   CheckSum;                                  " << myoption->CheckSum << endl;
		cout << hex << "WORD    Subsystem;                                 " << myoption->Subsystem << endl;
		cout << hex << "WORD    DllCharacteristics;                        " << myoption->DllCharacteristics << endl;
		cout << hex << "DWORD   SizeOfStackReserve;                        " << myoption->SizeOfStackReserve << endl;
		cout << hex << "DWORD   SizeOfStackCommit;                         " << myoption->SizeOfStackCommit << endl;
		cout << hex << "DWORD   SizeOfHeapReserve;                         " << myoption->SizeOfHeapReserve << endl;
		cout << hex << "DWORD   SizeOfHeapCommit;                          " << myoption->SizeOfHeapCommit << endl;
		cout << hex << "DWORD   LoaderFlags;                               " << myoption->LoaderFlags << endl;
		cout << hex << "DWORD   NumberOfRvaAndSizes;                       " << myoption->NumberOfRvaAndSizes << endl;
		cout << hex << "IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];" << &(myoption->DataDirectory) << endl;
		//数据目录表
		str.Format(_T("-------------------------------------------数据目录信息-------------------------------------\r\n"));
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("导出表基址;                               %8X\r\n"), g_pNt->OptionalHeader.DataDirectory[0].VirtualAddress);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("导出表大小;                               %d\r\n"), g_pNt->OptionalHeader.DataDirectory[0].Size);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		str.Format(_T("导出入基址;                                %8X\r\n"), g_pNt->OptionalHeader.DataDirectory[1].VirtualAddress);
		this->jiexipe.SetSel(-1); 
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("导出入大小;                                %d\r\n"), g_pNt->OptionalHeader.DataDirectory[1].Size);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		str.Format(_T("资源表基址;                                %8X\r\n"), g_pNt->OptionalHeader.DataDirectory[2].VirtualAddress);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("资源表大小;                                %d\r\n"), g_pNt->OptionalHeader.DataDirectory[2].Size);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		str.Format(_T("异常表基址;                                %8X\r\n"), g_pNt->OptionalHeader.DataDirectory[3].VirtualAddress);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("异常表大小;                                %d\r\n"), g_pNt->OptionalHeader.DataDirectory[3].Size);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		str.Format(_T("重定位表基址;                               %8X\r\n"), g_pNt->OptionalHeader.DataDirectory[5].VirtualAddress);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("重定位表大小;                               %d\r\n"), g_pNt->OptionalHeader.DataDirectory[5].Size);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		str.Format(_T("TLS表基址;                                  %8X\r\n"), g_pNt->OptionalHeader.DataDirectory[9].VirtualAddress);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("TLS表大小;                                  %d\r\n"), g_pNt->OptionalHeader.DataDirectory[9].Size);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		str.Format(_T("导入地址表基址;                             %8X\r\n"), g_pNt->OptionalHeader.DataDirectory[12].VirtualAddress);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("导入地址表大小;                             %d\r\n"), g_pNt->OptionalHeader.DataDirectory[12].Size);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		/////////////////////////////////////////////所有节表头////////////////////////////////////////////////////
		//所有区表头都在一起
		//大文件头中找区段数
		int nCountOfSection = g_pNt->FileHeader.NumberOfSections;
		//取第一个区表头
		PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(g_pNt);
		TCHAR szMsgSec[] = TEXT("---------------------------------------------------------------------------------\n"
			"节的属性参考：\r\n"
			"  00000020h  包含代码\r\n"
			"  00000040h  包含已经初始化的数据，如.const\r\n"
			"  00000080h  包含未初始化数据，如 .data?\r\n"
			"  02000000h  数据在进程开始以后被丢弃，如.reloc\r\n"
			"  04000000h  节中数据不经过缓存\r\n"
			"  08000000h  节中数据不会被交换到磁盘\r\n"
			"  10000000h  数据将被不同进程共享\r\n"
			"  20000000h  可执行\r\n"
			"  40000000h  可读\r\n"
			"  80000000h  可写\r\n"
			"常见的代码节一般为：60000020h,数据节一般为：c0000040h，常量节一般为：40000040h\r\n"
			"---------------------------------------------------------------------------------\n\n\r\n"
			"节的名称  未对齐前真实长度  内存中的偏移(对齐后的) 文件中对齐后的长度 文件中的偏移  节的属性\r\n"
			"---------------------------------------------------------------------------------------------\r\n");
		str.Format(L"%s\r\n", szMsgSec);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		
		//循环
		TCHAR szBuffer2[1024];
		TCHAR szSecName[16];
		TCHAR szFmtSec[] = TEXT("%s     %08x         %08x              %08x           %08x     %08x\n\n\r\n");
		for (int i = 0; i < nCountOfSection; i++)
		{
			//获取节的名称，注意长度为8的名称并不以0结尾
			//RtlZeroMemory(szSecName, sizeof(szSecName));
			//for (int i = 0; i < 8; ++i)
			//{
			//	if (pSec->Name[i])
			//	{
			//		szSecName[i] = pSec->Name[i];
			//	}
			//	else
			//	{
			//		szSecName[i] ='    ';//如果名称为0，则显示为空格
			//	}
			//}
			//获取节的主要信息
			/*wsprintf(szBuffer2, szFmtSec, CStringW(pSec->Name), pSec->Misc.VirtualSize,
				pSec->VirtualAddress, pSec->SizeOfRawData,
				pSec->PointerToRawData, pSec->Characteristics);*/
			str.Format(_T("%s     %08x         %08x              %08x           %08x     %08x\n\n\r\n"), 
				CStringW(pSec->Name), pSec->Misc.VirtualSize,
				pSec->VirtualAddress, pSec->SizeOfRawData,
				pSec->PointerToRawData, pSec->Characteristics);
			this->jiexipe.SetSel(-1);
			this->jiexipe.ReplaceSel(str);
		
			//下一个区表头首地址
			++pSec;
		}
		/////////////////////////////////////////////导出表///////////////////////////////////////////////////////////
		//typedef struct _IMAGE_EXPORT_DIRECTORY {
		//	DWORD   Characteristics;
		//	DWORD   TimeDateStamp;
		//	WORD    MajorVersion;
		//	WORD    MinorVersion;
		//	DWORD   Name;
		//	DWORD   Base;
		//	DWORD   NumberOfFunctions;
		//	DWORD   NumberOfNames;
		//	DWORD   AddressOfFunctions;     // RVA from base of image
		//	DWORD   AddressOfNames;         // RVA from base of image
		//	DWORD   AddressOfNameOrdinals;  // RVA from base of image
		//} IMAGE_EXPORT_DIRECTORY, *PIMAGE_EXPORT_DIRECTORY;
		//找到导出表  也就是第一个表下标为0
		DWORD dwExportRVA = g_pNt->OptionalHeader.DataDirectory[0].VirtualAddress;
		//获取在文件中的位置
		PIMAGE_EXPORT_DIRECTORY pExport = (PIMAGE_EXPORT_DIRECTORY)(RVAtoFOA(dwExportRVA) + g_pFileImageBase);
		//模块名字
		char* pName = (char*)(RVAtoFOA(pExport->Name) + g_pFileImageBase);
		printf("%s\r\n", pName);
		str.Format(_T("%s\r\n"), CStringW(pName));
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		//地址表中的个数
		DWORD dwCountOfFuntions = pExport->NumberOfFunctions;
		//名称表中的个数
		DWORD dwCountOfNames = pExport->NumberOfNames;
		//地址表地址
		PDWORD pAddrOfFuntion = (PDWORD)(RVAtoFOA(pExport->AddressOfFunctions) + g_pFileImageBase);
		//名称表地址
		PDWORD pAddrOfName = (PDWORD)(RVAtoFOA(pExport->AddressOfNames) + g_pFileImageBase);
		//序号表地址
		PWORD pAddrOfOrdial = (PWORD)(RVAtoFOA(pExport->AddressOfNameOrdinals) + g_pFileImageBase);
		//base值
		DWORD dwBase = pExport->Base;
		//遍历地址表中的元素
		str.Format(L"-----------------------------------------导出表中的导出函数与导出序号-------------------------------------------------- \r\n");
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		if (dwExportRVA == 0) {
			//printf("没有导出表\n");
			str.Format(L"没有导出表\r\n");
			this->jiexipe.SetSel(-1);
			this->jiexipe.ReplaceSel(str);
			//return;
		}
		else {
			for (int i = 0; i < dwCountOfFuntions;i++)
			{
				//地址表中可能存在无用的值（就是为0的值）
				if (pAddrOfFuntion[i] == 0)
				{
					continue;
				}
				//根据序号表中是否有值（地址表的下标值），
				//来判断是否是名称导出
				bool bRet = false;
				for (int j = 0; j < dwCountOfNames;j++)
				{
					//i为地址表下标j为序号表的下标（值为地址表下标）
					//判断是否在序号表中
					if (i == pAddrOfOrdial[j])
					{
						//因为序号表与名称表的位置一一对应
						//取出名称表中的名称地址RVA
						DWORD dwNameRVA = pAddrOfName[j];
						char* pFunName = (char*)(RVAtoFOA(dwNameRVA) + g_pFileImageBase);
						//printf("%04d  %s  0x%08x\n", i + dwBase, pFunName, pAddrOfFuntion[i]);
						str.Format(_T("%04d  %s  0x%08x\r\n"), i + dwBase, CStringW(pFunName), pAddrOfFuntion[i]);
						this->jiexipe.SetSel(-1);
						this->jiexipe.ReplaceSel(str);
						bRet = true;
						break;
					}
				}
				if (!bRet)
				{
					//序号表中没有，说明是以序号导出的
					//printf("%04d           %08X\n", i + dwBase, pAddrOfFuntion[i]);
					str.Format(_T("% 04d           %08X\r\n"), i + dwBase, pAddrOfFuntion[i]);
					this->jiexipe.SetSel(-1);
					this->jiexipe.ReplaceSel(str);
				}

			}
		}
		/////////////////////////////////////////////导出表///////////////////////////////////////////////////////////
		//typedef struct _IMAGE_IMPORT_DESCRIPTOR {
		//	union {
		//		DWORD   Characteristics;            // 0 for terminating null import descriptor
		//		DWORD   OriginalFirstThunk;         // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
		//	} DUMMYUNIONNAME;
		//	DWORD   TimeDateStamp;                  // 0 if not bound,
		//											// -1 if bound, and real date\time stamp
		//											//     in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
		//											// O.W. date/time stamp of DLL bound to (Old BIND)

		//	DWORD   ForwarderChain;                 // -1 if no forwarders
		//	DWORD   Name;
		//	DWORD   FirstThunk;                     // RVA to IAT (if bound this IAT has actual addresses)
		//} IMAGE_IMPORT_DESCRIPTOR;
		//typedef IMAGE_IMPORT_DESCRIPTOR UNALIGNED *PIMAGE_IMPORT_DESCRIPTOR;
		str.Format(L"-----------------------------------------导入表中的导入函数与导入模块--------------------------------------------------\r\n");
		//str.Format(L"没有导入表\r\n");
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		TCHAR szBuffer3[1024] = { 0 };
		//找到导入表  也就是第二个下标为1
		DWORD dwImpotRVA = g_pNt->OptionalHeader.DataDirectory[1].VirtualAddress;
		//在文件中的位置
		DWORD dwImportInFile = (DWORD)(RVAtoFOA(dwImpotRVA) + g_pFileImageBase);
		PIMAGE_IMPORT_DESCRIPTOR pImport = (PIMAGE_IMPORT_DESCRIPTOR)dwImportInFile;
		//遍历每一个导入表  通过最后一个为0作为判断条件
		if (dwImpotRVA == 0) {
			printf("没有导入表\n");
			str.Format(L"没有导入表\r\r\n");
			this->jiexipe.SetSel(-1);
			this->jiexipe.ReplaceSel(str);
			return;
		}
		else {
			while (pImport->Name)
			{
				//函数名称地址
				PIMAGE_THUNK_DATA pFirsThunk =
					(PIMAGE_THUNK_DATA)(RVAtoFOA(pImport->FirstThunk) + g_pFileImageBase);
				//导入库
				char* pName = (char*)(RVAtoFOA(pImport->Name) + g_pFileImageBase);
				TCHAR szMsgImport[] = TEXT("\n\n导入库：%s\r\n"
					"-----------------------------\n\r\n"
					"OriginalFirstThunk  %08x\r\n"
					"TimeDateStamp       %08x\r\n"
					"ForwarderChain      %08x\r\n"
					"FirstThunk          %08x\r\n"
					"-----------------------------\n\r\n");
				/*wsprintf(szBuffer3, szMsgImport, pName,
					pImport->OriginalFirstThunk, pImport->TimeDateStamp,
					pImport->ForwarderChain, pImport->FirstThunk);*/
				
				str.Format(_T("\n\n导入库：%s\r\n OriginalFirstThunk  %08x\r\n TimeDateStamp   %08x\r\n ForwarderChain     %08x\r\n FirstThunk           %08x\r\n -----------------------------\n\r\n"),
					CStringW(pName), pImport->OriginalFirstThunk,
					pImport->TimeDateStamp, pImport->ForwarderChain, pImport->FirstThunk);
				this->jiexipe.SetSel(-1);
				this->jiexipe.ReplaceSel(str);
				printf("导入模块名字%s\r\n", pName);
				//也是通过最后一个为0作为判断条件
				while (pFirsThunk->u1.AddressOfData)
				{
					//判断导入方式
					if (IMAGE_SNAP_BY_ORDINAL32(pFirsThunk->u1.AddressOfData))
					{
						//说明是序号导入(低16位是其序号)
						str.Format(_T("序号导入:\t\t%04X \r\n"), pFirsThunk->u1.Ordinal & 0xFFFF);
						this->jiexipe.SetSel(-1);
						this->jiexipe.ReplaceSel(str);
						//printf("\t\t%04X \n", pFirsThunk->u1.Ordinal & 0xFFFF);
					}
					else
					{
						//名称导入
						PIMAGE_IMPORT_BY_NAME pImportName =
							(PIMAGE_IMPORT_BY_NAME)(RVAtoFOA(pFirsThunk->u1.AddressOfData) + g_pFileImageBase);
						str.Format(_T("名称导入:\t\t%04X %s \r\n"), pImportName->Hint, CStringW(pImportName->Name));
						this->jiexipe.SetSel(-1);
						this->jiexipe.ReplaceSel(str);
						//printf("\t\t%04X %s \n", pImportName->Hint, pImportName->Name);
					}
					//
					pFirsThunk++;
				}
				pImport++;
			}
		}
		str.Format(L"--------------------------------------------------资源表--------------------------------------------------------------- \r\n");
		//str.Format(L"%s\n", pResName);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		//注意的是NameOffset偏移  OffsetToDirectory偏移  OffsetToData偏移都是资源表最开始的偏移
		//找到资源表
		DWORD dwResRVA =
			g_pNt->OptionalHeader.DataDirectory[2].VirtualAddress;
		DWORD dwResFOA = (DWORD)(RVAtoFOA(dwResRVA) + g_pFileImageBase);
		PIMAGE_RESOURCE_DIRECTORY pRes = (PIMAGE_RESOURCE_DIRECTORY)dwResFOA;
		//资源有三层 每一层都以一个PIMAGE_RESOURCE_DIRECTORY开头，之后跟数个
		//PIMAGE_RESOURCE_DIRECTORY_ENTRY结构，可以说第一层由一个PIMAGE_RESOURCE_DIRECTORY
		//与一个PIMAGE_RESOURCE_DIRECTORY_ENTRY结构体组成
		//第一层（种类）
		//种类个数
		DWORD dwCountOfResType =
			pRes->NumberOfIdEntries + pRes->NumberOfNamedEntries;

		for (int i = 0; i < dwCountOfResType;i++)
		{   //pRes代表PIMAGE_RESOURCE_DIRECTORY的首地址+1之后就是后面的PIMAGE_RESOURCE_DIRECTORY_ENTRY首地址
			PIMAGE_RESOURCE_DIRECTORY_ENTRY pResEntry =
				(PIMAGE_RESOURCE_DIRECTORY_ENTRY)(pRes + 1);
			//typedef struct _IMAGE_RESOURCE_DIRECTORY_ENTRY {
			//这个联合体说明资源叫什么  如果这种资源是已知的也就是微软定义的那么
			//联合体最高位为0也就是NameIsString成员为0这个时候整个四字节（union）代表着已知资源的类型，也就是ID起
			//作用  如果这种资源是未知是那么NameIsString的最高位为1 低31位指向一个name的结构体（PIMAGE_RESOURCE_DIR_STRING_U）偏移，也就是DWORD   Name;起作用
			//	union {
			//		struct {
			//			DWORD NameOffset : 31;
			//			DWORD NameIsString : 1;
			//		} DUMMYSTRUCTNAME;
			//		DWORD   Name;
			//		WORD    Id;
			//	} DUMMYUNIONNAME;
			//这个联合体说明资源在哪里
			//当DataIsDirectory字段为1时（也就是这个四字节最高位为1）说明这个联合体表示的地方是一个目录，OffsetToDirectory（低31位）表示具体有
			//多少个地方，这个些地方就是第二层
			//	union {
			//		DWORD   OffsetToData;
			//		struct {
			//			DWORD   OffsetToDirectory : 31;
			//			DWORD   DataIsDirectory : 1;
			//		} DUMMYSTRUCTNAME2;  
			//	} DUMMYUNIONNAME2;
			//} IMAGE_RESOURCE_DIRECTORY_ENTRY, *PIMAGE_RESOURCE_DIRECTORY_ENTRY;

			//判断这种资源是字符串还是ID
			if (pResEntry->NameIsString)
			{
				//如果是字符串，NameOffset保存的就是这个字符串的RVA
				//得到名字字符串的FOA
				DWORD dwName = (DWORD)((pResEntry->NameOffset) + (DWORD)pRes);
				//NameOffset所指向的结构体是IMAGE_RESOURCE_DIR_STRING_U类型
				//这里保存了字符串的长度和起始位置
				PIMAGE_RESOURCE_DIR_STRING_U pName = (PIMAGE_RESOURCE_DIR_STRING_U)dwName;
				//这里的字符串不是以0结尾的，所以需要拷贝出来加上‘\0’结尾后再打印
				WCHAR *pResName = new WCHAR[pName->Length + 1]{};
				memcpy(pResName, pName, (pName->Length) * sizeof(WCHAR));
				//因为是WCHAR，所以用wprintf
				//wprintf(L"%s\n", pResName);
				str.Format(_T("%s\r\n"), CStringW(pResName));
				this->jiexipe.SetSel(-1);
				this->jiexipe.ReplaceSel(str);
				//释放内存
				delete[] pResName;
			}
			else   //id
			{
				char* arryResType[] = { "", "鼠标指针（Cursor）", "位图（Bitmap）", "图标（Icon）", "菜单（Menu）"
					, "对话框（Dialog）", "字符串列表（String Table）", "字体目录（Font Directory）", "字体（Font）", "快捷键（Accelerators）"
					, "非格式化资源（Unformatted）", "消息列表（Message Table）", "鼠标指针组（Croup Cursor）", "", "图标组（Group Icon）", ""
					, "版本信息（Version Information）" };
				if (pResEntry->Id < 17)
				{
					str.Format(_T("arryResType[pResEntry->Id]  %s\r\n"), CStringW(arryResType[pResEntry->Id]));
					this->jiexipe.SetSel(-1);
					this->jiexipe.ReplaceSel(str);
					//printf("arryResType[pResEntry->Id]  %s\n", arryResType[pResEntry->Id]);
				}
				else
				{
					//printf("pResEntry->Id %04X\n", pResEntry->Id);
					str.Format(_T("pResEntry->Id %04X\r\n"), pResEntry->Id);
					this->jiexipe.SetSel(-1);
					this->jiexipe.ReplaceSel(str);
				}

				//判断是否有下一层（0个表示没有下一层）
				if (pResEntry->DataIsDirectory)
				{   //到了第二层相对结构体同样和上一层一样但是OffsetToDirectory就指向对三层了
					DWORD dwResSecond = (DWORD)pRes + pResEntry->OffsetToDirectory;
					PIMAGE_RESOURCE_DIRECTORY pResSecond = (PIMAGE_RESOURCE_DIRECTORY)dwResSecond;
					//第二层个数
					DWORD dwCountOfSecond =
						pResSecond->NumberOfIdEntries + pResSecond->NumberOfNamedEntries;
					//遍历每一个资源
					for (int iSecond = 0; iSecond < dwCountOfSecond;iSecond++)
					{
						PIMAGE_RESOURCE_DIRECTORY_ENTRY pResSecondEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(pResSecond + 1);

						//判断这种资源是字符串还是ID
						if (pResEntry->NameIsString)
						{
							//如果是字符串，NameOffset保存的就是这个字符串的RVA
							//得到名字字符串的FOA
							DWORD dwNameFOA = (DWORD)(RVAtoFOA(pResEntry->NameOffset) + g_pFileImageBase);
							//NameOffset所指向的结构体是IMAGE_RESOURCE_DIR_STRING_U类型
							//这里保存了字符串的长度和起始位置
							PIMAGE_RESOURCE_DIR_STRING_U pName = (PIMAGE_RESOURCE_DIR_STRING_U)dwNameFOA;
							//这里的字符串不是以0结尾的，所以需要拷贝出来加上‘\0’结尾后再打印
							WCHAR *pResName = new WCHAR[pName->Length + 1]{};
							memcpy(pResName, pName, (pName->Length) * sizeof(WCHAR));
							str.Format(_T("pResName %s\r\n"), CStringW(pResName));
							this->jiexipe.SetSel(-1);
							this->jiexipe.ReplaceSel(str);
							//wprintf(L"pResName %s\n", pResName);
							delete[] pResName;
						}
						else   //id
						{
							//printf("pResEntry->Id %04X\n", pResEntry->Id);
							str.Format(_T("pResEntry->Id %04X\r\n"), pResEntry->Id);
							this->jiexipe.SetSel(-1);
							this->jiexipe.ReplaceSel(str);
						}
						//判断有没有下一层
						//第三层  同样套路从第一个结构体开始找 到了OffsetToDirectory就是第三层了
						//这里要注意的是到了第三层这个IMAGE_RESOURCE_DIRECTORY_ENTRY结构体的第一个联合体就没用了
						//同时第二个联合体的DataIsDirectory为0没有下一层了 
						//通过OffsetToData字段找到资源结构体的偏移（指向_IMAGE_RESOURCE_DATA_ENTRY结构体）
						if (pResSecondEntry->DataIsDirectory)
						{
							//第三层的起始位置
							DWORD dwResThrid =
								(DWORD)pRes + pResSecondEntry->OffsetToDirectory;
							PIMAGE_RESOURCE_DIRECTORY pResThrid = (PIMAGE_RESOURCE_DIRECTORY)dwResThrid;

							PIMAGE_RESOURCE_DIRECTORY_ENTRY pResThridEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(pResThrid + 1);
							//第三层，已经是最后一层，使用PIMAGE_RESOURCE_DIRECTORY_ENTRY中的
							//OffsetToData成员，得到PIMAGE_RESOURCE_DATA_ENTRY结构的位置
							/*typedef struct _IMAGE_RESOURCE_DATA_ENTRY {
							DWORD   OffsetToData;   //资源偏移
							DWORD   Size;
							DWORD   CodePage;
							DWORD   Reserved;
							} IMAGE_RESOURCE_DATA_ENTRY, *PIMAGE_RESOURCE_DATA_ENTRY;
							*/
							PIMAGE_RESOURCE_DATA_ENTRY pResData =
								(PIMAGE_RESOURCE_DATA_ENTRY)(pResThridEntry->OffsetToData + (DWORD)pRes);
							//资源的RVA和Size
							DWORD dwResDataRVA = pResData->OffsetToData;
							DWORD dwResDataSize = pResData->Size;
							//PIMAGE_RESOURCE_DATA_ENTRY中的OffsetToData是个RVA
							DWORD dwResDataFOA = (DWORD)(RVAtoFOA(dwResDataRVA) + g_pFileImageBase);
							//资源的二进制数据
							//遍历打印资源的二进制数据  这里就只能是二进制了
							PBYTE pData = (PBYTE)dwResDataFOA;
							for (int iData = 0; iData < dwResDataSize; iData++)
							{
								if (iData % 16 == 0 && iData != 0)
								{
									//printf("\n");
									str.Format(L"\r\n");
									this->jiexipe.SetSel(-1);
									this->jiexipe.ReplaceSel(str);
								}
								//printf("%02X ", pData[iData]);
								str.Format(L"%02X ", pData[iData]);
								this->jiexipe.SetSel(-1);
								this->jiexipe.ReplaceSel(str);
							}
							//printf("\n");
							str.Format(L"\r\n");
							this->jiexipe.SetSel(-1);
							this->jiexipe.ReplaceSel(str);
						}
						//下一个资源
						pResSecondEntry++;
					}
				}
			}
			//下一种资源
			pResEntry++;
		}
		cout << "----------------------------------------------------重定位表------------------------------------------------------------ " << endl;
		str.Format(L"----------------------------------------------------重定位表------------------------------------------------------------- \r\n");
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		//因为代码用的是绝对地址因此要有定位表
		//当重定位发生时，只需要现在pe文件的加载基址，用现在的加载基址减去默认加载基址得到一个数，再用这个数加上需要重定位的数据即可，所以重定位
		//表中保存的只是需要重定位信息
		typedef struct _OFFSET_TYPE
		{
			WORD offset : 12; //本页的偏移量
			WORD type : 4;    //重定位类型（3）
		}OFFSET_TYPE, *POFFSET_TYPE;
		//重定位表RVA
		DWORD dwRelocRVA = g_pNt->OptionalHeader.DataDirectory[5].VirtualAddress;
		//是否为空
		if (!dwRelocRVA)
		{
			//printf("没有重定位表\n");
			str.Format(L"没有重定位表\r\n");
			this->jiexipe.SetSel(-1);
			this->jiexipe.ReplaceSel(str);
			return;
		}
		//重定位表在文件中的地址
		PIMAGE_BASE_RELOCATION pReloc = (PIMAGE_BASE_RELOCATION)(RVAtoFOA(dwRelocRVA) + g_pFileImageBase);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//循环重定位表
		//如果SizeOfBlock为0，说明没有需要重定位的数据了
		while (pReloc->SizeOfBlock)
		{
			//当前重定位页RVA
			//printf("%08X\n\n", pReloc->VirtualAddress);
			str.Format(L"%08X\n\r\n", pReloc->VirtualAddress);
			this->jiexipe.SetSel(-1);
			this->jiexipe.ReplaceSel(str);
			//这一页一共有多少个重定位块（即多少个需要重定位的数据）
			DWORD dwCount = (pReloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
			//指向重定位块地址
			POFFSET_TYPE pOffset = (POFFSET_TYPE)(pReloc + 1);
			//遍历每一个重定位块   
			for (int i = 0; i < dwCount;i++)
			{
				//在这一页中的位置地址RVA
				DWORD dwRelocDataRVA = pReloc->VirtualAddress + pOffset->offset;
				//转成FOA
				DWORD dwRelocDataFOA = (DWORD)(RVAtoFOA(dwRelocDataRVA) + g_pFileImageBase);
				//实际需要重定位的数据地址是个VA
				DWORD dwRealDataVA = *(DWORD*)dwRelocDataFOA;
				//转成RVA（这就是内存中的转换完成的相对地址了）
				DWORD dwRealDataRVA = dwRealDataVA - g_pNt->OptionalHeader.ImageBase;
				//再转FOA（RVA在文件中的地址）
				DWORD dwRealDataFOA = (DWORD)(RVAtoFOA(dwRealDataRVA) + g_pFileImageBase);
				//需要重定位的具体数据（字节数不确定）
				DWORD dwData = *(DWORD*)dwRealDataFOA;

				/*printf("需要重定位的第%d个数据 RVA：%08X  VA:%08X  DATA:%08X\n",
					i + 1, dwRelocDataRVA, dwRealDataVA, dwData);*/
				str.Format(L"需要重定位的第%d个数据 RVA：%08X  VA:%08X  DATA:%08X\r\n", i + 1, dwRelocDataRVA, dwRealDataVA, dwData);
				this->jiexipe.SetSel(-1);
				this->jiexipe.ReplaceSel(str);
				//下一个重定位数据位置
				pOffset++;
			}

			//下一页
			pReloc =
				(PIMAGE_BASE_RELOCATION)(pReloc->SizeOfBlock + (DWORD)pReloc);
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
		cout << "--------------------------------------------------线程表--------------------------------------------------------------- " << endl;
		str.Format(L"----------------------------------------------------线程表-------------------------------------------------------------- \r\n");
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		//找到线程表  001132A8  RVA 
		DWORD dwTLSsRVA = g_pNt->OptionalHeader.DataDirectory[9].VirtualAddress;
		//是否为空
		if (!dwTLSsRVA)
		{
			printf("没有表\n");
			str.Format(L"没有线程表\n\r\n");
			this->jiexipe.SetSel(-1);
			this->jiexipe.ReplaceSel(str);
			return;
		}
		//线程表在文件中的相对地址
		DWORD temp=RVAtoFOA(dwTLSsRVA); // 001120A8
		//PIMAGE_TLS_DIRECTORY pLTS = (PIMAGE_TLS_DIRECTORY)(RVAtoFOA(dwTLSsRVA) + g_pFileImageBase);
		//tls在文件中的绝对地址
		PIMAGE_TLS_DIRECTORY pLTS =(PIMAGE_TLS_DIRECTORY)((char*) g_pFileImageBase + temp);
		//回调表的地址这里是VA   0051A508
		PDWORD  callback=(PDWORD)pLTS->AddressOfCallBacks;
		//VA转文件地址 得到的是回调表的文件中的相对地址
		DWORD tempaddr = (DWORD)callback - 0x400000;
		//找到回调数组表中在文件中的相对地址
		DWORD TM=RVAtoFOA(tempaddr);
		//取到数组首地址在文件中的绝对地址
		DWORD *tempfaddr =(DWORD*)( (char*)(g_pFileImageBase)+ TM);
		//tempfaddr[0];
		int i=1;
		//循环遍历回调表中的函数地址
		while (*tempfaddr)
		{
			//callback[0];//0x43e410(va)  转 foa     //      ff0000
			tempfaddr[0];
			str.Format(_T("回调函数%d VA地址：%8X\r\n"), i, *tempfaddr);
			this->jiexipe.SetSel(-1);
			this->jiexipe.ReplaceSel(str);
			MessageBox(str);
			++tempfaddr;
			++i;
		}

		return;
	}

}
//解析pe
void PEdump::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//this->jiexipe.howScrollBar(SB_VERT, TRUE);
	myPE();
}
//pe解析框
void PEdump::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//UpdateData(false);
}
