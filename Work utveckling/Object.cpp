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

int CObject::getWCenter()
{
	return (getRight() - getLeft());
}

int CObject::getHCenter()
{
	return (getBottom() - getTop());
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

int CObject::getHeight()
{
	return (getBottom() - getTop());
}

int CObject::getWidth()
{
	return (getRight() - getLeft());
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

void CStatusObject::setOldStatus(Status initStatus)
{
		oldStatus = initStatus;
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

bool CStatusObject::isPressed(bool resetStatus, Status resetTo)
{
	if(itsStatus == PRESSED)			// If status is Pressed
	{
		if(resetStatus)					// Reset status
			itsStatus = resetTo;		// reset to other than normal if ititiated
		return true;					// Return true
	}
	else
		return false;					// Else return false
}

bool CStatusObject::isStatusChanged()
{
	if(oldStatus != itsStatus)
		return true;
	else 
		return false;
}

void CStatusObject::resetOldStatus()
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
	itsBgMode = OPAQUE;
	itsText = "";
	itsWeight = FW_NORMAL;
	extraFlags = NULL;
	textAlign = NULL;
	lfHeight	= 0;
	italic		= false;
	itsBgColor = -1;
	itsFrameColor = -1;
}

CStaticText::~CStaticText()
{

}

void CStaticText::draw(HDC hdc)
{
	int oldMode = -1;
	int oldBgColor = -1;
	int oldPen = -1;
	HPEN itsFrame = (HPEN)-1;
	HPEN oldFrame = (HPEN)-1;
	HFONT oldHf;
	UINT oldAlign;

	HFONT hf = CreateFont(lfHeight, 0, 0, 0, itsWeight, italic, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");

    if(!hf)
    {
        MessageBox(NULL, "Font creation failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
    }
	if(itsFrameColor != -1)
	{
		itsFrame = CreatePen(PS_SOLID, 1, itsFrameColor);
		oldFrame = (HPEN)SelectObject(hdc, itsFrame);
	}
	else
	{
		itsFrame = CreatePen(PS_SOLID, 1, itsBgColor);
		oldFrame = (HPEN)SelectObject(hdc, itsFrame);
	}



	if(itsBgMode == TRANSPARENT)
		oldMode = SetBkMode(hdc, itsBgMode);
	else
	{
		oldMode= SetBkMode(hdc, itsBgMode);
		oldBgColor = SetBkColor(hdc, itsBgColor);
	}

	if(itsBgColor != -1)
		Rectangle(hdc, getLeft(), getTop(), getRight(), getBottom());
	else if(itsFrameColor != -1)
		FrameRect(hdc, getRect(), CreateSolidBrush(itsFrameColor));

	oldAlign = SetTextAlign(hdc, textAlign);
    oldHf = (HFONT)SelectObject(hdc, hf);

    DrawText(hdc, itsText.getString(), -1, getRect(), DT_WORDBREAK | DT_EXPANDTABS | extraFlags);

	if(itsFrameColor != -1)
		FrameRect(hdc, getRect(), CreateSolidBrush(itsFrameColor));

	SelectObject(hdc, oldHf);
	DeleteObject(oldHf);
	DeleteObject(hf);
	SelectObject(hdc, oldFrame);
	DeleteObject(oldFrame);
	DeleteObject(itsFrame);

	if(oldAlign != -1)
		SetTextAlign(hdc, oldAlign);
	if(oldBgColor != -1)
		SetBkColor(hdc, oldBgColor);
	if(oldMode != -1)
		SetBkMode(hdc, oldMode);
}

void CStaticText::setFlags(UINT init)
{
	extraFlags = init;
}

void CStaticText::setFrame(COLORREF init)
{
	itsFrameColor = init;
}

void CStaticText::setTextAlign(UINT init)
{
	textAlign = init;
}

void CStaticText::setTextHeight(int init)
{
	lfHeight = init;
}

void CStaticText::setTextWeight(int init)
{
	itsWeight = init;
}

void CStaticText::setItalict(bool init)
{
	italic = init;
}

void CStaticText::setBgMode(int init)
{
	itsBgMode = init;
}

void CStaticText::setBgColor(COLORREF init)
{
	itsBgColor = init;
}

void CStaticText::setText(char* init)
{
	itsText = init;
}

void CStaticText::setText(int init)
{
	char* temp = IntToChar(init);
	itsText = temp;
	delete[] temp;
}

void CStaticText::setText(double init)
{
	char* temp = DoubleToChar(init);
	itsText = temp;
	delete[] temp;
}

char* CStaticText::getText()
{
	return itsText.getString();
}

//////////////////////////////////////////////////////////////////////
//
// CLASS: CDIAGRAM
//
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDiagram::CDiagram()
{
	for(int i = 0; i < MAX_DIAGRAMDOTS; i++)
		itsValues[i] = 0;

	antValues = 0;
}

CDiagram::~CDiagram()
{

}

void CDiagram::setDiagramDots(int *initPt, int initAnt)
{
	for(int i = 0; i < initAnt && i < MAX_DIAGRAMDOTS; i++)
		itsValues[i] = initPt[i];

	antValues = initAnt;
}

void CDiagram::draw(HDC hdc)
{
	if(antValues > 0)
	{
		// Calculate the spots and zoom of the diagram
		float maxValue = 0;
		for(int i = 0; i < antValues; i++)
			if(itsValues[i] > maxValue)
				maxValue = float(itsValues[i]);
		
		float addY = float(getHeight()/(maxValue*1.1));
		float addX = float(getWidth()/antValues);


		HPEN whitePen	= CreatePen(PS_SOLID, 0, RGB(255,255,255));
		HPEN redPen		= CreatePen(PS_SOLID, 0, RGB(255,  0,  0));
		//HPEN bluePen	= CreatePen(PS_SOLID, 0, RGB(0,  0,  255));
		
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0))); 
		HPEN oldPen = (HPEN)SelectObject(hdc, whitePen);
		Rectangle(hdc, getLeft(), getTop(), getRight(), getBottom());

		for(i = 1; i < antValues; i++)
		{
			MoveToEx(hdc, int(getLeft()+(i*addX)+1), int(getBottom()-(0.05*getHeight())), NULL);
			LineTo(hdc, int(getLeft()+(i*addX)+1), getBottom());
		}

		SelectObject(hdc, redPen);

		MoveToEx(hdc, getLeft()+1, int(getBottom()-(itsValues[0]*addY)-2), NULL);
		for(i = 1; i < antValues; i++)
		{
			if((itsValues[i]*addY)-2 < getHeight())
				LineTo(hdc, int(getLeft()+(i*addX)+1), int(getBottom()-(itsValues[i]*addY)-2));
		}
		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
	//	MB("Drawn")
	}
	//MB("Ojdå")
}

int CDiagram::getAntValues()
{
	return this->antValues;
}

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
//	alpha = RAD(-87);
//	alpha2 = RAD(-87);
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
//	alpha  += float(RAD(4) * speed);
//	alpha2 += float(RAD(0.333333333) * speed);

	RECT rc = {getLeft(),getTop(),getRight(),getBottom()};

	InvalidateRect(hWnd, &rc, NULL);

	counter++;
	if((counter/27) >= 2)				// 2 (Two) seconds long animation
		KillTimer(hWnd, CLOCK_TIMER);
}