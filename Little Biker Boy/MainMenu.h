// MainMenu.h: interface for the CMainMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINMENU_H__E634CD27_3E02_456C_BABF_B4EF5FA4AE6D__INCLUDED_)
#define AFX_MAINMENU_H__E634CD27_3E02_456C_BABF_B4EF5FA4AE6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MenuButton.h"
#include "Sprite.h"
#include "object.h"
#include "thegame.h"

struct HighScoreObj {
	int points;
	char name[HIGHSCORENAMEMAX];
};

enum MenuStatus { MAINMENU = 0, LOADGAMEMENU, SAVEGAMEMENU, OPTIONSMENU, CREDITSMENU, NEWGAMEMENU};

#define MENU_TIMER	1993

class CMainMenu 
{
public:
	CMainMenu();
	virtual ~CMainMenu();

	void		setMenuStatus(MenuStatus init, HWND hWnd, bool move = true);
	MenuStatus	getMenuStatus();
	CMenuButton* getButton(int init);

	GameMode	getMode();

	void		draw(HWND hWnd, bool forced = true);
	void		draw(HDC hdc, bool forced = true);
	void		addButton(CMenuButton* init);
	int			test(int initX, int initY, HWND hWnd, bool keyPressed);

	void		reset(HWND hWnd);

	int			LoadBack(LPSTR szFileName);


	void		addScore(int points, char* name);


// Show and close (Used to start the moving)
	void		show(HWND hWnd);
	void		close(HWND hWnd);
// Timer proc
	VOID		CALLBACK MainMenuTimerProc(HWND hwnd,UINT message,UINT idTimer, DWORD dwTime);
private:
	MenuStatus menuStatus;
	CSprite spriteBack;
	CMenuButton* itsMenuButtons[START+1];
	CMenuButton* activeButton;
	int nMenuButton;
	bool movingButton, bClose;
	POINTS subMenu, move; 
	RECT oldRc;
	CStaticText daysText, moneyText, jobsText, fitnessText;

	CStaticText highScoreHead;
	CStaticText highScore[MAXHIGHSCORE];
	HighScoreObj highScoreObj[MAXHIGHSCORE];



	void moveButton(CMenuButton* init, HWND hWnd);
	void setButton(CMenuButton* init);
	int setTexts(char* fileName);
	void UpdateHighscoreList();
};

int		InitMainMenu(CMainMenu &mainMenu, HWND hWnd);
VOID	CALLBACK MainMenuClassTimerProc(HWND hwnd,UINT message,UINT idTimer, DWORD dwTime);
void	LoadHighscore(char* file, HighScoreObj *highScoreObj);
void	SaveHighscore(char* file, HighScoreObj *highScoreObj);

#endif // !defined(AFX_MAINMENU_H__E634CD27_3E02_456C_BABF_B4EF5FA4AE6D__INCLUDED_)
