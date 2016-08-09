// Object.h: interface for the CObject class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "String.h"			// Used by the name
#include <Math.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CLOCK_TIMER			1100

class CObject  
{
public:
	CObject();
	virtual ~CObject();

	RECT	getItsPosition();
	RECT*	getRect();
	char*	getName();
	int		getLen();
	String	getString();

	virtual void	draw(HWND hWnd);
	virtual void	draw(HDC hdc);

	void	setName(char* initString);
	void	setPosition(RECT initPos);
	virtual void	setPosition(int left, int top, int right, int bottom);
// Position
	int		getLeft();
	int		getRight();
	int		getTop();
	int		getBottom();
	void	moveLeftTo(int init);
	void	moveRightTo(int init);
	void	moveTopTo(int init);
	void	moveBottomTo(int init);
	void	setLeft(int init);
	void	setRight(int init);
	void	setTop(int init);
	void	setBottom(int init);
private:
	RECT	itsPosition;
	String	sName;
};


enum Status { NORMAL = 1, NOT_PRESSABLE, MOUSE_OVER, ACTIVE, PRESSED };  //Status of the button

class CStatusObject : public CObject  
{
public:
	CStatusObject();
	virtual ~CStatusObject();

	virtual void	draw(HWND hWnd, bool forced = false);
	virtual void	draw(HDC hdc, bool forced = false);

	void	setStatus(Status initStatus);
	void	setOldStatus(Status initStatus);
	void	setStatusChanged(bool initStatusChanged);
	virtual int		test(int initX, int initY, HWND hWnd, bool keyPressed);

	Status	getStatus();
	Status	getOldStatus();
	bool	isStatusChanged();
	void	resetOldStatus();
	bool	isPressed();

private:
	Status itsStatus, oldStatus;
};


class CStaticText : public CObject  
{
public:
	CStaticText();
	virtual ~CStaticText();

	virtual void	draw(HDC hdc);
};

class CClock : public CObject
{
public: 
	CClock();
	~CClock();

	void	draw(HWND hWnd);
	void	draw(HDC hdc);

	void	start(HWND hWnd, int sec);

	VOID CALLBACK TimerProc( HWND hWnd, UINT message, UINT idTimer, DWORD dwTime);
private:
	POINT middle;
	POINT visare;
	POINT visare2;
	double alpha;
	double alpha2;
	int time;
	int counter;
	int radius;

	void countMiddle();
};

#endif // ifndef __OBJECT_H__
