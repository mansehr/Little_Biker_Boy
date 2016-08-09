// Work.h: interface for the CWork class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __WORK_H__
#define __WORK_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "fstream.h"
#include "String.h"

#define MAX_WORK 64
#define MAX_TEXT 1024
#define MAX_NAME_LENGTH 64

struct Work  
{
	unsigned int id;
	int nFitnes;
	int nCostInFittnes;
	int nWage;
	char text[MAX_TEXT];
	char name[MAX_NAME_LENGTH];
} work[MAX_WORK];

int antWork = 1, activeWork = 0;

int LoadWork(char* file)
{
	ifstream fil(file, ios::binary);
	if(fil.fail()) 
	{
		MessageBox(NULL, file, "Error opening", MB_OK);
		return false;
	}
	fil.read((char*) &antWork, sizeof(int));

	for(int i = 0; i < antWork; i++)
	{
		fil.read((char*) &work[i], sizeof(Work));
	}
	fil.close();

	return 1;
}
/*
int SaveWork(char* file)
{
	ofstream out(file, ios::binary);

	out.write((char*) &antWork, sizeof(unsigned int));

	for(int i = 0; i < antWork; i++)
	{
		out.write((char*) &work[i], sizeof(Work));
	}

	out.close();

	return 1;
}*/

int NewLoadWork(char *file)
{
	HANDLE fil;
	fil = CreateFile(file, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, file, "Error opening", MB_OK);
		return false;
	}

	
	Work tempItem;
	unsigned long antLesta;
	BOOL result;
	int i = 0;
	do 
	{
		result = ReadFile(fil, &tempItem, sizeof(tempItem), &antLesta, NULL);
		if(result == false)
		{
			MB("File reading error");
			break;
		}
		else
		{
			if(antLesta == sizeof(tempItem))
				work[i] = tempItem;
			else
				i--;
		}
		
		i++;


		

		/*				wsprintf(buffer, "Sizeofe bufferl: %d", sizeof(tempItem)); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

						wsprintf(buffer, "MAX: %d", lItem[activeLItem].maxPrice); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

						wsprintf(buffer, "Min: %d", lItem[activeLItem].minPrice); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

						wsprintf(buffer, "Price: %d", lItem[activeLItem].itsPrice); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);*/
	} while(antLesta == sizeof(tempItem));

	char buffer[32];
	wsprintf(buffer, "Antal Inlästa: %d", i); 
	MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

	antWork = i;
	//MB_INT(i);
	CloseHandle(fil);

	return 1;
}

int NewSaveWork(char* file)
{
	HANDLE fil;
	fil = CreateFile(file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, file, "Error opening", MB_OK);
		return false;
	}
	unsigned long antWrite = 0;

	WriteFile(fil, &work, sizeof(Work)*(antWork), &antWrite, NULL);


				/*		char buffer[32];
						wsprintf(buffer, "Antal: %d", antLItem); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

						wsprintf(buffer, "Antal skrivna: %d", antWrite); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

						wsprintf(buffer, "MAX: %d", lItem[activeLItem].price.getMax()); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

						wsprintf(buffer, "Min: %d", lItem[activeLItem].price.getMin()); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

						wsprintf(buffer, "Price: %d", lItem[activeLItem].price.getPrice()); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);
*/
	CloseHandle(fil);

	return 1;
}

#endif // ifndef __WORK_H__
