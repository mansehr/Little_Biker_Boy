#include "stdafx.h"
#include "bitmap.h"

//LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//
//		Filename:	Bitmap.cpp
//
//		Functionallity:	Bitmap functions to easier the work with bitmap
//
//		Comment:	Different usefull bitmap function bodies.
//
//		Date:		2003-10-10
//
//		Author:	Andreas Sehr
//
//LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL

HBITMAP CreateBitmapMask(HBITMAP hbmColour, COLORREF crTransparent)
{
	//Initialise the variables
	HDC hdcMem, hdcMem2;	
	HBITMAP hbmMask;	
	BITMAP bm;				

	//Get the width and height of the itmap and then create a maskbitmap whit same size
	GetObject(hbmColour, sizeof(BITMAP), &bm);
	hbmMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

	//Create universal dc used to the select the bitmaps for the drawing
	hdcMem = CreateCompatibleDC(0);
	hdcMem2 = CreateCompatibleDC(0);

	//Select the bitmps
	SelectObject(hdcMem, hbmColour);
	SelectObject(hdcMem2, hbmMask);
	
	//Set the background of the mask to Transparent
	SetBkColor(hdcMem, crTransparent);

	//Blit the bitmap and create a black and white mask
	BitBlt(hdcMem2, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
	BitBlt(hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCINVERT);
	
	//Clean
	DeleteDC(hdcMem);
	DeleteDC(hdcMem2);
		
	//Return the created bitmap mask
	return hbmMask;
}

int	DrawBitmap(HDC hdc, HBITMAP bitmap, int x, int y, int width, int height)
{
	// If no whidth and height is initiated
	if(width <= 0 || height <= 0)
	{
		// Create a bitmap object for width and height
		// and then set the variables
		BITMAP bm;
		GetObject(bitmap, sizeof(bm), &bm);
		width = bm.bmWidth;
		height = bm.bmHeight;
	}
	// Set the variables
	HDC hdcMem = CreateCompatibleDC(hdc);

	// Just select the bitmap and the copy it to the device context
	SelectObject(hdcMem, bitmap);
	BitBlt(hdc, x, y, width, height, hdcMem, 0, 0, SRCCOPY);
	
	// Clean
	DeleteDC(hdcMem);
	// Success
	return 1;
}

int	DrawBitmapWithMask(HDC hdc, HBITMAP mask, HBITMAP color, int x, int y, int width, int height)
{
	// If no whidth and height is initiated
	if(width <= 0 || height <= 0)
	{
		// Create a bitmap object for width and height
		// and then set the variables
		BITMAP bm;
		GetObject(color, sizeof(bm), &bm);
		width = bm.bmWidth;
		height = bm.bmHeight;
	}
	// Set the variables
	HDC hdcMem = CreateCompatibleDC(hdc);
	if(hdcMem == NULL)
	{
		Logg("<b>CreateCompatibleDC() in draw bitmap whith mask <u>ERROR</u></b>");
		MB("CreateCompatibleDC() in draw bitmap whith mask ERROR");
		return 0;
	}

	// Select the bitmap mask and draw the pixels that are valued (zero)
	// Then select the color bitmap and draw on the pixels that pervius was drawn
	SelectObject(hdcMem, mask);		
	BitBlt(hdc, x, y, width, height, hdcMem, 0, 0, SRCAND);
	SelectObject(hdcMem, color);
	BitBlt(hdc, x, y, width, height, hdcMem, 0, 0, SRCPAINT);
	
	// Clean
	DeleteDC(hdcMem);
	// Success
	return 1;
}

int	DrawBitmapWithMask(HDC hdc, HBITMAP mask, HBITMAP color, int x, int y, BITMAP bm)
{
	// Call the DrawBitmapWithMask with the width and height from the bitmap object
	// And return that value.
	return DrawBitmapWithMask(hdc, mask, color, x, y, bm.bmWidth, bm.bmHeight);
}

int	DrawBitmapWithMaskAndBackBrush(HDC hdc, HBITMAP mask, HBITMAP color, HBRUSH theBrush, int x, int y, int width, int height)
{
	// Iinitiate variables
	RECT bitmapRc;
	bitmapRc.left = x;
	bitmapRc.top = y;

	// If no whidth and height is initiated
	if(width <= 0 || height <= 0)
	{
		// Create a bitmap object for width and height
		// and then set the variables
		BITMAP bm;
		GetObject(color, sizeof(bm), &bm);
		bitmapRc.right = bitmapRc.left + bm.bmWidth;
		bitmapRc.bottom = bitmapRc.top + bm.bmWidth;
	}
	else
	{
		bitmapRc.right = bitmapRc.left + width;
		bitmapRc.bottom = bitmapRc.top + height;
	}

	HDC hdcBuffer = CreateCompatibleDC(hdc);
	if(hdcBuffer == NULL)
	{
		Logg("<b>CreateCompatibleDC()  Draw whith backbrush<u>ERROR</u></b>");
		MB("CreateCompatibleDC() Draw whith backbrush ERROR");
		return 0;
	}

    HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, bitmapRc.right, bitmapRc.bottom);
	if(hbmBuffer == NULL)
	{
		Logg("<b>CreateCompatibleBitmap() <u>ERROR</u></b>");
		MB("CreateCompatibleBitmap() ERROR");
		return 0;
	}
    SelectObject(hdcBuffer, hbmBuffer);

    HDC hdcMem = CreateCompatibleDC(hdc);
	if(hdcMem == NULL)
	{
		Logg("<b>CreateCompatibleDC() With back brush 2<u>ERROR</u></b>");
		MB("CreateCompatibleDC() With back brush 2 ERROR");
		return 0;
	}
	SelectObject(hdcMem, mask);

	if(theBrush != NULL)
	{
		FillRect(hdcBuffer, &bitmapRc, theBrush);
	}

    BitBlt(hdcBuffer, bitmapRc.left, bitmapRc.top, bitmapRc.right, bitmapRc.bottom, hdcMem, 0, 0, SRCAND);
    SelectObject(hdcMem, color);
    BitBlt(hdcBuffer, bitmapRc.left, bitmapRc.top, bitmapRc.right, bitmapRc.bottom, hdcMem, 0, 0, SRCPAINT);

    BitBlt(hdc, bitmapRc.left, bitmapRc.top, bitmapRc.right, bitmapRc.bottom, hdcBuffer, bitmapRc.left, bitmapRc.top, SRCCOPY);

    DeleteDC(hdcMem);
    DeleteDC(hdcBuffer);

    DeleteObject(hbmBuffer);
		
	return 1;
}

