// Room.cpp: implementation of the CRoom class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Room.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRoom::CRoom()
{
	nActiveSprite = 0;
	nObjects = 0;
	nStatusObjects = 0;
}

CRoom::~CRoom()
{

}

int CRoom::LoadBack(LPSTR szFileName)
{
	return spriteBack.LoadABitmap(szFileName, false);
}

void CRoom::draw(HWND hWnd, bool forced)
{
	HDC hdc			= GetDC(hWnd);
	this->draw(hdc, forced);
	ReleaseDC(hWnd, hdc);
}

void CRoom::draw(HDC hdc, bool forced)
{
	spriteBack.draw(hdc);
	for(int i = 0; i < nObjects; i++)
		itsObjects[i]->draw(hdc);
	for(int i = 0; i < nActiveSprite; i++)
		activeSprite[i]->draw(hdc, forced, NULL);
	for(int i = 0; i < nStatusObjects; i++)
		itsStatusObjects[i]->draw(hdc, forced);
}

void CRoom::addSprite(CActiveSprite* initSprite)
{
	if(nActiveSprite < MAXROOMOBJECTS)
		activeSprite[nActiveSprite++] = initSprite;
	else
	{
		MB("ActiveSprite in room oveflow")
		Logg("ActiveSprite in room oveflow");
	}
}

void CRoom::addObject(CObject *init)
{
	if(nObjects < MAXROOMOBJECTS)
		itsObjects[nObjects++] = init;
	else
	{
		MB("CObject in room oveflow")
		Logg("CObject in room oveflow");
	}
}

void CRoom::addObject(CStatusObject *init)
{
	if(nStatusObjects < MAXROOMOBJECTS)
		itsStatusObjects[nStatusObjects++] = init;
	else
	{
		MB("CStatusObject in room oveflow")
		Logg("CStatusObject in room oveflow");
	}
}

int CRoom::test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSqr, bool keyPressed)
{

	for(int i = 0; i < nStatusObjects; i++)
		if(itsStatusObjects[i]->test(initX, initY, hWnd, theInfoSqr, keyPressed))
			InvalidateRect(hWnd, itsStatusObjects[i]->getRect(), false);//itsStatusObjects[i]->draw(hWnd);

	// Goes trough all of the activesprites objects and if any is active then that ones is 
	// tested and maybe repainted... Then the function quits.
	for(int i = 0; i < nActiveSprite; i++)
		if( activeSprite[i]->getStatus() == ACTIVE || activeSprite[i]->getStatus() == MOUSE_OVER)
		{
			if(activeSprite[i]->test(initX, initY, hWnd, theInfoSqr, keyPressed))
			{				
				// Have to call the invalidate rect funtion for win 98;
				InvalidateRect(hWnd, activeSprite[i]->getRect(), false);
				//activeSprite[i]->draw(hWnd, spriteBack.getBitmap(), false);

				/*char szBuffer[64];
				wsprintf(szBuffer, "Left:%d: Right:%d: Top:%d: Bottom:%d",activeSprite[i]->getRect()->left,
													activeSprite[i]->getRect()->right,
													activeSprite[i]->getRect()->top,
													activeSprite[i]->getRect()->bottom);
				if(i > 1)
					MB_HWND(szBuffer)*/
			}
			return 1;
		}
	// If no activesprite object is active then this loop goes trough ALL objects...

	for(int i = 0; i < nActiveSprite; i++)
	{
		if(activeSprite[i]->test(initX, initY, hWnd, theInfoSqr, keyPressed))
		{
			//activeSprite[i]->draw(hWnd, false, NULL);
			InvalidateRect(hWnd, activeSprite[i]->getRect(), false);
			return 1;
		}
	}

	return 0;
}
