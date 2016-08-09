// Config LBB Files.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "work.h"
#include "drug.h"
#include "stock.h"
#include "String.h"
//#include <commctrl.h>
#include <commdlg.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
TCHAR file[1024];//char* file = "sav.txt";

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK	Start(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WorkProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	StockProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	DrugProc(HWND, UINT, WPARAM, LPARAM);
bool				EmptyBox(HWND hDlg, int start, int nrItem);

int LoadWork(Work &work);

// File filter for OpenFile dialog
#define FILE_FILTER_TEXT \
    TEXT(	"LBB Files (*.con)\0*.con;\0" \
			"All Files (*.*)\0*.*;\0\0")

// Begin default media search at root directory
#define DEFAULT_MEDIA_PATH  TEXT("\0")

BOOL GetClipFileName(LPTSTR szName)
{
    static OPENFILENAME ofn;
    static BOOL bSetInitialDir = FALSE;

    // Reset filename
    *szName = 0;

    // Fill in standard structure fields
    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = NULL;
    ofn.lpstrFilter       = FILE_FILTER_TEXT;
    ofn.lpstrCustomFilter = NULL;
    ofn.nFilterIndex      = 1;
    ofn.lpstrFile         = szName;
    ofn.nMaxFile          = MAX_PATH;
    ofn.lpstrTitle        = TEXT("Open Media File...\0");
    ofn.lpstrFileTitle    = NULL;
    ofn.lpstrDefExt       = TEXT("*\0");
    ofn.Flags             = OFN_CREATEPROMPT | OFN_PATHMUSTEXIST;

    // Remember the path of the first selected file
    if (bSetInitialDir == FALSE)
    {
        ofn.lpstrInitialDir = DEFAULT_MEDIA_PATH;
        bSetInitialDir = TRUE;
    }
    else
        ofn.lpstrInitialDir = NULL;

    // Create the standard file open dialog and return its result
    return GetOpenFileName((LPOPENFILENAME)&ofn);
}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CONFIGLBBFILES, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	DialogBox(hInstance, (LPCTSTR)IDD_STARTDLG, NULL, (DLGPROC)Start);

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_CONFIGLBBFILES);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)Start;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_CONFIGLBBFILES);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_CONFIGLBBFILES;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	hInst = hInstance;

	return RegisterClassEx(&wcex);
}

// Mesage handler for start box.
LRESULT CALLBACK Start(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_COMMAND:
			if (LOWORD(wParam) == ID_EDITSTOCK) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				if(GetClipFileName(file))
				{
					if(IsDlgButtonChecked(hDlg, IDC_CHECK1))
					{
						LoadStock(file);
					}
					else
						NewLoadStock(file);
				}
					
				DialogBox(hInst, (LPCTSTR)IDD_STOCKDLG, NULL, (DLGPROC)StockProc);
			}
			if (LOWORD(wParam) == ID_EDITWORK) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				if(GetClipFileName(file))
				{
					if(IsDlgButtonChecked(hDlg, IDC_CHECK1))
					{
						LoadWork(file);
					}
					else
						NewLoadWork(file);
				}
				EndDialog(hDlg, LOWORD(wParam));
				DialogBox(hInst, (LPCTSTR)IDD_WORKDLG, NULL, (DLGPROC)WorkProc);
			}
			if (LOWORD(wParam) == ID_EDITDRUGS) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				if(GetClipFileName(file))
				{
					if(IsDlgButtonChecked(hDlg, IDC_CHECK1))
					{
						LoadDrug(file);
					}
					else
						NewLoadDrug(file);
				}
				DialogBox(hInst, (LPCTSTR)IDD_DRUGDLG, NULL, (DLGPROC)DrugProc);
			}
			if (LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return TRUE;	
	}
    return FALSE;
}

