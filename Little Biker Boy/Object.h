// Object.h: interface for the CObject class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "String.h"			// Used by the name
#include "Bitmap.h"	
#include <Math.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	int		getWCenter();
	int		getHCenter();
	int		getHeight();
	int		getWidth();
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

#endif // ifndef __OBJECT_H__