int	DrawBitmapWithMaskAndBackBrush(HDC hdc, HBITMAP mask, HBITMAP color, HBRUSH theBrush, int x, int y, BITMAP bm)
{
	return DrawBitmapWithMaskAndBackBrush(hdc, mask, color, theBrush, x, y, bm.bmWidth, bm.bmHeight);
}

int	DrawBitmapWithMaskAndBackBitmap(HDC hdc, HBITMAP mask, HBITMAP color, HBITMAP* theBitmap, int x, int y, int width, int height)
{
	HBRUSH theBrush = CreatePatternBrush(*theBitmap);
	int result = DrawBitmapWithMaskAndBackBrush(hdc, mask, color, theBrush, x, y, width, height);
	DeleteObject(theBrush);
	return result;
}

int	DrawBitmapWithMaskAndBackBitmap(HDC hdc, HBITMAP mask, HBITMAP color, HBITMAP* theBitmap, int x, int y, BITMAP bm)
{
	return DrawBitmapWithMaskAndBackBitmap(hdc, mask, color, theBitmap, x, y, bm.bmWidth, bm.bmHeight);
}

int	DrawBitmapWithMaskAndBackColor(HDC hdc, HBITMAP mask, HBITMAP color, COLORREF theColor, int x, int y, int width, int height)
{
	HBRUSH theBrush = CreateSolidBrush(theColor);
	int result = DrawBitmapWithMaskAndBackBrush(hdc, mask, color, theBrush, x, y, width, height);
	DeleteObject(theBrush);
	return result;
}

int	DrawBitmapWithMaskAndBackColor(HDC hdc, HBITMAP mask, HBITMAP color, COLORREF theColor, int x, int y, BITMAP bm)
{
	return 	DrawBitmapWithMaskAndBackColor(hdc, mask, color, theColor, x, y, bm.bmWidth, bm.bmHeight);
}

HBITMAP LoadABitmap(LPSTR szFileName)
{
	// Just load from a file and return the loaded bitmap
	return (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}


// CBitmapWithMask CLASS   

CBitmapWithMask::CBitmapWithMask()
{
	bmp				= NULL;
	mask			= NULL;
	maskColor		= RGB(0, 0, 0);
}

CBitmapWithMask::~CBitmapWithMask()
{
	DeleteObject( bmp );
	DeleteObject( mask );
}

HBITMAP* CBitmapWithMask::getBitmap()
{
	return &bmp;
}

HBITMAP CBitmapWithMask::getTheBitmap()
{
	return bmp;
}

HBITMAP* CBitmapWithMask::getMask()
{
	return &mask;
}

HBITMAP CBitmapWithMask::getTheMask()
{
	return mask;
}

int CBitmapWithMask::LoadABitmap(LPSTR szFileName, bool createMask)
{
	bmp  = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if(!bmp)
		return 0;	
	
	GetObject(bmp, sizeof(bm), &bm);

	if(createMask)
	{
		mask = CreateBitmapMask(bmp, maskColor);		
	}
	return 1;
}

int CBitmapWithMask::LoadAMask(LPSTR szFileName)
{
	mask  = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if(!mask)
		return 0;

	return 1;
}

void CBitmapWithMask::setMaskColor(COLORREF initMask)
{
	maskColor = initMask;
	if(bmp)
		mask = CreateBitmapMask(bmp, maskColor);
}