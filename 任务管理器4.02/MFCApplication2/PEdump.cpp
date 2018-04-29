// PEdump.cpp : ʵ���ļ�
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
// PEdump �Ի���

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


// PEdump ��Ϣ�������

//���ļ�
void PEdump::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*CDialogEx::OnOK();*/
	hWinEdit = this->crichedit;
	_openFile(this->m_hWnd);
}

void PEdump::_openFile(HWND hWinMain)
{
	//OPENFILENAME stOF;
	//HANDLE hFile, hMapFile;
	//DWORD totalSize;		//�ļ���С
	//LPVOID lpMemory;		//�ڴ�ӳ���ļ����ڴ����ʼλ��

	//TCHAR szFileName[MAX_PATH] = { 0 };	//Ҫ�򿪵��ļ�·����������
	//TCHAR bufTemp1[10];					//ÿ���ַ���ʮ�������ֽ���
	//TCHAR bufTemp2[20];					//��һ��
	//TCHAR lpServicesBuffer[100];		//һ�е���������
	//TCHAR bufDisplay[50];				//������ASCII���ַ�
	//DWORD dwCount;						//��������16�����¼�
	//DWORD dwCount1;						//��ַ˳��
	//DWORD dwBlanks;						//���һ�пո���

	TCHAR szExtPe[] = TEXT("PE Files\0*.exe;*.dll;*.scr;*.fon;*.drv\0All Files(*.*)\0*.*\0\0");


	RtlZeroMemory(&stOF, sizeof(stOF));
	stOF.lStructSize = sizeof(stOF);
	stOF.hwndOwner = hWinMain;
	stOF.lpstrFilter = szExtPe;
	stOF.lpstrFile = szFileName;
	stOF.nMaxFile = MAX_PATH;
	stOF.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&stOF))		//���û�ѡ��򿪵��ļ�
	{
		hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			totalSize = GetFileSize(hFile, NULL);//��ȡ�ļ���С
			if (totalSize)
			{
				hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);//�ڴ�ӳ���ļ�
				if (hMapFile)
				{
					lpMemory = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);//����ļ����ڴ��ӳ����ʼλ��
					if (lpMemory)
					{
						//��ʼ�����ļ�

						//��������ʼ��
						RtlZeroMemory(bufTemp1, 10);
						RtlZeroMemory(bufTemp2, 20);
						RtlZeroMemory(lpServicesBuffer, 100);
						RtlZeroMemory(bufDisplay, 50);

						dwCount = 1;

						//����һ��д��lpServicesBuffer
						dwCount1 = 0;
						wsprintf(bufTemp2, TEXT("%08x  "), dwCount1);
						lstrcat(lpServicesBuffer, bufTemp2);    //�������ܣ��ú�����һ���ַ�����������һ���ַ������档

						dwBlanks = (16 - totalSize % 16) * 3;//�����һ�еĿո���

						while (TRUE)
						{
							if (totalSize == 0)//���һ��
							{
								while (dwBlanks)//���ո�
								{
									lstrcat(lpServicesBuffer, TEXT("#"));
									--dwBlanks;
								}

								lstrcat(lpServicesBuffer, TEXT("  "));//�ڶ�����������м�Ŀո�							
								lstrcat(lpServicesBuffer, bufDisplay);//����������							
								lstrcat(lpServicesBuffer, TEXT("\n"));//�س����з���
								break;
							}

							//����ɿ�����ʾ��ascii����,д������е�ֵ
							if (*(char *)lpMemory > 0x20 && *(char *)lpMemory < 0x7e)
							{
								bufDisplay[dwCount - 1] = (TCHAR)*(char *)lpMemory;
							}
							else
							{
								bufDisplay[dwCount - 1] = (TCHAR)0x2e;//�������ASCII��ֵ������ʾ��.��
							}
							wsprintf(bufTemp1, TEXT("%02X   "), *(BYTE *)lpMemory);//�ֽڵ�ʮ�������ַ�����@bufTemp1��							
							lstrcat(lpServicesBuffer, bufTemp1);//���ڶ���д��lpServicesBuffer

							if (dwCount == 16)//�ѵ�16���ֽڣ�
							{
								lstrcat(lpServicesBuffer, TEXT("  "));//�ڶ�����������м�Ŀո�
								lstrcat(lpServicesBuffer, bufDisplay);//��ʾ�������ַ� 
								lstrcat(lpServicesBuffer, TEXT("\n"));//�س�����

								_appendInfo(lpServicesBuffer);//д������
								CString str;
								str.Format(_T("%s"), lpServicesBuffer);
								//MessageBox(str);
								RtlZeroMemory(lpServicesBuffer, 100);

								if (dwStop == 1)
								{
									break;
								}

								wsprintf(bufTemp2, TEXT("%08X  "), (++dwCount1) * 16); // ��ʾ��һ�еĵ�ַ
								lstrcat(lpServicesBuffer, bufTemp2);
								dwCount = 0;
								RtlZeroMemory(bufDisplay, 50);
							}
							--totalSize;
							++dwCount;
							//++(TCHAR *)lpMemory;
							lpMemory = (char *)lpMemory + 1;

						}

						_appendInfo(lpServicesBuffer); //������һ��
						UnmapViewOfFile(lpMemory);
					}
					CloseHandle(hMapFile);
				}
			}
			CloseHandle(hFile);
		}
	}
}
//׷�ӵ����
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
//����pe
void PEdump::cclordPE(void * pe)
{

}

