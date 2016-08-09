// List.cpp: implementation of the CList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "List.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListObject::CListObject()
{
	reset();
}

CListObject::CListObject(saveListItem item)
{
	CListObject();
	setItem(item);
}

CListObject::~CListObject()
{

}

void CListObject::reset()
{
	visualString = "";
	bStringChanged = false;
	id = 0;
	quantity = 0;
	for(int i = 0; i < MAX_PREVPRICE; i++)
		prevPrice[i] = 0;
	nFitness = 0;
	nCostInSleep = 0;
	extraString = "";
	itsText.setText("Hello");
}

int CListObject::test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSqr, bool keyPressed)
{
	if(initX > getLeft() && initX < getRight()
	&& initY > getTop()  && initY < getBottom()
	&& getStatus() != NOT_PRESSABLE)
	{
		if(keyPressed)							// If key is pressed
			setStatus(ACTIVE);					// Status is Active
		else if(getStatus() != ACTIVE)
			setStatus(MOUSE_OVER);				// Otherwise status is Mouse over
	}
	else if(getStatus() != ACTIVE && getStatus() != NOT_PRESSABLE)
	{
		//Logg("Listobject == Normal", getName());
		setStatus(NORMAL);							// Mouse was outside the button
	}

	if(isStatusChanged())
		return 1;								// return 1 because status was changed
	else
		return 0;
}

void CListObject::draw(HWND hWnd, bool forced)
{
	HDC hdc = GetDC(hWnd);
	draw(hdc);
	ReleaseDC(hWnd, hdc);

}

void CListObject::draw(HDC hdc, bool forced)
{
	if(isStatusChanged() || isStringChanged(false) || forced)
	{
		COLORREF textColor, itsBackColor, itsFrameColor;
		bool italic = false;
		int bold = FW_NORMAL;
		if(getStatus() == ACTIVE)
		{
			itsFrameColor = RGB(132, 178, 245);
			textColor = RGB(128, 128, 128);
			itsBackColor = RGB(132, 178, 245);
		}
		else if(getStatus() == NOT_PRESSABLE)
		{
			itsFrameColor = RGB(230, 230, 230);
			textColor = RGB(100, 100, 100);
			itsBackColor = RGB(230, 230, 230);
		}
		else
		{
			itsFrameColor = RGB(255, 255, 255);
			textColor = RGB(0, 0, 0);
			itsBackColor = RGB(255, 255, 255);
		}
						
		//HBRUSH original_brush;
		//original_brush = (HBRUSH)SelectObject(hdc, itsFrameColor); 

		//Rectangle(hdc, getLeft(), getTop(), getRight(), getBottom());

		updatePosition();

		if(visualString != "")
		{
			itsVisualText.setText(visualString.getString());
			itsVisualText.setBgColor(itsBackColor);
			itsVisualText.setTextColor(textColor);
			itsVisualText.setFrame(itsFrameColor);
			itsVisualText.draw(hdc);
		}
		else
		{
			itsText.setText(getName());
			itsText.setBgColor(itsBackColor);
			itsText.setTextColor(textColor);
			itsText.setFrame(itsFrameColor);
			itsText.draw(hdc);

			itsPriceText.setText(getPrice());
			itsPriceText.setBgColor(itsBackColor);
			itsPriceText.setTextColor(textColor);
			itsPriceText.setFrame(itsFrameColor);
			itsPriceText.setFlags(DT_RIGHT);
			itsPriceText.setRightMargin(15);
			itsPriceText.draw(hdc);

			itsStockText.setText(getQuantity());
			itsStockText.setBgColor(itsBackColor);
			itsStockText.setTextColor(textColor);
			itsStockText.setFrame(itsFrameColor);
			itsStockText.setFlags(DT_RIGHT);
			itsStockText.setRightMargin(20);
			itsStockText.draw(hdc);
		}

		//Logg(this->getName(), this->getId());

		//DrawText(hdc, visualString.getString(), visualString.getLen(), &rt, DT_EXPANDTABS);
		//MB(visualString.getString());

		//SelectObject (hdc, original_brush);
		//SetTextColor(hdc, textColor);
		//SetBkColor(hdc, itsBackColor);
		//DeleteObject(itsFrameColor);
	}
}

