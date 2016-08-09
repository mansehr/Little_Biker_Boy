// Object.h: interface for the CObject class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __STATICTEXT_H__
#define __STATICTEXT_H__

#include "Object.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStaticText : public CObject  
{
public:
	CStaticText();
	virtual ~CStaticText();

	virtual void	draw(HWND hWnd);
	virtual void	draw(HDC hdc);

	void setBgMode(int init);
	void setBgColor(COLORREF init);
	void setFrame(COLORREF init);
	void setText(char* init);
	void setText(char* init, int nInit);
	void setText(int init);
	void setText(double init);
	void setTextColor(COLORREF init);
	void setFlags(UINT init);
	void setTextAlign(UINT init);
	void setTextHeight(int init);
	void setTextWeight(int init);
	void setItalict(bool init);
	void setMargin(int init);
	void setTopMargin(int init);
	void setRightMargin(int init);
	void setBottomMargin(int init);
	void setLeftMargin(int init);

	char*	getText();
	int		getTextLen();

private:
	RECT	itsMargin;
	bool	italic;
    long	lfHeight;
	int		itsBgMode;
	COLORREF itsBgColor;
	COLORREF itsFrameColor;
	COLORREF itsTextColor;
	int		itsWeight;
	String	itsText;
	UINT	extraFlags;
	UINT	textAlign;
	HFONT	itsFont;

	void setFont();
};

#endif // ifndef __STATICTEXT_H__