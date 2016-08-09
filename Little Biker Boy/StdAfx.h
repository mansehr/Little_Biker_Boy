// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers


// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>
//#include <fstream>

// Directx Includes
//#include <dmusici.h>
//#include <dsound.h> 
//#include <dshow.h> 


// Local Header Files
#include "Resource.h"
#include "Object.h"
#include "StatusObject.h"
#include "Clock.h"
#include "InfoSquare.h"
#include "Diagram.h"
#include "filhant.h"

//#include "Square.h"

#include "logFile.h"


//Defines debuglevels  DEBUGHIG, DEBUGMED or DEBUGLOW
//#define DEBUGMED

#ifdef DEBUGHIG
#define DEBUGMED
#endif

#ifdef DEBUGMED
#define DEBUGLOW
#endif

#define INIT_MONEY 10000
#define INIT_MAXDAYS 1
#define INIT_FITNESS 200

#define INIT_EASY_MONEY 5000
#define INIT_NORMAL_MONEY 1000
#define INIT_HARD_MONEY 500
#define INIT_EASY_MAXDAYS 1825
#define INIT_NORMAL_MAXDAYS 1095
#define INIT_HARD_MAXDAYS 730
#define INIT_EASY_FITNESS 60
#define INIT_NORMAL_FITNESS 40
#define INIT_HARD_FITNESS 20


#define SafeRelease(pInterface) if(pInterface != NULL) {pInterface->Release(); pInterface=NULL;}
#define SafeDelete(pObject) if(pObject != NULL) {delete pObject; pObject=NULL;}

#define MB(x) MessageBox(NULL, x, "Hm", MB_OK | MB_ICONEXCLAMATION);
#define MB_HWND(x) MessageBox(hWnd, x, "Hm", MB_OK | MB_ICONEXCLAMATION);
#define MB_INT(x)	char buffer[32]; \
					wsprintf(buffer, "Int: %d", x); \
					MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);
#define MB_INT_HWND(x)	char buffer[32]; \
					wsprintf(buffer, "Int: %d", x); \
					MessageBox(hWnd, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

#define SCREEN_WIDTH	1024
#define SCREEN_HEIGHT	768
#define SCREEN_BITS		32

#define RAD(x) ((x)*0.01745329)

#define SAVEFILE1 "save/save1.sav"
#define SAVEFILE2 "save/save2.sav"
#define STOCKFILE "data/stock.con"
#define DRUGFILE "data/drug1.con"
#define TRAININGFILE "data/drug2.con"
#define CORDINATESFILE "data/cordinates.txt"
#define LOADPICFILE "data/loading.bmp"
#define HIGHSCOREFILE "save/highscore.sav"

#define MAX_AWAKE 100
#define ADD_AWAKE 5

#define MAX_BUFFER 100


// Define global Variables
#define LISTOBJECT_HEIGHT 18
#define MAX_LISTOBJECTS 64
#define MAX_PREVPRICE 20
#define MAX_PREVMONEY 100
#define MAX_PREVFITNESS 50
#define MAX_WORKHANDLES 6

#define MAX_TRAININGTOSELL 10
#define MAX_STOCKTOSELL 100

#define MAXHIGHSCORE 10
#define HIGHSCORENAMEMAX 5

//GameMode
enum		GameMode {		EASY_MODE = 0,
							NORMAL_MODE,
							HARD_MODE
};

// Game status
enum		GameStatus {	INIT = 0, 
							INTRO1,
							INTRO2, 
							STARTMENU, 
							RUNING, 
								BEDROOM,
								TOWN, 
								OFFICE, 
								SHOP,
								WORKOUT,
							END_GAME,
							EXIT
};
// Menu Buttons
enum RADIOBUTTON_ID {
					SLOT1 = 0, 
					SLOT2,
					EASY,
					MEDIUM,
					HARD
};

enum BUTTON_ID {	NEWGAME = HARD + 1, 
					LOADGAME,
					SAVEGAME, 
					OPTIONS, 
					CREDITS, 
					EXITGAME, 
					LOAD,
					SAVE,
					BACK,
					START 
};


// Active Sprites(Game buttons)
enum EAS { 
	BED = 0, 
	PAPER, 
	BOX, 
	DOOR, 
	CLOSE,
	BIGCLOSE,
	LARROW, // Left Arrow
	RARROW,	// Right Arrow
	BIGLARROW,
	BIGRARROW,
	BIGACCEPT,
	ACCEPT,
	CONFIRM,
	UARROW,	// Up Arrow
	DARROW,	// Down Arrow
	SLEEP,	// Sleep button
	HOUSEWORKOUT, 
	HOUSEHOME, 
	HOUSESHOP, 
	HOUSEOFFICE,
	WORKOUTDOOR,
	WORKOUTPAPER,
	WORKOUTEXIT,
	OFFICEEXIT,
	OFFICEPAPER1,
	OFFICEPAPER2,
	OFFICEPAPER3,
	OFFICEPAPER4,
	OFFICEPAPER5,
	OFFICEPAPER6,
	SHOPMAN, 
	SHOPEXIT
};

enum RADIOS {
	BUYONE = 0,
	BUYTEN,
	BUYALL
};

// Rooms
enum EROOM { 
	eMENU = 0,
	eBEDROOM,
	eTOWN,
	eSHOP,
	eWORKOUT,
	eOFFICE,
	eENDGAME
};

// Squares
enum SQUARE { 
	sSTATUS = 0,
	sSLEEP,
	sBUYPART,
	sGETWORK,
	sBUYTRAINING,
	sBUYDRUG
};

// Lists
enum LISTS { 
	lSTOCKGOT = 0,
	lSTOCK,
	lDRUG,
	lTRAINING,
	lWORKGOT
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