void CListObject::updatePosition()
{
	RECT rt = *getRect();
	rt.left = rt.left + 4;
	rt.top = rt.top + 1;
	rt.right = rt.right - 4;
	rt.bottom = rt.bottom - 1;

	itsVisualText.setPosition(rt);

	rt.right = rt.left + (rt.right - rt.left)/2;

	itsText.setPosition(rt);

	rt.left = itsText.getRight() + 2;
	rt.right = rt.left + (getRight() - rt.left)/2;

	itsStockText.setPosition(rt);

	rt.left = itsStockText.getRight() + 2;
	rt.right = getRight() - 4;

	itsPriceText.setPosition(rt);
}

bool CListObject::isStringChanged(bool reset)
{
	if(bStringChanged == true)
	{
		//MB("I lilla stringchanged = true");
		if(reset)
			bStringChanged = false;
		return true;
	}
	else
		return false;
}


void CListObject::setVisualString(char* init)
{
	UpdateTextFont();

	bStringChanged = true;
	visualString = init;
}

char* CListObject::getVisualString()
{
	return visualString.getString();
}


//ID publics
void CListObject::setId(int init)
{ 
	id = init; 
}

int	CListObject::getId()				
{ 
	return id; 
}

int* CListObject::getPrevPrice()
{
	return prevPrice;
}

int	CListObject::getPrevPrice(int init)
{
	if(init > 0 && init < MAX_PREVPRICE)
		return prevPrice[init];
	else
		return prevPrice[0];
}

//CPrice Publics
void CListObject::setPrice(int initPrice) 
{ 
	price.setPrice(initPrice);
}
void CListObject::setPrice(CPrice &init)
{ 
	price.setPrice(init);
}

void CListObject::setMin(int initMin)	
{ 
	price.setMin(initMin);
}

void CListObject::setMax(int initMax)	
{ 
	price.setMax(initMax);
}

void CListObject::fixPrice()				
{ 
	for(int i = 0; i < MAX_PREVPRICE-1; i++)
		prevPrice[i] = prevPrice[i+1];
	prevPrice[MAX_PREVPRICE-1] = getPrice();
	price.fixPrice(); 
}

int CListObject::getPrice()				
{ 
	return price.getPrice();
}

int CListObject::getMax()				
{ 
	return price.getMax();
}

int CListObject::getMin()				
{ 
	return price.getMin();
}

double CListObject::getChange()			
{ 
	return price.getChange();
}

//String
void CListObject::setName(char* init)	
{ 
	UpdateTextFont();
	CObject::setName(init); 
}


void CListObject::UpdateTextFont()
{
	itsText.setTextHeight(16);
	itsText.setFlags(DT_SINGLELINE | DT_VCENTER);
	itsText.setLeftMargin(2);

	itsPriceText.setTextHeight(16);
	itsPriceText.setFlags(DT_SINGLELINE | DT_VCENTER);
	itsPriceText.setLeftMargin(2);

	itsStockText.setTextHeight(16);
	itsStockText.setFlags(DT_SINGLELINE | DT_VCENTER);
	itsStockText.setLeftMargin(2);

	itsVisualText.setTextHeight(16);
	itsVisualText.setFlags(DT_SINGLELINE | DT_VCENTER);
	itsVisualText.setLeftMargin(2);
}

char* CListObject::getName()				
{ 
	return CObject::getName(); 
}

int CListObject::getQuantity()			
{ 
	return quantity; 
}

void CListObject::setQuantity(int init)	
{ 
	quantity = init;
}

void CListObject::setExtraString(char* init)
{
	this->extraString = init;
}

char* CListObject::getExtraString()
{
	return this->extraString.getString();
}

