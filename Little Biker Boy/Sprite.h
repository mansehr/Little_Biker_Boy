#ifndef __Sprite_h__
#define __Sprite_h__

#include "Object.h"
#include "Bitmap.h"
#include "Sound.h"


class CSprite : public CObject , public CBitmapWithMask
{
public:
	CSprite();

	// CLASS FUNCTIONS ////////////////////////////////
	void	draw(HDC hdc);

	void	setPosition(int left, int top, int bottom = 0, int right = 0);
};



class CActiveSprite : public CBitmapWithMask, public CStatusObject
{
public:
	CActiveSprite();
//	virtual ~CActiveSprite();

	// CLASS FUNCTIONS ////////////////////////////////
	virtual void	draw(HWND hWnd, bool forced = false, HBITMAP* back = NULL);
	virtual void	draw(HDC hdc, bool forced = false, HBITMAP* back = NULL);
	int				LoadActiveBitmap(LPSTR szFileName, bool createMask = true);
	//void			setBitmap(HBITMAP initBitmap, Status buttonType);
	void			setMaskColor(COLORREF initMask);
	void			setLeft(int init);
	void			setTop(int init);
	void			setSound(CSound *init);
	RECT*			getRect();
	void			setPosition(int left, int top, int bottom = 0, int right = 0);
	virtual int		test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSqr, bool keyPressed = false);

protected:
	HBITMAP activeBmp;		// Difrent bitmaps for difrent statuses
	HBITMAP activeMask;		// Masks for the bitmaps
	BITMAP activeBm;
	RECT activeRect;
	CSound* klick;
};

class CRadioButton : public CActiveSprite
{
public:
	CRadioButton();

	virtual void	draw(HWND hWnd, bool forced = false, HBITMAP* back = NULL);
	virtual void	draw(HDC hdc, bool forced = false, HBITMAP* back = NULL);
	int				LoadPressedBitmap(LPSTR szFileName, bool createMask = true);
	void			setMaskColor(COLORREF initMask);
	void			setLeft(int init);
	void			setTop(int init);
	RECT*			getRect();
	void			setPosition(int left, int top, int bottom = 0, int right = 0);

	int	test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSqr, bool keyPressed = false);
private:
	HBITMAP pressedBmp;		// Difrent bitmaps for difrent statuses
	HBITMAP pressedMask;		// Masks for the bitmaps
	BITMAP pressedBm;
	RECT pressedRect;

};


#define MAX_RADIO 10
class CRadioHolder : public CStatusObject
{
public:
	CRadioHolder();

	int		getNumberRadios();
	CRadioButton* getRadio (int init);
	CRadioButton* getActiveRadio();

	void	add(CRadioButton *init);

	void	draw(HDC hdc, bool forced = false);
	int		test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSqr, bool keyPressed);

private:
	CRadioButton *itsRadio[MAX_RADIO];
	CRadioButton *activeRadio;
	int rAntal;	
};

#endif // __Sprite_h__