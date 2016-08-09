#include "stdafx.h"
#include ".\pile.h"

CPile::CPile(void)
{
	itsValue = 1;
	itsChange = 0;
	itsCompareValue = 0;
	itsMultiply = 1;
	compLarger = false;
	itsValueText.setBgMode(TRANSPARENT);
	itsValueText.setFlags(DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	itsValueText.setText("");
	itsCompareText.setBgMode(TRANSPARENT);
	itsCompareText.setFlags(DT_SINGLELINE | DT_TOP| DT_CENTER);
	itsCompareText.setText("");
	itsChangeText.setBgMode(TRANSPARENT);
	itsChangeText.setFlags(DT_SINGLELINE | DT_BOTTOM| DT_CENTER);
	itsChangeText.setText("");
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
	/**/itsValueText.setPosition(getItsPosition());
	itsCompareText.setPosition(getItsPosition());
	itsChangeText.setPosition(getItsPosition());
	/*
	itsValueText.setPosition(getLeft(), getBottom()-20, getRight(), getBottom());
	itsCompareText.setPosition(getItsPosition());
	itsChangeText.setPosition(getLeft(), getTop()+(getHeight()/2), getRight(), getBottom());*/

	int tempValue = int(itsValue*itsMultiply);
	int tempCompare = int(itsCompareValue*itsMultiply);
	int tempChange = int(itsChange*itsMultiply);

	int maxValue;
	if(itsValue > tempCompare)
		maxValue = tempValue;
	else
		maxValue = tempCompare;

	double div = 1;
	if(maxValue > getHeight())
	{
		div = getHeight()/(maxValue*1.1);
	}
	int itsVTop = int(div*tempValue);
	int itsCTop = int(div*tempCompare);
	int itsCHTop = int(div*tempChange);

	COLORREF white = RGB(255, 255, 255);
	COLORREF lightGreen = RGB(100, 200, 100);
	COLORREF green = RGB(0, 120, 0);
	COLORREF black = RGB(0, 0, 0);
	COLORREF red = RGB(255, 0,0);
	COLORREF orange = RGB(255, 128,0);

	HBRUSH compareBrush;
	HBRUSH whiteBrush = CreateSolidBrush(white);
	HBRUSH greenBrush = CreateSolidBrush(green);
	
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, whiteBrush);
	Rectangle(hdc, getLeft(), getTop(), getRight(), getBottom());

	HPEN pen = CreatePen(PS_SOLID, 0, green);
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
	SelectObject(hdc, greenBrush);

	Rectangle(hdc, getLeft()+1, getBottom()-itsVTop, getRight()-1, getBottom()-1);

	COLORREF compareColor;
	if(compLarger)
	{
		compareColor = lightGreen;
	}
	else
	{
		if(itsCompareValue > itsValue)
			compareColor = red;
		else
			compareColor = lightGreen;
	}

	DeleteObject(pen);
	pen = CreatePen(PS_SOLID, 0, compareColor);
	SelectObject(hdc, pen);
	compareBrush = CreateSolidBrush(compareColor);
	SelectObject(hdc, compareBrush);

	if(itsCompareValue != 0)
		Rectangle(hdc, getLeft()+1, getBottom()-itsCTop, getRight()-1, getBottom());

	if(compLarger)
	{
		compareColor = lightGreen;
		if(itsVTop >= getHeight())
			itsCHTop = 0;
		else if((itsVTop+itsCHTop) > getHeight())
			itsCHTop = getHeight() - itsVTop;
	}
	else
	{
		if(itsCompareValue > itsValue)
			compareColor = red;
		else
			compareColor = orange;
	}

	DeleteObject(pen);
	pen = CreatePen(PS_SOLID, 0, compareColor);
	SelectObject(hdc, pen);
	DeleteObject(compareBrush);
	compareBrush = CreateSolidBrush(compareColor);
	SelectObject(hdc, compareBrush);

	if((0-itsCHTop) > itsVTop)
		itsCHTop = (0-itsVTop);

	if(itsChange != 0)
		Rectangle(hdc, getLeft()+1, getBottom()-itsCHTop-itsVTop, getRight()-1, getBottom()-itsVTop);

	DeleteObject(pen);
	pen = CreatePen(PS_SOLID, 1, black);
	SelectObject(hdc, pen);
	MoveToEx(hdc, getLeft(), getBottom()-itsVTop, NULL);
	LineTo(hdc, getRight(), getBottom()-itsVTop);

	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldPen);
	DeleteObject(pen);
	DeleteObject(whiteBrush);
	DeleteObject(greenBrush);
	DeleteObject(compareBrush);

	itsValueText.draw(hdc);
	if(itsCompareValue != 0)
		itsCompareText.draw(hdc);
	if(itsChange != 0)
		itsChangeText.draw(hdc);
	
	//MB(itsValueText.getText());
}

void CPile::setCompareValue(int init)
{
	itsCompareValue = init;
	if(itsCompareValue < 0)
		itsCompareText.setText((-itsCompareValue));
	else
		itsCompareText.setText(itsCompareValue);
//	MB_INT((-itsCompareValue))
}

void CPile::setChange(int init)
{
	itsChange = init;
	if(itsChange < 0)
		itsChangeText.setText((-itsChange));
	else
		itsChangeText.setText(itsChange);
//	MB_INT((-itsCompareValue))
}

void CPile::setValue(int init)
{
	itsValue = init;
	itsValueText.setText(init);
}

void CPile::setCompLarger(bool init)
{
	compLarger = init;
}

void CPile::setMultiply(float init)
{
	itsMultiply = init;
}