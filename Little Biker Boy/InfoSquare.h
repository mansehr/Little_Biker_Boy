// InfoSquare.h: interface for the CObject class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __INFOSQUARE_H__
#define __INFOSQUARE_H__

#include "StaticText.h"

//TimerID
#define INFOSQR_TIMER		1101

class CInfoSquare : public CStaticText
{
public:
	CInfoSquare();

	void draw(HDC hdc);
	void draw(HWND hWnd);
	void drawSquare(bool init);

	void startTimer(HWND hWnd, String initId, char* itsText, int initX, int initY);
	void stopTimer(HWND hWnd, String initId, bool forced = false);

	void setPos(HWND hWnd, POINTS init);

	VOID CALLBACK TimerProc( HWND hWnd, UINT message, UINT idTimer, DWORD dwTime);
//	static CInfoSquare* getActiveinfoSqr();
private:
	bool showSquare;
	int counter;
	POINTS itsPoint;
	String itsId;
//	static CInfoSquare *activeInfSqr;
};

#endif