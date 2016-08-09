 /*			File: WinMain.cpp

				Contents: The winMin function and winProc for 
				the game The Little Biker Boy
				
				Editor: SiTi
				
				Date: 23-06-03
*/

//		INCLUDES		////////////////////////////////////////////////
#include "stdafx.h"
#include "TheGame.h"
#include "List.h"
#include "Sprite.h"
#include "Room.h"
#include "Square.h"
#include "MainMenu.h"
#include "MenuButton.h"
#include "filhant.h"
#include "sound.h"
#include "pile.h"

//		GLOBALS		////////////////////////////////////////////////
HWND		main_Window_Handle = NULL;
WNDCLASS	main_Window_Class;
TCHAR		szWindowClass[8] = "LBB_Win";
TheGame		theGame;
char		mediaBuffer[200];


//	MAINMENU GLOBALS	///////////////////////////////////////
CMainMenu mainMenu;
MenuStatus	menuStatus;


	//	RUNING GAME  GLOBALS	///////////////////////////////////////
bool initDone = false;			// So the bitmaps wont be loaded twice

const int nAs = SHOPEXIT+1;		// The last ActiveSprite in the enumeration
CActiveSprite as[nAs];			// A vector of activeSprite

const int nRadio = BUYALL+1;
CRadioButton rb[nRadio];
CRadioHolder buyNumberRadios;

const int nRoom = eENDGAME+1;
CRoom room[nRoom];

CInfoSquare theInfoSqr;
CClock clockAnim;
CDiagram diagShop;
CDiagram diagWorkout;
CDiagram moneyDiagram;
CDiagram fitnessDiagram;
CStaticText playerStatusText;
CStaticText statusMoneyText;
CStaticText statusDays;
CStaticText statusClick;
CStaticText workGotText;
CStaticText workGotAntText;
CStaticText workLeftAntText;
CStaticText timesSleep;
CStaticText drugText;
CStaticText sleepDays;
CStaticText days;
CStaticText moneyText;
CStaticText awakeText;
CStaticText fitnessText;
CStaticText getWorkText[3];

String scoreName;
CStaticText scoreText;
CStaticText enterNameText;

CPile fitnessPile;
CPile fitnessCostPile;
//CPile sleepPile;
CPile awakePile;

int nSleep;
const int nSquare = sBUYDRUG+1;
CSquare square[nSquare];

CSound* m_pSound;
CSound* klickSound;

// DX GLOBALS		////////////////////////////////////////////////
//IDirectMusicPerformance8* m_pDirectAudioPerformance;
//IDirectMusicLoader8* m_pDirectAudioLoader; 

//bool	initSound(HWND hWnd);
//void	UninitializeSound();


//		FUNCTIONS	////////////////////////////////////////////////
LRESULT		CALLBACK WindowProc( HWND hWnd, UINT msg, 
							 	   WPARAM wParam, LPARAM lParam);
LRESULT		MainMenuProc( HWND hWnd, UINT msg, 
 						  WPARAM wParam, LPARAM lParam);
int WINAPI	WinMain( HINSTANCE hinstance, HINSTANCE hprevinstance,
						LPSTR lpcmdline,	int ncmdshow);
int		GameInit(HINSTANCE initInstance);		
void	ButtonAction(HWND hWnd);
void	DrawMenu(HWND hWnd, bool forced);
void	TestButtons(HWND hWnd, int x, int y, bool buttonDown);
		// Rungame Functions
int		initRunGame(HWND hWnd);




//		WINMAIN		///////////////////////////////////////////////	
int WINAPI WinMain( HINSTANCE hinstance, HINSTANCE hprevinstance,
					LPSTR lpcmdline,	int ncmdshow)
{
	startLogg();
//	CoInitialize(NULL); 
	theGame.setStatus(INIT);
	if( GameInit(hinstance) == 0 ) 					// Init game
	{
		DestroyWindow(main_Window_Handle);
		ChangeDisplaySettings(NULL, 0);		// switch back to the desktop
		PostQuitMessage(0);
	}

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);				// Send msg to WindowProc
	}

//	UninitializeSound();
//	CoUninitialize();
	UnregisterClass( szWindowClass, main_Window_Class.hInstance );
	endLogg();
	return(msg.wParam);
}