// Mesage handler for work dlg.
LRESULT CALLBACK WorkProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	const int nrItem = 5;

	switch (message)
	{
		case WM_INITDIALOG:
			SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
		break;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK)
			{
				if(EmptyBox(hDlg, IDC_FIT, nrItem) != true)
				{
					SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
					MessageBox(hDlg, "Now the work is saved \nJust load the game...", "Now Saved", MB_OK);
					DestroyWindow(hDlg);
				}
			}
			if (LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			if (LOWORD(wParam) == IDC_LOAD) 
			{	
				SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
				EndDialog(hDlg, LOWORD(wParam));
				DialogBox(hInst, (LPCTSTR)IDD_STARTDLG, NULL, (DLGPROC)Start);
			
			}
			if (LOWORD(wParam) == IDC_DELETE) 
			{
				char objectName[MAX_NAME_LENGTH];
				strcpy(objectName, work[activeWork].name);

				for(int i = activeWork; i < antWork-1; i++)
				{
					strcpy(work[i].name, work[i+1].name);
					strcpy(work[i].text, work[i+1].text);
					work[i].id = i;
					work[i].nWage = work[i+1].nWage;
					work[i].nCostInFittnes = work[i+1].nCostInFittnes;
					work[i].nFitnes = work[i+1].nFitnes;
				}

				strcpy(work[i].name, "");
				strcpy(work[i].text, "");
				work[i].id = 0;
				work[i].nCostInFittnes = 0;
				work[i].nWage = 0;
				work[i].nFitnes = 0;

				if(antWork > 0)
					antWork--;

				activeWork--;

				SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
				MessageBox(hDlg, "Object Deleted", objectName, MB_OK | MB_ICONEXCLAMATION);
			}
			if (LOWORD(wParam) == IDC_RIGHT) 
			{	
				if(EmptyBox(hDlg, IDC_FIT, nrItem) != true)
				{
					SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
					if(activeWork < antWork-1)
					{
						activeWork++;
					}
					else
					{
						if(MessageBox(hDlg, "Add one more Work object?", "Add?", MB_ICONQUESTION | MB_YESNO) == IDYES)
							if(antDrug < MAX_WORK)
							{
								antWork++;
								activeWork++;
								work[activeWork].id = activeWork;
							}
							else
								MessageBox(hDlg, "Max Work\n Contact programmer !!!", "Array overflow", MB_OK);
					}
					SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
				}
			}

			if (LOWORD(wParam) == IDC_LEFT) 
			{	
				SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
				if(activeWork > 0)
					activeWork--;

				SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
			}
			if (LOWORD(wParam) == UPDATE_DLG) 
			{	
				char* str[nrItem+1];

				str[0] = IntToChar(work[activeWork].id);
				str[1] = IntToChar(work[activeWork].nFitnes);
				str[2] = IntToChar(work[activeWork].nCostInFittnes);
				str[3] = IntToChar(work[activeWork].nWage);
				str[4] = work[activeWork].name;
				str[5] = work[activeWork].text;


				int i = 0;
				for(int  item = IDC_ID; i < nrItem+1; i++, item++)
				{
					SetDlgItemText(hDlg, item, str[i]);	
				}
			}
			if (LOWORD(wParam) == SAVE_DLG) 
			{
				String str[nrItem];
				char* tmpStr;
				int i= 0;
				int len;
				bool emptyBox = false;
				for(int  item = IDC_FIT; i < nrItem && emptyBox != true; i++, item++)
				{
					len = GetWindowTextLength(GetDlgItem(hDlg, item));
					if(len > 0)
					{
						tmpStr = (char*)GlobalAlloc(GPTR, len + 1);
						GetDlgItemText(hDlg, item, tmpStr, len + 1);
						str[i] = tmpStr;
						GlobalFree((HANDLE)tmpStr);	
					}
					else
					{
						emptyBox = true;
						MessageBox(hDlg, "All fields are not filled!!!", "Oups!", MB_OK);
					}
				}

				if(emptyBox == false)
				{
					work[activeWork].id = activeWork;
					work[activeWork].nFitnes = str[0].convertToInt();
					work[activeWork].nCostInFittnes = str[1].convertToInt();
					work[activeWork].nWage = str[2].convertToInt();
					strcpy(work[activeWork].name, str[3].getString());
					strcpy(work[activeWork].text, str[4].getString());

					NewSaveWork(file);
				}
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return TRUE;	
	}
    return FALSE;
}

