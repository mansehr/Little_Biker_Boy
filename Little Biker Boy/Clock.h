// Clock.h: interface for the CObject class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "Object.h"			// Used by the name

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CLOCK_TIMER			1100	// TimerID

class CClock : public CObject
{
public: 
	CClock();
	~CClock();

	void	draw(HWND hWnd);
	void	draw(HDC hdc);

	int		LoadBack(LPSTR szFileName);
	void	setMiddle(int initX, int initY);

	void	start(HWND hWnd, int sec);

	VOID CALLBACK TimerProc( HWND hWnd, UINT message, UINT idTimer, DWORD dwTime);
private:
	POINT middle;
	POINT visare;
	POINT visare2;
	double alpha;
	double alpha2;
	int speed;
	int counter;
	int radius;
	bool backIsLoaded;

	CBitmapWithMask back;
	void recount();
};

#endif