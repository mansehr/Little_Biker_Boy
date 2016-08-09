// TheGame.cpp: implementation of the TheGame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TheGame.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TheGame::TheGame()
{
	bmpLoad		= LoadABitmap(LOADPICFILE);
	bmpLoadMask	= CreateBitmapMask(bmpLoad, RGB(0,0,255));
	if(!bmpLoad)
		MB("Load Bitmap Not Loaded");
	itsPlayer.itsMode		= GameMode(-1);
	itsStatus	= INIT;
	oldStatus	= INIT;
	reset();
	srand((unsigned int)time(NULL) );
}

TheGame::~TheGame()
{

}

GameStatus TheGame::getStatus()
{
	return itsStatus;
}

GameStatus TheGame::getOldStatus()
{
	return oldStatus;
}

GameMode TheGame::getGameMode()
{
	return itsPlayer.itsMode;
}

int TheGame::getDays()
{
	return itsPlayer.days;
}

int TheGame::getMaxDays()
{
	return itsPlayer.maxDay;
}

int TheGame::getMoney()
{
	return itsPlayer.money;
}

double TheGame::getAwake()
{
	return itsPlayer.awake;
}

double TheGame::getFitness()
{
	return itsPlayer.fitness;
}

EROOM TheGame::getActiveRoom()
{
	return activeRoom;
}

CWork* TheGame::getActiveWorkpt()
{
	return itsWork[activeWorkHandle].getActiveWorkpt();
}

CWork TheGame::getActiveWork()
{
	return itsWork[activeWorkHandle].getActiveWork();
}

int TheGame::getActiveWorkNumber()
{
	return itsWork[activeWorkHandle].getActiveWorkNumber();
}

int* TheGame::getPrevMoney()
{
	return itsPlayer.prevMoney;
}

int* TheGame::getPrevFitness()
{
	return itsPlayer.prevFitness;
}

int TheGame::getTimesSleeped()
{
	return itsPlayer.timesSleeped;
}

bool  TheGame::isStatusChanged(bool reset)
{
	if(oldStatus != itsStatus)
	{
		if(reset)
			oldStatus = itsStatus;
		return true;
	}
	else 
		return false;
}

void TheGame::drawLoadPic(HWND hWnd, bool forced)
{
	if((oldStatus != itsStatus && drawLoad) || forced)
	{
		POINT pt;
		BITMAP bm;
		GetObject(bmpLoad, sizeof(bm), &bm);
		pt.x = ((SCREEN_WIDTH - bm.bmWidth) /2);
		pt.y = ((SCREEN_HEIGHT - bm.bmHeight) /2);
		HDC hdc = GetDC(hWnd);
		DrawBitmapWithMask(hdc, bmpLoadMask, bmpLoad, pt.x, pt.y);
		ReleaseDC(hWnd, hdc);
		drawLoad = false;
	}
}

void TheGame::setStatus(GameStatus initStatus)
{
	oldStatus = itsStatus;
	itsStatus = initStatus;
	drawLoad = true;
	switch(initStatus)
	{
		case STARTMENU:	activeRoom = eMENU;		break;
		case BEDROOM:	activeRoom = eBEDROOM; 	break;
		case TOWN:		activeRoom = eTOWN;		break;
		case SHOP:		activeRoom = eSHOP;		break;
		case WORKOUT:	activeRoom = eWORKOUT;	break;
		case OFFICE:	activeRoom = eOFFICE;	break;
		case END_GAME:	activeRoom = eENDGAME;	break;
		default:		activeRoom = eBEDROOM;	break;
	}
}

void TheGame::setGameMode(GameMode init)
{
	itsPlayer.itsMode = init;
}

void TheGame::switchStatus()
{
	setStatus(oldStatus);
}

#define MAX_STOCK 128
#define MAX_NAME_LENGTH 64

struct ListItem
{
	unsigned int id;
	CPrice price;
	char name[MAX_NAME_LENGTH];
	int quantity;
} lItem[MAX_STOCK];