// Mesage handler for stock dlg.
LRESULT CALLBACK StockProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	const int nrItem = 4;

	switch (message)
	{
		case WM_INITDIALOG:
			SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
		break;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK)
			{
				if(EmptyBox(hDlg, IDC_FIT, nrItem) != true)
				{
					SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
					MessageBox(hDlg, "Now the Stock is saved \nJust load the game...", "Now Saved", MB_OK);
					DestroyWindow(hDlg);
				}
			}
			if (LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			if (LOWORD(wParam) == IDC_DELETE) 
			{
				char objectName[MAX_NAME_LENGTH];
				strcpy(objectName, lItem[activeLItem].name);

				for(int i = activeLItem; i < antLItem-1; i++)
				{
					strcpy(lItem[i].name, lItem[i+1].name);
					lItem[i].id = i;
					lItem[i].minPrice = lItem[i+1].minPrice;
					lItem[i].maxPrice = lItem[i+1].maxPrice;
					lItem[i].itsPrice = lItem[i+1].itsPrice;			
				}

				strcpy(lItem[i].name, "");
				lItem[i].id = 0;
				lItem[i].minPrice = 0;
				lItem[i].maxPrice = 0;
				lItem[i].itsPrice = 0;

				if(antLItem > 0)
					antLItem--;

				activeLItem--;

				SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
				MessageBox(hDlg, "Object Deleted", objectName, MB_OK | MB_ICONEXCLAMATION);
			}
			if (LOWORD(wParam) == IDC_LOAD) 
			{	
				SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
				EndDialog(hDlg, LOWORD(wParam));
				DialogBox(hInst, (LPCTSTR)IDD_STARTDLG, NULL, (DLGPROC)Start);	
			} 
			if (LOWORD(wParam) == IDC_RIGHT) 
			{	
				if(EmptyBox(hDlg, IDC_MAX, nrItem) != true)
				{
					SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
					if(activeLItem < antLItem-1)
					{
						activeLItem++;
					}
					else
					{
						if(MessageBox(hDlg, "Add one more Stock object?", "Add?", MB_ICONQUESTION | MB_YESNO) == IDYES)
							if(antLItem < MAX_STOCK)
							{
								antLItem++;
								activeLItem++;
								lItem[activeLItem].id = activeLItem;
							}
							else
								MessageBox(hDlg, "Max List Item\n Contact programmer !!!", "Array overflow", MB_OK);
					}
					SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
				}
			}

			if (LOWORD(wParam) == IDC_LEFT) 
			{	
				SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
				if(activeLItem > 0)
					activeLItem--;

				SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
			}
			if (LOWORD(wParam) == UPDATE_DLG) 
			{	
				char* str[nrItem];

				str[0] = IntToChar(lItem[activeLItem].id);
				str[1] = IntToChar(lItem[activeLItem].minPrice);
				str[2] = IntToChar(lItem[activeLItem].maxPrice);
				str[3] = IntToChar(lItem[activeLItem].itsPrice);
				str[4] = lItem[activeLItem].name;

				int i = 0;
				for(int  item = IDC_ID; i < nrItem+1; i++, item++)
				{
					SetDlgItemText(hDlg, item, str[i]);	
				}
			}
			if (LOWORD(wParam) == SAVE_DLG) 
			{
				String str[nrItem];
				char* tmpStr;
				int i= 0;
				int len;
				bool emptyBox = false;
				for(int  item = IDC_MAX; i < nrItem && emptyBox != true; i++, item++)
				{
					len = GetWindowTextLength(GetDlgItem(hDlg, item));
					if(len > 0)
					{
						tmpStr = (char*)GlobalAlloc(GPTR, len + 1);
						GetDlgItemText(hDlg, item, tmpStr, len + 1);
						str[i] = tmpStr;
						GlobalFree((HANDLE)tmpStr);	
					}
					else
					{
						emptyBox = true;
						MessageBox(hDlg, "All fields are not filled!!!", "Oups!", MB_OK);
					}
				}

				if(emptyBox == false)
				{
					lItem[activeLItem].id = activeLItem;
					lItem[activeLItem].minPrice = str[0].convertToInt();
					lItem[activeLItem].maxPrice = str[1].convertToInt();
					lItem[activeLItem].itsPrice = str[2].convertToInt();
					strcpy(lItem[activeLItem].name, str[3].getString());

					NewSaveStock(file);
				}
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return TRUE;	
	}
    return FALSE;
}

