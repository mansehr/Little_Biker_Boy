
#include "stdafx.h"
#include "LogFile.h"
#include <time.h>


#define LOGG_FILE "logg.htm"

HANDLE loggFile;
time_t appTimer;

void startLogg()
{
	BOOL fileSuccess = false;
	loggFile = CreateFile(LOGG_FILE, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(loggFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "Loggfile creation Failed", "Error creating file", MB_OK);
		return;
	}

	ULONG antWrite;

	char* toWrite =	"<HTML>\n"
						"<HEAD>\n"
						"<TITLE>Little Biker Boy Logg</TITLE>\n"
						"</HEAD>\n<BODY BGCOLOR=\"#FFFFFF\" TEXT=\"#000000\">\n"
						"<H1><U><CENTER>Little Biker Boy debug logg</H1></U></CENTER>\n"
						"<UL>";			
	//MB(toWrite);
	//MB_INT(strlen(toWrite));

	fileSuccess = WriteFile(loggFile, toWrite, strlen(toWrite), &antWrite, NULL);
	if(fileSuccess == false)
	{
		MessageBox(NULL, "Loggfile writing Failed", "Error writing file", MB_OK);
	}

	/*Logg("Hej");
	Logg("Inten", 15);
	Logg(15);
	float temp = 56.5;
	Logg(temp);
	double t = 0.8273;
	Logg(t);*/

#ifdef DEBUGHIG
	Logg("Debug level", "DEBUGHIG");
#endif

#ifdef DEBUGMED
	Logg("Debug level", "DEBUGMED");
#endif

#ifdef DEBUGLOW
	Logg("Debug level", "DEBUGLOW");
#endif

	time_t osBinaryTime;
	appTimer = time( &osBinaryTime ) ;
	Logg("Start timer", (long)appTimer);

//	MB_INT(antWrite);
}

void endLogg()
{
	time_t osBinaryTime;
	appTimer = (time( &osBinaryTime ) - appTimer);
	Logg("Run time(sec)", (long)appTimer);

	ULONG antWrite;
	char* toWrite =	"</UL>\n"
					"</BODY>\n"
					"</HTML>\n";

	WriteFile(loggFile, toWrite, strlen(toWrite), &antWrite, NULL);

	CloseHandle(loggFile);
}

void Logg(char* chInit)
{
	ULONG antWrite;
	WriteFile(loggFile, "<li>", 4, &antWrite, NULL);
	WriteFile(loggFile, chInit, strlen(chInit), &antWrite, NULL);
	WriteFile(loggFile, "</li>\n", 6, &antWrite, NULL);
}

void Logg(char* chInit, char* chTwo)
{
	char buffer[100];
	wsprintf(buffer,"%s: %s", chInit, chTwo);
	Logg(buffer);
}

void Logg(char* chInit, int nInit)
{
	char buffer[100];
	wsprintf(buffer,"%s: %i", chInit, nInit);
	Logg(buffer);
}

void Logg(int nInit)
{
	char buffer[100];
	wsprintf(buffer,"%i",  nInit);
	Logg(buffer);
}

void Logg(float flInit)
{
	char buffer[100];
	wsprintf(buffer,"%%d",  flInit);
	Logg(buffer);	
}

void Logg(double dbInit)
{
	char buffer[100];
	wsprintf(buffer,"%d",  dbInit);
	Logg(buffer);
}

void Logg(long double dbInit)
{
	char buffer[100];
	wsprintf(buffer,"%ld",  dbInit);
	Logg(buffer);
}