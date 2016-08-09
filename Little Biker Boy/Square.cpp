// Square.cpp: implementation of the CSquare class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Square.h"

CSquare* activeSquare;
//////////////////////////////////////////////////////////////////////
// TimerProc
//////////////////////////////////////////////////////////////////////
VOID CALLBACK SquareClassTimerProc( 
    HWND hWnd,        // handle to window for timer messages 
    UINT message,     // WM_TIMER message 
    UINT idTimer,     // timer identifier 
    DWORD dwTime)     // current system time 
{ 
	activeSquare->SquareTimerProc(hWnd, message, idTimer, dwTime);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSquare::CSquare()
{
	CObject::setPosition(0,0,0,0);
	this->setBackColor(RGB(100, 100, 100));
	move = 15;
	margin = 40;
	reziseBox = false;
	close	= false;
	frame = 2;
	setStatus(NOT_PRESSABLE);
}

CSquare::~CSquare()
{
	DeleteObject(itsBrush);
}

void CSquare::draw(HWND initHWnd, bool forced)
{
	HDC hdc = GetDC(initHWnd);		
	draw(hdc, forced);
	ReleaseDC(initHWnd, hdc);
}

void CSquare::draw(HDC hdc, bool forced)
{
	if(getStatus() == ACTIVE || getStatus() == NORMAL)
	{
		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, getRight(), getBottom());
		HBITMAP hbmOldBuffer = HBITMAP (SelectObject(hdcMem, hbmBuffer));

		HBRUSH original_brush = (HBRUSH)SelectObject(hdcMem, itsBrush); 
		Rectangle(hdcMem, getLeft(), getTop(), getRight(), getBottom());

		BitBlt(hdc, getLeft(), getTop(), getRight(), getBottom(), hdcMem, getLeft(), getTop(), SRCPAINT);


		SelectObject(hdcMem, hbmOldBuffer);
		SelectObject (hdcMem, original_brush);
		DeleteDC(hdcMem);
		DeleteObject(hbmBuffer);

		if(reziseBox == false && getStatus() == ACTIVE)
		{
			CRoom::draw(hdc);
			
			HBRUSH frameBrush = CreateSolidBrush(RGB(0,0,0));
			FrameRect(hdc, getRect(), frameBrush);
			DeleteObject(frameBrush);
		}
	}
}

void CSquare::drawFrame(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	HBRUSH frameBrush = CreateSolidBrush(RGB(0,0,0));
	
	FrameRect(hdc, getRect(), frameBrush);
	
	DeleteObject(frameBrush);
	ReleaseDC(hWnd, hdc);
}

void CSquare::setMarginAndMove(int initMargin, int initMove)
{
	margin = initMargin;
	move = initMove;	
}

void CSquare::setBackColor(COLORREF initColor)
{
	backColor = initColor;
	DeleteObject(itsBrush);
	itsBrush = CreateSolidBrush(backColor);
}

int CSquare::test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSqr, bool keyPressed)
{
	if(getStatus() == ACTIVE)
		return CRoom::test(initX,initY, hWnd, theInfoSqr, keyPressed);
	else
		return 0;
}

void CSquare::showSquare(HWND hWnd, int x, int y)
{
	setLeft(x);
	setTop(y);
	setRight(getLeft() + 10);
	setBottom(getTop() + 10);

	SetTimer(hWnd,      // handle to main window 
	BOX_TIMER,            // timer identifier 
	10,                    // 0.01-second interval 
	(TIMERPROC) SquareClassTimerProc); // timer callback

	activeSquare = this;
	reziseBox = true;
	close = false;
	setStatus(NORMAL);
}

void CSquare::showSquare(HWND hWnd, RECT* rc)
{
	setLeft(rc->left + ((rc->right - rc->left) /2));
	setTop(rc->top + ((rc->bottom - rc->top) /2));

	showSquare(hWnd, getLeft(), getTop());
}

