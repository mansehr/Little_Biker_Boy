// MainMenu.cpp: implementation of the CMainMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainMenu.h"
#include "Filhant.h"
#include "TheGame.h"

const int nButtons = START+1;
CMenuButton Button[nButtons];

// 	INITMAINMENU		///////////////////////////////////////
int InitMainMenu(CMainMenu &mainMenu, HWND hWnd)
{
	Logg("<b>Init Main Menu</b>");

	Button[NEWGAME].setName("newGame");
	Button[LOADGAME].setName("loadGame");
	Button[SAVEGAME].setName("saveGame");
	Button[OPTIONS].setName("options");
	Button[CREDITS].setName("credits");
	Button[EXITGAME].setName("exitGame");
	Button[LOAD].setName("load");
	Button[SAVE].setName("save");
	Button[SLOT1].setName("slot1");
	Button[SLOT2].setName("slot2");
	Button[BACK].setName("back");
	Button[EASY].setName("easy");
	Button[MEDIUM].setName("medium");
	Button[HARD].setName("hard");
	Button[START].setName("start");

	for(int i = 0; i < nButtons; i++)
	{
		Button[i].setMaskColor(RGB(255, 255, 0));

		String normalString, mouseOverString, activeString;
		normalString	= normalString		+"data/Menu/"+Button[i].getName()+".bmp";
		mouseOverString	= mouseOverString	+"data/Menu/"+Button[i].getName()+"1.bmp";
		activeString	= activeString		+"data/Menu/"+Button[i].getName()+"2.bmp";

		if( Button[i].LoadABitmap(normalString.getString()	 , NORMAL)		== 0 ||
			Button[i].LoadABitmap(mouseOverString.getString(), MOUSE_OVER)	== 0 ||
			Button[i].LoadABitmap(activeString.getString()	 , ACTIVE)		== 0 )
		{
			Logg("<b>Bitmap Load Error</b>", Button[i].getName());
			MessageBox(hWnd, Button[i].getName(), "Bitmap Load error", MB_OK);
			return 0;
		}
		if(LoadPosition(&Button[i], "data/Menu/menuButtons.txt") == 0)
		{
			Logg("<b>Bitmap Position Error</b>", Button[i].getName());
			MessageBox(hWnd, "Load position", "Load error", MB_OK);
			return 0;
		}
#ifdef DEBUGMED
		Logg("Adding to main menu Bitmap", Button[i].getName());
#endif
		mainMenu.addButton(&Button[i]);
	}
	mainMenu.LoadBack("data/Menu/MenuBG.bmp");
	mainMenu.setMenuStatus(MAINMENU, NULL);

	Button[SLOT1].stayActive(true);
	Button[SLOT1].setStatus(ACTIVE);

	Button[MEDIUM].stayActive(true);
	Button[MEDIUM].setStatus(ACTIVE);

	Logg("<b>Init Main Menu <u>Done</u></b>");

	return 1;
}


