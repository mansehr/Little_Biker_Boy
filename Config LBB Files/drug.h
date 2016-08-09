// Drug.h: interface for the CWork class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __DRUG_H__
#define __DRUG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fstream.h>
#include "String.h"

#define MAX_DRUG 64
#define MAX_TEXT 1024
#define MAX_NAME_LENGTH 64

struct Drug  
{
	unsigned int id;
	int nFitnes;
	int nCostInSleep;
	int nWage;
	char text[MAX_TEXT];
	char name[MAX_NAME_LENGTH];
} drug[MAX_DRUG];

int antDrug = 1, activeDrug = 0;

int LoadDrug(char* file)
{
	ifstream fil(file, ios::binary);
	if(fil.fail()) 
	{
		MessageBox(NULL, file, "Error opening", MB_OK);
		return false;
	}

	fil.read((char*) &antDrug, sizeof(int));

	for(int i = 0; i < antDrug; i++)
	{
		fil.read((char*) &drug[i], sizeof(Drug));
	}
	fil.close();

	return 1;
}
/*
int SaveDrug(char* file)
{
	ofstream out(file, ios::binary);

	for(int i = 0; i < antDrug; i++)
	{
		out.write((char*) &drug[i], sizeof(Drug));
	}

	out.close();

	return 1;
}*/

int NewLoadDrug(char *file)
{
	HANDLE fil;
	fil = CreateFile(file, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, file, "Error opening", MB_OK);
		return false;
	}

	
	Drug tempItem;
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
				drug[i] = tempItem;
			else
				i--;
		}
		i++;


	} while(antLesta == sizeof(tempItem));

		MB_INT(i);
		wsprintf(buffer, "Antal Inlästa: %d", i); 
		MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

	/*	wsprintf(buffer, "Sizeofe bufferl: %d", sizeof(tempItem)); 
		MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

		wsprintf(buffer, "Cost in sleep: %d", work[activeWork].nCostInFittnes); 
		MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

		wsprintf(buffer, "Price: %d", work[activeWork].nWage); 
		MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);*/

	antDrug = i;

	CloseHandle(fil);

	return 1;
}

int NewSaveDrug(char* file)
{
	HANDLE fil;
	fil = CreateFile(file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, file, "Error opening", MB_OK);
		return false;
	}
	unsigned long antWrite = 0;

	WriteFile(fil, &drug, sizeof(Drug)*(antDrug), &antWrite, NULL);


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
