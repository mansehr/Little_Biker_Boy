
#include "stdAfx.h"
#include "sprite.h"

CSprite::CSprite()
{

}

void CSprite::draw(HDC hdc)
{
	if( mask != NULL )
	{
		DrawBitmapWithMask(hdc, mask, bmp, getLeft(), getTop(), bm);
	}
	else
	{
		DrawBitmap(hdc, bmp, getLeft(), getTop(), bm.bmWidth, bm.bmHeight);
		/*HDC hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, bmp);
		BitBlt(hdc, getLeft(), getTop(), bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		DeleteDC(hdcMem);*/
	}
}

void CSprite::setPosition(int left, int top, int bottom, int right)
{
	CObject::setPosition(left, top, bottom, right);
}







//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CActiveSprite::CActiveSprite()
{
	activeBmp		= NULL;
	activeMask		= NULL;
	klick			= NULL;
}

void CActiveSprite::draw(HWND hWnd, bool forced, HBITMAP* back)
{
	HDC hdc			= GetDC(hWnd);
	draw(hdc,  forced, back);
	ReleaseDC(hWnd, hdc);
}

void CActiveSprite::draw(HDC hdc, bool forced, HBITMAP* back)
{
	if( isStatusChanged() || forced)		// If status is changed
	{												// Then draw the button again
		resetOldStatus();					// Reset the status
		HBITMAP* drawMask, *drawBmp;
		BITMAP drawBm;
		switch(getStatus())
		{
			case ACTIVE:		// Active has the same picture as Mouse_Over
			case MOUSE_OVER: if(activeMask != NULL)
							 {
								drawMask = &activeMask; 
								drawBmp = &activeBmp;
								drawBm = activeBm;
							 }
				break;
			case NORMAL:	drawMask = &mask; 
							drawBmp = &bmp; 
							drawBm = bm;
				break;
			default:		drawMask = &mask; 
							drawBmp = &bmp;
							drawBm = bm;
				break;
		}

		if(back == NULL)
		{
			DrawBitmapWithMask(hdc, *drawMask, *drawBmp, getLeft(), getTop(), drawBm);
		}
		else
		{
			DrawBitmapWithMaskAndBackBitmap(hdc, *drawMask, *drawBmp, back, getLeft(), getTop(), drawBm);
		}

		//DeleteObject(drawMask);
		//DeleteObject(drawBmp);
	}
}

int CActiveSprite::LoadActiveBitmap(LPSTR szFileName, bool createMask)
{
	activeBmp = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	GetObject(activeBmp, sizeof(activeBm), &activeBm);

	if(!activeBmp)
		return 0;
	else if(createMask)
		activeMask = CreateBitmapMask(activeBmp, maskColor);
	else 
		activeMask = NULL;
	return 1;
}

void CActiveSprite::setMaskColor(COLORREF initMask)
{
	CBitmapWithMask::setMaskColor(initMask);
	if(activeBmp && activeMask)
		activeMask = CreateBitmapMask(activeBmp, initMask);
}

void CActiveSprite::setLeft(int init)
{
	activeRect.left = init;
	CObject::setLeft(init);
}

void CActiveSprite::setTop(int init)
{
	activeRect.top = init;
	CObject::setTop(init);
}

RECT* CActiveSprite::getRect()
{
	if(getStatus() == MOUSE_OVER || getStatus() == ACTIVE)
		return &activeRect;
	else
		return CObject::getRect();
}

void CActiveSprite::setPosition(int left, int top, int bottom, int right)
{
	activeRect.left = left;
	activeRect.top = top;
	CObject::setPosition(left, top, bottom, right);
}

void CActiveSprite::setSound(CSound *init)
{
	klick = init;
}