//		GAMEINIT		///////////////////////////////////////////////	
// GameInit function fills the windclass with data and creates the window with 
// the createwindow function
int GameInit(HINSTANCE initInstance)
{
	Logg("<b>Init game</b>");
	DEVMODE dmScreenSettings;                       // Device Mode
	memset(&dmScreenSettings,0,sizeof(dmScreenSettings)); // Make sure memory's cleared
	dmScreenSettings.dmSize = sizeof(dmScreenSettings);      // Size of the devmode structure
	dmScreenSettings.dmPelsWidth  = SCREEN_WIDTH;          // Selected screen width
	dmScreenSettings.dmPelsHeight = SCREEN_HEIGHT;            // Selected screen height
	dmScreenSettings.dmBitsPerPel = SCREEN_BITS;              // Selected bits per pixel
	dmScreenSettings.dmFields  = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	// Try to set the selected mode and get results. NOTE: CDS_FULLSCREEN gets rid of start bar.
	if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		Logg("Setting Screen mode Error");
		MessageBox(NULL, "Error setting fullscreen mode", "Display error", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}
	else
		Logg("Screen Set Done");

//Define and fill the windows class stukture
	WNDCLASS winClass;
	winClass.style 				= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc 		= WindowProc;
	winClass.cbClsExtra			= 0;
	winClass.cbWndExtra			= 0;
	winClass.hInstance			= initInstance;
	winClass.hIcon				= LoadIcon(initInstance, (LPCTSTR)IDI_ICON);
	winClass.hCursor			= LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground		= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName		= NULL;
	winClass.lpszClassName		= szWindowClass;

	if( RegisterClass(&winClass) ==0 )
	{
		Logg("Register Class Error");
		MessageBox(NULL, "Where not able to register the class", "ERROR MESSAGE", MB_OK);
 		return 0;
	}
	else
		Logg("Register Class Done");

	HWND hWnd = CreateWindow( szWindowClass,  "The Little Biker Boy", WS_POPUP , 
						 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL, initInstance, NULL);
	if( hWnd == 0 )
	{
		Logg("Create Window Error");
		MessageBox(NULL, "Where not able to create the window", "ERROR MESSAGE", MB_OK);
		return 0;
	}
	else
		Logg("Create Window Done");

	main_Window_Handle	= hWnd;
	main_Window_Class	= winClass; 

	Logg("<b>Init game <u>Done</u></b>");
	return 1;			// No errors
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HDC 			hdc;
	static HDC			hdcBuffer;
	static HBITMAP		hbmBuffer;
	PAINTSTRUCT 	ps;
	POINTS 			mouse = MAKEPOINTS(lParam);
	bool 			lButtonDown;
	static int		antPaint;
	if(wParam & MK_LBUTTON)
		lButtonDown = true;
	else
		lButtonDown = false;

	switch (message)
	{
	case WM_CREATE:
		antPaint = 0;

		Logg("WM_CREATE");

		theGame.setStatus(INTRO1);
		theGame.drawLoadPic(hWnd, true);

#ifdef DEBUGMED
		SendMessage(hWnd, MM_MCINOTIFY, NULL, NULL);
#else
		wsprintf(mediaBuffer,"open intro.avi type mpegvideo alias intro");
		mciSendString(mediaBuffer,  0, 0, 0); 
		
		wsprintf(mediaBuffer,"play intro fullscreen notify");
		mciSendString(mediaBuffer, 0, 0, hWnd);

		Logg("<b>Play Intro</b>");
#endif
	
//		initSound(hWnd);
/*
		m_pSound = new CSound();
		m_pSound->InitialiseForMP3();
		m_pSound->LoadSound("dig.mp3");
		m_pSound->Play();*/
	break;
	case MM_MCINOTIFY:
#ifndef DEBUGMED
		if(theGame.getStatus() == INTRO1) 
		{
			wsprintf(mediaBuffer,"Close intro");
			mciSendString(mediaBuffer,0,0,0);
		} else {
			wsprintf(mediaBuffer,"Close intro2");
			mciSendString(mediaBuffer,0,0,0);
		}
		Logg("<b>Intro <u>End</u></b>");

		if(theGame.getStatus() == INTRO1)
		{
			mciSendString("open intro1.avi type mpegvideo alias intro2",  0, 0, 0); 

			mciSendString("play intro2 fullscreen notify", 0, 0, hWnd);

			theGame.setStatus(INTRO2);
			Logg("<b>Play Intro</b>");
		}
		else
#endif
		{

		
			if( InitMainMenu(mainMenu, hWnd) == 0 )						// Load menu bitmaps
				DestroyWindow(hWnd);

			theGame.setStatus(STARTMENU);							// Run main menu
#ifdef DEBUGMED
			//initRunGame(main_Window_Handle);
			//theGame.setStatus(BEDROOM);
			//theInfoSqr.startTimer(hWnd);
#endif

			//square[sSTATUS].setStatus(ACTIVE);
			ShowWindow(hWnd, SW_SHOWMAXIMIZED);
			UpdateWindow(hWnd);
			//InvalidateRect(hWnd, NULL, TRUE);
		}
		break;

	case WM_LBUTTONDOWN:
#ifdef DEBUGHIG
		{
			char szBuffer[32];
			wsprintf(szBuffer, "MouseX: %d      MousaeY: %d", mouse.x, mouse.y);
			Logg("WM_LBUTTONDOWN", szBuffer);
		}
#endif
	case WM_MOUSEMOVE:
		theInfoSqr.setPos(hWnd, mouse);
		TestButtons(hWnd, mouse.x, mouse.y, lButtonDown);
		break;
	case WM_LBUTTONUP:
		TestButtons(hWnd, mouse.x, mouse.y, lButtonDown);
		ButtonAction(hWnd);
		break;
	case WM_PAINT:
	{	
		if(theGame.getStatus() > INTRO1)
		{
			hdc = BeginPaint(hWnd, &ps);

#ifdef DEBUGHIG
			antPaint++;
			char buffer[100];
			wsprintf(buffer, "Repainting: \tLeft: %i, Top: %i, Right: %i, Bottom: %i          \t\t      Paint: %i", ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right, ps.rcPaint.bottom, antPaint);
			Logg(buffer);
#endif
			theGame.drawLoadPic(hWnd);			// Draw load picture if room is changed
											
			hdcBuffer = CreateCompatibleDC(hdc);
			if(hdcBuffer == NULL)
			{
				EndPaint(hWnd, &ps);
				Logg("<b>CreateCompatibleDC() in PAINT <u>ERROR</u><b>");
				MB("CreateCompatibleDC() In Paint ERROR");
				return 0;
			}

			hbmBuffer = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
			if(hbmBuffer == NULL)
			{
				DeleteDC(hdcBuffer);
				EndPaint(hWnd, &ps);
				Logg("<b>CreateCompatibleBitmap() in PAINT<u>ERROR</u><b>");
				MB("CreateCompatibleBitmap() ERROR");
				return 0;
			}

			HBITMAP hbmOldBuffer = HBITMAP (SelectObject(hdcBuffer, hbmBuffer));
			if(theGame.getStatus() == STARTMENU)
				mainMenu.draw(hdcBuffer);

			if(theGame.getStatus() > RUNING)
			{
				room[theGame.getActiveRoom()].draw(hdcBuffer, true);
			}
	

			theInfoSqr.draw(hdcBuffer);

			BitBlt(hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right, ps.rcPaint.bottom, hdcBuffer, ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);
			EndPaint(hWnd, &ps);

			SelectObject(hdcBuffer, hbmOldBuffer);
			DeleteDC(hdcBuffer);
			DeleteObject(hbmBuffer);
		}
	}
		break;
	case WM_KEYDOWN:
	{

		int virtual_code = (int)wParam;
		int key_state = (int)lParam;

		switch(virtual_code)
		{
			case VK_ESCAPE:
			{
				if(	theGame.getStatus() > RUNING && 
					theGame.getStatus() < END_GAME )
				{
					if( theGame.getStatus() == STARTMENU && 
						theGame.getOldStatus() > STARTMENU)
					{
						theGame.switchStatus();		// Set old status to its new status
						mainMenu.reset(hWnd);		// Reset button postitions
					}
					else
					{
						theGame.setStatus(STARTMENU);
					}

					if(theGame.isStatusChanged(false))
					{
						//MB_HWND("Updates");
						InvalidateRect(hWnd, NULL, TRUE);
					}
				}
			} 
			break;
			default: break;
		}
	}
		break;
	case WM_CHAR:
		if(theGame.getStatus() == END_GAME)
		{
			if((int)wParam >= 20 && scoreName.getLen() < HIGHSCORENAMEMAX-1)
			{
				scoreName += (char)wParam;
				scoreText.setText(scoreName.getString());
				scoreText.draw(hWnd);
			}
			else if((int)wParam == 8)
			{
				scoreName.deleteLastChar();
				scoreText.setText(scoreName.getString());
				scoreText.draw(hWnd);
			}
#ifdef DEBUGHIG
			else
			{
				char temp[2];
				temp[0] = (char)wParam;
				temp[1] = '\0';
				char buffer[MAX_BUFFER];
				wsprintf(buffer, "wParam int: %i \nwParam char: %s", (int)wParam, temp);
				MessageBox(hWnd, buffer, "Cool", MB_OK);
			}
#endif
		}
		break;
	case WM_DESTROY: 
		ChangeDisplaySettings(NULL, 0);		// switch back to the desktop
		PostQuitMessage(0);
		Logg("<b>Destroy Window Done</b>");
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


////////// Rungame Functions ///////////////////////////////////////////////////////

void TestButtons(HWND hWnd, int x, int y, bool buttonDown)
{
	if(theGame.getStatus() == STARTMENU)
		mainMenu.test(x, y, hWnd, buttonDown);

	if(theGame.getStatus() > RUNING)
	{
		if(theGame.getStatus() == BEDROOM)
			if( square[sSTATUS].getStatus() == NOT_PRESSABLE && 
				square[sSLEEP].getStatus() == NOT_PRESSABLE )
				room[eBEDROOM].test(x, y, hWnd, theInfoSqr, buttonDown);
			else if(square[sSTATUS].getStatus() != NOT_PRESSABLE)
				square[sSTATUS].test(x, y, hWnd, theInfoSqr, buttonDown);
			else
				square[sSLEEP].test(x, y, hWnd, theInfoSqr, buttonDown);

		if(theGame.getStatus() == TOWN)
			if( square[sBUYPART].getStatus() == NOT_PRESSABLE)
				room[eTOWN].test(x, y, hWnd, theInfoSqr, buttonDown);
			else
				square[sBUYPART].test(x,y, hWnd, theInfoSqr, buttonDown);

		if(theGame.getStatus() == SHOP)
			if( square[sBUYPART].getStatus() == NOT_PRESSABLE)
				room[eSHOP].test(x, y, hWnd, theInfoSqr, buttonDown);
			else
				square[sBUYPART].test(x,y, hWnd, theInfoSqr, buttonDown);

		if(theGame.getStatus() == WORKOUT)
		{
			if( square[sBUYDRUG].getStatus() == NOT_PRESSABLE && 
				square[sBUYTRAINING].getStatus() == NOT_PRESSABLE)
				room[eWORKOUT].test(x, y, hWnd, theInfoSqr, buttonDown);
			else if(square[sBUYDRUG].getStatus() != NOT_PRESSABLE)
				square[sBUYDRUG].test(x,y, hWnd, theInfoSqr, buttonDown);
			else
				square[sBUYTRAINING].test(x,y, hWnd, theInfoSqr, buttonDown);
		}
		if(theGame.getStatus() == OFFICE)
		{
			if( square[sGETWORK].getStatus() == NOT_PRESSABLE)
				room[eOFFICE].test(x, y, hWnd, theInfoSqr, buttonDown);
			else
				square[sGETWORK].test(x,y, hWnd, theInfoSqr, buttonDown);
		}
		if(theGame.getStatus() == END_GAME)
		{
			room[eENDGAME].test(x, y, hWnd, theInfoSqr, buttonDown);
		}
	}
}

void ButtonAction(HWND hWnd)
{
	if(theGame.getStatus() == STARTMENU)
	{
		if(mainMenu.getButton(START)->isPressed())
		{	
			mainMenu.reset(hWnd);
			theGame.setGameMode(mainMenu.getMode());
			theGame.setStatus(BEDROOM);
			if(initRunGame(hWnd) == 0)
				DestroyWindow(hWnd);

			InvalidateRect(hWnd, NULL, TRUE); 
			return;
		}
		if(mainMenu.getButton(NEWGAME)->isPressed())
			mainMenu.setMenuStatus(NEWGAMEMENU, hWnd);

		if(mainMenu.getButton(LOADGAME)->isPressed())
			mainMenu.setMenuStatus(LOADGAMEMENU, hWnd);

		if(mainMenu.getButton(SAVEGAME)->isPressed())
			mainMenu.setMenuStatus(SAVEGAMEMENU, hWnd);

		if(mainMenu.getButton(OPTIONS)->isPressed())
			mainMenu.setMenuStatus(OPTIONSMENU, hWnd);

		if(mainMenu.getButton(CREDITS)->isPressed())
			mainMenu.setMenuStatus(CREDITSMENU, hWnd);	

		if(mainMenu.getButton(EXITGAME)->isPressed())
			DestroyWindow(hWnd);

		if(mainMenu.getButton(BACK)->isPressed())
			mainMenu.close(hWnd);

		if(mainMenu.getButton(LOAD)->isPressed())
		{
			initRunGame(hWnd);
			if(mainMenu.getButton(SLOT1)->getStatus() == ACTIVE)
				theGame.LoadFromFile(SAVEFILE1);
			else
				theGame.LoadFromFile(SAVEFILE2);

			theGame.setStatus(theGame.getOldStatus());
			mainMenu.reset(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		if(mainMenu.getButton(SAVE)->isPressed())
		{
			if(mainMenu.getButton(SLOT1)->getStatus() == ACTIVE)
				theGame.SaveToFile(SAVEFILE1);
			else
				theGame.SaveToFile(SAVEFILE2);

			theGame.setStatus(theGame.getOldStatus());
			mainMenu.reset(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	if(theGame.getStatus() > RUNING)
	{
		if( theGame.getStatus() == BEDROOM)
		{
			if(as[DOOR].isPressed())
			{	
				theGame.setStatus(TOWN); 
				InvalidateRect(hWnd, NULL, TRUE);	
			}
			if(as[BOX].isPressed())
			{
				square[sSTATUS].showSquare(hWnd, as[BOX].getRect());

				workLeftAntText.setText("Work left", theGame.getWorkLeft());
				workGotAntText.setText("You have taken", theGame.getTakenWorkHandle().getWorkNumber());

				statusClick.setText("Times Sleeped", theGame.getTimesSleeped());

				char buffer[MAX_BUFFER];
				wsprintf(buffer, "Played Days: %i / %i", theGame.getDays(), theGame.getMaxDays());
				statusDays.setText(buffer);

				timesSleep.setText(theGame.getTimesSleeped());

				moneyText.setText("Your money", theGame.getMoney());
				moneyText.setName("statusMoneyText");
				LoadPosition(&moneyText, CORDINATESFILE);

				moneyDiagram.setDiagramDots(theGame.getPrevMoney(), MAX_PREVMONEY);
				fitnessDiagram.setDiagramDots(theGame.getPrevFitness(), MAX_PREVFITNESS);

				fitnessPile.setValue(int(theGame.getFitness()));
				fitnessPile.setCompareValue(0);
				fitnessPile.setChange(0);
				fitnessPile.setName("statusFitnessPile");
				LoadPosition(&fitnessPile, CORDINATESFILE);

				awakePile.setValue(int(theGame.getAwake()));
				awakePile.setCompareValue(0);
				awakePile.setChange(0);
				awakePile.setName("statusAwakePile");
				LoadPosition(&awakePile, CORDINATESFILE);

				fitnessText.setName("statusFitnessText");
				LoadPosition(&fitnessText, CORDINATESFILE);

				awakeText.setName("statusAwakeText");
				LoadPosition(&awakeText, CORDINATESFILE);

			/*	fitnessCostPile.setName("statusFitnessCostPile");
				LoadPosition(&fitnessCostPile, CORDINATESFILE);*/
			}

			if(as[BED].isPressed())
			{
				square[sSLEEP].showSquare(hWnd, as[BED].getRect());
				fitnessPile.setValue(int(theGame.getFitness()));
				fitnessPile.setCompareValue(0);
				fitnessPile.setChange(0);

				awakePile.setValue(int(theGame.getAwake()));
				awakePile.setCompareValue(0);
				awakePile.setChange(nSleep * ADD_AWAKE);
				awakePile.setCompLarger(true);

				days.setText(theGame.getDays());
				InvalidateRect(hWnd, days.getRect(), FALSE);
			}

			if(as[PAPER].isPressed())
			{	DestroyWindow(hWnd);	}

			if( square[sSTATUS].getStatus() == ACTIVE)
			{
				if(as[CLOSE].isPressed())
				{
					square[sSTATUS].closeSquare(hWnd);
					awakePile.setCompLarger(false);
					awakePile.setCompareValue(0);

					moneyText.setName("moneyText");
					LoadPosition(&moneyText, CORDINATESFILE);

					fitnessPile.setName("fitnessPile");
					LoadPosition(&fitnessPile, CORDINATESFILE);

					awakePile.setName("awakePile");
					LoadPosition(&awakePile, CORDINATESFILE);

					fitnessText.setName("fitnessText");
					LoadPosition(&fitnessText, CORDINATESFILE);

					awakeText.setName("awakeText");
					LoadPosition(&awakeText, CORDINATESFILE);
				}
			}
			if( square[sSLEEP].getStatus() == ACTIVE)
			{
				if(as[CLOSE].isPressed())
				{
					square[sSLEEP].closeSquare(hWnd);
					awakePile.setCompLarger(false);
					awakePile.setCompareValue(0);
				}

				if(as[UARROW].isPressed())
					if(nSleep < 10)
					{
						nSleep++;
						sleepDays.setText(nSleep);
						InvalidateRect(hWnd, sleepDays.getRect(), FALSE);
						awakePile.setChange(nSleep * ADD_AWAKE);
						InvalidateRect(hWnd, awakePile.getRect(), FALSE);
					}

				if(as[DARROW].isPressed())
					if(nSleep > 1)
					{
						nSleep--;
						sleepDays.setText(nSleep);
						InvalidateRect(hWnd, sleepDays.getRect(), FALSE);
						awakePile.setChange(nSleep * ADD_AWAKE);
						InvalidateRect(hWnd, awakePile.getRect(), FALSE);
					}

				if(as[SLEEP].isPressed())
				{
					if(theGame.sleep(nSleep))		// Were we able to sleep?
					{
						clockAnim.start(hWnd, nSleep);

						awakePile.setValue(int(theGame.getAwake()));
						awakePile.draw(hWnd);

						days.setText(theGame.getDays());
						InvalidateRect(hWnd, days.getRect(), FALSE);
					}
					else
						InvalidateRect(hWnd, NULL, TRUE);		// Game over set status is allready done. just repaint
				}
			}
		}
		else if(theGame.getStatus() == TOWN)
		{
			if(as[HOUSEWORKOUT].isPressed())
			{	
				theGame.setStatus(WORKOUT); 
				InvalidateRect(hWnd, NULL, TRUE);	
			}
			if(as[HOUSEHOME].isPressed())
			{	
				theGame.setStatus(BEDROOM); 
				InvalidateRect(hWnd, NULL, TRUE);	
			}
			if(as[HOUSESHOP].isPressed())
			{	
				theGame.setStatus(SHOP); 
				InvalidateRect(hWnd, NULL, TRUE);	
			}
			if(as[HOUSEOFFICE].isPressed())
			{	
				theGame.setStatus(OFFICE); 
				InvalidateRect(hWnd, NULL, TRUE);	
			}
		}
		else if(theGame.getStatus() == SHOP)
		{
			
			if(as[SHOPMAN].isPressed())
			{
				diagShop.setDiagramDots(theGame.getList(lSTOCK)->getActiveObj()->getPrevPrice(), MAX_PREVPRICE);
				square[sBUYPART].showSquare(hWnd, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
			}

			if(as[SHOPEXIT].isPressed())
			{
				theGame.setStatus(TOWN); 
				InvalidateRect(hWnd, NULL, TRUE);
			}
			if( square[sBUYPART].getStatus() == ACTIVE)
			{
				if(as[CLOSE].isPressed())
					square[sBUYPART].closeSquare(hWnd);

				if(as[RARROW].isPressed(true, MOUSE_OVER))
				{
					int quant = 1;
					if(rb[BUYONE].isPressed(false))
						quant = 1;
					else if(rb[BUYTEN].isPressed(false))
						quant = 10;
					else if(rb[BUYALL].isPressed(false))
						quant = 1000;

					theGame.BuyStock(hWnd, quant);
				}

				if(as[LARROW].isPressed(true, MOUSE_OVER))
				{
					int quant = 1;
					if(rb[BUYONE].isPressed(false))
						quant = 1;
					else if(rb[BUYTEN].isPressed(false))
						quant = 10;
					else if(rb[BUYALL].isPressed(false))
						quant = 1000;

					theGame.SellStock(hWnd, quant);
				}

				if(theGame.getList(lSTOCK)->isStatusChanged())
				{
					diagShop.setDiagramDots(theGame.getList(lSTOCK)->getActiveObj()->getPrevPrice(), MAX_PREVPRICE);
					InvalidateRect(hWnd, diagShop.getRect(), FALSE);
				}
					
			
				moneyText.setText("Your money", theGame.getMoney());
				InvalidateRect(hWnd, moneyText.getRect(), FALSE);
			}
		}
		else if(theGame.getStatus() == OFFICE)
		{
			if(as[OFFICEEXIT].isPressed())
			{
				theGame.setStatus(TOWN); 
				InvalidateRect(hWnd, NULL, TRUE);
			}
			for(int i = OFFICEPAPER1; i <= OFFICEPAPER6; i++)
				if(as[i].isPressed())
				{
					theGame.setActiveWorkHandle(i-OFFICEPAPER1);

					//MB_INT(theGame.getActiveWorkHandle().getWorkNumber());
					if(theGame.getActiveWorkHandle().getWorkNumber() > 0)
					{
						UpdateWork(getWorkText, theGame.getActiveWork());
						fitnessCostPile.setValue(int(theGame.getFitness()));
						fitnessCostPile.setCompareValue(theGame.getActiveWork().getFitness());
						if(theGame.getFitness() >= theGame.getActiveWork().getFitness())
							fitnessCostPile.setChange(-theGame.getActiveWork().getCostInFitnes());
						else 
							fitnessCostPile.setChange(0);
					}
					else
					{
						getWorkText[0].setText("Wage",0);
						getWorkText[1].setText("You have now taken all jobbs in this sektion");
						getWorkText[2].setText("End of this mission");
						fitnessCostPile.setChange(0);
						fitnessCostPile.setCompareValue(0);
						fitnessCostPile.setValue(0);
					}
					square[sGETWORK].showSquare(hWnd, as[i].getRect());
				}

			if(square[sGETWORK].getStatus() == ACTIVE)
			{
				if(as[BIGLARROW].isPressed(false, MOUSE_OVER))
				{
					theGame.setActiveWork(theGame.getActiveWorkNumber() - 1);
				}

				if(as[BIGRARROW].isPressed(false, MOUSE_OVER))
				{
					theGame.setActiveWork(theGame.getActiveWorkNumber() + 1);
				}
				if( as[BIGLARROW].isPressed(true, MOUSE_OVER) ||
					as[BIGRARROW].isPressed(true, MOUSE_OVER))
				{

					if(theGame.getActiveWorkHandle().getWorkNumber() > 0)
					{
						UpdateWork(getWorkText, theGame.getActiveWork());

						fitnessCostPile.setCompareValue(theGame.getActiveWork().getFitness());
						if(theGame.getFitness() >= theGame.getActiveWork().getFitness())
							fitnessCostPile.setChange(-theGame.getActiveWork().getCostInFitnes());
						else 
							fitnessCostPile.setChange(0);
					}
					else
					{
						getWorkText[0].setText("Wage",0);
						getWorkText[1].setText("You have now taken all jobbs in this sektion");
						getWorkText[2].setText("End of this mission");
						fitnessCostPile.setChange(0);
						fitnessCostPile.setCompareValue(0);
						fitnessCostPile.setValue(0);
					}
					InvalidateRect(hWnd, NULL, false);
				}

				if(as[BIGCLOSE].isPressed())
					square[sGETWORK].closeSquare(hWnd);

				if(as[BIGACCEPT].isPressed())
				{
					if(theGame.getWorkAction(theGame.getActiveWork()))
					{
						if(theGame.getWorkLeft() == 0)
						{
							theGame.setStatus(END_GAME);
							InvalidateRect(hWnd, NULL, TRUE);
						}
						else
							square[sGETWORK].closeSquare(hWnd);
					}
					else
					{
						MB_HWND("Work Not able to be taken\nTry Another one");
					}
				}
			}
		}

		else if(theGame.getStatus() == WORKOUT)
		{
			if(as[WORKOUTEXIT].isPressed())
			{
				theGame.setStatus(TOWN); 
				InvalidateRect(hWnd, NULL, TRUE);
			}
			if(as[WORKOUTPAPER].isPressed())
			{
				diagWorkout.setDiagramDots(theGame.getList(lDRUG)->getActiveObj()->getPrevPrice(), MAX_PREVPRICE);
				fitnessPile.setChange(theGame.getList(lDRUG)->getActiveObj()->getFitness());
				awakePile.setChange(-(theGame.getList(lDRUG)->getActiveObj()->getCostInSleep()));
				drugText.setText(theGame.getList(lDRUG)->getActiveObj()->getExtraString());

				square[sBUYDRUG].showSquare(hWnd, as[WORKOUTPAPER].getRect());
			}

			if(as[WORKOUTDOOR].isPressed())
			{
				diagWorkout.setDiagramDots(theGame.getList(lTRAINING)->getActiveObj()->getPrevPrice(), MAX_PREVPRICE);
				fitnessPile.setChange(theGame.getList(lTRAINING)->getActiveObj()->getFitness());
				awakePile.setChange(-(theGame.getList(lTRAINING)->getActiveObj()->getCostInSleep()));
				drugText.setText(theGame.getList(lTRAINING)->getActiveObj()->getExtraString());
								
				square[sBUYTRAINING].showSquare(hWnd, as[WORKOUTDOOR].getRect());
			}

			if( square[sBUYDRUG].getStatus() == ACTIVE)
			{
				if(as[CLOSE].isPressed())
				{
					square[sBUYDRUG].closeSquare(hWnd);
				}

				if(as[ACCEPT].isPressed(true, MOUSE_OVER))
				{
					int quant = 1;
					if(rb[BUYONE].isPressed(false))
						quant = 1;
					else if(rb[BUYTEN].isPressed(false))
						quant = 10;
					else if(rb[BUYALL].isPressed(false))
						quant = 1000;

					theGame.BuyDrug(hWnd, quant);

					moneyText.setText("Your money", theGame.getMoney());
					InvalidateRect(hWnd, moneyText.getRect(), FALSE);

					fitnessPile.setValue(int(theGame.getFitness()));
					InvalidateRect(hWnd, fitnessPile.getRect(), FALSE);
				}

				if(theGame.getList(lDRUG)->isStatusChanged())
				{
					diagWorkout.setDiagramDots(theGame.getList(lDRUG)->getActiveObj()->getPrevPrice(), MAX_PREVPRICE);
					InvalidateRect(hWnd, diagWorkout.getRect(), FALSE);

					drugText.setText(theGame.getList(lDRUG)->getActiveObj()->getExtraString());
					InvalidateRect(hWnd, drugText.getRect(), FALSE);

					fitnessPile.setChange(theGame.getList(lDRUG)->getActiveObj()->getFitness());
					InvalidateRect(hWnd, fitnessPile.getRect(), FALSE);
				}
			}
			if( square[sBUYTRAINING].getStatus() == ACTIVE)
			{
				if(as[CLOSE].isPressed())
					square[sBUYTRAINING].closeSquare(hWnd);

				if(as[ACCEPT].isPressed(true, MOUSE_OVER))
				{
					int quant = 1;
					if(rb[BUYONE].isPressed(false))
						quant = 1;
					else if(rb[BUYTEN].isPressed(false))
						quant = 10;
					else if(rb[BUYALL].isPressed(false))
						quant = 1000;

					theGame.BuyTraining(hWnd, quant);

					moneyText.setText("Your money", theGame.getMoney());
					InvalidateRect(hWnd, moneyText.getRect(), FALSE);

					fitnessPile.setValue(int(theGame.getFitness()));
					InvalidateRect(hWnd, fitnessPile.getRect(), FALSE);

					awakePile.setValue(int(theGame.getAwake()));
					InvalidateRect(hWnd, awakePile.getRect(), FALSE);
				}

				if(theGame.getList(lTRAINING)->isStatusChanged())
				{
					diagWorkout.setDiagramDots(theGame.getList(lTRAINING)->getActiveObj()->getPrevPrice(), MAX_PREVPRICE);
					InvalidateRect(hWnd, diagWorkout.getRect(), FALSE);

					fitnessPile.setChange(theGame.getList(lTRAINING)->getActiveObj()->getFitness());
					InvalidateRect(hWnd, fitnessPile.getRect(), FALSE);

					awakePile.setChange(-(theGame.getList(lTRAINING)->getActiveObj()->getCostInSleep()));
					InvalidateRect(hWnd, awakePile.getRect(), FALSE);

					drugText.setText(theGame.getList(lTRAINING)->getActiveObj()->getExtraString());
					InvalidateRect(hWnd, drugText.getRect(), FALSE);
				}
			}
		}
		else if(theGame.getStatus() == END_GAME)
		{
			if(as[CONFIRM].isPressed())
			{
				int points = CountPoints(theGame);
				char* name;
				if(scoreName.getLen() > 0)
					name = scoreName.getString();
				else
					name = "ANYM";

				mainMenu.addScore(points, scoreName.getString());
				scoreName.setToNull();

				theGame.setStatus(STARTMENU);
				mainMenu.setMenuStatus(OPTIONSMENU, hWnd, false);
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
	}
}

int initRunGame(HWND hWnd)
{
	theInfoSqr.setPosition(0, 0, 200, 100);


	Logg("<b>Init Game Variables</b>");
	theGame.drawLoadPic(hWnd, true);

	if(initDone == false)	// Is initiation done before
	{
		theGame.LoadWork("data/work.con");

		Logg("Setting all varible names");

		as[DOOR].setName("door");
		as[PAPER].setName("paper");
		as[BOX].setName("box");
		as[BED].setName("bed");
		as[CLOSE].setName("ButClose");
		as[BIGCLOSE].setName("ButBigClose");
		as[LARROW].setName("ButLeft");
		as[RARROW].setName("ButRight");
		as[BIGLARROW].setName("ButBigLeft");
		as[BIGRARROW].setName("ButBigRight");
		as[BIGACCEPT].setName("ButBigAccept");
		as[ACCEPT].setName("butAccept");
		as[CONFIRM].setName("confirm");
		as[UARROW].setName("ButUp");
		as[DARROW].setName("ButDown");
		as[SLEEP].setName("Sleep");
		as[HOUSEWORKOUT].setName("houseWorkout");
		as[HOUSESHOP].setName("houseShop");
		as[HOUSEOFFICE].setName("houseOffice");
		as[HOUSEHOME].setName("houseHome");
		as[SHOPMAN].setName("shopMan");
		as[SHOPEXIT].setName("shopExit");
		as[OFFICEEXIT].setName("officeExit");
		as[OFFICEPAPER1].setName("officePaper1");
		as[OFFICEPAPER2].setName("officePaper2");
		as[OFFICEPAPER3].setName("officePaper3");
		as[OFFICEPAPER4].setName("officePaper4");
		as[OFFICEPAPER5].setName("officePaper5");
		as[OFFICEPAPER6].setName("officePaper6");
		as[WORKOUTPAPER].setName("workoutPaper");
		as[WORKOUTDOOR].setName("workoutDoor");
		as[WORKOUTEXIT].setName("workoutExit");

		rb[BUYONE].setName("butBuyOne");
		rb[BUYTEN].setName("butBuyTen");
		rb[BUYALL].setName("butBuyAll");

		klickSound = new CSound();
//		klickSound->InitialiseForWavMidi(m_pDirectAudioPerformance, m_pDirectAudioLoader);
		klickSound->LoadSound("dig.wav");


		Logg("Load bitmap and position");
		for(int i = 0; i < nAs; i++)
		{
			LoadPosition(&as[i], CORDINATESFILE);
			LoadInfoText(&as[i], CORDINATESFILE);
			as[i].setMaskColor(RGB(0,0,255));
			//as[i].setSound(klickSound);
			String			normalString,	activeString;
			normalString	= normalString	+"data/"+as[i].getName()+".bmp";		
			activeString	= activeString	+"data/"+as[i].getName()+"1.bmp";

			if( as[i].LoadABitmap(normalString.getString(), TRUE)			== 0 ||
				as[i].LoadActiveBitmap(activeString.getString(), TRUE)	== 0 )
			{
				Logg("Bitmap Load error", as[i].getName());
				MessageBox(NULL, as[i].getName(), "Bitmap Load error", MB_OK);
				return 0;
			}
		}

		for(int i = 0; i < nRadio; i++)
		{
			LoadPosition(&rb[i], CORDINATESFILE);
			rb[i].setMaskColor(RGB(0,0,255));
			rb[i].setSound(klickSound);
			String	normalString,	activeString,	pressedString;
			normalString	= normalString +"data/"+rb[i].getName()+".bmp";		
			activeString	= activeString+"data/"+rb[i].getName()+"1.bmp";
			pressedString	= pressedString+"data/"+rb[i].getName()+"2.bmp";

			if( rb[i].LoadABitmap(normalString.getString(), TRUE)			== 0 ||
				rb[i].LoadActiveBitmap(activeString.getString(), TRUE)	== 0 ||
				rb[i].LoadPressedBitmap(pressedString.getString(), TRUE)			== 0)
			{
				Logg("Bitmap Load error", rb[i].getName());
				MessageBox(NULL, rb[i].getName(), "Bitmap Load error", MB_OK);
				return 0;
			}
		}
		Logg("Load bitmap and position <u>Done</u>");
		
		// Status Square
		clockAnim.setName("clock");
		LoadPosition(&clockAnim, CORDINATESFILE);
		clockAnim.setMiddle(clockAnim.getLeft()+138, clockAnim.getTop()+208);
		clockAnim.LoadBack("data/clock.bmp");

		days.setText(theGame.getDays());
		days.setName("days");
		LoadPosition(&days, CORDINATESFILE);
		days.setBgMode(TRANSPARENT);

		workGotText.setText("Your Got Work Status");
		workGotText.setName("workGotText");
		LoadPosition(&workGotText, CORDINATESFILE);
		workGotText.setFlags(DT_SINGLELINE | DT_TOP | DT_CENTER);
		workGotText.setBgColor(RGB(255,255,255));
		workGotText.setFrame(RGB(0,0,0));
		workGotText.setTextWeight(FW_BOLD);

		playerStatusText.setText("Your Player Status");
		playerStatusText.setName("playerStatusText");
		LoadPosition(&playerStatusText, CORDINATESFILE);
		playerStatusText.setFlags(DT_SINGLELINE | DT_TOP | DT_CENTER);
		playerStatusText.setBgColor(RGB(255,255,255));
		playerStatusText.setFrame(RGB(0,0,0));
		playerStatusText.setTextWeight(FW_BOLD);

		workGotAntText.setText("You have taken", theGame.getTakenWorkHandle().getWorkNumber());
		workGotAntText.setName("workGotAntText");
		LoadPosition(&workGotAntText, CORDINATESFILE);
		workGotAntText.setFlags(DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		workGotAntText.setBgColor(RGB(255,255,255));
		workGotAntText.setFrame(RGB(0,0,0));
		workGotAntText.setLeftMargin(20);
		workGotAntText.setTextWeight(FW_BOLD);

		workLeftAntText.setText("Work left", theGame.getWorkLeft());
		workLeftAntText.setName("workLeftAntText");
		LoadPosition(&workLeftAntText, CORDINATESFILE);
		workLeftAntText.setFlags(DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		workLeftAntText.setBgColor(RGB(255,255,255));
		workLeftAntText.setFrame(RGB(0,0,0));
		workLeftAntText.setLeftMargin(20);
		workLeftAntText.setTextWeight(FW_BOLD);

		awakeText.setText("Sleep:");
		awakeText.setName("awakeText");
		LoadPosition(&awakeText, CORDINATESFILE);
		awakeText.setBgColor(RGB(255,255,255));
		awakeText.setFrame(RGB(0,0,0));
		awakeText.setTextWeight(FW_BOLD);
		awakeText.setFlags(DT_SINGLELINE | DT_CENTER | DT_TOP);

		statusDays.setText("Played Days", theGame.getDays());
		statusDays.setName("statusDays");
		LoadPosition(&statusDays, CORDINATESFILE);
		statusDays.setBgColor(RGB(255,255,255));
		statusDays.setFrame(RGB(0,0,0));
		statusDays.setTextWeight(FW_BOLD);
		statusDays.setFlags(DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		statusClick.setText("Times Sleeped", theGame.getTimesSleeped());
		statusClick.setName("statusClick");
		LoadPosition(&statusClick, CORDINATESFILE);
		statusClick.setBgColor(RGB(255,255,255));
		statusClick.setFrame(RGB(0,0,0));
		statusClick.setTextWeight(FW_BOLD);
		statusClick.setFlags(DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		timesSleep.setName("timesSleep");
		LoadPosition(&timesSleep, CORDINATESFILE);
		timesSleep.setBgColor(RGB(255,255,255));
		timesSleep.setFrame(RGB(0,0,0));
		timesSleep.setTextWeight(FW_BOLD);
		timesSleep.setFlags(DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		timesSleep.setText(theGame.getTimesSleeped());

		fitnessText.setText("Fitness:");
		fitnessText.setName("fitnessText");
		LoadPosition(&fitnessText, CORDINATESFILE);
		fitnessText.setBgMode(TRANSPARENT);
		fitnessText.setTextWeight(FW_BOLD);
		fitnessText.setBgColor(RGB(255,255,255));
		fitnessText.setFrame(RGB(0,0,0));
		fitnessText.setFlags(DT_SINGLELINE | DT_CENTER | DT_TOP);

		fitnessPile.setName("fitnessPile");
		LoadPosition(&fitnessPile, CORDINATESFILE);
		fitnessPile.setValue(int(theGame.getFitness()));
		fitnessPile.setCompLarger(true);
		fitnessPile.setMultiply(float(0.2));

		fitnessCostPile.setName("fitnessCostPile");
		LoadPosition(&fitnessCostPile, CORDINATESFILE);
		fitnessCostPile.setValue(int(theGame.getFitness()));
		fitnessCostPile.setCompLarger(false);
		fitnessCostPile.setMultiply(float(0.1));

		awakePile.setName("awakePile");
		LoadPosition(&awakePile, CORDINATESFILE);
		awakePile.setCompLarger(false);
		awakePile.setValue(int(theGame.getAwake()));
		awakePile.setMultiply(2);

		nSleep = 1;
		sleepDays.setText(nSleep);
		sleepDays.setName("sleepDays");
		LoadPosition(&sleepDays, CORDINATESFILE);
		sleepDays.setBgColor(RGB(255, 255, 255));
		sleepDays.setFrame(RGB(0,0,0));
		sleepDays.setFlags(DT_SINGLELINE | DT_CENTER| DT_VCENTER);

		moneyDiagram.setName("moneyDiagram");
		LoadPosition(&moneyDiagram, CORDINATESFILE);
		moneyDiagram.setDiagramDots(theGame.getPrevMoney(), MAX_PREVMONEY);
		moneyDiagram.setText("Your Money Graph");

		fitnessDiagram.setName("fitnessDiagram");
		LoadPosition(&fitnessDiagram, CORDINATESFILE);
		fitnessDiagram.setDiagramDots(theGame.getPrevFitness(), MAX_PREVFITNESS);
		fitnessDiagram.setText("Your Fitness Graph");

		moneyText.setName("statusMoneyText");
		LoadPosition(&moneyText, CORDINATESFILE);

		square[sSTATUS].setName("status");
		square[sSTATUS].addSprite(&as[CLOSE]);
		square[sSTATUS].addObject(&playerStatusText);
		square[sSTATUS].addObject(&fitnessText);
		square[sSTATUS].addObject(&awakeText);
		square[sSTATUS].addObject(&fitnessPile);
		square[sSTATUS].addObject(&awakePile);
		square[sSTATUS].addObject(&moneyDiagram);
		square[sSTATUS].addObject(&fitnessDiagram);
		square[sSTATUS].addObject(&moneyText);
		square[sSTATUS].addObject(&timesSleep);
		square[sSTATUS].addObject(&workGotText);
		square[sSTATUS].addObject(&workGotAntText);
		square[sSTATUS].addObject(&workLeftAntText);
		square[sSTATUS].addObject(&statusDays);
		square[sSTATUS].addObject(&statusClick);
		square[sSTATUS].addObject(theGame.getList(lWORKGOT));

		square[sSLEEP].setName("sleep");
		square[sSLEEP].addSprite(&as[CLOSE]);
		square[sSLEEP].addSprite(&as[UARROW]);
		square[sSLEEP].addSprite(&as[DARROW]);
		square[sSLEEP].addSprite(&as[SLEEP]);
		square[sSLEEP].addObject(&clockAnim);
		square[sSLEEP].addObject(&sleepDays);
		square[sSLEEP].addObject(&days);
		square[sSLEEP].addObject(&fitnessText);
		square[sSLEEP].addObject(&awakeText);
		square[sSLEEP].addObject(&fitnessPile);
		square[sSLEEP].addObject(&awakePile);

		//Buy Square
		theGame.LoadLists();
		buyNumberRadios.add(&rb[BUYONE]);
		buyNumberRadios.add(&rb[BUYTEN]);
		buyNumberRadios.add(&rb[BUYALL]);

		moneyText.setName("moneyText");
		LoadPosition(&moneyText, CORDINATESFILE);
		moneyText.setText("Your money", theGame.getMoney());
		moneyText.setBgMode(OPAQUE);
		moneyText.setTextWeight(FW_BOLD);
		moneyText.setBgColor(RGB(255,255,255));
		moneyText.setFrame(RGB(0,0,0));
		moneyText.setFlags(DT_SINGLELINE | DT_VCENTER | DT_CENTER);

		diagShop.setName("diagShop");
		LoadPosition(&diagShop, CORDINATESFILE);
		diagShop.setDiagramDots(theGame.getList(lSTOCK)->getActiveObj()->getPrevPrice(), MAX_PREVPRICE);

		square[sBUYPART].setName("buySell");
		square[sBUYPART].addObject(&buyNumberRadios);
		square[sBUYPART].addObject(theGame.getList(lSTOCK));
		square[sBUYPART].addObject(theGame.getList(lSTOCKGOT));
		square[sBUYPART].addObject(&moneyText);
		square[sBUYPART].addObject(&diagShop);
		square[sBUYPART].addSprite(&as[LARROW]);
		square[sBUYPART].addSprite(&as[RARROW]);
		square[sBUYPART].addSprite(&as[CLOSE]);

		// Work square
		getWorkText[0].setName("wage");
		getWorkText[0].setBgMode(OPAQUE);
		getWorkText[0].setTextWeight(FW_BOLD);
		getWorkText[0].setBgColor(RGB(255,255,255));
		getWorkText[0].setFrame(RGB(0,0,0));
		getWorkText[0].setFlags(DT_VCENTER | DT_CENTER);
		getWorkText[1].setName("getWorkText");
		getWorkText[1].setItalict(TRUE);
		getWorkText[2].setName("getWorkName");
		getWorkText[2].setFlags(DT_CENTER | DT_SINGLELINE);
		getWorkText[2].setTextHeight(30);
		getWorkText[2].setTextWeight(FW_BOLD);

		UpdateWork(getWorkText, theGame.getActiveWork());

		square[sGETWORK].setMarginAndMove(0, 0);
		square[sGETWORK].setBackColor(RGB(0,0,0));
		square[sGETWORK].setName("Get Work");
		square[sGETWORK].LoadBack("data/OfficePaperBg.bmp");
		square[sGETWORK].addObject(&fitnessCostPile);
		square[sGETWORK].addSprite(&as[BIGCLOSE]);
		square[sGETWORK].addSprite(&as[BIGLARROW]);
		square[sGETWORK].addSprite(&as[BIGRARROW]);
		square[sGETWORK].addSprite(&as[BIGACCEPT]);
		for(int i = 0; i < 3; i++)
		{
			getWorkText[i].setBgMode(TRANSPARENT);
			LoadPosition(&getWorkText[i], CORDINATESFILE);
			square[sGETWORK].addObject(&getWorkText[i]);
		}

		// Buy Drug Square
		diagWorkout.setName("diagWorkout");
		LoadPosition(&diagWorkout, CORDINATESFILE);
		diagWorkout.setDiagramDots(theGame.getList(lTRAINING)->getActiveObj()->getPrevPrice(), MAX_PREVPRICE);

		drugText.setName("drugText");
		LoadPosition(&drugText, CORDINATESFILE);
		drugText.setFrame(RGB(0,0,0));
		drugText.setBgColor(RGB(255,255,255));
		drugText.setItalict(true);
		drugText.setMargin(10);
		drugText.setFlags(DT_VCENTER);

		square[sBUYDRUG].setName("Buy Drug");
		square[sBUYDRUG].addSprite(&as[CLOSE]);
		square[sBUYDRUG].addSprite(&as[ACCEPT]);
		square[sBUYDRUG].addObject(theGame.getList(lDRUG));
		square[sBUYDRUG].addObject(&moneyText);
		square[sBUYDRUG].addObject(&buyNumberRadios);
		square[sBUYDRUG].addObject(&awakeText);
		square[sBUYDRUG].addObject(&awakePile);
		square[sBUYDRUG].addObject(&fitnessText);
		square[sBUYDRUG].addObject(&fitnessPile);
		square[sBUYDRUG].addObject(&diagWorkout);
		square[sBUYDRUG].addObject(&drugText);

		// Buy Training Square
		square[sBUYTRAINING].setName("Buy Trainging");
		square[sBUYTRAINING].addSprite(&as[CLOSE]);
		square[sBUYTRAINING].addSprite(&as[ACCEPT]);
		square[sBUYTRAINING].addObject(theGame.getList(lTRAINING));
		square[sBUYTRAINING].addObject(&moneyText);
		square[sBUYTRAINING].addObject(&buyNumberRadios);
		square[sBUYTRAINING].addObject(&awakeText);
		square[sBUYTRAINING].addObject(&awakePile);
		square[sBUYTRAINING].addObject(&fitnessText);
		square[sBUYTRAINING].addObject(&fitnessPile);
		square[sBUYTRAINING].addObject(&diagWorkout);
		square[sBUYTRAINING].addObject(&drugText);

		// Initiate Rooms
		room[eBEDROOM].LoadBack("data/home.bmp");
		room[eBEDROOM].addSprite(&as[BED]);
		room[eBEDROOM].addSprite(&as[PAPER]);
		room[eBEDROOM].addSprite(&as[BOX]);
		room[eBEDROOM].addSprite(&as[DOOR]);
		room[eBEDROOM].addObject(&square[sSTATUS]);
		room[eBEDROOM].addObject(&square[sSLEEP]);


		room[eTOWN].LoadBack("data/town.bmp");
		room[eTOWN].addSprite(&as[HOUSEWORKOUT]);
		room[eTOWN].addSprite(&as[HOUSEHOME]);
		room[eTOWN].addSprite(&as[HOUSESHOP]);
		room[eTOWN].addSprite(&as[HOUSEOFFICE]);
		
		room[eSHOP].LoadBack("data/shop.bmp");
		room[eSHOP].addSprite(&as[SHOPMAN]);
		room[eSHOP].addSprite(&as[SHOPEXIT]);
		room[eSHOP].addObject(&square[sBUYPART]);

		room[eWORKOUT].LoadBack("data/workout.bmp");
		room[eWORKOUT].addSprite(&as[WORKOUTDOOR]);
		room[eWORKOUT].addSprite(&as[WORKOUTPAPER]);
		room[eWORKOUT].addSprite(&as[WORKOUTEXIT]);
		room[eWORKOUT].addObject(&square[sBUYDRUG]);
		room[eWORKOUT].addObject(&square[sBUYTRAINING]);

		room[eOFFICE].LoadBack("data/office.bmp");
		room[eOFFICE].addSprite(&as[OFFICEEXIT]);
		room[eOFFICE].addSprite(&as[OFFICEPAPER1]);
		room[eOFFICE].addSprite(&as[OFFICEPAPER2]);
		room[eOFFICE].addSprite(&as[OFFICEPAPER3]);
		room[eOFFICE].addSprite(&as[OFFICEPAPER4]);
		room[eOFFICE].addSprite(&as[OFFICEPAPER5]);
		room[eOFFICE].addSprite(&as[OFFICEPAPER6]);
		room[eOFFICE].addObject(&square[sGETWORK]);

		scoreText.setName("scoreText");
		LoadPosition(&scoreText, CORDINATESFILE);
		scoreText.setFlags(DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		scoreText.setBgColor(RGB(74,122, 164));
		scoreText.setTextHeight(26);
		scoreText.setTextWeight(FW_BOLD);

		enterNameText.setText("Enter Name:");
		enterNameText.setName("enterNameText");
		LoadPosition(&enterNameText, CORDINATESFILE);
		enterNameText.setFlags(DT_SINGLELINE | DT_TOP | DT_CENTER);
		enterNameText.setBgColor(RGB(255, 255, 255));
		enterNameText.setFrame(RGB(0,0,0));
		enterNameText.setTextWeight(FW_BOLD);

		room[eENDGAME].addObject(&enterNameText);
		room[eENDGAME].addObject(&scoreText);
		room[eENDGAME].addSprite(&as[CONFIRM]);
	}
	else		// If init done then just reset all variables
	{
		Logg("Init Game allready done, just resetting values");
		for(int i = 0; i < nAs; i++)
			as[i].setStatus(NORMAL);

		for(int i = 0; i < nSquare; i++)
			square[i].setStatus(NOT_PRESSABLE);

		theGame.reset();
		Logg("Resetting Values Done");
	}
	initDone = true;		// If this functions is called then the 
							// Initiation is done.
	Logg("<b>Init Game Variables <u>Done</u></b>");

	return 1;
}