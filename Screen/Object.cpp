// Object.cpp: implementation of the CObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Object.h"

//////////////////////////////////////////////////////////////////////
//
// CLASS: COBJECT
//
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CObject::CObject()
{

}

CObject::~CObject()
{

}

void CObject::draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	draw(hdc);
	ReleaseDC(hWnd, hdc);
}

void CObject::draw(HDC hdc)
{
	MessageBox(NULL, "I objects DRAW ska vi inte va", "Ajdå", MB_OK);
}

RECT CObject::getItsPosition()
{
	return itsPosition;
}

char* CObject::getName()
{
	return sName.getString();
}

int CObject::getLen()
{
	return sName.getLen();
}

RECT* CObject::getRect()
{
	return &itsPosition;
}

void CObject::setName(char* initString)
{
	sName = initString;
}

String CObject::getString()
{
	return sName;
}


void CObject::setPosition(RECT initPos)
{
	itsPosition = initPos; 
}

void CObject::setPosition(int left, int top, int right, int bottom)
{
	itsPosition.left	= left;
	itsPosition.top		= top;
	itsPosition.right	= right;
	itsPosition.bottom	= bottom;
}

int	CObject::getLeft()
{
	return itsPosition.left;
}

int	CObject::getRight()
{
	return itsPosition.right;
}

int	CObject::getTop()
{
	return itsPosition.top;
}

int	CObject::getBottom()
{
	return itsPosition.bottom;
}

void CObject::moveLeftTo(int init)
{
	itsPosition.right -= itsPosition.left - init;
	itsPosition.left = init;
}

void CObject::moveRightTo(int init)
{
	itsPosition.left -= itsPosition.right - init;
	itsPosition.right = init;
}

void CObject::moveTopTo(int init)
{
	itsPosition.bottom -= itsPosition.top - init;
	itsPosition.top = init;
}

void CObject::moveBottomTo(int init)
{
	itsPosition.top -= itsPosition.bottom - init;
	itsPosition.bottom = init;
}

void CObject::setLeft(int init)
{
	itsPosition.left = init;
}

void CObject::setRight(int init)
{
	itsPosition.right = init;
}

void CObject::setTop(int init)
{
	itsPosition.top = init;
}

void CObject::setBottom(int init)
{
	itsPosition.bottom = init;
}




//////////////////////////////////////////////////////////////////////
//
// CLASS: CSTATUSOBJECT
//
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatusObject::CStatusObject()
{
	itsStatus		= NORMAL;
	oldStatus		= NORMAL;		// Old status has to be diffrent or else it wont be painted a first time;
}

CStatusObject::~CStatusObject()
{

}
void CStatusObject::draw(HWND hWnd, bool forced)
{
	HDC hdc = GetDC(hWnd);
	draw(hdc, forced);
	ReleaseDC(hWnd, hdc);

}

void CStatusObject::draw(HDC hdc, bool forced)
{
	MessageBox(NULL, "I status objects DRAW ska vi inte va", "Inte Här", MB_OK);
}

Status	CStatusObject::getStatus()
{
	return itsStatus;
}

Status	CStatusObject::getOldStatus()
{
	return oldStatus;
}

void CStatusObject::setStatus(Status initStatus)
{
		oldStatus = itsStatus;
		itsStatus = initStatus;
}
void CStatusObject::setStatusChanged(bool initStatusChanged)
{
	oldStatus = Status(itsStatus + 1);
}

int CStatusObject::test(int initX, int initY, HWND hWnd, bool keyPressed)
{
	MessageBox(hWnd, "I status objects TEST ska vi inte va", "Inte Här", MB_OK);
	return 0;
}

bool CStatusObject::isPressed()
{
	if(itsStatus == PRESSED)		// If status is Pressed
	{
		itsStatus = NORMAL;		// Change status
		return true;					// Return true
	}
	else
		return false;					// Else return false
}

bool  CStatusObject::isStatusChanged()
{
	if(oldStatus != itsStatus)
		return true;
	else 
		return false;
}

void	CStatusObject::resetOldStatus()
{
	oldStatus = itsStatus;
}



//////////////////////////////////////////////////////////////////////
//
// CLASS: CSTATICTEXT
//
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CStaticText::CStaticText()
{

}

CStaticText::~CStaticText()
{

}

void CStaticText::draw(HDC hdc)
{
	TextOut(hdc, getLeft(), getTop(), getString().getString(), getString().getLen());
}


CClock* activeClock;
//////////////////////////////////////////////////////////////////////
// TimerProc
//////////////////////////////////////////////////////////////////////
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
	alpha = 0;
	alpha2 = 0;
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
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0,0,0));
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
	HBRUSH brush;
	HBRUSH original_brush;
	brush = CreateSolidBrush(RGB(50,50,200));
	original_brush = (HBRUSH)SelectObject(hdc, brush); 

//	Rectangle(hdc, getLeft(),getTop(),getRight(),getBottom());
	countMiddle();
	if(!visare.x )
	{
		visare.x = middle.x+(radius-10);
		visare.y = middle.y;
		visare2.x = middle.x;
		visare2.y = middle.y+(radius-20);
	}
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

void CClock::start(HWND hWnd, int sec)
{	
	counter = 0;
	time = sec;

	activeClock = this;

	countMiddle();

	SetTimer(hWnd,      // handle to main window 
	CLOCK_TIMER,            // timer identifier 
	25,                    // 0.01-second interval 
	(TIMERPROC) ClockClassTimerProc); // timer callback
}

void CClock::countMiddle()
{
	middle.x = getLeft()+((getRight()-getLeft())/2);
	middle.y = getTop()+((getBottom()-getTop())/2);

	radius = ((getRight()-getLeft())/2);
}

VOID CALLBACK CClock::TimerProc( 
    HWND hWnd,        // handle to window for timer messages 
    UINT message,     // WM_TIMER message 
    UINT idTimer,     // timer identifier 
    DWORD dwTime)     // current system time 
{ 

	visare.x = int(cos(alpha) * (radius-10));
	visare.y = int(sin(alpha) * (radius-10));
	visare2.x = int(cos(alpha2) * (radius-20));
	visare2.y = int(sin(alpha2) * (radius-20));

	visare.x += middle.x;
	visare.y += middle.y;
	visare2.x += middle.x;
	visare2.y += middle.y;

	alpha  += float(RAD(3*360 / 40));
	alpha2 += float(RAD(360 / 40));

	RECT rc = {getLeft(),getTop(),getRight(),getBottom()};

	InvalidateRect(hWnd, &rc, NULL);

	counter++;
	if((counter/25) > time)
		KillTimer(hWnd, CLOCK_TIMER);
}