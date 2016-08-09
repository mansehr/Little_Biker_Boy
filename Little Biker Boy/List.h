// List.h: interface for the CList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIST_H__72DB690F_3BFA_4AA5_8816_44C513943A83__INCLUDED_)
#define AFX_LIST_H__72DB690F_3BFA_4AA5_8816_44C513943A83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Object.h"
#include "String.h"
#include "price.h"
#include "sprite.h"
#include "stdAfx.h"

#define MAX_NAME 64
#define MAX_TEXT 1024


struct stockItem
{
	unsigned int id;
	int maxPrice;
	int minPrice;
	int itsPrice;
	char name[MAX_NAME];
	int quantity;
};

struct saveListItem
{
	stockItem stock;
	int		nFitness;
	int		nCostInSleep;
	int		prevPrice[MAX_PREVPRICE];
	Status	itsStatus, oldStatus;
};

struct drugItem
{
	unsigned int id;
	int nFitness;
	int nCostInSleep;
	int nPrice;
	char text[MAX_TEXT];
	char name[MAX_NAME];
};

struct NewListItem
{
	unsigned int id;
	int maxPrice;
	int minPrice;
	int itsPrice;
	char name[MAX_NAME];
};

class CListObject : public CStatusObject  
{
public:
	CListObject();
	CListObject(saveListItem item);
	virtual ~CListObject();

		//ID publics
	void			setId(int init);
	int				getId();

	//CPrice Publics
	void			setPrice(int initPrice);
	void			setPrice(CPrice &init);
	void			setMin(int initMin);
	void			setMax(int initMax);
	void			fixPrice();
	int				getPrice();
	int				getMax();
	int				getMin();
	int*			getPrevPrice();
	int				getPrevPrice(int init);
	double			getChange();

	//String
	String*			getStringAddress();
	void			setName(char* init);
	char*			getName();

	int				getQuantity();
	void			setQuantity(int init);

//	void			Update(HWND hWnd);
	void			Reset();

	void			setItem(saveListItem init);
	void			getItem(saveListItem &init);

	void			setExtraString(char* init);
	char*			getExtraString();
	void			setCostInSleep(int init);
	int				getCostInSleep();
	void			setFitnes(int init);
	int				getFitness();


	bool			isStringChanged(bool reset = true);
	void			setVisualString(char* init);
	char*			getVisualString();
	void			reset();

	virtual int		test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSqr, bool keyPressed);

	virtual void	draw(HWND hWnd, bool forced = false);
	virtual void	draw(HDC hdc, bool forced = false);

	void			UpdateTextFont();
private:
	bool		bStringChanged;
	String		visualString;
	unsigned int id;
	CPrice		price;
	int			quantity;
	int			prevPrice[MAX_PREVPRICE];
	
	// Drug/Training Item
	int			nFitness;
	int			nCostInSleep;
	String		extraString;
	CStaticText itsVisualText;
	CStaticText itsText;
	CStaticText itsPriceText;
	CStaticText itsStockText;

	void			updatePosition();
};


class CList : public CStatusObject   
{
public:
	CList();
	virtual ~CList();

	void	addObject();
	void	addObject(CListObject* init);

	void	deleteLastObj();
	void	deleteObj(int init);
	void	deleteActiveObj();
	void	deleteAllObjects();

	void	draw(HWND hWnd, bool forced = false);
	void	draw(HDC hdc, bool forced = false);
	void	drawObjects(HWND hWnd, int start, int end);
	void	drawObjects(HDC hdc, int start, int end);

	CListObject* getActiveObj();
	CListObject* getObj(int number);
	int		getActiveObjNr();
	int		getNumber();

	void	setActiveObject(unsigned int  init);
	void	setHeaderText(char* init);
	void	setObj(int number, CListObject* init);
	void	setPosition(int left, int top, int right, int bottom);

	int		test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSqr, bool keyPressed);

	//void	Update(HWND hWnd, int init);

private:
	CStaticText itsHeader;
	CListObject itsObjects[MAX_LISTOBJECTS];
	CListObject* activeListObject;
	int			nObjects;
	int			nActiveObj;
	int			buttonsX;
	int			maxLItem;
	int			topLItem;
	CActiveSprite butUp, butDown;
};


#endif // !defined(AFX_LIST_H__72DB690F_3BFA_4AA5_8816_44C513943A83__INCLUDED_)
