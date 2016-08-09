// InfoSquare.cpp: implementation of the CObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InfoSquare.h"


//////////////////////////////////////////////////////////////////////
//
// CLASS: CInfoSquare
//
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CInfoSquare *activeInfSqr;
VOID CALLBACK InfoSquareTimerProc( HWND hWnd, UINT message, UINT idTimer, DWORD dwTime)     // current system time
{
	activeInfSqr->TimerProc(hWnd, message, idTimer, dwTime);
}

CInfoSquare::CInfoSquare()
{
	this->setBgColor(RGB(250, 200, 75));
	this->setFrame(RGB(0,0,0));
	this->setMargin(10);
	this->setText("Weei förklarings text");
	this->setTextColor(RGB(0,0,0));
	showSquare = false;
	counter = 0;
	itsId = "";
}

/*static CInfoSquare* CInfoSquare::getActiveinfoSqr()
{
	return activeInfSqr;
}*/

void CInfoSquare::draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	draw(hdc);
	ReleaseDC(hWnd, hdc);
}

void CInfoSquare::draw(HDC hdc)
{
	if(showSquare && getTextLen() > 0)
	{
		CStaticText::draw(hdc);
#ifdef DEBUGHIG
		Logg("Ritar infosquare");
#endif
	}
}

void CInfoSquare::setPos(HWND hWnd, POINTS init)
{
	RECT oldPos = getItsPosition();
	itsPoint = init;
	setPosition(itsPoint.x, itsPoint.y, itsPoint.x + getWidth(), itsPoint.y+getHeight());
	if(showSquare)
	{
		InvalidateRect(hWnd, &oldPos, FALSE);
		InvalidateRect(hWnd, getRect(), FALSE);
	}
}

void CInfoSquare::stopTimer(HWND hWnd, String initId, bool forced)
{
	if((itsId == initId && showSquare == true) || forced)
	{
		KillTimer(hWnd, INFOSQR_TIMER);
		showSquare = false;
		itsId.setToNull();
	}
}

void CInfoSquare::drawSquare(bool init)
{
	showSquare = init;
}

void CInfoSquare::startTimer(HWND hWnd, String initId, char* itsText, int initX, int initY)
{
	if(itsId != initId && showSquare == false)
	{
		setText(itsText);
		if(getTextLen() > 0)
		{
			counter = 0;

			activeInfSqr = this;

			SetTimer(hWnd,      // handle to main window
			INFOSQR_TIMER,            // timer identifier
			1000,                    // 0.01-second interval
			(TIMERPROC) InfoSquareTimerProc); // timer callback

			itsId = initId;
			itsPoint.x = initX;
			itsPoint.y = initY;
			setPosition(itsPoint.x, itsPoint.y, itsPoint.x + getWidth(), itsPoint.y+getHeight());
		}
	}
}

VOID CALLBACK CInfoSquare::TimerProc(
    HWND hWnd,        // handle to window for timer messages
    UINT message,     // WM_TIMER message
    UINT idTimer,     // timer identifier
    DWORD dwTime)     // current system time
{
	counter++;
	if(counter >= 1)
	{
		KillTimer(hWnd, INFOSQR_TIMER);
		showSquare = true;
		InvalidateRect(hWnd, getRect(), FALSE);
	}
}