void CListObject::setCostInSleep(int init)
{
	nCostInSleep = init;
}

int CListObject::getCostInSleep()
{
	return nCostInSleep;
}

void CListObject::setFitnes(int init)
{
	nFitness = init;
}

int CListObject::getFitness()
{
	return nFitness;
}

void CListObject::Reset()
{
	id = 0;
	price.setPrice(0);
	CObject::getString().setToNull();
	quantity = 0;
	for(int i = 0; i < MAX_PREVPRICE-1; i++)
		prevPrice[i] = 0;
}

void CListObject::setItem(saveListItem init)
{
	id = init.stock.id;
	setName(init.stock.name);
	price.setPrice(init.stock.itsPrice);
	price.setMax(init.stock.maxPrice);
	price.setMin(init.stock.minPrice);
	quantity = init.stock.quantity;
	//setPosition(init.itsPosition);
	nCostInSleep = init.nCostInSleep;
	nFitness = init.nFitness;
	setStatus(init.itsStatus);
	setOldStatus(init.oldStatus);

	for(int i = 0; i < MAX_PREVPRICE; i++)
		prevPrice[i] = init.prevPrice[i];
}

void CListObject::getItem(saveListItem &returnItem)
{
	returnItem.stock.id = id;
	strcpy_s(returnItem.stock.name, getName());
	returnItem.stock.itsPrice = price.getPrice();
	returnItem.stock.maxPrice = price.getMax();
	returnItem.stock.minPrice = price.getMin();
	returnItem.stock.quantity = quantity;
	//returnItem.itsPosition = getItsPosition();
	returnItem.nCostInSleep = getCostInSleep();
	returnItem.nFitness = getFitness();
	returnItem.itsStatus = getStatus();
	returnItem.oldStatus = getOldStatus();
	for(int i = 0; i < MAX_PREVPRICE; i++)
		returnItem.prevPrice[i] = prevPrice[i];
}

