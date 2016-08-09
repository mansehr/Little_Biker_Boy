// StaticText.cpp: implementation of the CObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StaticText.h"

//////////////////////////////////////////////////////////////////////
//
// CLASS: CSTATICTEXT
//
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CStaticText::CStaticText()
{
	itsMargin.bottom = 0;
	itsMargin.left = 0;
	itsMargin.right = 0;
	itsMargin.top = 0;
	itsBgMode = OPAQUE;
	itsText = "";
	itsWeight = FW_NORMAL;
	extraFlags = NULL;
	textAlign = NULL;
	lfHeight	= 0;
	italic		= false;
	itsBgColor = -1;
	itsFrameColor = -1;
	itsTextColor = -1;
	itsFont = NULL;
	setFont();
}

CStaticText::~CStaticText()
{
	DeleteObject(itsFont);
	itsFont = NULL;
}

void CStaticText::draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	draw(hdc);
	ReleaseDC(hWnd, hdc);
}

void CStaticText::draw(HDC hdc)
{
	int oldMode = -1;
	int oldBgColor = -1;
	int oldTextColor = -1;
	int oldPen = -1;
	HPEN itsFrame = (HPEN)-1;
	HPEN oldFrame = (HPEN)-1;
	HFONT oldHf;
	UINT oldAlign;

	if(itsFrameColor != -1)
	{
		itsFrame = CreatePen(PS_SOLID, 1, itsFrameColor);
		oldFrame = (HPEN)SelectObject(hdc, itsFrame);
	}
	else
	{
		itsFrame = CreatePen(PS_SOLID, 1, itsBgColor);
		oldFrame = (HPEN)SelectObject(hdc, itsFrame);
	}

	if(itsBgMode == TRANSPARENT)
		oldMode = SetBkMode(hdc, itsBgMode);
	else
	{
		oldMode= SetBkMode(hdc, itsBgMode);
		oldBgColor = SetBkColor(hdc, itsBgColor);
	}

	if(itsTextColor != -1)
	{
		oldTextColor = SetTextColor(hdc, itsTextColor);
	}

	if(itsBgColor != -1)
	{
		HBRUSH itsBgBrush;
		itsBgBrush = CreateSolidBrush(itsBgColor);
		FillRect(hdc, getRect(), itsBgBrush);
		DeleteObject(itsBgBrush);
	}
	else if(itsFrameColor != -1)
	{
		HBRUSH itsFrameBrush;
		itsFrameBrush = CreateSolidBrush(itsBgColor);
		FrameRect(hdc, getRect(), itsFrameBrush);
		DeleteObject(itsFrameBrush);
	}

    oldHf = (HFONT)SelectObject(hdc, itsFont);

	oldAlign = SetTextAlign(hdc, textAlign);

	RECT drawRect = *getRect();
	drawRect.left += itsMargin.left;
	drawRect.top  += itsMargin.top;
	drawRect.right -= itsMargin.right;
	drawRect.bottom -= itsMargin.bottom;

    DrawText(hdc, itsText.getString(), -1, &drawRect, DT_WORDBREAK |DT_EXPANDTABS | extraFlags);

	if(itsFrameColor != -1)
	{
		HBRUSH frameBrush = CreateSolidBrush(itsFrameColor);
		FrameRect(hdc, getRect(), frameBrush);
		DeleteObject(frameBrush);
	}

	SelectObject(hdc, oldHf);
	DeleteObject(oldHf);
	SelectObject(hdc, oldFrame);
	DeleteObject(oldFrame);
	DeleteObject(itsFrame);

	if(oldAlign != -1)
		SetTextAlign(hdc, oldAlign);
	if(oldBgColor != -1)
		SetBkColor(hdc, oldBgColor);
	if(oldTextColor != -1)
		SetTextColor(hdc, oldTextColor);
	if(oldMode != -1)
		SetBkMode(hdc, oldMode);
}

void CStaticText::setFlags(UINT init)
{
	extraFlags = init;
}

void CStaticText::setFrame(COLORREF init)
{
	itsFrameColor = init;
}

void CStaticText::setTextAlign(UINT init)
{
	textAlign = init;
}

void CStaticText::setTextHeight(int init)
{
	lfHeight = init;
	setFont();
}

void CStaticText::setTextWeight(int init)
{
	itsWeight = init;
	setFont();
}

void CStaticText::setItalict(bool init)
{
	italic = init;
	setFont();
}

void CStaticText::setMargin(int init)
{
	itsMargin.bottom = init;
	itsMargin.left = init;
	itsMargin.right = init;
	itsMargin.top = init;
}

void CStaticText::setLeftMargin(int init)
{
	itsMargin.left = init;
}

void CStaticText::setTopMargin(int init)
{
	itsMargin.top = init;
}

void CStaticText::setRightMargin(int init)
{
	itsMargin.right = init;
}

void CStaticText::setBottomMargin(int init)
{
	itsMargin.bottom = init;
}

void CStaticText::setBgMode(int init)
{
	itsBgMode = init;
}

void CStaticText::setBgColor(COLORREF init)
{
	itsBgColor = init;
}

void CStaticText::setText(char* init)
{
	itsText = init;
}

void CStaticText::setText(char* init, int nInit)
{
	char buffer[MAX_BUFFER];
	wsprintf(buffer, "%s : %i", init, nInit);
	itsText = buffer;
}

void CStaticText::setText(int init)
{
	char* temp = IntToChar(init);
	itsText = temp;
	delete[] temp;
}

void CStaticText::setText(double init)
{
	char* temp = DoubleToChar(init);
	itsText = temp;
	delete[] temp;
}

void CStaticText::setTextColor(COLORREF init)
{
	itsTextColor = init;
}

char* CStaticText::getText()
{
	return itsText.getString();
}

int CStaticText::getTextLen()
{
	return itsText.getLen();
}

void CStaticText::setFont()
{
	DeleteObject(itsFont);
	itsFont = NULL;
 	itsFont		=	CreateFont(lfHeight, 0, 0, 0, itsWeight, italic, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");
	if(!itsFont)
    {
		Logg("Font creation failed!");
        MessageBox(NULL, "Font creation failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
    }
}