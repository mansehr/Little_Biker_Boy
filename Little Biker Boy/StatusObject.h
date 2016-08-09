// StatusObject.h: interface for the CStatusObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSOBJECT_H__6D7BF297_2C59_45E0_90B7_5A1126B2CBAE__INCLUDED_)
#define AFX_STATUSOBJECT_H__6D7BF297_2C59_45E0_90B7_5A1126B2CBAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Object.h"
#include "infoSquare.h"

//Status of the button(StatusObject)
enum Status { NORMAL = 1, NOT_PRESSABLE, MOUSE_OVER, ACTIVE, PRESSED };  

class CStatusObject : public CObject  
{
public:
	CStatusObject();
	virtual ~CStatusObject();

	virtual void	draw(HWND hWnd, bool forced = false);
	virtual void	draw(HDC hdc, bool forced = false);

	void			setStatus(Status initStatus);
	void			setOldStatus(Status initStatus);
	void			setStatusChanged(bool initStatusChanged);
	virtual int		test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSquare, bool keyPressed);

	Status	getStatus();
	Status	getOldStatus();
	bool	isStatusChanged();
	void	resetOldStatus();
	bool	isPressed(bool resetStatus = true, Status resetTo = NORMAL);

	char*	getInfoText();
	void	setInfoText(char* init);

private:
	Status itsStatus, oldStatus;
	String infoText;
};


#endif // !defined(AFX_STATUSOBJECT_H__6D7BF297_2C59_45E0_90B7_5A1126B2CBAE__INCLUDED_)