// Mesage handler for work box.
LRESULT CALLBACK DrugProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	const int nrItem = 5;

	switch (message)
	{
		case WM_INITDIALOG:
			SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
		break;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK)
			{
				if(EmptyBox(hDlg, IDC_FIT, nrItem) != true)
				{
					SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
					MessageBox(hDlg, "Now the Drug is saved \nJust load the game...", "Now Saved", MB_OK);
					DestroyWindow(hDlg);
				}
			}
			if (LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			if (LOWORD(wParam) == IDC_LOAD) 
			{	
				SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
				EndDialog(hDlg, LOWORD(wParam));
				DialogBox(hInst, (LPCTSTR)IDD_STARTDLG, NULL, (DLGPROC)Start);
			}
			if (LOWORD(wParam) == IDC_DELETE) 
			{
				char objectName[MAX_NAME_LENGTH];
				strcpy(objectName, drug[activeDrug].name);

				for(int i = activeDrug; i < antDrug-1; i++)
				{
					strcpy(drug[i].name, drug[i+1].name);
					strcpy(drug[i].text, drug[i+1].text);
					drug[i].id = i;
					drug[i].nWage = drug[i+1].nWage;
					drug[i].nCostInSleep = drug[i+1].nCostInSleep;
					drug[i].nFitnes = drug[i+1].nFitnes;
				}

				strcpy(drug[i].name, "");
				strcpy(drug[i].text, "");
				drug[i].id = 0;
				drug[i].nCostInSleep = 0;
				drug[i].nWage = 0;
				drug[i].nFitnes = 0;

				if(antDrug > 0)
					antDrug--;

				activeDrug--;

				SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
				MessageBox(hDlg, "Object Deleted", objectName, MB_OK | MB_ICONEXCLAMATION);
			}
			if (LOWORD(wParam) == IDC_RIGHT) 
			{	
				if(EmptyBox(hDlg, IDC_FIT, nrItem) != true)
				{
					SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
					if(activeDrug < antDrug-1)
					{
						activeDrug++;
					}
					else
					{
						if(MessageBox(hDlg, "Add one more Drug object?", "Add?", MB_ICONQUESTION | MB_YESNO) == IDYES)
							if(antDrug < MAX_WORK)
							{
								antDrug++;
								activeDrug++;
								drug[activeDrug].id = activeDrug;
							}
							else
								MessageBox(hDlg, "Max Drug\n Contact programmer !!!", "Array overflow", MB_OK);
					}
					SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
				}
			}

			if (LOWORD(wParam) == IDC_LEFT) 
			{	
				SendMessage(hDlg, WM_COMMAND, SAVE_DLG, NULL);
				if(activeDrug > 0)
					activeDrug--;

				SendMessage(hDlg, WM_COMMAND, UPDATE_DLG, NULL);
			}
			if (LOWORD(wParam) == UPDATE_DLG) 
			{	
				char* str[nrItem+1];

				str[0] = IntToChar(drug[activeDrug].id);
				str[1] = IntToChar(drug[activeDrug].nFitnes);
				str[2] = IntToChar(drug[activeDrug].nCostInSleep);
				str[3] = IntToChar(drug[activeDrug].nWage);
				str[4] = drug[activeDrug].name;
				str[5] = drug[activeDrug].text;


				int i = 0;
				for(int  item = IDC_ID; i < nrItem+1; i++, item++)
					SetDlgItemText(hDlg, item, str[i]);	
			}
			if (LOWORD(wParam) == SAVE_DLG) 
			{
				String str[nrItem];
				char* tmpStr;
				int i= 0;
				int len;
				bool emptyBox = false;
				for(int  item = IDC_FIT; i < nrItem && emptyBox != true; i++, item++)
				{
					len = GetWindowTextLength(GetDlgItem(hDlg, item));
					if(len > 0)
					{
						tmpStr = (char*)GlobalAlloc(GPTR, len + 1);
						GetDlgItemText(hDlg, item, tmpStr, len + 1);
						str[i] = tmpStr;
						GlobalFree((HANDLE)tmpStr);	
					}
					else
					{
						emptyBox = true;
						MessageBox(hDlg, "All fields are not filled!!!", "Oups!", MB_OK);
					}
				}

				if(emptyBox == false)
				{
					drug[activeDrug].id = activeDrug;
					drug[activeDrug].nFitnes = str[0].convertToInt();
					drug[activeDrug].nCostInSleep = str[1].convertToInt();
					drug[activeDrug].nWage = str[2].convertToInt();
					strcpy(drug[activeDrug].name, str[3].getString());
					strcpy(drug[activeDrug].text, str[4].getString());

					NewSaveDrug(file);
				}
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return TRUE;	
	}
    return FALSE;
}

bool EmptyBox(HWND hDlg, int start, int nrItem)
{
	char szBuffer[512];
	int len;
	for(int i = 0, item = start; i < nrItem; i++, item++)
	{
		len = GetWindowTextLength(GetDlgItem(hDlg, item));
		if(len == 0)
		{
			MessageBox(hDlg, "All fields are not filled!!!", "Oups!", MB_OK);
			return true;
		}
		else if(item == IDC_TEXT && len > MAX_TEXT)
		{
			wsprintf(szBuffer, "Array overflow:\n Too much text \n %d Characters", len);
			MessageBox(hDlg, szBuffer, "Oups!", MB_OK);
			return true;
		}
		else if(item == IDC_NAME && len > MAX_NAME_LENGTH)
		{
			wsprintf(szBuffer, "Array overflow:\n Too long name \n %d Characters", len);
			MessageBox(hDlg, szBuffer, "Oups!", MB_OK);
			return true;
		}
	}
	return false;
}