int TheGame::LoadLists()
{
	list[lSTOCK].setName("buyPartsList");
	list[lSTOCKGOT].setName("buyPartsListGot");
	list[lDRUG].setName("buyDrugList");
	list[lTRAINING].setName("buyTrainingList");
	list[lWORKGOT].setName("workGotList");

	for(int j = 0; j <= lTRAINING; j++)
	{
		LoadPosition(&list[j], CORDINATESFILE);

		list[j].setHeaderText("\tItem\t\t\t           Stock\t        Price");
	}
	LoadPosition(&list[lWORKGOT], CORDINATESFILE);
	list[lWORKGOT].setHeaderText("\t\tYour Taken Work");

	HANDLE fil;
	NewListItem listItem;
	unsigned long antLesta;
	BOOL result;
	fil = CreateFile(STOCKFILE, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		Logg("Error opening File", STOCKFILE);
		MessageBox(NULL, STOCKFILE, "Error opening", MB_OK);
		return false;
	}

	
	int i = 0;
	do 
	{
		result = ReadFile(fil, &listItem, sizeof(listItem), &antLesta, NULL);
		if(result == false)
		{
			MessageBox(NULL, STOCKFILE, "Error opening", MB_OK);
			return false;
		}
		else
		{
			if(antLesta == sizeof(listItem))
			{
				list[lSTOCK].addObject();
				list[lSTOCK].getObj(i)->setName(listItem.name);
				list[lSTOCK].getObj(i)->setId(listItem.id);
				list[lSTOCK].getObj(i)->setPrice(listItem.itsPrice);
				list[lSTOCK].getObj(i)->setMax(listItem.maxPrice);
				list[lSTOCK].getObj(i)->setMin(listItem.minPrice);
				list[lSTOCK].getObj(i)->setQuantity(rand()%MAX_STOCKTOSELL);
				
				for(int j = 0; j < MAX_PREVPRICE; j++)
					list[lSTOCK].getObj(i)->fixPrice();

				i++;
			}
		}
	} while(antLesta == sizeof(NewListItem));

	CloseHandle(fil);
	list[lSTOCK].setActiveObject(0);


	// Drug listitems
	drugItem dItem;
	fil = CreateFile(DRUGFILE, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, DRUGFILE, "Error opening", MB_OK);
		return false;
	}

	i = 0;
	do 
	{
		result = ReadFile(fil, &dItem, sizeof(dItem), &antLesta, NULL);
		if(result == false)
		{
			MessageBox(NULL, DRUGFILE, "Error opening", MB_OK);
			return false;
		}
		else
		{
			if(antLesta == sizeof(dItem))
			{
				list[lDRUG].addObject();
				list[lDRUG].getObj(i)->setName(dItem.name);
				list[lDRUG].getObj(i)->setId(dItem.id);
				list[lDRUG].getObj(i)->setPrice(dItem.nPrice);
				list[lDRUG].getObj(i)->setMin(int(dItem.nPrice*0.5));
				list[lDRUG].getObj(i)->setMax(dItem.nPrice*2);
				list[lDRUG].getObj(i)->setQuantity(rand()%MAX_TRAININGTOSELL);
				list[lDRUG].getObj(i)->setCostInSleep(dItem.nCostInSleep);
				list[lDRUG].getObj(i)->setFitnes(dItem.nFitness);
				list[lDRUG].getObj(i)->setExtraString(dItem.text);
		
				for(int j = 0; j < MAX_PREVPRICE; j++)
					list[lDRUG].getObj(i)->fixPrice();

				i++;
			}
		}
	} while(antLesta == sizeof(drugItem));

	CloseHandle(fil);
	list[lDRUG].setActiveObject(0);


	// Training List
	fil = CreateFile(TRAININGFILE, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, TRAININGFILE, "Error opening", MB_OK);
		return false;
	}

	i = 0;
	do 
	{
		result = ReadFile(fil, &dItem, sizeof(dItem), &antLesta, NULL);
		if(result == false)
		{
			MessageBox(NULL, DRUGFILE, "Error opening", MB_OK);
			return false;
		}
		else
		{
			if(antLesta == sizeof(dItem))
			{
				list[lTRAINING].addObject();
				list[lTRAINING].getObj(i)->setName(dItem.name);
				list[lTRAINING].getObj(i)->setId(dItem.id);
				list[lTRAINING].getObj(i)->setPrice(dItem.nPrice);
				list[lTRAINING].getObj(i)->setMin(int(dItem.nPrice*0.5));
				list[lTRAINING].getObj(i)->setMax(dItem.nPrice*2);
				list[lTRAINING].getObj(i)->setQuantity(rand()%MAX_TRAININGTOSELL);
				list[lTRAINING].getObj(i)->setCostInSleep(dItem.nCostInSleep);
				list[lTRAINING].getObj(i)->setFitnes(dItem.nFitness);
				list[lTRAINING].getObj(i)->setExtraString(dItem.text);

				for(int j = 0; j < MAX_PREVPRICE; j++)
					list[lTRAINING].getObj(i)->fixPrice();
				
				i++;
			}
		}
	} while(antLesta == sizeof(drugItem));
	CloseHandle(fil);
	list[lTRAINING].setActiveObject(0);
	
	return 1;
}

