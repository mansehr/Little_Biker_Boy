
/////////////////////////////////////////////////
//
//		File: MenuButton.cpp
//
//		Description: Deklare the funktions for the MenuButton class.
//
////////////////////////////////////////////////

#include "stdAfx.h"
#include "MenuButton.h"

#ifndef __MenuButton_cpp__
#define __MenuButton_cpp__

CMenuButton::CMenuButton()
{
	bmpActive		= NULL;
	bmpMouseOver	= NULL;
	bmpPressed		= NULL;
	bmpNormal		= NULL;
	maskActive		= NULL;
	maskMouseOver	= NULL;
	maskPressed		= NULL;
	maskNormal		= NULL;					
}

void CMenuButton::draw(HWND initHWnd, bool forced)
{
	if( isStatusChanged() || forced)		// If status is changed
	{												// Then draw the button again
		HDC hdc			= GetDC(initHWnd);
		draw(hdc, forced);
		ReleaseDC(initHWnd, hdc);
	}
}

void CMenuButton::draw(HDC hdc, bool forced)
{
	//FillRect(hdc, getRect(), NULL);

	if( isStatusChanged() || forced)		// If status is changed
	{												// Then draw the button again		
		switch(getStatus())
		{
			case ACTIVE:	 bmp = bmpActive;	mask = maskActive; break;
			case MOUSE_OVER: bmp = bmpMouseOver;mask = maskMouseOver; break;
			case PRESSED:	 bmp = bmpPressed;	mask = maskPressed; break;
			case NORMAL:	 bmp = bmpNormal;	mask = maskNormal; break;
			default:		 bmp = bmpNormal;	mask = maskNormal; break;
		}
		if (bmp == 0)					// If display isnt a bitmap
			if (bmpNormal != 0)					// If Normal IS a loaded bitmap
			{
				bmp	= bmpNormal;		// Display is Normal bitmap
				mask = maskNormal;
			}
			else								// If Normal ISN'T loaded
				return;							// Exit draw
				
		DrawBitmapWithMask(hdc, mask, bmp, getLeft(), getTop());
	}
}

int CMenuButton::test(int initX, int initY, HWND hWnd, bool keyPressed)
{
	if(bmpNormal && getRight() == 0 && getBottom() == 0)
	{
		BITMAP bm;
		GetObject(bmpNormal, sizeof(BITMAP), (LPVOID) &bm);
		setRight(getLeft() + bm.bmWidth);
		setBottom(getTop()  + bm.bmHeight);
	}
	if(getStatus() != NOT_PRESSABLE)
		if(initX > getLeft() && initX < getRight()
		&& initY > getTop()  && initY < getBottom() )
		{
			if( getStatus() == ACTIVE && !keyPressed)		// If key Realeased
					setStatus(PRESSED);						// Then status changes to pressed

			if( getStatus() != PRESSED )					// If status NOT equal to Pressed
			{
				if(keyPressed)							// If key is pressed
					setStatus(ACTIVE);					// Status is Active
				else
					setStatus(MOUSE_OVER);				// Otherwise status is Mouse over
			}
		}
		else if(bStayActive)
		{
			setStatus(ACTIVE);							// Mouse was outside the button, but vill still be active
		}
		else
			setStatus(NORMAL);							// Mouse was outside the button

	if(isStatusChanged())
	{
		if(!bStayActive)
			resetOldStatus();
		else
			setStatus(ACTIVE);

		InvalidateRect(hWnd, getRect(), FALSE);
		return 1;								// return 1 because status was changed
	}
	else
		return 0;
}

int CMenuButton::LoadABitmap(LPSTR szFileName, Status buttonType)
{
	HBITMAP theBmp = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if(!theBmp)
		return 0;
	setBitmap(theBmp, buttonType);
	return 1;
}

void CMenuButton::setBitmap(HBITMAP initBitmap, Status buttonType)
{
	switch(buttonType)
	{
		case ACTIVE:	 bmpActive	 = initBitmap; maskActive	 = CreateBitmapMask(initBitmap, maskColor); break;
		case MOUSE_OVER: bmpMouseOver= initBitmap; maskMouseOver = CreateBitmapMask(initBitmap, maskColor); break;
		case PRESSED:	 bmpPressed	 = initBitmap; maskPressed	 = CreateBitmapMask(initBitmap, maskColor); break;
		default:		 bmpNormal	 = initBitmap; maskNormal	 = CreateBitmapMask(initBitmap, maskColor);
	}

}

void CMenuButton::stayActive(bool init)
{
	bStayActive = init;
}

void CMenuButton::setMaskColor(COLORREF initMask)
{
	maskColor = initMask;
	if(bmpActive)
		maskActive	 = CreateBitmapMask(bmpActive, maskColor);
	if(bmpMouseOver)
		maskMouseOver = CreateBitmapMask(bmpMouseOver, maskColor);
	if(bmpPressed)
		maskPressed	 = CreateBitmapMask(bmpPressed, maskColor);
	if(bmpNormal)
		maskNormal	 = CreateBitmapMask(bmpNormal, maskColor);
}

#endif // __MenuButton_cpp__