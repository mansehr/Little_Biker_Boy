// StatusObject.cpp: implementation of the CStatusObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatusObject.h"


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

int CStatusObject::test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSquare, bool keyPressed)
{
	//MessageBox(hWnd, "I status objects TEST ska vi inte va", "Inte Här", MB_OK);

	if(getStatus() == MOUSE_OVER)
	{
		theInfoSquare.startTimer(hWnd, getString(), getInfoText(), initX, initY);
	}
	else if(getStatus() == NORMAL || getStatus() == PRESSED)
		theInfoSquare.stopTimer(hWnd, getString());		// Stop Drawing the timer, the name is the id

	if(isStatusChanged())
		return 1;								// return 1 because status was changed
	else
		return 0;
}

bool CStatusObject::isPressed(bool resetStatus, Status resetTo)
{
	if(itsStatus == PRESSED)			// If status is Pressed
	{
#ifdef DEBUGMED
		Logg(this->getName(), "Is Pressed");
#endif
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


char*	CStatusObject::getInfoText()
{
	return infoText.getString();
}

void	CStatusObject::setInfoText(char* init)
{
	infoText = init;
}