void TheGame::BuyStock(HWND hWnd, int quantity)
{
	bool exist = false;
	int gotAnt = list[lSTOCKGOT].getNumber();					// Antalet listObject
	int quant = list[lSTOCK].getActiveObj()->getQuantity();		// Antalet som kan köpas
	int price = list[lSTOCK].getActiveObj()->getPrice();		// Priset
	int id = list[lSTOCK].getActiveObj()->getId();				// Id
	
	int i = 0;
	for(; i < gotAnt && exist != true; i++)			// Gå igenom listan och se om den existerar
		if(id== list[lSTOCKGOT].getObj(i)->getId())				// Har den samma id?
			exist = true;										// Om den har det så finns den

	if( exist != true && gotAnt < 16 &&							// Finns den och mindre än 16 object
		itsPlayer.money >= price && quant > 0)					// Har man pengar och finns det några kvar att köpa
	{
		list[lSTOCKGOT].addObject();
		list[lSTOCKGOT].getObj(i)->setName(list[lSTOCK].getActiveObj()->getName());
		list[lSTOCKGOT].getObj(i)->setId(list[lSTOCK].getActiveObj()->getId());
	}
	else if(exist == true && gotAnt < 10 && 
			itsPlayer.money >= price && quant > 0)
		i--;
	else
		return;

	//Köper
	for(int j = 1; list[lSTOCKGOT].getObj(i)->getQuantity() < 100 && list[lSTOCK].getActiveObj()->getQuantity() > 0
	 && j <= quantity && itsPlayer.money >= price; j++)
	{
		list[lSTOCK].getActiveObj()->setQuantity (list[lSTOCK].getActiveObj()->getQuantity() - 1);
		list[lSTOCKGOT].getObj(i)->setQuantity(list[lSTOCKGOT].getObj(i)->getQuantity() + 1);
		list[lSTOCKGOT].getObj(i)->setPrice(price);
		itsPlayer.money -= price;
	}

	list[lSTOCK].getActiveObj()->draw(hWnd, true);
	InvalidateRect(hWnd, list[lSTOCKGOT].getObj(i)->getRect(), FALSE);
}

void TheGame::BuyDrug(HWND hWnd, int quantity)
{
	int quant = list[lDRUG].getActiveObj()->getQuantity();
	int price = list[lDRUG].getActiveObj()->getPrice();

	//Köper
	for(int j = 1; list[lDRUG].getActiveObj()->getQuantity() > 0
	 && j <= quantity && itsPlayer.money >= price; j++)
	{
		list[lDRUG].getActiveObj()->setQuantity (list[lDRUG].getActiveObj()->getQuantity() - 1);
		itsPlayer.money -= price;
		itsPlayer.fitness += list[lDRUG].getActiveObj()->getFitness();
	}

	list[lDRUG].getActiveObj()->draw(hWnd, true);
}


void TheGame::BuyTraining(HWND hWnd, int quantity)
{
	int quant = list[lTRAINING].getActiveObj()->getQuantity();
	int price = list[lTRAINING].getActiveObj()->getPrice();

	MB_HWND("You wanasd buy")
	//Köper
	for(int j = 1; list[lTRAINING].getActiveObj()->getQuantity() > 0
	 && j <= quantity && itsPlayer.money >= price && itsPlayer.awake >= list[lTRAINING].getActiveObj()->getCostInSleep(); j++)
	{
		list[lTRAINING].getActiveObj()->setQuantity (list[lTRAINING].getActiveObj()->getQuantity() - 1);
		itsPlayer.fitness += list[lTRAINING].getActiveObj()->getFitness();
		itsPlayer.awake -= list[lTRAINING].getActiveObj()->getCostInSleep();
		itsPlayer.money -= price;
		MB_HWND("You bought!")
	}

	list[lDRUG].getActiveObj()->draw(hWnd, true);
}

