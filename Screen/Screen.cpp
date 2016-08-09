// Screen.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "object.h"
#include "pile.h"

#define MAX_LOADSTRING 100
#define PILE		//Clock, Box, Pile


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
VOID CALLBACK MyTimerProc(HWND hwnd,UINT message,UINT idTimer, DWORD dwTime);

RECT box;
CClock clock;
CPile pile;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SCREEN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_SCREEN);

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
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_SCREEN);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_SCREEN;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	POINTS mouse =  MAKEPOINTS(lParam);

	switch (message) 
	{
		case WM_CREATE:
			box.top = 100;
			box.bottom = 200;
			box.left = 100;
			box.right = 200;
			
			clock.setPosition(150, 150, 250, 250);

			pile.setPosition(100, 50, 120, 150);
			pile.setValue(60);
			pile.setChange(-500);
			pile.setCompLarger(false);
		break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			{
			hdc = BeginPaint(hWnd, &ps);
#ifdef CLOCK
			clock.draw(hdc);
#endif
#ifdef PILE 
			pile.draw(hdc);

			//Rectangle(hdc, 100, 50, 70, 200);
#endif
#ifdef BOX
			RECT rt;
			GetClientRect(hWnd, &rt);
			
			HPEN pen = CreatePen(PS_SOLID, 4, RGB(0,0,0));
			HPEN oldPen = (HPEN)SelectObject(hdc, pen);
			HBRUSH brush;
			HBRUSH original_brush;
			brush = CreateSolidBrush(RGB(250,245,100));
			original_brush = (HBRUSH)SelectObject(hdc, brush); 


			Rectangle(hdc, box.left, box.top, box.right, box.bottom);

			SelectObject (hdc, original_brush);
			DeleteObject (brush);
			SelectObject (hdc, oldPen);
			DeleteObject (pen);
#endif			
			EndPaint(hWnd, &ps);
			}
			break;
		case WM_LBUTTONDOWN:
#ifdef CLOCK
			clock.start(hWnd, 2);
#endif
#ifdef BOX
			SetTimer(hWnd,      // handle to main window 
			1001,            // timer identifier 
			25,                    // 0.01-second interval 
			(TIMERPROC) MyTimerProc); // timer callback 
#endif	
			break;
		case WM_RBUTTONDOWN:
			box.left = mouse.x;
			box.top = mouse.y;
			box.right = box.left + 5;
			box.bottom = box.top + 5;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

VOID CALLBACK MyTimerProc( 
    HWND hWnd,        // handle to window for timer messages 
    UINT message,     // WM_TIMER message 
    UINT idTimer,     // timer identifier 
    DWORD dwTime)     // current system time 
{ 
	const int move = 15;
	const int margin = 40;
	RECT rt;
	GetClientRect(hWnd, &rt);

	box.left -= move;
	box.top -= move;
	box.bottom += move;
	box.right += move;

	if(box.left <= rt.left+margin)
		box.left = rt.left+margin;

	if(box.top <= rt.top+margin)
		box.top = rt.top+margin;

	if(box.bottom >= rt.bottom-margin)
		box.bottom = rt.bottom-margin;

	if(box.right >= rt.right-margin)
		box.right = rt.right-margin;
	
	InvalidateRect(hWnd, &box, FALSE);
	
	if(box.left   == rt.left+margin   && box.top   == rt.top+margin   &&
	   box.bottom == rt.bottom-margin && box.right == rt.right-margin )
		KillTimer(hWnd, 1001); 
}