// Work.cpp: implementation of the CWork class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Work.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWork::CWork()
{
	itsWork.id = 0;
	strcpy(itsWork.name,"Name");
	itsWork.nCostInfitness = 0;
	itsWork.nFitnes = 0;
	itsWork.nWage = 0;
	strcpy(itsWork.text, "Text");
}

CWork::~CWork()
{

}

int CWork::Load(HANDLE fil, DWORD &antRead)
{
	return ReadFile(fil, &itsWork, sizeof(itsWork), &antRead, NULL);
}

int	CWork::getFitness()
{
	return itsWork.nFitnes;
}

int	CWork::getCostInFitnes()
{
	return itsWork.nCostInfitness;
}

int	CWork::getWage()
{
	return itsWork.nWage;
}

char* CWork::getText()
{
	return itsWork.text;
}

char* CWork::getName()
{
	return itsWork.name;
}

int CWork::getId()
{
	return itsWork.id;
}



///////// CWorkHandler //////////////////////////////////////////
CWorkHandler::CWorkHandler()
{
	/*for(int i = 0; i < MAX_WORK; i++)
		itsWork[i] = 0;*/

	activeWork = 0;
	nWork = 0;

	//MB("Skapar en Work Handler")
}

CWorkHandler::~CWorkHandler()
{
	//MB("Tar bort en Work Handler")

	/*for(int i = 0; i < MAX_WORK; i++)
	{
		delete itsWork[i];
		itsWork[i] = 0;
	}*/

	activeWork = 0;
	nWork = 0;
}

void CWorkHandler::addObject(CWork &init)
{
	itsWork[nWork] = init;
	nWork++;
}

void CWorkHandler::deleteLastObject(bool deleteIt)
{
	cout << "Tar bort lastObject: " << nWork << endl;
	if(nWork > 0)
	{
		nWork--;
		if(nWork <= activeWork && nWork > 0)
			activeWork--;
		
		/*if(deleteIt)
			delete itsWork[nWork];

		itsWork[nWork] = NULL;*/
	}
	cout << "activteWork efter delete Last object: " << activeWork << endl;
}

void CWorkHandler::deleteObject(int init, bool deleteIt)
{
	cout << "Tar bort work: " << init << endl;
	for(int i = init; i < nWork-1; i++)
	{
		itsWork[i] = itsWork[i + 1];
	}
	deleteLastObject(deleteIt);
}

void CWorkHandler::deleteActiveObject(bool deleteIt)
{
	cout << "Tar bort activteWork: " << activeWork << endl;
	deleteObject(activeWork, deleteIt);
}

CWork* CWorkHandler::getActiveWorkpt()
{
	return &itsWork[activeWork];
}

CWork CWorkHandler::getActiveWork()
{
	return itsWork[activeWork];
}

CWork CWorkHandler::getObject(int init)
{
	if(init >= 0 && init < nWork)
		return itsWork[init];
	else
		return itsWork[0];
}

void CWorkHandler::setActiveWork(int init)
{
//	MB("Set active Work")
	if(init >= 0 && init < nWork)
		activeWork = init;

//	MB("set active Work 2")
}

int CWorkHandler::getActiveWorkNumber()
{
	return activeWork;
}

int CWorkHandler::getWorkNumber()
{
	return nWork;
}


int UpdateWork(CStaticText* init, CWork initWork)
{
//	MB("Inuti Update");
	init[0].setText(initWork.getWage());
	init[1].setText(initWork.getText());
	init[2].setText(initWork.getName());
//	MB("Inuti Update 2");
	
	return 1;
}