void CSquare::closeSquare(HWND hWnd)
{
	SetTimer(hWnd,      // handle to main window 
	BOX_TIMER,            // timer identifier 
	10,                    // 0.01-second interval 
	(TIMERPROC) SquareClassTimerProc); // timer callback

	activeSquare = this;
	reziseBox = true;
	close = true;
	setStatus(NORMAL);
}

//////////////////////////////////////////////////////////////////////
// TimerProc
//////////////////////////////////////////////////////////////////////
VOID CALLBACK CSquare::SquareTimerProc( 
    HWND hWnd,        // handle to window for timer messages 
    UINT message,     // WM_TIMER message 
    UINT idTimer,     // timer identifier 
    DWORD dwTime)     // current system time 
{ 
	bool leftStop = false;
	bool rightStop = false;
	bool topStop = false;
	bool bottomStop = false;
	RECT rt;

	GetClientRect(hWnd, &rt);
	if(move == 0)					// If move == 0
	{								// The just resize the window to max
		if(close == true)			// Or if the clos i tru den reset all variables
		{
			reziseBox = false;
			KillTimer(hWnd, BOX_TIMER);
			setStatus(NOT_PRESSABLE);
		}
		else
		{
			reziseBox = false;
			KillTimer(hWnd, BOX_TIMER);
			setPosition(rt);
			CRoom::draw(hWnd);		// Draw all the active Objects
			drawFrame(hWnd);
			setStatus(ACTIVE);
		}
		InvalidateRect(hWnd, &rt, FALSE);
	}


	if(close == true)
	{
		rt = getItsPosition();
		rt.left -= frame;
		rt.right += frame;
		rt.top -= frame;
		rt.bottom += frame;

		setLeft(getLeft()	+ move);
		setTop(getTop()		+ move);
		setBottom(getBottom()- move);
		setRight(getRight()	- move);

		if( getLeft() >= getRight())
		{
			leftStop = true;
			setLeft(getLeft()-move);
		}
		if( getTop() >= getBottom())
		{
			topStop = true;
			setTop(getTop()-move);
		}

		if(getBottom() <= getTop())
		{
			bottomStop = true;
			setBottom(getBottom()+move);
		}

		if( getRight() <= getLeft())
		{
			rightStop = true;
			setRight(getRight()+move);
		}
		
		RECT redrawRect = rt;
		redrawRect.right = getLeft();
		InvalidateRect(hWnd, &redrawRect, FALSE);
		redrawRect = rt;
		redrawRect.left = getRight();
		InvalidateRect(hWnd, &redrawRect, FALSE);
		redrawRect = rt;
		redrawRect.bottom = getTop();
		InvalidateRect(hWnd, &redrawRect, FALSE);
		redrawRect = rt;
		redrawRect.top = getBottom();
		InvalidateRect(hWnd, &redrawRect, FALSE);


		if(leftStop   && topStop &&
		   bottomStop && rightStop)
		{
			reziseBox = false;
			KillTimer(hWnd, BOX_TIMER);
			GetClientRect(hWnd, &rt);
			InvalidateRect(hWnd, &rt, FALSE);
			setStatus(NOT_PRESSABLE);
		}
	}
	else
	{
		GetClientRect(hWnd, &rt);

		setLeft(getLeft()	- move);
		setTop(getTop()		- move);
		setBottom(getBottom()+ move);
		setRight(getRight()	+ move);

		if( getLeft() <= rt.left+margin)
		{
			leftStop = true;
			setLeft(rt.left+margin);
		}

		if( getTop() <= rt.top+margin)
		{
			topStop = true;
			setTop(rt.top+margin);
		}

		if(getBottom() >= rt.bottom-margin)
		{
			bottomStop = true;
			setBottom(rt.bottom-margin);
		}

		if( getRight() >= rt.right-margin)
		{
			rightStop = true;
			setRight(rt.right-margin);
		}


		this->draw(hWnd);
		
		
		if(leftStop   && topStop &&
		   bottomStop && rightStop)
		{
			reziseBox = false;
			KillTimer(hWnd, BOX_TIMER);
			CRoom::draw(hWnd);		// Draw all the active Objects
			drawFrame(hWnd);
			setStatus(ACTIVE);
		}
	}
}