void TheGame::SellStock(HWND hWnd, int quantity)
{
	int activeNr = list[lSTOCKGOT].getActiveObjNr();
	if(activeNr >= 0 && activeNr < list[lSTOCKGOT].getNumber())
	{
		for(int i = 0; i < list[lSTOCK].getNumber(); i++)
		{
			if(list[lSTOCKGOT].getActiveObj()->getId() == list[lSTOCK].getObj(i)->getId())
			{
				for(int j = 1;list[lSTOCKGOT].getActiveObj()->getQuantity() > 0 && j <= quantity; j++)
				{
					list[lSTOCK].getObj(i)->setQuantity(list[lSTOCK].getObj(i)->getQuantity() + 1);
					itsPlayer.money += list[lSTOCK].getObj(i)->getPrice();
					list[lSTOCKGOT].getActiveObj()->setQuantity(list[lSTOCKGOT].getActiveObj()->getQuantity()-1);
				}
				if(list[lSTOCKGOT].getActiveObj()->getQuantity() == 0)	// No more to sell
				{
					list[lSTOCKGOT].deleteActiveObj();					// Delete the object
					i = list[lSTOCK].getNumber();						// To stop the loop
				}
			}
		}
		list[lSTOCK].draw(hWnd, false);
		list[lSTOCKGOT].draw(hWnd, true);
	}
}

int TheGame::getWorkAction(CWork initWork)
{
	if( initWork.getCostInFitnes() <= itsPlayer.fitness &&
		initWork.getFitness() <= itsPlayer.fitness)
	{
		itsPlayer.money += initWork.getWage();
		itsPlayer.fitness -= double(initWork.getCostInFitnes());
		takenWork.addObject(getActiveWork());
		list[lWORKGOT].addObject();
		list[lWORKGOT].getObj(list[lWORKGOT].getNumber()-1)->setVisualString(initWork.getName());
		itsWork[activeWorkHandle].deleteActiveObject(false);

		itsPlayer.takenWork += 1;
		
		return true;
	}
	else
		return false;
}

int TheGame::getWorkLeft()
{
	int returnInt = 0;
	for(int i = 0; i < MAX_WORKHANDLES; i++)
	{
		returnInt += itsWork[i].getWorkNumber();
	}

	return returnInt;
}

int TheGame::sleep(int initDays)
{
	itsPlayer.timesSleeped++;
	for(int j = 0; j < initDays; j++)
	{
		itsPlayer.days++;
		if(itsPlayer.days > itsPlayer.maxDay)
		{
			setStatus(END_GAME);
			return 0;
		}

		for(int i = 0; i < MAX_PREVMONEY-1; i++)
			itsPlayer.prevMoney[i] = itsPlayer.prevMoney[i+1];
		itsPlayer.prevMoney[MAX_PREVMONEY-1] = itsPlayer.money;

		for(int i = 0; i < MAX_PREVFITNESS-1; i++)
			itsPlayer.prevFitness[i] = itsPlayer.prevFitness[i+1];
		itsPlayer.prevFitness[MAX_PREVFITNESS-1] = int(itsPlayer.fitness);

		if(itsPlayer.awake <= MAX_AWAKE-ADD_AWAKE)
			itsPlayer.awake += ADD_AWAKE;

		for(int listUpdate = lSTOCK; listUpdate <= lTRAINING; listUpdate++)
			for(int i = 0; i < list[listUpdate].getNumber(); i++)
			{
				list[listUpdate].getObj(i)->fixPrice();
				if(listUpdate == lSTOCK)
					list[listUpdate].getObj(i)->setQuantity(rand()%MAX_STOCKTOSELL);
				else
					list[listUpdate].getObj(i)->setQuantity(rand()%MAX_TRAININGTOSELL);
			}
	}
	return 1;
}

void TheGame::reset()
{	
	list[lSTOCKGOT].deleteAllObjects();
	list[lWORKGOT].deleteAllObjects();
	activeWorkHandle = 0;
	switch(itsPlayer.itsMode)
	{
	case EASY_MODE: 
		itsPlayer.money = INIT_EASY_MONEY; 
		itsPlayer.maxDay = INIT_EASY_MAXDAYS;
		itsPlayer.fitness = INIT_EASY_FITNESS; 
	break;
	case NORMAL_MODE: 
		itsPlayer.money = INIT_NORMAL_MONEY; 
		itsPlayer.maxDay = INIT_NORMAL_MAXDAYS;
		itsPlayer.fitness = INIT_NORMAL_FITNESS; 
	break;
	case HARD_MODE: 
		itsPlayer.money = INIT_HARD_MONEY; 
		itsPlayer.maxDay = INIT_HARD_MAXDAYS;
		itsPlayer.fitness = INIT_HARD_FITNESS; 
	break;
	default:
		itsPlayer.money = INIT_MONEY; 
		itsPlayer.maxDay = INIT_MAXDAYS;
		itsPlayer.fitness = INIT_FITNESS; 
		break;
	}
	
	itsPlayer.days = 0;
	itsPlayer.timesSleeped = 0;
	itsPlayer.awake = 50;
	itsPlayer.takenWork = 0;
	for(int i = 0; i < MAX_PREVMONEY; i++)
		itsPlayer.prevMoney[i] = itsPlayer.money;

	for(int i = 0; i < MAX_PREVFITNESS; i++)
		itsPlayer.prevFitness[i] = int(itsPlayer.fitness);

	drawLoad = false;
}

