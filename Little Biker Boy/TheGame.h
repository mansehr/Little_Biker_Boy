// TheGame.h: interface for the TheGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THEGAME_H__ACD877D1_1375_4CAF_B0E5_7AA174B8308B__INCLUDED_)
#define AFX_THEGAME_H__ACD877D1_1375_4CAF_B0E5_7AA174B8308B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "list.h"
#include "Bitmap.h"
#include "price.h"
#include "String.h"
#include "Work.h"
#include "stdAfx.h"

struct Player
{
	double	awake;
	int		days;
	int		timesSleeped;
	int		money;
	double	fitness;
	int		prevMoney[MAX_PREVMONEY];
	int		prevFitness[MAX_PREVFITNESS];
	int		takenWork;
	GameMode	itsMode;
	int			maxDay;
};

struct TheGameSave
{
	GameStatus	itsStatus;
	GameStatus	oldStatus;
	
	bool drawLoad;
	EROOM activeRoom;
	Player	itsPlayer;

	int activeWorkHandle;
};

class TheGame  
{
public:
	TheGame();
	virtual ~TheGame();

	GameStatus	getStatus();
	GameStatus	getOldStatus();
	GameMode	getGameMode();
	void		setGameMode(GameMode init);
	bool		isStatusChanged(bool reset);
	int			getDays();
	int			getMaxDays();
	int			getMoney();
	CWorkHandler	getActiveWorkHandle();
	CWorkHandler	getTakenWorkHandle();
	void		setActiveWorkHandle(int init);
	void		setActiveWork(int init);
	EROOM		getActiveRoom();
	CWork*		getActiveWorkpt();
	CWork		getActiveWork();
	int			getActiveWorkNumber();
	int			getWorkLeft();
	int			getTimesSleeped();
	int*		getPrevMoney();
	int*		getPrevFitness();
	double		getAwake();
	double		getFitness();
	void		setStatus(GameStatus initStatus);
	void		switchStatus();
	int			LoadLists();
	void		BuyStock(HWND hWnd, int quantity);
	void		BuyDrug(HWND hWnd, int quantity);
	void		BuyTraining(HWND hWnd, int quantity);
	void		SellStock(HWND hWnd, int quantity);
	
	int			getWorkAction(CWork initWork);
	void		drawLoadPic(HWND hWnd, bool forced = false);

	int			SaveToFile(char* fileName);
	int			LoadFromFile(char* fileName);

	int			LoadWork(char* file);

	int			sleep(int initDays);
	void		reset();

	CList*		getList(int init);

private:
	HBITMAP bmpLoad;
	HBITMAP bmpLoadMask;

	GameStatus	itsStatus;
	GameStatus	oldStatus;
	
	bool drawLoad;
	EROOM activeRoom;
	Player	itsPlayer;

	//int antWork, 
	int activeWorkHandle;//, oldWork;
	CWorkHandler	itsWork[MAX_WORKHANDLES];
	CWorkHandler	takenWork;

	CList	list[lWORKGOT+1];
};

int CountPoints(TheGame &init);

#endif // !defined(AFX_THEGAME_H__ACD877D1_1375_4CAF_B0E5_7AA174B8308B__INCLUDED_)
