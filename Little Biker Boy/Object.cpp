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

void CObject::setName(char* initString)
{
	sName = initString;
}

char* CObject::getName()
{
	return sName.getString();
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

RECT CObject::getItsPosition()
{
	return itsPosition;
}

int CObject::getLen()
{
	return sName.getLen();
}

RECT* CObject::getRect()
{
	return &itsPosition;
}

String CObject::getString()
{
	return sName;
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