int TheGame::SaveToFile(char* fileName)
{
	HANDLE fil;
	unsigned long int antWritten;
	BOOL result;

	fil = CreateFile(fileName, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		Logg("Error opening File", fileName);
		MessageBox(NULL, fileName, "Error opening", MB_OK);
		return false;
	}

	TheGameSave tempSaveGame;
	tempSaveGame.activeRoom = activeRoom;
	tempSaveGame.activeWorkHandle = activeWorkHandle;
	tempSaveGame.drawLoad = drawLoad;
	tempSaveGame.itsPlayer = itsPlayer;
	tempSaveGame.itsStatus = itsStatus;
	tempSaveGame.oldStatus = oldStatus;

	Logg("Itsplayer days", tempSaveGame.itsPlayer.days);

	result = WriteFile(fil, &tempSaveGame, sizeof(TheGameSave), &antWritten, NULL); 
	if(result == false)
	{
		Logg("Error saving", fileName);
		MessageBox(NULL, fileName, "Error opening", MB_OK);
		return false;
	}

	saveListItem lISave;
	int listObjToSave;
	for(int listUpdate = lSTOCKGOT; listUpdate <= lWORKGOT; listUpdate++)
	{
		listObjToSave = list[listUpdate].getNumber();
		result = WriteFile(fil, &listObjToSave, sizeof(int), &antWritten, NULL); 
		if(result == false)
		{
			Logg("Error saving", fileName);
			MessageBox(NULL, fileName, "Error writing", MB_OK);
			return false;
		}
		for(int i = 0; i < list[listUpdate].getNumber(); i++)
		{
			list[listUpdate].getObj(i)->getItem(lISave);
			result = WriteFile(fil, &lISave, sizeof(saveListItem), &antWritten, NULL); 
			if(result == false)
			{
				Logg("Error saving", fileName);
				MessageBox(NULL, fileName, "Error writing", MB_OK);
				return false;
			}
		}
	}
	for(int i = 1; i < MAX_WORKHANDLES; i++)
	{
		result = WriteFile(fil, itsWork, sizeof(CWorkHandler)*MAX_WORKHANDLES, &antWritten, NULL); 
		if(result == false)
		{
			Logg("Error saving", fileName);
			MessageBox(NULL, fileName, "Error writing", MB_OK);
			return false;
		}
	}

	result = WriteFile(fil, &takenWork, sizeof(CWorkHandler), &antWritten, NULL); 
	if(result == false)
	{
		Logg("Error saving", fileName);
		MessageBox(NULL, fileName, "Error writing", MB_OK);
		return false;
	}

	CloseHandle(fil);

	// Write mini dump(only player status) In another file
	char buffer[2*MAX_BUFFER];
	wsprintf(buffer,"%smini", fileName);
	fil = CreateFile(buffer, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		Logg("Error opening File", fileName);
		MessageBox(NULL, fileName, "Error opening", MB_OK);
		return false;
	}
	result = WriteFile(fil, &itsPlayer, sizeof(itsPlayer), &antWritten, NULL); 
	if(result == false)
	{
		Logg("Error saving", fileName);
		MessageBox(NULL, fileName, "Error writing", MB_OK);
		return false;
	}
	CloseHandle(fil);
	return true;
}

