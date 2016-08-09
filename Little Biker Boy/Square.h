// Square.h: interface for the CSquare class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __Square_h__
#define __Square_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Room.h"

#define BOX_TIMER	1992

VOID	CALLBACK SquareClassTimerProc(HWND hwnd,UINT message,UINT idTimer, DWORD dwTime);



class CSquare : public CRoom, public CStatusObject
{
public:
	CSquare();
	virtual ~CSquare();
	
	// CLASS FUNCTIONS ////////////////////////////////
	void	draw(HWND initHWnd, bool forced = false);
	void	draw(HDC hdc, bool forced = false);
	void	drawFrame(HWND hWnd);
	void	setMarginAndMove(int initMargin, int initMove);
	void	setBackColor(COLORREF initBack);

	int		test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSqr, bool keyPressed);

// Show and close (Used to start the moving)
	void	showSquare(HWND hWnd, RECT* rc);
	void	showSquare(HWND hWnd, int x, int y);
	void	closeSquare(HWND hWnd);
// Timer proc
	VOID	CALLBACK SquareTimerProc(HWND hwnd,UINT message,UINT idTimer, DWORD dwTime);

protected:
	COLORREF	backColor;
	HBRUSH		itsBrush;
	int			move;
	int			margin;
	bool		reziseBox;
	bool		close;
	int			frame;
};

#endif // ifndef __Square_h__