CMainMenu* activeMenu;
//////////////////////////////////////////////////////////////////////
// TimerProc
//////////////////////////////////////////////////////////////////////
VOID CALLBACK MainMenuClassTimerProc( 
    HWND hWnd,        // handle to window for timer messages 
    UINT message,     // WM_TIMER message 
    UINT idTimer,     // timer identifier 
    DWORD dwTime)     // current system time 
{ 
	activeMenu->MainMenuTimerProc(hWnd, message, idTimer, dwTime);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMainMenu::CMainMenu()
{
	nMenuButton = 0;

	CReadSiTiFile fCord;
	if(fCord.open("data/Menu/menuButtons.txt") == false)
	{
		MessageBox(NULL, "Coulnt load \"Sub Menu\" cordinates", "Nooooo", MB_OK);
	}
	subMenu.x = fCord.getAsInt("subMenuX");
	subMenu.y = fCord.getAsInt("subMenuY");
	fCord.close();

	movingButton = false;

	activeButton = NULL;

	daysText.setName("menuDaysText");
	moneyText.setName("menuMoneyText");
	jobsText.setName("menuJobsText");
	fitnessText.setName("menuFitnessText");

	LoadPosition(&daysText, "data/Menu/menuButtons.txt");
	LoadPosition(&moneyText, "data/Menu/menuButtons.txt");
	LoadPosition(&jobsText, "data/Menu/menuButtons.txt");
	LoadPosition(&fitnessText, "data/Menu/menuButtons.txt");

	daysText.setBgColor(RGB(255,255,255));
	moneyText.setBgColor(RGB(255,255,255));
	jobsText.setBgColor(RGB(255,255,255));
	fitnessText.setBgColor(RGB(255,255,255));
	
	daysText.setFlags(DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	moneyText.setFlags(DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	jobsText.setFlags(DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	fitnessText.setFlags(DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	daysText.setTextWeight(FW_BOLD);
	moneyText.setTextWeight(FW_BOLD);
	jobsText.setTextWeight(FW_BOLD);
	fitnessText.setTextWeight(FW_BOLD);

	//setTexts(SAVEFILE1);


	LoadHighscore(HIGHSCOREFILE, highScoreObj);
	UpdateHighscoreList();

	highScoreHead.setText("HIGHSCORE");
	highScoreHead.setPosition(450, 300, 750, 340);
	highScoreHead.setBgMode(TRANSPARENT);
	highScoreHead.setTextColor(RGB(218, 233, 172));
	highScoreHead.setFlags(DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	highScoreHead.setTextHeight(40);
	highScoreHead.setTextWeight(FW_BOLD);

	for(int i = 0; i < MAXHIGHSCORE; i++)
	{
		highScore[i].setBgMode(TRANSPARENT);
		highScore[i].setTextHeight(24);
		highScore[i].setTextColor(RGB(218, 233, 172));
		highScore[i].setFlags(DT_SINGLELINE | DT_VCENTER);
		highScore[i].setPosition(380, 350+(i*25), 750, 370+(i*25));
		highScoreHead.setTextWeight(FW_BOLD);
	}
}

CMainMenu::~CMainMenu()
{

}

void CMainMenu::setMenuStatus(MenuStatus init, HWND hWnd, bool move)
{
	for(int i = 0; i < nMenuButton; i++)
		if(i != SLOT1 && i != SLOT2 && i != EASY && i != MEDIUM && i != HARD)
			itsMenuButtons[i]->setStatus(NORMAL);	// Set all the buttons to normal
													// So none is active
	if(hWnd != NULL)
	{
		if(init == LOADGAMEMENU)
		{
			if(itsMenuButtons[SLOT1]->getStatus() == ACTIVE)
				setTexts(SAVEFILE1);
			else
				setTexts(SAVEFILE2);

			if(move)
				moveButton(itsMenuButtons[LOADGAME], hWnd);
			else
				setButton(itsMenuButtons[LOADGAME]);
		}
			
		if(init == SAVEGAMEMENU)
		{
			if(itsMenuButtons[SLOT1]->getStatus() == ACTIVE)
				setTexts(SAVEFILE1);
			else
				setTexts(SAVEFILE2);
			
			if(move)
				moveButton(itsMenuButtons[SAVEGAME], hWnd);
			else
				setButton(itsMenuButtons[SAVEGAME]);
		}
		
		if(init == OPTIONSMENU)
			if(move)
				moveButton(itsMenuButtons[OPTIONS], hWnd);
			else
				setButton(itsMenuButtons[OPTIONS]);
		
		if(init == CREDITSMENU)
			if(move)
				moveButton(itsMenuButtons[CREDITS], hWnd);
			else
				setButton(itsMenuButtons[CREDITS]);

		if(init == NEWGAMEMENU)
			if(move)
				moveButton(itsMenuButtons[NEWGAME], hWnd);
			else
				setButton(itsMenuButtons[NEWGAME]);
	}
	menuStatus = init;
}

MenuStatus CMainMenu::getMenuStatus()
{
	return menuStatus;
}

int CMainMenu::LoadBack(LPSTR szFileName)
{
	return spriteBack.LoadABitmap(szFileName, false);
}

void CMainMenu::draw(HWND hWnd, bool forced)
{
	HDC hdc			= GetDC(hWnd);
	this->draw(hdc, forced);
	ReleaseDC(hWnd, hdc);
}

void CMainMenu::draw(HDC hdc, bool forced)
{
	spriteBack.draw(hdc);

	if(getMenuStatus() == MAINMENU || movingButton && !bClose)	
		for(int i = NEWGAME; i <= EXITGAME; i++)
			itsMenuButtons[i]->draw(hdc, forced);

	if(getMenuStatus() == NEWGAMEMENU)
	{
		itsMenuButtons[NEWGAME]->draw(hdc, forced);
		itsMenuButtons[EASY]->draw(hdc, forced);
		itsMenuButtons[MEDIUM]->draw(hdc, forced);
		itsMenuButtons[HARD]->draw(hdc, forced);
		itsMenuButtons[START]->draw(hdc, forced);
	}

	if(getMenuStatus() == LOADGAMEMENU)
	{
		itsMenuButtons[LOADGAME]->draw(hdc, forced);
		itsMenuButtons[LOAD]->draw(hdc, forced);
	}

	if(getMenuStatus() == SAVEGAMEMENU)
	{
		itsMenuButtons[SAVEGAME]->draw(hdc, forced);
		itsMenuButtons[SAVE]->draw(hdc, forced);
	}

	if(getMenuStatus() == OPTIONSMENU)
	{
		itsMenuButtons[OPTIONS]->draw(hdc, forced);
		if(movingButton == false)
		{
			highScoreHead.draw(hdc);
			for(int i = 0; i < MAXHIGHSCORE; i++)
				highScore[i].draw(hdc);
		}
	}

	if(getMenuStatus() == CREDITSMENU)	
		itsMenuButtons[CREDITS]->draw(hdc, forced);

	if( (getMenuStatus() == LOADGAMEMENU ||
		getMenuStatus() == SAVEGAMEMENU ||
		getMenuStatus() == OPTIONSMENU ||
		getMenuStatus() == CREDITSMENU  ||
		getMenuStatus() == NEWGAMEMENU)	&&
		movingButton != true)
		itsMenuButtons[BACK]->draw(hdc, forced);

	if( (getMenuStatus() == LOADGAMEMENU ||
		 getMenuStatus() == SAVEGAMEMENU)&&
		movingButton != true)
	{
		itsMenuButtons[SLOT1]->draw(hdc, forced);
		itsMenuButtons[SLOT2]->draw(hdc, forced);
		daysText.draw(hdc);
		moneyText.draw(hdc);
		jobsText.draw(hdc);
		fitnessText.draw(hdc);
	}
}

void CMainMenu::addButton(CMenuButton* init)
{
	itsMenuButtons[nMenuButton++] = init;
}

CMenuButton* CMainMenu::getButton(int init)
{
	return itsMenuButtons[init];
}

GameMode CMainMenu::getMode()
{
	if(itsMenuButtons[EASY]->getStatus() == ACTIVE)
		return EASY_MODE;
	else if(itsMenuButtons[MEDIUM]->getStatus() == ACTIVE)
		return NORMAL_MODE;
	else if(itsMenuButtons[HARD]->getStatus() == ACTIVE)
		return HARD_MODE;
	else
		return EASY_MODE;
}

int CMainMenu::test(int initX, int initY, HWND hWnd, bool keyPressed)
{
	if(movingButton != true)
	{
		if(getMenuStatus() == MAINMENU)	
		{
			for(int i = NEWGAME; i <= EXITGAME; i++)
				itsMenuButtons[i]->test(initX, initY, hWnd, keyPressed);
		}
		if(getMenuStatus() == LOADGAMEMENU)	
		{
			itsMenuButtons[LOADGAME]->test(initX, initY, hWnd, keyPressed);
			itsMenuButtons[BACK]->test(initX, initY, hWnd, keyPressed);
			itsMenuButtons[LOAD]->test(initX, initY, hWnd, keyPressed);
		}
		if(getMenuStatus() == SAVEGAMEMENU)	
		{
			itsMenuButtons[SAVEGAME]->test(initX, initY, hWnd, keyPressed);
			itsMenuButtons[BACK]->test(initX, initY, hWnd, keyPressed);
			itsMenuButtons[SAVE]->test(initX, initY, hWnd, keyPressed);
		}
		if(getMenuStatus() == OPTIONSMENU)	
		{
			itsMenuButtons[OPTIONS]->test(initX, initY, hWnd, keyPressed);
			itsMenuButtons[BACK]->test(initX, initY, hWnd, keyPressed);
		}
		if(getMenuStatus() == CREDITSMENU)	
		{
			itsMenuButtons[CREDITS]->test(initX, initY, hWnd, keyPressed);
			itsMenuButtons[BACK]->test(initX, initY, hWnd, keyPressed);
		}
		if( getMenuStatus() == LOADGAMEMENU ||
			getMenuStatus() == SAVEGAMEMENU)
		{
			itsMenuButtons[SLOT1]->test(initX, initY, hWnd, keyPressed);
			if(itsMenuButtons[SLOT1]->getStatus() == PRESSED)
			{
				setTexts(SAVEFILE1);
				itsMenuButtons[SLOT1]->stayActive(true);
				itsMenuButtons[SLOT1]->setStatus(ACTIVE);
				itsMenuButtons[SLOT2]->stayActive(false);
				itsMenuButtons[SLOT2]->setStatus(NORMAL);
				InvalidateRect(hWnd, itsMenuButtons[SLOT1]->getRect(), FALSE);
				InvalidateRect(hWnd, itsMenuButtons[SLOT2]->getRect(), FALSE);
				InvalidateRect(hWnd, daysText.getRect(), FALSE);
				InvalidateRect(hWnd, moneyText.getRect(), FALSE);
				InvalidateRect(hWnd, jobsText.getRect(), FALSE);
				InvalidateRect(hWnd, fitnessText.getRect(), FALSE);
			}
			itsMenuButtons[SLOT2]->test(initX, initY, hWnd, keyPressed);
			if(itsMenuButtons[SLOT2]->getStatus() == PRESSED)
			{
				setTexts(SAVEFILE2);
				itsMenuButtons[SLOT2]->stayActive(true);
				itsMenuButtons[SLOT2]->setStatus(ACTIVE);
				itsMenuButtons[SLOT1]->stayActive(false);
				itsMenuButtons[SLOT1]->setStatus(NORMAL);
				InvalidateRect(hWnd, itsMenuButtons[SLOT1]->getRect(), FALSE);
				InvalidateRect(hWnd, itsMenuButtons[SLOT2]->getRect(), FALSE);
				InvalidateRect(hWnd, daysText.getRect(), FALSE);
				InvalidateRect(hWnd, moneyText.getRect(), FALSE);
				InvalidateRect(hWnd, jobsText.getRect(), FALSE);
				InvalidateRect(hWnd, fitnessText.getRect(), FALSE);
			}
		}
		if(getMenuStatus() == NEWGAMEMENU)	
		{
			itsMenuButtons[EASY]->test(initX, initY, hWnd, keyPressed);
			if(itsMenuButtons[EASY]->getStatus() == PRESSED)
			{
				itsMenuButtons[EASY]->stayActive(true);
				itsMenuButtons[EASY]->setStatus(ACTIVE);
				itsMenuButtons[MEDIUM]->stayActive(false);
				itsMenuButtons[MEDIUM]->setStatus(NORMAL);
				itsMenuButtons[HARD]->stayActive(false);
				itsMenuButtons[HARD]->setStatus(NORMAL);
				InvalidateRect(hWnd, itsMenuButtons[EASY]->getRect(), FALSE);
				InvalidateRect(hWnd, itsMenuButtons[MEDIUM]->getRect(), FALSE);
				InvalidateRect(hWnd, itsMenuButtons[HARD]->getRect(), FALSE);
			}
			itsMenuButtons[MEDIUM]->test(initX, initY, hWnd, keyPressed);
			if(itsMenuButtons[MEDIUM]->getStatus() == PRESSED)
			{
				itsMenuButtons[MEDIUM]->stayActive(true);
				itsMenuButtons[MEDIUM]->setStatus(ACTIVE);
				itsMenuButtons[EASY]->stayActive(false);
				itsMenuButtons[EASY]->setStatus(NORMAL);
				itsMenuButtons[HARD]->stayActive(false);
				itsMenuButtons[HARD]->setStatus(NORMAL);
				InvalidateRect(hWnd, itsMenuButtons[EASY]->getRect(), FALSE);
				InvalidateRect(hWnd, itsMenuButtons[MEDIUM]->getRect(), FALSE);
				InvalidateRect(hWnd, itsMenuButtons[HARD]->getRect(), FALSE);
			}
			itsMenuButtons[HARD]->test(initX, initY, hWnd, keyPressed);
			if(itsMenuButtons[HARD]->getStatus() == PRESSED)
			{
				itsMenuButtons[HARD]->stayActive(true);
				itsMenuButtons[HARD]->setStatus(ACTIVE);
				itsMenuButtons[MEDIUM]->stayActive(false);
				itsMenuButtons[MEDIUM]->setStatus(NORMAL);
				itsMenuButtons[EASY]->stayActive(false);
				itsMenuButtons[EASY]->setStatus(NORMAL);
				InvalidateRect(hWnd, itsMenuButtons[EASY]->getRect(), FALSE);
				InvalidateRect(hWnd, itsMenuButtons[MEDIUM]->getRect(), FALSE);
				InvalidateRect(hWnd, itsMenuButtons[HARD]->getRect(), FALSE);
			}
			itsMenuButtons[START]->test(initX, initY, hWnd, keyPressed);
			itsMenuButtons[BACK]->test(initX, initY, hWnd, keyPressed);
		}
	}

	return 0;
}

void CMainMenu::addScore(int initPoints, char* initName)
{
	for(int i = 0; i < MAXHIGHSCORE; i++)
	{
		if(highScoreObj[i].points < initPoints)
		{
			for(int j = MAXHIGHSCORE-1; j > i; j--)
			{
				highScoreObj[j] = highScoreObj[j-1];
			}
			highScoreObj[i].points = initPoints;
			strcpy_s(highScoreObj[i].name, initName);

			UpdateHighscoreList();

			SaveHighscore(HIGHSCOREFILE, highScoreObj);

			i = MAXHIGHSCORE; //End loop
		}
	}
}

void CMainMenu::UpdateHighscoreList()
{
	for(int i = 0; i < MAXHIGHSCORE; i++)
	{
		char buffer[MAX_BUFFER];
		wsprintf(buffer, "%i. %s \t\t%i", i+1, highScoreObj[i].name, highScoreObj[i].points);
		highScore[i].setText(buffer);
	}
}

void CMainMenu::reset(HWND hWnd)
{
	menuStatus = MAINMENU;
	for(int i = 0; i < nMenuButton; i++)
		if(i != SLOT1 && i != SLOT2 && i != EASY && i != MEDIUM && i != HARD)
			itsMenuButtons[i]->setStatus(NORMAL);	// Set all the buttons to normal, So none is active

	if(activeButton != NULL)
		activeButton->setPosition(oldRc);

	KillTimer(hWnd, MENU_TIMER); 
}

void CMainMenu::show(HWND hWnd)
{
	movingButton = true;
	bClose = false;

	move.x = (activeButton->getLeft() - subMenu.x) / 20;
	move.y = (activeButton->getTop()  - subMenu.y) / 20;
	
	activeMenu = this;

	SetTimer(hWnd,      // handle to main window 
	MENU_TIMER,            // timer identifier 
	30,                    // 0.01-second interval 
	(TIMERPROC) MainMenuClassTimerProc); // timer callback
}

void CMainMenu::close(HWND hWnd)
{
	movingButton = true;
	bClose = true;

	activeMenu = this;

	SetTimer(hWnd,      // handle to main window 
	MENU_TIMER,            // timer identifier 
	30,                    // 0.01-second interval 
	(TIMERPROC) MainMenuClassTimerProc); // timer callback

	InvalidateRect(hWnd, NULL, FALSE);
}

//////////////////////////////////////////////////////////////////////
// TimerProc
//////////////////////////////////////////////////////////////////////
VOID CALLBACK CMainMenu::MainMenuTimerProc( 
    HWND hWnd,        // handle to window for timer messages 
    UINT message,     // WM_TIMER message 
    UINT idTimer,     // timer identifier 
    DWORD dwTime)     // current system time 
{ 
	RECT rt;
	bool inPosX = false;
	bool inPosY = false;

	if(bClose)
	{

		activeButton->moveLeftTo(activeButton->getLeft()+move.x);
		activeButton->moveTopTo(activeButton->getTop()+move.y);
		
		if(activeButton->getLeft() >= oldRc.left)
		{
			activeButton->moveLeftTo(oldRc.left);
			inPosX = true;
		}
		if(activeButton->getTop() >= oldRc.top)
		{
			activeButton->moveTopTo(oldRc.top);
			inPosY = true;
		}
	}
	else
	{
		activeButton->moveLeftTo(activeButton->getLeft()-move.x);
		activeButton->moveTopTo(activeButton->getTop()-move.y);
		
		if(activeButton->getLeft() <= subMenu.x)
		{
			activeButton->moveLeftTo(subMenu.x);
			inPosX = true;
		}
		if(activeButton->getTop() <= subMenu.y)
		{
			activeButton->moveTopTo(subMenu.y);
			inPosY = true;
		}
	}

	if(inPosX && inPosY)
	{
		movingButton = false;
		KillTimer(hWnd, MENU_TIMER);
		if(bClose)
			setMenuStatus(MAINMENU, hWnd);
		InvalidateRect(hWnd, NULL, FALSE);
	}

	rt = activeButton->getItsPosition();
	rt.left -= move.x;
	rt.right += move.x;
	rt.top -= move.y;
	rt.bottom += move.y;
	InvalidateRect(hWnd, &rt, FALSE);
}

//Private
void CMainMenu::moveButton(CMenuButton* init, HWND hWnd)
{
	oldRc = init->getItsPosition();
	init->setStatus(NOT_PRESSABLE);
	activeButton = init;
	show(hWnd);
}

void CMainMenu::setButton(CMenuButton* init)
{
	oldRc = init->getItsPosition();
	init->setStatus(NOT_PRESSABLE);
	activeButton = init;

	move.x = (activeButton->getLeft() - subMenu.x) / 20;
	move.y = (activeButton->getTop()  - subMenu.y) / 20;

	init->moveLeftTo(subMenu.x);
	init->moveTopTo(subMenu.y);
}

int CMainMenu::setTexts(char* fileName)
{
	Player tempPlayer;
	HANDLE fil;
	BOOL result;
	unsigned long int antRead;
	char buffer[2*MAX_BUFFER];

	wsprintf(buffer,"%smini", fileName);
	fil = CreateFile(buffer, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		Logg("Error opening save File", fileName);
		MessageBox(NULL, fileName, "Error opening", MB_OK);
		return 0;
	}
	result = ReadFile(fil, &tempPlayer, sizeof(tempPlayer), &antRead, NULL); 
	if(result == false)
	{
		Logg("Error saving", fileName);
		MessageBox(NULL, fileName, "Error writing", MB_OK);
		return 0;
	}
	else
	{
		daysText.setText("Days", tempPlayer.days);
		moneyText.setText("Money", tempPlayer.money);
		jobsText.setText("Job Taken", tempPlayer.takenWork);
		fitnessText.setText("Fitness", int(tempPlayer.fitness));
	}
	CloseHandle(fil);
	return 1;
}


void LoadHighscore(char* file, HighScoreObj *highScoreObj)
{
	HANDLE fil;
	BOOL result;
	unsigned long int antRead;

	fil = CreateFile(file, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		Logg("Error opening File", file);
		MessageBox(NULL, file, "Error opening", MB_OK);
		return;
	}
	result = ReadFile(fil, highScoreObj, sizeof(HighScoreObj)*MAXHIGHSCORE, &antRead, NULL); 
	if(result == false)
	{
		Logg("Error saving", file);
		MessageBox(NULL, file, "Error writing", MB_OK);
		return;
	}
	else
	{
		Logg("Load Highscore Done");
	}
	CloseHandle(fil);

}
void SaveHighscore(char* file, HighScoreObj *highScoreObj)
{
	HANDLE fil;
	BOOL result;
	unsigned long int antRead;

	fil = CreateFile(file, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		Logg("Error opening File", file);
		MessageBox(NULL, file, "Error opening", MB_OK);
		return;
	}
	result = WriteFile(fil, highScoreObj, sizeof(HighScoreObj)*MAXHIGHSCORE, &antRead, NULL); 
	if(result == false)
	{
		Logg("Error saving", file);
		MessageBox(NULL, file, "Error writing", MB_OK);
		return;
	}
	else
	{
		Logg("Save Highscore Done", antRead);
	}
	CloseHandle(fil);
}