int TheGame::LoadFromFile(char* fileName)
{
	HANDLE fil;
	unsigned long antRead;
	BOOL result;
	fil = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		Logg("Error opening File", fileName);
		MessageBox(NULL, fileName, "Error opening", MB_OK);
		return false;
	}

	TheGameSave tempSaveGame;
	result = ReadFile(fil, &tempSaveGame, sizeof(TheGameSave), &antRead, NULL); 
	if(result == false)
	{
		Logg("Error Reading", fileName);
		MessageBox(NULL, fileName, "Error Reading The Game", MB_OK);
		return false;
	}
	else
	{
		activeRoom = tempSaveGame.activeRoom;
		activeWorkHandle = tempSaveGame.activeWorkHandle;
		drawLoad = tempSaveGame.drawLoad;
		itsPlayer = tempSaveGame.itsPlayer;
		Logg("Itsplayer days", tempSaveGame.itsPlayer.days);
		itsStatus = tempSaveGame.itsStatus;
		oldStatus = tempSaveGame.oldStatus;
	}

	CListObject *lItem;
	saveListItem lISave;
	int listObjToLoad = 0;
	for(int listUpdate = lSTOCKGOT; listUpdate <= lWORKGOT; listUpdate++)
	{
		list[listUpdate].deleteAllObjects();
		result = ReadFile(fil, &listObjToLoad, sizeof(int), &antRead, NULL); 
		if(result == false)
		{
			Logg("Error saving", fileName);
			MessageBox(NULL, fileName, "Error writing", MB_OK);
			return false;
		}
		for(int i = 0; i < listObjToLoad; i++)
		{
			Logg("Listobject", i);
			result = ReadFile(fil, &lISave, sizeof(saveListItem), &antRead, NULL); 
			if(result == false)
			{
				Logg("Error saving", fileName);
				MessageBox(NULL, fileName, "Error writing", MB_OK);
				return false;
			}
			else
			{
				//lItem = new CListObject(lISave);
				lItem = new CListObject(lISave);
				list[listUpdate].addObject(lItem);
				delete lItem;
				lItem = NULL;
			}
		}
		Logg("Load list done");
	}
	for(int i = 1; i < MAX_WORKHANDLES; i++)
	{
		result = ReadFile(fil, itsWork, sizeof(CWorkHandler)*MAX_WORKHANDLES, &antRead, NULL); 
		if(result == false)
		{
			Logg("Error saving", fileName);
			MessageBox(NULL, fileName, "Error writing", MB_OK);
			return false;
		}
	}

	result = ReadFile(fil, &takenWork, sizeof(CWorkHandler), &antRead, NULL); 
	if(result == false)
	{
		Logg("Error saving", fileName);
		MessageBox(NULL, fileName, "Error writing", MB_OK);
		return false;
	}

	CloseHandle(fil);
	return true;
}

int TheGame::LoadWork(char* file)
{
	HANDLE fil;
	fil = CreateFile(file, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, file, "Error opening", MB_OK);
		return false;
	}
	DWORD antRead = 0;
	int i = 0;
	do 
	{
		CWork tempWork;
		tempWork.Load(fil, antRead);
		i++;

		if(i == 1)
			itsWork[0].addObject(tempWork);
		else if(i == 2)
			itsWork[1].addObject(tempWork);
		else if(i == 3)
			itsWork[2].addObject(tempWork);
		else if(i == 4)
			itsWork[3].addObject(tempWork);
		else if(i == 5)
			itsWork[4].addObject(tempWork);
		else if(i == 6)
			itsWork[5].addObject(tempWork);
		else
		{
			i = 1;
			itsWork[0].addObject(tempWork);
		}

	} while(antRead == sizeof(SaveWork));

	CloseHandle(fil);

	return 1;
}

CWorkHandler TheGame::getActiveWorkHandle()
{
	return itsWork[activeWorkHandle];
}

CWorkHandler TheGame::getTakenWorkHandle()
{
	return takenWork;
}

void TheGame::setActiveWorkHandle(int init)
{
	if(init >= 0 && init < 6)
		activeWorkHandle = init;
}

void TheGame::setActiveWork(int init)
{
	itsWork[activeWorkHandle].setActiveWork(init);
}

CList* TheGame::getList(int init)
{
	if(init >= 0 && init <= lWORKGOT)
		return &list[init];	
	else
		return NULL;
}






int CountPoints(TheGame &init)
{
	int returnInt = 0;
	float modePoints = 1;
	switch(init.getGameMode())
	{
		case EASY_MODE: modePoints = 1; break;
		case NORMAL_MODE: modePoints = float(1.2); break;
		case HARD_MODE: modePoints = 1.5; break;
	}
	returnInt = int((float(init.getMoney())*float(init.getFitness())*modePoints) /
				   float(5*init.getTimesSleeped()+init.getDays()));

	return returnInt;
}