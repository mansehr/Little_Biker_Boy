// Stock.h: interface for the ClItem class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __STOCK_H__
#define __STOCK_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <fstream.h>
#include <windows.h>
#include "String.h"
#include "price.h"

#define MAX_STOCK 128
#define MAX_NAME_LENGTH 64

struct ListItem
{
	unsigned int id;
	CPrice price;
	char name[MAX_NAME_LENGTH];
	int quantity;
} oldLItem[MAX_STOCK];


struct NewListItem
{
	unsigned int id;
	int maxPrice;
	int minPrice;
	int itsPrice;
	char name[MAX_NAME_LENGTH];
} lItem[MAX_STOCK];

int antLItem = 1, activeLItem = 0;

int LoadStock(char *file)
{
	ifstream fil;
	fil.open(file, ios::binary);
	if(fil.fail()) 
	{
		MessageBox(NULL, file, "Error opening", MB_OK);
		return false;
	}
	fil.read((char*) &antLItem, sizeof(unsigned int));

	for(int i = 0; i < antLItem; i++)
	{
		fil.read((char*) &oldLItem[i], sizeof(ListItem));
		
		lItem[i].id = oldLItem[i].id;
		lItem[i].maxPrice = oldLItem[i].price.getMin();
		lItem[i].minPrice = oldLItem[i].price.getMax();
		lItem[i].itsPrice = oldLItem[i].price.getPrice();
		strcpy(lItem[i].name, oldLItem[i].name);


	/*	char ch;
		lItem[i].name.setToNull();
		do
		{
			fil.get(ch);
			lItem[i].name += ch;
		} while(ch != '\0' && !fil.eof());*/
	}
/*
		char buffer[32];
					wsprintf(buffer, "MAX: %d", oldLItem[activeLItem].price.getMax()); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

						wsprintf(buffer, "Min: %d", oldLItem[activeLItem].price.getMin()); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

						wsprintf(buffer, "Price: %d", oldLItem[activeLItem].price.getPrice()); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);
*/
	fil.close();

	return 1;
}
/*
int SaveStock(char* file)
{
	ofstream out(file, ios::binary);

	out.write((char*) &antLItem, sizeof(unsigned int));

	for(int i = 0; i < antLItem; i++)
	{
		out.write((char*) &lItem[i], sizeof(ListItem));
		/*out.write((char*) &lItem[i].price, sizeof(lItem[i].price));

		for(int j = 0; j < lItem[i].name.getLen(); j++)
			out.put(lItem[i].name.getChar(j));
		out.put('\0');
	}
				/*		char buffer[32];
						wsprintf(buffer, "MAX: %d", lItem[activeLItem].price.getMax()); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

						wsprintf(buffer, "Min: %d", lItem[activeLItem].price.getMin()); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

						wsprintf(buffer, "Price: %d", lItem[activeLItem].price.getPrice()); 
						MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

	out.close();

	return 1;
}*/

int NewLoadStock(char *file)
{
	HANDLE fil;
	fil = CreateFile(file, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, file, "Error opening", MB_OK);
		return false;
	}

	
	NewListItem tempItem;
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
				lItem[i] = tempItem;
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
	} while(antLesta == sizeof(NewListItem));

	char buffer[32];
	wsprintf(buffer, "Antal Inlästa: %d", i); 
	MessageBox(NULL, buffer, "Hm", MB_OK | MB_ICONEXCLAMATION);

	antLItem = i;
	//MB_INT(i);
	CloseHandle(fil);

	return 1;
}

int NewSaveStock(char* file)
{
	HANDLE fil;
	fil = CreateFile(file, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, file, "Error opening", MB_OK);
		return false;
	}
	unsigned long antWrite = 0;

	WriteFile(fil, &lItem, sizeof(NewListItem)*(antLItem), &antWrite, NULL);


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

#endif // ifndef __lItem_H__