#include "stdafx.h"
#include ".\pile.h"

CPile::CPile(void)
{
	itsValue = 1;
	itsCompareValue = 1;
	compLarger = false;
}

CPile::~CPile(void)
{
}

void CPile::draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	draw(hdc);
	ReleaseDC(hWnd, hdc);
}

void CPile::draw(HDC hdc)
{
	int maxValue;
	if(itsValue > itsCompareValue)
		maxValue = itsValue;
	else
		maxValue = itsCompareValue;

	double div = 1;
	if(maxValue > (getBottom()-getTop()))
	{
		div = (getBottom()-getTop())/(maxValue*1.1);
	}
	int itsVTop = int(div*itsValue);
	int itsCTop = int(div*itsCompareValue);

	COLORREF white = RGB(255, 255, 255);
	COLORREF lightGreen = RGB(100, 200, 100);
	COLORREF green = RGB(0, 120, 0);
	COLORREF black = RGB(0, 0, 0);
	COLORREF red = RGB(255, 0,0);
	COLORREF orange = RGB(255, 128,0);
	
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, CreateSolidBrush(white));
	Rectangle(hdc, getLeft(), getTop(), getRight(), getBottom());

	HPEN pen = CreatePen(PS_SOLID, 0, green);
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
	SelectObject(hdc, CreateSolidBrush(green));

	Rectangle(hdc, getLeft()+1, getBottom()-itsVTop, getRight()-1, getBottom()-1);

	COLORREF compareColor;
	if(compLarger)
	{
		if(itsCompareValue > itsValue)
			compareColor = lightGreen;
		else
			compareColor = red;
	}
	else
	{
		if(itsCompareValue > itsValue)
			compareColor = orange;
		else
			compareColor = lightGreen;
	}

	pen = CreatePen(PS_SOLID, 0, compareColor);
	SelectObject(hdc, pen);
	SelectObject(hdc, CreateSolidBrush(compareColor));

	Rectangle(hdc, getLeft()+1, getBottom()-itsCTop, getRight()-1, getBottom()-itsVTop);

	pen = CreatePen(PS_SOLID, 1, black);
	SelectObject(hdc, pen);
	MoveToEx(hdc, getLeft(), getBottom()-itsVTop, NULL);
	LineTo(hdc, getRight(), getBottom()-itsVTop);

	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldPen);
	DeleteObject(pen);
}

void CPile::setCompareValue(int init)
{
	itsCompareValue = init;
}

void CPile::setChange(int init)
{
	itsCompareValue = itsValue - init;
}

void CPile::setValue(int init)
{
	itsValue = init;
}

void CPile::setCompLarger(bool init)
{
	compLarger = init;
}