//rvaתfoa
DWORD PEdump::RVAtoFOA(DWORD dwRVA)
{
	//��RVA�����ĸ�������
	//�ҵ��������κ�
	//��ȥ�������ε���ʼλ�ã��������ļ��е���ʼλ��
	//���ļ�ͷ����������
	int nCountOfSection = g_pNt->FileHeader.NumberOfSections;
	//���α�ͷ
	PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(g_pNt);
	//����չͷ���ҵ��������
	DWORD dwSecAligment = g_pNt->OptionalHeader.SectionAlignment;
	//ѭ��
	for (int i = 0; i < nCountOfSection; i++)
	{
		//�����ڴ��е���ʵ��С
		//Misc.VirtualSize % dwSecAligment�����0����պö��������ȶ��루��0�����棩
		//Misc.VirtualSize / dwSecAligment * dwSecAligment   + dwSecAligment     //�����������Ķ���
		DWORD dwRealVirSize = pSec->Misc.VirtualSize % dwSecAligment ?
			pSec->Misc.VirtualSize / dwSecAligment * dwSecAligment + dwSecAligment
			: pSec->Misc.VirtualSize;
		//�����е���������ַת�ļ�ƫ��  ˼·�� ��Ҫת���ĵ�ַ�������
		//����ʼ��ַ���Ƚ��������һ�������У�������ʼ��ַС����ʼ��ַ���������ƫ�ƺͣ���
		//����Ҫת������������ַ��ȥ���ε���ʼ��ַ����������ַ��
		//�õ��������ַ����������ƫ�ƣ����õõ������ƫ�Ƽ����������ļ��е�ƫ�Ƶ���ʼλ��
		//��pointerToRawData�ֶ�)���������ļ��е��ļ�ƫ��
		if (dwRVA >= pSec->VirtualAddress &&
			dwRVA < pSec->VirtualAddress + dwRealVirSize)
		{
			//FOA = RVA - �ڴ������ε���ʼλ�� + ���ļ������ε���ʼλ�� 
			return dwRVA - pSec->VirtualAddress + pSec->PointerToRawData;
		}
		//��һ�����ε�ַ
		pSec++;
	}
}
DWORD PEdump::VAtoFOA(DWORD dwVA) {
	//��RVA�����ĸ�������
	//�ҵ��������κ�
	//��ȥ�������ε���ʼλ�ã��������ļ��е���ʼλ��
	//���ļ�ͷ����������
	int nCountOfSection = g_pNt->FileHeader.NumberOfSections;
	//���α�ͷ
	PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(g_pNt);
	//����չͷ���ҵ��������
	DWORD dwSecAligment = g_pNt->OptionalHeader.SectionAlignment;
	//ѭ��
	for (int i = 0; i < nCountOfSection; i++)
	{
		//�����ڴ��е���ʵ��С
		//Misc.VirtualSize % dwSecAligment�����0����պö��������ȶ��루��0�����棩
		//Misc.VirtualSize / dwSecAligment * dwSecAligment   + dwSecAligment     //�����������Ķ���
		DWORD dwRealVirSize = pSec->Misc.VirtualSize % dwSecAligment ?
			pSec->Misc.VirtualSize / dwSecAligment * dwSecAligment + dwSecAligment
			: pSec->Misc.VirtualSize;
		//�����е���������ַת�ļ�ƫ��  ˼·�� ��Ҫת���ĵ�ַ�������
		//����ʼ��ַ���Ƚ��������һ�������У�������ʼ��ַС����ʼ��ַ���������ƫ�ƺͣ���
		//����Ҫת������������ַ��ȥ���ε���ʼ��ַ����������ַ��
		//�õ��������ַ����������ƫ�ƣ����õõ������ƫ�Ƽ����������ļ��е�ƫ�Ƶ���ʼλ��
		//��pointerToRawData�ֶ�)���������ļ��е��ļ�ƫ��
		if (dwVA >= pSec->VirtualAddress &&
			dwVA <= pSec->VirtualAddress + dwRealVirSize)
		{
			//FOA = RVA - �ڴ������ε���ʼλ�� + ���ļ������ε���ʼλ�� 
			return dwVA - pSec->VirtualAddress + pSec->PointerToRawData;
		}
		//��һ�����ε�ַ
		pSec++;
	}
}
void PEdump::myPE() {
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
	TCHAR szExtPe[] = TEXT("PE Files\0*.exe;*.dll;*.scr;*.fon;*.drv\0All Files(*.*)\0*.*\0\0");
	RtlZeroMemory(&stOF, sizeof(stOF));
	stOF.lStructSize = sizeof(stOF);
//	stOF.hwndOwner = hWinMain;
	stOF.lpstrFilter = szExtPe;
	stOF.lpstrFile = szFileName;
	stOF.nMaxFile = MAX_PATH;
	stOF.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&stOF))		//���û�ѡ��򿪵��ļ�
	{
		hFile = CreateFile((LPCWSTR)szFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
		//�������Ч�ľ��
		if (hFile == INVALID_HANDLE_VALUE) {
			printf("�ļ���ʧ��\n");
			return;
		}
		//��ȡ�ļ���С
		dwFileSize = GetFileSize(hFile, NULL);
		g_pFileImageBase = new BYTE[dwFileSize]{};
		DWORD dwRead;
		//���ļ���ȡ���ڴ���
		bool bRet = ReadFile(hFile, g_pFileImageBase, dwFileSize, &dwRead, NULL);
		//�����ȡʧ�ܾͷ���
		if (!bRet)
		{
			delete[] g_pFileImageBase;
		}
		//�رվ��
		CloseHandle(hFile);
		/////////////////////////////////dosͷ///////////////////////////////////////////////
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
		/////////////////////////////////dosͷ///////////////////////////////////////////////
		//ʹ��PIMAGE_DOS_HEADER��ռ64�ֽڣ�����ǰ64���ֽ�
		PIMAGE_DOS_HEADER pDos = (PIMAGE_DOS_HEADER)g_pFileImageBase;
		//�ж�PE�ļ��ı�ʶ�Ƿ���ȷ����һ�����ԣ���ô���Ͳ���PE�ļ�
		if (pDos->e_magic != IMAGE_DOS_SIGNATURE)//0x5A4D('MZ')
		{
			return;
		}
		CString str;
		str.Format(L"---------------------------DOSͷ��_IMAGE_DOS_HEADER��------------------------------- \r\n");
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

		/////////////////////////////////NTͷ///////////////////////////////////////////////

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
		TCHAR szMsg[] = TEXT("�ļ�����%s\r\n"
			"-----------------------------------------\n\n\r\n"
			"����ƽ̨��      0x%04x  (014c:Intel 386   014dh:Intel 486  014eh:Intel 586)\r\n"
			"�ڵ�������      %d\r\n"
			"�ļ����ԣ�      0x%04x  (��β-��ֹ�ദ����-DLL-ϵͳ�ļ�-��ֹ��������-��ֹ��������-�޵���-32λ-Сβ-X-X-X-�޷���-����-��ִ��-���ض�λ)\r\n"
			"����װ�����ַ��  0x%08x\n"
			"�ļ�ִ�����(RVA��ַ)��  0x%04x\n\r\n");
		TCHAR szBuffer[1024];
		PIMAGE_NT_HEADERS pImageNtHeaders = (PIMAGE_NT_HEADERS)g_pNt;
		wsprintf(szBuffer, szMsg, szFileName, pImageNtHeaders->FileHeader.Machine,
			pImageNtHeaders->FileHeader.NumberOfSections, pImageNtHeaders->FileHeader.Characteristics,
			pImageNtHeaders->OptionalHeader.ImageBase, pImageNtHeaders->OptionalHeader.AddressOfEntryPoint);
		str.Format(L"%s\r\n", szBuffer);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		PIMAGE_FILE_HEADER mytmf = &(g_pNt->FileHeader);
		str.Format(_T("---------------------------FILEͷ��IMAGE_FILE_HEADER ��----------------------------- "));
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
		cout << "----------------------------��չͷ��PIMAGE_OPTIONAL_HEADER32 ��----------------------------------------------------- " << endl;

		cout << "---------------------------------------Standard fields.------------------------------------------------------------- " << endl;
		cout << hex << "WORD    Magic;                                     " << myoption->Magic << endl;
		cout << hex << "BYTE    MajorLinkerVersion;                        " << myoption->MajorLinkerVersion << endl;
		cout << hex << "BYTE    MinorLinkerVersion;                        " << myoption->MinorLinkerVersion << endl;
		cout << hex << "DWORD   SizeOfCode;                                " << myoption->SizeOfCode << endl;
		cout << hex << "DWORD   SizeOfInitializedData;                     " << myoption->SizeOfInitializedData << endl;
		cout << hex << "DWORD   SizeOfUninitializedData;                   " << myoption->SizeOfUninitializedData << endl;
		cout << hex << "DWORD   AddressOfEntryPoint;                       " << myoption->AddressOfEntryPoint << endl;
		str.Format(_T("��ڵ㣨OEP��;               %8X\r\n"), myoption->AddressOfEntryPoint);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		cout << hex << "DWORD   BaseOfCode;                                " << myoption->BaseOfCode << endl;
		str.Format(_T("��ʼ�����ַ��RVA);                    %8X\r\n"), myoption->BaseOfCode);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
	/*	cout << hex << "DWORD   BaseOfData;                                " << myoption->BaseOfData << endl;
		str.Format(_T("��ʼ���ݻ�ַ��RVA);                    %8X\r\n"), myoption->BaseOfData);*/
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		cout << "----------------------------------------- NT additional fields.----------------------------------------------------- " << endl;
		cout << hex << "DWORD   ImageBase;                                 " << myoption->ImageBase << endl;
		str.Format(_T("�����ַ;                               %8X\r\n"), myoption->ImageBase);
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
		//����Ŀ¼��
		str.Format(_T("-------------------------------------------����Ŀ¼��Ϣ-------------------------------------\r\n"));
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("�������ַ;                               %8X\r\n"), g_pNt->OptionalHeader.DataDirectory[0].VirtualAddress);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("�������С;                               %d\r\n"), g_pNt->OptionalHeader.DataDirectory[0].Size);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		str.Format(_T("�������ַ;                                %8X\r\n"), g_pNt->OptionalHeader.DataDirectory[1].VirtualAddress);
		this->jiexipe.SetSel(-1); 
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("�������С;                                %d\r\n"), g_pNt->OptionalHeader.DataDirectory[1].Size);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		str.Format(_T("��Դ���ַ;                                %8X\r\n"), g_pNt->OptionalHeader.DataDirectory[2].VirtualAddress);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("��Դ���С;                                %d\r\n"), g_pNt->OptionalHeader.DataDirectory[2].Size);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		str.Format(_T("�쳣���ַ;                                %8X\r\n"), g_pNt->OptionalHeader.DataDirectory[3].VirtualAddress);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("�쳣���С;                                %d\r\n"), g_pNt->OptionalHeader.DataDirectory[3].Size);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		str.Format(_T("�ض�λ���ַ;                               %8X\r\n"), g_pNt->OptionalHeader.DataDirectory[5].VirtualAddress);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("�ض�λ���С;                               %d\r\n"), g_pNt->OptionalHeader.DataDirectory[5].Size);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		str.Format(_T("TLS���ַ;                                  %8X\r\n"), g_pNt->OptionalHeader.DataDirectory[9].VirtualAddress);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("TLS���С;                                  %d\r\n"), g_pNt->OptionalHeader.DataDirectory[9].Size);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		str.Format(_T("�����ַ���ַ;                             %8X\r\n"), g_pNt->OptionalHeader.DataDirectory[12].VirtualAddress);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		str.Format(_T("�����ַ���С;                             %d\r\n"), g_pNt->OptionalHeader.DataDirectory[12].Size);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		/////////////////////////////////////////////���нڱ�ͷ////////////////////////////////////////////////////
		//��������ͷ����һ��
		//���ļ�ͷ����������
		int nCountOfSection = g_pNt->FileHeader.NumberOfSections;
		//ȡ��һ������ͷ
		PIMAGE_SECTION_HEADER pSec = IMAGE_FIRST_SECTION(g_pNt);
		TCHAR szMsgSec[] = TEXT("---------------------------------------------------------------------------------\n"
			"�ڵ����Բο���\r\n"
			"  00000020h  ��������\r\n"
			"  00000040h  �����Ѿ���ʼ�������ݣ���.const\r\n"
			"  00000080h  ����δ��ʼ�����ݣ��� .data?\r\n"
			"  02000000h  �����ڽ��̿�ʼ�Ժ󱻶�������.reloc\r\n"
			"  04000000h  �������ݲ���������\r\n"
			"  08000000h  �������ݲ��ᱻ����������\r\n"
			"  10000000h  ���ݽ�����ͬ���̹���\r\n"
			"  20000000h  ��ִ��\r\n"
			"  40000000h  �ɶ�\r\n"
			"  80000000h  ��д\r\n"
			"�����Ĵ����һ��Ϊ��60000020h,���ݽ�һ��Ϊ��c0000040h��������һ��Ϊ��40000040h\r\n"
			"---------------------------------------------------------------------------------\n\n\r\n"
			"�ڵ�����  δ����ǰ��ʵ����  �ڴ��е�ƫ��(������) �ļ��ж����ĳ��� �ļ��е�ƫ��  �ڵ�����\r\n"
			"---------------------------------------------------------------------------------------------\r\n");
		str.Format(L"%s\r\n", szMsgSec);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		
		//ѭ��
		TCHAR szBuffer2[1024];
		TCHAR szSecName[16];
		TCHAR szFmtSec[] = TEXT("%s     %08x         %08x              %08x           %08x     %08x\n\n\r\n");
		for (int i = 0; i < nCountOfSection; i++)
		{
			//��ȡ�ڵ����ƣ�ע�ⳤ��Ϊ8�����Ʋ�����0��β
			//RtlZeroMemory(szSecName, sizeof(szSecName));
			//for (int i = 0; i < 8; ++i)
			//{
			//	if (pSec->Name[i])
			//	{
			//		szSecName[i] = pSec->Name[i];
			//	}
			//	else
			//	{
			//		szSecName[i] ='    ';//�������Ϊ0������ʾΪ�ո�
			//	}
			//}
			//��ȡ�ڵ���Ҫ��Ϣ
			/*wsprintf(szBuffer2, szFmtSec, CStringW(pSec->Name), pSec->Misc.VirtualSize,
				pSec->VirtualAddress, pSec->SizeOfRawData,
				pSec->PointerToRawData, pSec->Characteristics);*/
			str.Format(_T("%s     %08x         %08x              %08x           %08x     %08x\n\n\r\n"), 
				CStringW(pSec->Name), pSec->Misc.VirtualSize,
				pSec->VirtualAddress, pSec->SizeOfRawData,
				pSec->PointerToRawData, pSec->Characteristics);
			this->jiexipe.SetSel(-1);
			this->jiexipe.ReplaceSel(str);
		
			//��һ������ͷ�׵�ַ
			++pSec;
		}
		/////////////////////////////////////////////������///////////////////////////////////////////////////////////
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
		//�ҵ�������  Ҳ���ǵ�һ�����±�Ϊ0
		DWORD dwExportRVA = g_pNt->OptionalHeader.DataDirectory[0].VirtualAddress;
		//��ȡ���ļ��е�λ��
		PIMAGE_EXPORT_DIRECTORY pExport = (PIMAGE_EXPORT_DIRECTORY)(RVAtoFOA(dwExportRVA) + g_pFileImageBase);
		//ģ������
		char* pName = (char*)(RVAtoFOA(pExport->Name) + g_pFileImageBase);
		printf("%s\r\n", pName);
		str.Format(_T("%s\r\n"), CStringW(pName));
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		//��ַ���еĸ���
		DWORD dwCountOfFuntions = pExport->NumberOfFunctions;
		//���Ʊ��еĸ���
		DWORD dwCountOfNames = pExport->NumberOfNames;
		//��ַ���ַ
		PDWORD pAddrOfFuntion = (PDWORD)(RVAtoFOA(pExport->AddressOfFunctions) + g_pFileImageBase);
		//���Ʊ��ַ
		PDWORD pAddrOfName = (PDWORD)(RVAtoFOA(pExport->AddressOfNames) + g_pFileImageBase);
		//��ű��ַ
		PWORD pAddrOfOrdial = (PWORD)(RVAtoFOA(pExport->AddressOfNameOrdinals) + g_pFileImageBase);
		//baseֵ
		DWORD dwBase = pExport->Base;
		//������ַ���е�Ԫ��
		str.Format(L"-----------------------------------------�������еĵ��������뵼�����-------------------------------------------------- \r\n");
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		if (dwExportRVA == 0) {
			//printf("û�е�����\n");
			str.Format(L"û�е�����\r\n");
			this->jiexipe.SetSel(-1);
			this->jiexipe.ReplaceSel(str);
			//return;
		}
		else {
			for (int i = 0; i < dwCountOfFuntions;i++)
			{
				//��ַ���п��ܴ������õ�ֵ������Ϊ0��ֵ��
				if (pAddrOfFuntion[i] == 0)
				{
					continue;
				}
				//������ű����Ƿ���ֵ����ַ����±�ֵ����
				//���ж��Ƿ������Ƶ���
				bool bRet = false;
				for (int j = 0; j < dwCountOfNames;j++)
				{
					//iΪ��ַ���±�jΪ��ű���±ֵ꣨Ϊ��ַ���±꣩
					//�ж��Ƿ�����ű���
					if (i == pAddrOfOrdial[j])
					{
						//��Ϊ��ű������Ʊ��λ��һһ��Ӧ
						//ȡ�����Ʊ��е����Ƶ�ַRVA
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
					//��ű���û�У�˵��������ŵ�����
					//printf("%04d           %08X\n", i + dwBase, pAddrOfFuntion[i]);
					str.Format(_T("% 04d           %08X\r\n"), i + dwBase, pAddrOfFuntion[i]);
					this->jiexipe.SetSel(-1);
					this->jiexipe.ReplaceSel(str);
				}

			}
		}
		/////////////////////////////////////////////������///////////////////////////////////////////////////////////
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
		str.Format(L"-----------------------------------------������еĵ��뺯���뵼��ģ��--------------------------------------------------\r\n");
		//str.Format(L"û�е����\r\n");
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		TCHAR szBuffer3[1024] = { 0 };
		//�ҵ������  Ҳ���ǵڶ����±�Ϊ1
		DWORD dwImpotRVA = g_pNt->OptionalHeader.DataDirectory[1].VirtualAddress;
		//���ļ��е�λ��
		DWORD dwImportInFile = (DWORD)(RVAtoFOA(dwImpotRVA) + g_pFileImageBase);
		PIMAGE_IMPORT_DESCRIPTOR pImport = (PIMAGE_IMPORT_DESCRIPTOR)dwImportInFile;
		//����ÿһ�������  ͨ�����һ��Ϊ0��Ϊ�ж�����
		if (dwImpotRVA == 0) {
			printf("û�е����\n");
			str.Format(L"û�е����\r\r\n");
			this->jiexipe.SetSel(-1);
			this->jiexipe.ReplaceSel(str);
			return;
		}
		else {
			while (pImport->Name)
			{
				//�������Ƶ�ַ
				PIMAGE_THUNK_DATA pFirsThunk =
					(PIMAGE_THUNK_DATA)(RVAtoFOA(pImport->FirstThunk) + g_pFileImageBase);
				//�����
				char* pName = (char*)(RVAtoFOA(pImport->Name) + g_pFileImageBase);
				TCHAR szMsgImport[] = TEXT("\n\n����⣺%s\r\n"
					"-----------------------------\n\r\n"
					"OriginalFirstThunk  %08x\r\n"
					"TimeDateStamp       %08x\r\n"
					"ForwarderChain      %08x\r\n"
					"FirstThunk          %08x\r\n"
					"-----------------------------\n\r\n");
				/*wsprintf(szBuffer3, szMsgImport, pName,
					pImport->OriginalFirstThunk, pImport->TimeDateStamp,
					pImport->ForwarderChain, pImport->FirstThunk);*/
				
				str.Format(_T("\n\n����⣺%s\r\n OriginalFirstThunk  %08x\r\n TimeDateStamp   %08x\r\n ForwarderChain     %08x\r\n FirstThunk           %08x\r\n -----------------------------\n\r\n"),
					CStringW(pName), pImport->OriginalFirstThunk,
					pImport->TimeDateStamp, pImport->ForwarderChain, pImport->FirstThunk);
				this->jiexipe.SetSel(-1);
				this->jiexipe.ReplaceSel(str);
				printf("����ģ������%s\r\n", pName);
				//Ҳ��ͨ�����һ��Ϊ0��Ϊ�ж�����
				while (pFirsThunk->u1.AddressOfData)
				{
					//�жϵ��뷽ʽ
					if (IMAGE_SNAP_BY_ORDINAL32(pFirsThunk->u1.AddressOfData))
					{
						//˵������ŵ���(��16λ�������)
						str.Format(_T("��ŵ���:\t\t%04X \r\n"), pFirsThunk->u1.Ordinal & 0xFFFF);
						this->jiexipe.SetSel(-1);
						this->jiexipe.ReplaceSel(str);
						//printf("\t\t%04X \n", pFirsThunk->u1.Ordinal & 0xFFFF);
					}
					else
					{
						//���Ƶ���
						PIMAGE_IMPORT_BY_NAME pImportName =
							(PIMAGE_IMPORT_BY_NAME)(RVAtoFOA(pFirsThunk->u1.AddressOfData) + g_pFileImageBase);
						str.Format(_T("���Ƶ���:\t\t%04X %s \r\n"), pImportName->Hint, CStringW(pImportName->Name));
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
		str.Format(L"--------------------------------------------------��Դ��--------------------------------------------------------------- \r\n");
		//str.Format(L"%s\n", pResName);
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		//ע�����NameOffsetƫ��  OffsetToDirectoryƫ��  OffsetToDataƫ�ƶ�����Դ���ʼ��ƫ��
		//�ҵ���Դ��
		DWORD dwResRVA =
			g_pNt->OptionalHeader.DataDirectory[2].VirtualAddress;
		DWORD dwResFOA = (DWORD)(RVAtoFOA(dwResRVA) + g_pFileImageBase);
		PIMAGE_RESOURCE_DIRECTORY pRes = (PIMAGE_RESOURCE_DIRECTORY)dwResFOA;
		//��Դ������ ÿһ�㶼��һ��PIMAGE_RESOURCE_DIRECTORY��ͷ��֮�������
		//PIMAGE_RESOURCE_DIRECTORY_ENTRY�ṹ������˵��һ����һ��PIMAGE_RESOURCE_DIRECTORY
		//��һ��PIMAGE_RESOURCE_DIRECTORY_ENTRY�ṹ�����
		//��һ�㣨���ࣩ
		//�������
		DWORD dwCountOfResType =
			pRes->NumberOfIdEntries + pRes->NumberOfNamedEntries;

		for (int i = 0; i < dwCountOfResType;i++)
		{   //pRes����PIMAGE_RESOURCE_DIRECTORY���׵�ַ+1֮����Ǻ����PIMAGE_RESOURCE_DIRECTORY_ENTRY�׵�ַ
			PIMAGE_RESOURCE_DIRECTORY_ENTRY pResEntry =
				(PIMAGE_RESOURCE_DIRECTORY_ENTRY)(pRes + 1);
			//typedef struct _IMAGE_RESOURCE_DIRECTORY_ENTRY {
			//���������˵����Դ��ʲô  ���������Դ����֪��Ҳ����΢�������ô
			//���������λΪ0Ҳ����NameIsString��ԱΪ0���ʱ���������ֽڣ�union����������֪��Դ�����ͣ�Ҳ����ID��
			//����  ���������Դ��δ֪����ôNameIsString�����λΪ1 ��31λָ��һ��name�Ľṹ�壨PIMAGE_RESOURCE_DIR_STRING_U��ƫ�ƣ�Ҳ����DWORD   Name;������
			//	union {
			//		struct {
			//			DWORD NameOffset : 31;
			//			DWORD NameIsString : 1;
			//		} DUMMYSTRUCTNAME;
			//		DWORD   Name;
			//		WORD    Id;
			//	} DUMMYUNIONNAME;
			//���������˵����Դ������
			//��DataIsDirectory�ֶ�Ϊ1ʱ��Ҳ����������ֽ����λΪ1��˵������������ʾ�ĵط���һ��Ŀ¼��OffsetToDirectory����31λ����ʾ������
			//���ٸ��ط������Щ�ط����ǵڶ���
			//	union {
			//		DWORD   OffsetToData;
			//		struct {
			//			DWORD   OffsetToDirectory : 31;
			//			DWORD   DataIsDirectory : 1;
			//		} DUMMYSTRUCTNAME2;  
			//	} DUMMYUNIONNAME2;
			//} IMAGE_RESOURCE_DIRECTORY_ENTRY, *PIMAGE_RESOURCE_DIRECTORY_ENTRY;

			//�ж�������Դ���ַ�������ID
			if (pResEntry->NameIsString)
			{
				//������ַ�����NameOffset����ľ�������ַ�����RVA
				//�õ������ַ�����FOA
				DWORD dwName = (DWORD)((pResEntry->NameOffset) + (DWORD)pRes);
				//NameOffset��ָ��Ľṹ����IMAGE_RESOURCE_DIR_STRING_U����
				//���ﱣ�����ַ����ĳ��Ⱥ���ʼλ��
				PIMAGE_RESOURCE_DIR_STRING_U pName = (PIMAGE_RESOURCE_DIR_STRING_U)dwName;
				//������ַ���������0��β�ģ�������Ҫ�����������ϡ�\0����β���ٴ�ӡ
				WCHAR *pResName = new WCHAR[pName->Length + 1]{};
				memcpy(pResName, pName, (pName->Length) * sizeof(WCHAR));
				//��Ϊ��WCHAR��������wprintf
				//wprintf(L"%s\n", pResName);
				str.Format(_T("%s\r\n"), CStringW(pResName));
				this->jiexipe.SetSel(-1);
				this->jiexipe.ReplaceSel(str);
				//�ͷ��ڴ�
				delete[] pResName;
			}
			else   //id
			{
				char* arryResType[] = { "", "���ָ�루Cursor��", "λͼ��Bitmap��", "ͼ�꣨Icon��", "�˵���Menu��"
					, "�Ի���Dialog��", "�ַ����б�String Table��", "����Ŀ¼��Font Directory��", "���壨Font��", "��ݼ���Accelerators��"
					, "�Ǹ�ʽ����Դ��Unformatted��", "��Ϣ�б�Message Table��", "���ָ���飨Croup Cursor��", "", "ͼ���飨Group Icon��", ""
					, "�汾��Ϣ��Version Information��" };
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

				//�ж��Ƿ�����һ�㣨0����ʾû����һ�㣩
				if (pResEntry->DataIsDirectory)
				{   //���˵ڶ�����Խṹ��ͬ������һ��һ������OffsetToDirectory��ָ���������
					DWORD dwResSecond = (DWORD)pRes + pResEntry->OffsetToDirectory;
					PIMAGE_RESOURCE_DIRECTORY pResSecond = (PIMAGE_RESOURCE_DIRECTORY)dwResSecond;
					//�ڶ������
					DWORD dwCountOfSecond =
						pResSecond->NumberOfIdEntries + pResSecond->NumberOfNamedEntries;
					//����ÿһ����Դ
					for (int iSecond = 0; iSecond < dwCountOfSecond;iSecond++)
					{
						PIMAGE_RESOURCE_DIRECTORY_ENTRY pResSecondEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(pResSecond + 1);

						//�ж�������Դ���ַ�������ID
						if (pResEntry->NameIsString)
						{
							//������ַ�����NameOffset����ľ�������ַ�����RVA
							//�õ������ַ�����FOA
							DWORD dwNameFOA = (DWORD)(RVAtoFOA(pResEntry->NameOffset) + g_pFileImageBase);
							//NameOffset��ָ��Ľṹ����IMAGE_RESOURCE_DIR_STRING_U����
							//���ﱣ�����ַ����ĳ��Ⱥ���ʼλ��
							PIMAGE_RESOURCE_DIR_STRING_U pName = (PIMAGE_RESOURCE_DIR_STRING_U)dwNameFOA;
							//������ַ���������0��β�ģ�������Ҫ�����������ϡ�\0����β���ٴ�ӡ
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
						//�ж���û����һ��
						//������  ͬ����·�ӵ�һ���ṹ�忪ʼ�� ����OffsetToDirectory���ǵ�������
						//����Ҫע����ǵ��˵��������IMAGE_RESOURCE_DIRECTORY_ENTRY�ṹ��ĵ�һ���������û����
						//ͬʱ�ڶ����������DataIsDirectoryΪ0û����һ���� 
						//ͨ��OffsetToData�ֶ��ҵ���Դ�ṹ���ƫ�ƣ�ָ��_IMAGE_RESOURCE_DATA_ENTRY�ṹ�壩
						if (pResSecondEntry->DataIsDirectory)
						{
							//���������ʼλ��
							DWORD dwResThrid =
								(DWORD)pRes + pResSecondEntry->OffsetToDirectory;
							PIMAGE_RESOURCE_DIRECTORY pResThrid = (PIMAGE_RESOURCE_DIRECTORY)dwResThrid;

							PIMAGE_RESOURCE_DIRECTORY_ENTRY pResThridEntry = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(pResThrid + 1);
							//�����㣬�Ѿ������һ�㣬ʹ��PIMAGE_RESOURCE_DIRECTORY_ENTRY�е�
							//OffsetToData��Ա���õ�PIMAGE_RESOURCE_DATA_ENTRY�ṹ��λ��
							/*typedef struct _IMAGE_RESOURCE_DATA_ENTRY {
							DWORD   OffsetToData;   //��Դƫ��
							DWORD   Size;
							DWORD   CodePage;
							DWORD   Reserved;
							} IMAGE_RESOURCE_DATA_ENTRY, *PIMAGE_RESOURCE_DATA_ENTRY;
							*/
							PIMAGE_RESOURCE_DATA_ENTRY pResData =
								(PIMAGE_RESOURCE_DATA_ENTRY)(pResThridEntry->OffsetToData + (DWORD)pRes);
							//��Դ��RVA��Size
							DWORD dwResDataRVA = pResData->OffsetToData;
							DWORD dwResDataSize = pResData->Size;
							//PIMAGE_RESOURCE_DATA_ENTRY�е�OffsetToData�Ǹ�RVA
							DWORD dwResDataFOA = (DWORD)(RVAtoFOA(dwResDataRVA) + g_pFileImageBase);
							//��Դ�Ķ���������
							//������ӡ��Դ�Ķ���������  �����ֻ���Ƕ�������
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
						//��һ����Դ
						pResSecondEntry++;
					}
				}
			}
			//��һ����Դ
			pResEntry++;
		}
		cout << "----------------------------------------------------�ض�λ��------------------------------------------------------------ " << endl;
		str.Format(L"----------------------------------------------------�ض�λ��------------------------------------------------------------- \r\n");
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		//��Ϊ�����õ��Ǿ��Ե�ַ���Ҫ�ж�λ��
		//���ض�λ����ʱ��ֻ��Ҫ����pe�ļ��ļ��ػ�ַ�������ڵļ��ػ�ַ��ȥĬ�ϼ��ػ�ַ�õ�һ���������������������Ҫ�ض�λ�����ݼ��ɣ������ض�λ
		//���б����ֻ����Ҫ�ض�λ��Ϣ
		typedef struct _OFFSET_TYPE
		{
			WORD offset : 12; //��ҳ��ƫ����
			WORD type : 4;    //�ض�λ���ͣ�3��
		}OFFSET_TYPE, *POFFSET_TYPE;
		//�ض�λ��RVA
		DWORD dwRelocRVA = g_pNt->OptionalHeader.DataDirectory[5].VirtualAddress;
		//�Ƿ�Ϊ��
		if (!dwRelocRVA)
		{
			//printf("û���ض�λ��\n");
			str.Format(L"û���ض�λ��\r\n");
			this->jiexipe.SetSel(-1);
			this->jiexipe.ReplaceSel(str);
			return;
		}
		//�ض�λ�����ļ��еĵ�ַ
		PIMAGE_BASE_RELOCATION pReloc = (PIMAGE_BASE_RELOCATION)(RVAtoFOA(dwRelocRVA) + g_pFileImageBase);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//ѭ���ض�λ��
		//���SizeOfBlockΪ0��˵��û����Ҫ�ض�λ��������
		while (pReloc->SizeOfBlock)
		{
			//��ǰ�ض�λҳRVA
			//printf("%08X\n\n", pReloc->VirtualAddress);
			str.Format(L"%08X\n\r\n", pReloc->VirtualAddress);
			this->jiexipe.SetSel(-1);
			this->jiexipe.ReplaceSel(str);
			//��һҳһ���ж��ٸ��ض�λ�飨�����ٸ���Ҫ�ض�λ�����ݣ�
			DWORD dwCount = (pReloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
			//ָ���ض�λ���ַ
			POFFSET_TYPE pOffset = (POFFSET_TYPE)(pReloc + 1);
			//����ÿһ���ض�λ��   
			for (int i = 0; i < dwCount;i++)
			{
				//����һҳ�е�λ�õ�ַRVA
				DWORD dwRelocDataRVA = pReloc->VirtualAddress + pOffset->offset;
				//ת��FOA
				DWORD dwRelocDataFOA = (DWORD)(RVAtoFOA(dwRelocDataRVA) + g_pFileImageBase);
				//ʵ����Ҫ�ض�λ�����ݵ�ַ�Ǹ�VA
				DWORD dwRealDataVA = *(DWORD*)dwRelocDataFOA;
				//ת��RVA��������ڴ��е�ת����ɵ���Ե�ַ�ˣ�
				DWORD dwRealDataRVA = dwRealDataVA - g_pNt->OptionalHeader.ImageBase;
				//��תFOA��RVA���ļ��еĵ�ַ��
				DWORD dwRealDataFOA = (DWORD)(RVAtoFOA(dwRealDataRVA) + g_pFileImageBase);
				//��Ҫ�ض�λ�ľ������ݣ��ֽ�����ȷ����
				DWORD dwData = *(DWORD*)dwRealDataFOA;

				/*printf("��Ҫ�ض�λ�ĵ�%d������ RVA��%08X  VA:%08X  DATA:%08X\n",
					i + 1, dwRelocDataRVA, dwRealDataVA, dwData);*/
				str.Format(L"��Ҫ�ض�λ�ĵ�%d������ RVA��%08X  VA:%08X  DATA:%08X\r\n", i + 1, dwRelocDataRVA, dwRealDataVA, dwData);
				this->jiexipe.SetSel(-1);
				this->jiexipe.ReplaceSel(str);
				//��һ���ض�λ����λ��
				pOffset++;
			}

			//��һҳ
			pReloc =
				(PIMAGE_BASE_RELOCATION)(pReloc->SizeOfBlock + (DWORD)pReloc);
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
		cout << "--------------------------------------------------�̱߳�--------------------------------------------------------------- " << endl;
		str.Format(L"----------------------------------------------------�̱߳�-------------------------------------------------------------- \r\n");
		this->jiexipe.SetSel(-1);
		this->jiexipe.ReplaceSel(str);
		//�ҵ��̱߳�  001132A8  RVA 
		DWORD dwTLSsRVA = g_pNt->OptionalHeader.DataDirectory[9].VirtualAddress;
		//�Ƿ�Ϊ��
		if (!dwTLSsRVA)
		{
			printf("û�б�\n");
			str.Format(L"û���̱߳�\n\r\n");
			this->jiexipe.SetSel(-1);
			this->jiexipe.ReplaceSel(str);
			return;
		}
		//�̱߳����ļ��е���Ե�ַ
		DWORD temp=RVAtoFOA(dwTLSsRVA); // 001120A8
		//PIMAGE_TLS_DIRECTORY pLTS = (PIMAGE_TLS_DIRECTORY)(RVAtoFOA(dwTLSsRVA) + g_pFileImageBase);
		//tls���ļ��еľ��Ե�ַ
		PIMAGE_TLS_DIRECTORY pLTS =(PIMAGE_TLS_DIRECTORY)((char*) g_pFileImageBase + temp);
		//�ص���ĵ�ַ������VA   0051A508
		PDWORD  callback=(PDWORD)pLTS->AddressOfCallBacks;
		//VAת�ļ���ַ �õ����ǻص�����ļ��е���Ե�ַ
		DWORD tempaddr = (DWORD)callback - 0x400000;
		//�ҵ��ص�����������ļ��е���Ե�ַ
		DWORD TM=RVAtoFOA(tempaddr);
		//ȡ�������׵�ַ���ļ��еľ��Ե�ַ
		DWORD *tempfaddr =(DWORD*)( (char*)(g_pFileImageBase)+ TM);
		//tempfaddr[0];
		int i=1;
		//ѭ�������ص����еĺ�����ַ
		while (*tempfaddr)
		{
			//callback[0];//0x43e410(va)  ת foa     //      ff0000
			tempfaddr[0];
			str.Format(_T("�ص�����%d VA��ַ��%8X\r\n"), i, *tempfaddr);
			this->jiexipe.SetSel(-1);
			this->jiexipe.ReplaceSel(str);
			MessageBox(str);
			++tempfaddr;
			++i;
		}

		return;
	}

}
//����pe
void PEdump::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//this->jiexipe.howScrollBar(SB_VERT, TRUE);
	myPE();
}
//pe������
void PEdump::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//UpdateData(false);
}
