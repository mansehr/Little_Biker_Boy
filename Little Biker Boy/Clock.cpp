// Clock.cpp: implementation of the CObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Clock.h"


//////////////////////////////////////////////////////////////////////
// TimerProc
//////////////////////////////////////////////////////////////////////
CClock* activeClock;
VOID CALLBACK ClockClassTimerProc(
    HWND hWnd,        // handle to window for timer messages
    UINT message,     // WM_TIMER message
    UINT idTimer,     // timer identifier
    DWORD dwTime)     // current system time
{
	activeClock->TimerProc(hWnd, message, idTimer, dwTime);
}

//////////////////////////////////////////////////////////////////////
//
// CLASS: CCLOCK
//
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CClock::CClock()
{
	speed = 0;
	alpha = RAD(-87);
	alpha2 = RAD(-87);
	backIsLoaded = false;
}

CClock::~CClock()
{

}

void CClock::draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	draw(hdc);
	ReleaseDC(hWnd, hdc);
}

void CClock::draw(HDC hdc)
{
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(100,110,120));
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
	HBRUSH brush = CreateSolidBrush(RGB(50,50,200));
	HBRUSH original_brush = (HBRUSH)SelectObject(hdc, brush);

	recount();

	if(backIsLoaded)
		DrawBitmapWithMask(hdc, back.getTheMask(), back.getTheBitmap(), getTop(), getLeft());
	else
		Ellipse(hdc, getLeft(),getTop(),getRight(),getBottom());

	MoveToEx(hdc, middle.x, middle.y, NULL);
	LineTo(hdc, visare.x, visare.y);
	MoveToEx(hdc, middle.x, middle.y, NULL);
	LineTo(hdc, visare2.x, visare2.y);

	SelectObject (hdc, original_brush);
	DeleteObject (brush);
	SelectObject (hdc, oldPen);
	DeleteObject (pen);
}

int	CClock::LoadBack(LPSTR szFileName)
{
	backIsLoaded = true;
	back.setMaskColor(RGB(0,0,255));
	return back.LoadABitmap(szFileName, true);
}

void CClock::setMiddle(int initX, int initY)
{
	middle.x = initX;
	middle.y = initY;
}

void CClock::start(HWND hWnd, int sec)
{
	counter = 0;
	speed = sec;

	activeClock = this;

	recount();

	SetTimer(hWnd,      // handle to main window
	CLOCK_TIMER,            // timer identifier
	27,                    // 0.01-second interval
	(TIMERPROC) ClockClassTimerProc); // timer callback
}

void CClock::recount()
{
	radius = ((getRight()-getLeft())/2);

	visare.x = int(cos(alpha) * (radius-(radius*0.5)));
	visare.y = int(sin(alpha) * (radius-(radius*0.5)));
	visare2.x = int(cos(alpha2) * (radius-(radius*0.7)));
	visare2.y = int(sin(alpha2) * (radius-(radius*0.7)));

	visare.x += middle.x;
	visare.y += middle.y;
	visare2.x += middle.x;
	visare2.y += middle.y;
}

VOID CALLBACK CClock::TimerProc(
    HWND hWnd,        // handle to window for timer messages
    UINT message,     // WM_TIMER message
    UINT idTimer,     // timer identifier
    DWORD dwTime)     // current system time
{
	alpha  += float(RAD(4) * speed);
	alpha2 += float(RAD(0.333333333) * speed);

	RECT rc = {getLeft(),getTop(),getRight(),getBottom()};

	InvalidateRect(hWnd, &rc, NULL);

	counter++;
	if((counter/27) >= 2)				// 2 (Two) seconds long animation
		KillTimer(hWnd, CLOCK_TIMER);
}