/*CListObject CListObject::operator = (const CListObject & rhs)
{
	this->id = rhs.getId();
	setName(rhs.getName());
	price.setPrice(rhs.getPrice());
	price.setMax(rhs.getMax());
	price.setMin(rhs.getMin());
	quantity = rhs.getQuantity();
	//setPosition(init.itsPosition);
	nCostInSleep = rhs.getCostInSleep();
	nFitness = rhs.getFitness();
	setStatus(rhs.getStatus());
	setOldStatus(rhs.getOldStatus());

	for(int i = 0; i < MAX_PREVPRICE; i++)
		prevPrice[i] = rhs.getPrevPrice(i);	
}*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction			CList
//////////////////////////////////////////////////////////////////////

CList::CList()
{
	//itsHeader.setPosition(getLeft(), getTop(), getRight(), getTop()+LISTOBJECT_HEIGHT);

	activeListObject	= NULL;
	nActiveObj			= 0;
	buttonsX			= 0;
	maxLItem			= 0;
	topLItem			= 0;
	butUp.setMaskColor(RGB(0,0,255));
	butDown.setMaskColor(RGB(0,0,255));
	butUp.LoadABitmap("data/ButUp.bmp", true);
	butUp.LoadActiveBitmap("data/ButUp1.bmp", true);
	butDown.LoadABitmap("data/ButDown.bmp", true);
	butDown.LoadActiveBitmap("data/ButDown1.bmp", true);
}

CList::~CList()
{
	//delete [] *itsObjects;
	activeListObject	= NULL;
}

void CList::addObject()
{
	CListObject* temp = new CListObject;
	this->addObject(temp);
	delete temp;
	temp = NULL;
}

void CList::addObject(CListObject* init)
{
	itsObjects[nObjects] = *init;
	if(nObjects == 0)
	{
		//activeListObject = &itsObjects[nObjects];
		itsObjects[nObjects].setPosition(getLeft(), itsHeader.getBottom(), getRight(), itsHeader.getBottom()+LISTOBJECT_HEIGHT);
		setActiveObject(0);
	}
	else if (nObjects < MAX_LISTOBJECTS)
		itsObjects[nObjects].setPosition(getLeft(), itsObjects[nObjects-1].getBottom(), getRight(), itsObjects[nObjects-1].getBottom()+LISTOBJECT_HEIGHT);
	else
	{
		Logg("List Overflow");
		MB("List overflow");
	}
	itsObjects[nObjects].UpdateTextFont();
	nObjects++;
}

void CList::draw(HWND hWnd, bool forced)
{
	HDC hdc = GetDC(hWnd);
	draw(hdc, forced);
	ReleaseDC(hWnd, hdc);
}

void CList::draw(HDC hdc, bool forced)
{
	if(isStatusChanged() || forced)
	{
		//MessageBox(NULL, "Hello", "Noooo1", MB_OK);
		if(forced == true)
		{
			Rectangle(hdc, getLeft(), getTop(), getRight(), getBottom());
			itsHeader.draw(hdc);
		}
		if(this->nObjects > this->maxLItem) 
		{
			butUp.draw(hdc, forced);
			butDown.draw(hdc, forced);
		}
		int i = topLItem;
		if(nObjects > 0)
		{
			itsObjects[i].setTop(itsHeader.getBottom());
			itsObjects[i].setBottom(itsObjects[i].getTop()+LISTOBJECT_HEIGHT);
			for(i = i+1; i < nObjects; i++)
			{
				itsObjects[i].setTop(itsObjects[i-1].getBottom());
				itsObjects[i].setBottom(itsObjects[i].getTop()+LISTOBJECT_HEIGHT);
			}
			for(i = topLItem; i < nObjects && i < (topLItem+maxLItem-1); i++)
			{
				itsObjects[i].draw(hdc, forced);
			}
		}
	}
}


void CList::drawObjects(HWND hWnd, int start, int end)
{
	HDC hdc = GetDC(hWnd);
	drawObjects(hdc, start, end);
	ReleaseDC(hWnd, hdc);

}

void CList::drawObjects(HDC hdc, int start, int end)
{
	if(end == 0)
		for(int i = 0; i < nObjects; i++)
			itsObjects[i].draw(hdc, true);
	else
		for(int i = start; i < nObjects && i < end; i++)
			itsObjects[i].draw(hdc, true);
}

CListObject* CList::getActiveObj()
{
	if(activeListObject != NULL)
		return CList::activeListObject;
	else
		return NULL;
}

CListObject* CList::getObj(int number)
{
	if(number > 0 && number < nObjects)
		return &itsObjects[number];
	else
		return &itsObjects[0];
}

void CList::setActiveObject(unsigned int init)
{
	if(init > 0 && init < unsigned int(nObjects))
		nActiveObj = init;
	else
		nActiveObj = 0;

	activeListObject = &itsObjects[nActiveObj];
	activeListObject->setStatus(ACTIVE);
}

void CList::setHeaderText(char* init)
{
	itsHeader.setText(init);
	itsHeader.setBgColor(RGB(230, 230, 230));
	itsHeader.setTextColor(RGB(100, 100, 100));
	itsHeader.setTextHeight(16);
	itsHeader.setTextWeight(FW_BOLD);
	itsHeader.setFrame(RGB(200, 200, 200));
	itsHeader.setItalict(true);
	itsHeader.setFlags(DT_VCENTER);
}

void CList::setPosition(int left, int top, int right, int bottom)
{
	CObject::setPosition(left, top, right, bottom);
	buttonsX = getLeft()+((getRight()-getLeft())/2)-24;
	butUp.setPosition(buttonsX, getTop()-53);
	butDown.setPosition(buttonsX, getBottom()+5);
	maxLItem = (bottom-top)/LISTOBJECT_HEIGHT;

	itsHeader.setPosition(left+4, top+2, right-4, top+LISTOBJECT_HEIGHT);
}

void CList::setObj(int number, CListObject* init)
{
	if(number > 0 && number < nObjects)
		CList::itsObjects[number] = *init;
}

int CList::getActiveObjNr()
{
	return nActiveObj;
}

int CList::getNumber()
{
	return nObjects;
}

void CList::deleteLastObj()
{
	if(nObjects > 0)
	{
		nObjects--;
		if(&itsObjects[nObjects] == activeListObject)
			if(nObjects > 0)
			{
				setActiveObject(0);
			}
			else
				activeListObject = NULL;

		if(nObjects != 0)
			activeListObject->setStatus(ACTIVE);

		itsObjects[nObjects].reset();

	//	delete itsObjects[nObjects];
	//	itsObjects[nObjects] = NULL;
	}
#ifdef DEBUGHIG
	Logg("Deleted last Object");
#endif

}



void CList::deleteObj(int init)
{
#ifdef DEBUGHIG
	Logg("Delete Object", itsObjects[init].getName());
#endif
	for(int i = init; i < nObjects-1; i++)
	{
		itsObjects[i] = itsObjects[i + 1];
	//	Update(NULL, i);
	}
	deleteLastObj();
}

void CList::deleteActiveObj()
{
#ifdef DEBUGHIG
	Logg("Delete Active Object", itsObjects[nActiveObj].getName());
#endif

	deleteObj(nActiveObj);
}

void CList::deleteAllObjects()
{
	for(int i = nObjects; i > 0; i--)
		deleteLastObj();

}

int CList::test(int initX, int initY, HWND hWnd, CInfoSquare &theInfoSqr, bool keyPressed)
{
	if(	initX >= this->getTop() && initY <= this->getBottom())
	{
		for(int i = 0; i < nObjects; i++)
			if(itsObjects[i].test(initX, initY, hWnd, theInfoSqr, keyPressed))
			{
				if (itsObjects[i].getStatus() == ACTIVE &&
					activeListObject->getId() != itsObjects[i].getId())
				{


					if (activeListObject->getStatus() != NOT_PRESSABLE && 
						activeListObject != &itsObjects[i])
						activeListObject->setStatus(NORMAL);

					activeListObject->draw(hWnd);

					activeListObject = &itsObjects[i];
					nActiveObj		 = i;

					activeListObject->draw(hWnd);
					
					setStatusChanged(true);
				}
			}
	}

	if(this->nObjects > this->maxLItem)
	{
		if(butUp.test(initX, initY, hWnd, theInfoSqr, keyPressed))
		{
			butUp.draw(hWnd);
			if(butUp.isPressed(true, MOUSE_OVER))
				if(topLItem > 0)
				{
					topLItem--;
					if(this->nActiveObj > (this->topLItem+this->maxLItem-2))
					{
						this->nActiveObj = this->topLItem+this->maxLItem-2;
						activeListObject->setStatus(NORMAL);
						activeListObject = &itsObjects[this->nActiveObj];
						activeListObject->setStatus(ACTIVE);
					}
					this->draw(hWnd, true);
				}
		}

		if(butDown.test(initX, initY, hWnd, theInfoSqr, keyPressed))
		{
			butDown.draw(hWnd);
			if(butDown.isPressed(true, MOUSE_OVER))
				if((topLItem+maxLItem) < nObjects)
				{
					topLItem++;
					if(this->nActiveObj < this->topLItem)
					{	
						this->nActiveObj = this->topLItem;
						activeListObject->setStatus(NORMAL);
						activeListObject = &itsObjects[this->nActiveObj];
						activeListObject->setStatus(ACTIVE);
					}
					this->draw(hWnd, true);
				}
		}
	}
		
	return 0;
}

/*void  CList::Update(HWND hWnd, int init)
{
	if(init < 0)
	{
		for(int i = 0; i < nObjects; i++)
		{
			itsObjects[i].Update(hWnd);
		}
	}
	else if(init < nObjects)
	{
		//Logg("Update i list", init);
		itsObjects[init].Update(hWnd);
	}
	else
		Logg("Update går inte, init > nObjects");
}*/


