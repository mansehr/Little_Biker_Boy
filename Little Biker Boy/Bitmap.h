#ifndef __Bitmap_h__
#define __Bitmap_h__

//LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
//
//		Filename:	Bitmap.h
//
//		Functionallity:	Bitmap functions to easier the work with bitmap
//
//		Comment:	Different usefull bitmap functions defintions...
//
//		Date:		2003-10-10
//
//		Author:	Andreas Sehr
//
//LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL

//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
//
//	Function name: CreateBitmapMask
//
//	Call the function with:	The original bitmap and a color that are suposed 
//									to be transparent
//
//	Returnvalue:		The created bitmap mask.
//
//	Comment: 	Creates a bitmapmask that are used 
//				to make a bitmapbakground look transparent
//				when drawing whit the DrawButmapWhitMask function
//
//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
HBITMAP CreateBitmapMask(HBITMAP hbmColour, COLORREF crTransparent);

//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
//
//	Function name:	DrawBitmap
//
//	Call the function with: 	The drawingcontext, the bitmap, the position, and 
//									the size of the bitmap
//
//	Returnvalue:	A value != 0 if succes
//
//	Comment:	Draw a bitmap at a specifik position.
//
//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
int		DrawBitmap(HDC hdc, HBITMAP bitmap, int x, int y, int width = 0, int height = 0);

//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
//
//	Function name:	DrawBitmapWhitMask
//
//	Call the function with:	The drawingcontext, the bitmap, the maskBitmap, 
//									the position, and the size of the bitmap
//
//	Returnvalue:	A value != 0 if succes
//
//	Comment:	Draw a bitmap whit a background mask at a specifik position
//				The maskbitmap maskes one color look transparent
//
//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
int		DrawBitmapWithMask(HDC hdc, HBITMAP mask, HBITMAP color, int x, int y, BITMAP bm);
int		DrawBitmapWithMask(HDC hdc, HBITMAP mask, HBITMAP color, int x, int y, int width = 0, int height = 0);

//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
//
//	Function name:	DrawBitmapWhitMaskAndBackBrush
//
//	Call the function with:	The drawingcontext, the bitmap, the maskBitmap,
//								the backgroundBrush, the position, and the size of the bitmap
//
//	Returnvalue:	A value != 0 if succes
//
//	Comment:	Draw a bitmap whit a background color brush and mask bitmap 
//				at a specifik position.
//				The maskbitmap maskes one color look transparent.
//
//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
int		DrawBitmapWithMaskAndBackBrush(HDC hdc, HBITMAP mask, HBITMAP color, HBRUSH theBrush, int x, int y, int width = 0, int height = 0);
int		DrawBitmapWithMaskAndBackBrush(HDC hdc, HBITMAP mask, HBITMAP color, HBRUSH theBrush, int x, int y, BITMAP bm);

//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
//
//	Function name:	DrawBitmapWhitMaskAndBackBitmap
//
//	Call the function with:	The drawingcontext, the bitmap, the maskBitmap, 
//									the backBitmap, the position, and the size of the bitmap
//
//	Returnvalue:	A value != 0 if succes
//
//	Comment:	Draw a bitmap whit a background bitmap and mask at a specifik position
//				The maskbitmap maskes one color look transparent
//
//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
int		DrawBitmapWithMaskAndBackBitmap(HDC hdc, HBITMAP mask, HBITMAP color, HBITMAP* theBitmap, int x, int y, int width = 0, int height = 0);
int		DrawBitmapWithMaskAndBackBitmap(HDC hdc, HBITMAP mask, HBITMAP color, HBITMAP* theBitmap, int x, int y, BITMAP bm);

//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
//
//	Function name:	DrawBitmapWhitMaskAndBackColor
//
//	Call the function with:	The drawingcontext, the bitmap, the maskBitmap, 
//									the background color, the position, and the size of the bitmap
//
//	Returnvalue:	A value != 0 if succes
//
//	Comment:	Draw a bitmap whit a background color and mask at a specifik position
//				The maskbitmap maskes one color look transparent
//
//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
int		DrawBitmapWithMaskAndBackColor(HDC hdc, HBITMAP mask, HBITMAP color, COLORREF theColor, int x, int y, int width = 0, int height = 0);
int		DrawBitmapWithMaskAndBackColor(HDC hdc, HBITMAP mask, HBITMAP color, COLORREF theColor, int x, int y, BITMAP bm);


//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
//
//	Function name:	LoadABitmap
//
//	Call the function with: A charpointer with the file name and path relative to the 
//								runing program.	
//
//	Returnvalue:		The loaded bitmap.
//					
//	Comment:	Use this function to load a bitmap	 
//
//FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
HBITMAP LoadABitmap(LPSTR szFileName);


//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
//
//	Class name:	CBitmapWithMask
//
//	Comment: 	Handles a bitmap and a bitmap mask
//				Call the loadbitmap function to load a bitmapfile into
//				the memory. Then call the getBitmap function to get the bitmap
//				and the getMask function to get the maskbitmap.
//
//CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
class CBitmapWithMask
{													
public:
	CBitmapWithMask();
	~CBitmapWithMask();
	
	// CLASS FUNCTIONS ////////////////////////////////
	HBITMAP*	getBitmap();
	HBITMAP 	getTheBitmap();
	HBITMAP*	getMask();
	HBITMAP 	getTheMask();
	int			LoadABitmap(LPSTR szFileName, bool createMask = false);
	int			LoadAMask(LPSTR szFileName);
	void		setMaskColor(COLORREF initMask);

protected:
	BITMAP		bm;
	HBITMAP 	bmp;			// Difrent bitmaps for difrent statuses
	HBITMAP 	mask;		// Masks for the bitmaps
	COLORREF 	maskColor;
};

#endif // __Bitmap_h__