int CActiveSprite::test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSqr, bool keyPressed)
{
	if(bmp && getRight() == 0 && getBottom() == 0)
	{
		setRight(getLeft() + bm.bmWidth);
		setBottom(getTop()  + bm.bmHeight);
		if(activeBmp)
		{
			activeRect.right = activeRect.left + activeBm.bmWidth;
			activeRect.bottom = activeRect.top + activeBm.bmHeight;
		}
	}
		
	if(initX > getRect()->left && initX < getRect()->right
	&& initY > getRect()->top  && initY < getRect()->bottom)
	{
		HDC hdc = GetDC(hWnd);
		HDC hdcMem = CreateCompatibleDC(hdc);
		if(getStatus() == MOUSE_OVER && activeMask != NULL)
			SelectObject(hdcMem, activeMask);
		else 
			SelectObject(hdcMem, mask);

		if(GetPixel(hdcMem, initX-getRect()->left, initY-getRect()->top) == RGB(0,0,0))
		{
			if( getStatus() == ACTIVE && !keyPressed)		// If key Realeased
			{
				setStatus(PRESSED);							// Then status changes to pressed
				if(klick != NULL)
					klick->Play();
			}

			if( getStatus() != PRESSED )					// If status NOT equal to Pressed
			{
				if(keyPressed)							// If key is pressed
					setStatus(ACTIVE);					// Status is Active
				else
					setStatus(MOUSE_OVER);				// Otherwise status is Mouse over
			}
		}
		else
			setStatus(NORMAL);

		DeleteDC(hdcMem);
		ReleaseDC(hWnd, hdc);
	}
	else 
	{
		setStatus(NORMAL);							// Mouse was outside the button
	}
	return CStatusObject::test(initX, initY, hWnd, theInfoSqr,keyPressed);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRadioButton::CRadioButton()
{
	pressedBmp		= NULL;
	pressedMask		= NULL;
}

void CRadioButton::draw(HWND hWnd, bool forced, HBITMAP* back)
{
	HDC hdc	= GetDC(hWnd);
	draw(hdc,  forced, back);
	ReleaseDC(hWnd, hdc);
}

void CRadioButton::draw(HDC hdc, bool forced, HBITMAP* back)
{
	if( isStatusChanged() || forced)		// If status is changed
	{												// Then draw the button again
		resetOldStatus();					// Reset the status
		HBITMAP drawMask, drawBmp;
		BITMAP drawBm;
		switch(getStatus())
		{
			case ACTIVE:		// Active has the same picture as Mouse_Over
			case MOUSE_OVER: if(activeMask != NULL)
							 {
								drawMask = activeMask; 
								drawBmp = activeBmp;
								drawBm = activeBm;
							 }
				break;
			case NORMAL:	drawMask = mask; 
							drawBmp = bmp; 
							drawBm = bm;
				break;
			case PRESSED:	drawMask = pressedMask; 
							drawBmp = pressedBmp; 
							drawBm = pressedBm;
				break;
			default:		drawMask = mask; 
							drawBmp = bmp;
							drawBm = bm;
				break;
		}

		if(back == NULL)
			DrawBitmapWithMask(hdc, drawMask, drawBmp, getLeft(), getTop(), drawBm);
		else
			DrawBitmapWithMaskAndBackBitmap(hdc, drawMask, drawBmp, back, getLeft(), getTop(), drawBm);
	}
}

int CRadioButton::LoadPressedBitmap(LPSTR szFileName, bool createMask)
{
	pressedBmp = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	GetObject(pressedBmp, sizeof(activeBm), &pressedBm);

	if(!pressedBmp)
		return 0;
	else if(createMask)
		pressedMask = CreateBitmapMask(pressedBmp, maskColor);
	else 
		pressedMask = NULL;
	return 1;
}

void CRadioButton::setMaskColor(COLORREF initMask)
{
	CActiveSprite::setMaskColor(initMask);
	if(pressedBmp && pressedMask)
		pressedMask = CreateBitmapMask(pressedBmp, initMask);
}

void CRadioButton::setLeft(int init)
{
	pressedRect.left = init;
	CActiveSprite::setLeft(init);
}

void CRadioButton::setTop(int init)
{
	pressedRect.top = init;
	CActiveSprite::setTop(init);
}

RECT* CRadioButton::getRect()
{
	if(getStatus() == PRESSED)
		return &pressedRect;
	else
		return CActiveSprite::getRect();
}

void CRadioButton::setPosition(int left, int top, int bottom, int right)
{
	pressedRect.left = left;
	pressedRect.top = top;
	CActiveSprite::setPosition(left, top, bottom, right);
}


int CRadioButton::test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSqr, bool keyPressed)
{
	if(bmp && getRight() == 0 && getBottom() == 0)
	{
		setRight(getLeft() + bm.bmWidth);
		setBottom(getTop()  + bm.bmHeight);
		if(activeBmp)
		{
			activeRect.right = activeRect.left + activeBm.bmWidth;
			activeRect.bottom = activeRect.top + activeBm.bmHeight;
		}
		if(pressedBmp)
		{
			pressedRect.right = pressedRect.left + pressedBm.bmWidth;
			pressedRect.bottom = pressedRect.top + pressedBm.bmHeight;
		}
	}
		
	if(initX > getRect()->left && initX < getRect()->right
	&& initY > getRect()->top  && initY < getRect()->bottom)
	{
		HDC hdc = GetDC(hWnd);
		HDC hdcMem = CreateCompatibleDC(hdc);
		if(getStatus() == MOUSE_OVER && activeMask != NULL)
			SelectObject(hdcMem, activeMask);
		else if(getStatus() == MOUSE_OVER && pressedMask != NULL)
			SelectObject(hdcMem, pressedMask);
		else 
			SelectObject(hdcMem, mask);

		if(GetPixel(hdcMem, initX-getRect()->left, initY-getRect()->top) == RGB(0,0,0))
		{
			if( getStatus() == ACTIVE && !keyPressed)		// If key Realeased
			{
				setStatus(PRESSED);							// Then status changes to pressed
				if(klick != NULL)
					klick->Play();
				
				//MB("Pressed")
			}

			if( getStatus() != PRESSED )					// If status NOT equal to Pressed
			{
				if(keyPressed)							// If key is pressed
				{
					setStatus(ACTIVE);					// Status is Active
				}
				
			}
//			MB("Test")
		}

		DeleteDC(hdcMem);
		ReleaseDC(hWnd, hdc);
	}
	else if(getStatus() == ACTIVE)
		setStatus(NORMAL);

	return CStatusObject::test(initX, initY, hWnd, theInfoSqr,keyPressed);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRadioHolder::CRadioHolder()
{
	rAntal = 0;
	for(int i = 0; i < MAX_RADIO; i++)
		itsRadio[i] = NULL;

	activeRadio = NULL;
}


int CRadioHolder::getNumberRadios() 
{
	return rAntal;
}

CRadioButton* CRadioHolder::getRadio (int init) 
{
	return itsRadio[init];
}

CRadioButton* CRadioHolder::getActiveRadio() 
{
	return activeRadio;
}

void CRadioHolder::add(CRadioButton *init)
{
	if(rAntal < MAX_RADIO)
	{
		itsRadio[rAntal] = init;
		if (rAntal == 0)
		{
			itsRadio[rAntal]->setStatus(PRESSED);
			activeRadio = itsRadio[rAntal];
		}
		++rAntal;
	}
}

int CRadioHolder::test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSqr, bool keyPressed)
{
	for(int i = 0; i < rAntal; i++)
	{
		if(itsRadio[i]->test(initX, initY, hWnd, theInfoSqr, keyPressed))
		{
			InvalidateRect(hWnd, itsRadio[i]->getRect(), FALSE);
			if( itsRadio[i]->getStatus() == PRESSED &&
				itsRadio[i] != activeRadio)
			{
				activeRadio->setStatus(NORMAL);
				InvalidateRect(hWnd, activeRadio->getRect(), FALSE);
				activeRadio = itsRadio[i];
				InvalidateRect(hWnd, activeRadio->getRect(), FALSE);
			}
		}
	}
	
	//MB("TEST");
	return true;
}

void CRadioHolder::draw(HDC hdc, bool forced)
{
	for(int i = 0; i < rAntal; i++)
		itsRadio[i]->draw(hdc, forced);

	
	//char sz[64];
	//wsprintf(sz, "RAntal: %d ", rAntal);
	//wsprintf(sz, "Top: %d \nBottom: %d \nLeft: %d \nRight: %d", itsRadio[0]->getTop(), itsRadio[0]->getBottom(), itsRadio[0]->getLeft(), itsRadio[0]->getRight());
	//MB(sz);
}