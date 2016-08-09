// Room.h: interface for the CRoom class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __ROOM_H__
#define __ROOM_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define MAX_ACTIVESPRITE_POINTERS 10

#include "Sprite.h"
#include "List.h"
#include "stdAfx.h"

#define MAXROOMOBJECTS 14

class CRoom  
{
public:
	CRoom();
	virtual ~CRoom();

	void draw(HWND hWnd, bool forced = true);
	void draw(HDC hdc, bool forced = true);
	void addSprite(CActiveSprite* initSprite);
	void addObject(CStatusObject* init);
	void addObject(CObject* init);
	int test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSqr, bool keyPressed);

	int LoadBack(LPSTR szFileName);

private:
	CSprite spriteBack;
	CActiveSprite* activeSprite[MAXROOMOBJECTS];
	CStatusObject* itsStatusObjects[MAXROOMOBJECTS];
	CObject* itsObjects[MAXROOMOBJECTS];
	int nActiveSprite;
	int nObjects;
	int nStatusObjects;
};

#endif // __ROOM_H__
