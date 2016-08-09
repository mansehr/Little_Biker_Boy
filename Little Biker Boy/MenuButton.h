#ifndef __MenuButton_h__
#define __MenuButton_h__

#include "Object.h"
#include "Bitmap.h"


class CMenuButton : public CBitmapWithMask, public CStatusObject
{																	//Button class
public:
	CMenuButton();
	
	// CLASS FUNCTIONS ////////////////////////////////
	void	draw(HWND initHWnd, bool forced = false);
	void	draw(HDC hdc, bool forced = false);
	int		test(int initX, int initY, HWND hWnd, bool keyPressed = false);
	int		LoadABitmap(LPSTR szFileName, Status buttonType);
	void	setBackground(HDC initHdc);
	void	setBitmap(HBITMAP initBitmap, Status buttonType);
	void	setMaskColor(COLORREF initMask);
	void	stayActive(bool init);

private:
	bool bStayActive;
	HBITMAP bmpActive, bmpMouseOver, bmpPressed, bmpNormal;		// Difrent bitmaps for difrent statuses
	HBITMAP maskActive, maskMouseOver, maskPressed, maskNormal;	// Masks for the bitmaps
};

#endif // __MenuButton_h__