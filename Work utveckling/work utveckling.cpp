// work utveckling.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "work.h"

int LoadWork(char* file);

CWorkHandler tempHandle;

int _tmain(int argc, _TCHAR* argv[])
{
	/*CWork* itsWork[20];
	for(int i = 0; i < 20; i++)
		itsWork = new CWork;

	itsWork[0]->Load(*/

	LoadWork("work.con");

	cout << tempHandle.getActiveWorkNumber() << ". "<< tempHandle.getActiveWork().getName() <<  " : "<< endl;
		tempHandle.setActiveWork(tempHandle.getActiveWorkNumber() + 3);
	cout << tempHandle.getActiveWorkNumber() << ". "<< tempHandle.getActiveWork().getName() <<  " : "<< endl;

//		tempHandle.deleteActiveObject(false);
	cout << tempHandle.getActiveWorkNumber() << ". "<< tempHandle.getActiveWork().getName() <<  " : "<< endl;
		tempHandle.setActiveWork(tempHandle.getActiveWorkNumber() + 3);
	cout << tempHandle.getActiveWorkNumber() << ". "<< tempHandle.getActiveWork().getName() <<  " : "<< endl;

	cout << tempHandle.getActiveWork().getName() << ". "<< tempHandle.getActiveWork().getFitness() <<  " : " << tempHandle.getActiveWork().getId() << endl;

		CWork itsWork = tempHandle.getActiveWork();
	cout << itsWork.getName() << " : " << itsWork.getFitness() << " : " << itsWork.getId() << endl;
		tempHandle.deleteActiveObject(true);
	cout << itsWork.getName() << " : " << itsWork.getFitness() << " : " << itsWork.getId() << endl;

	system("PAUSE");

	return 0;
}


int LoadWork(char* file)
{
	HANDLE fil;
	fil = CreateFile(file, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fil == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, file, "Error opening", MB_OK);
		return false;
	}
	DWORD antRead = 0;
	int i = 0;
	do 
	{
		CWork tempWork;
		tempWork.Load(fil, antRead);
		i++;

	/*	if(i <= 3)
			itsWork[5].addObject(tempWork);
		else if(i <= 6)
			itsWork[4].addObject(tempWork);
		else if(i <= 9)
			itsWork[3].addObject(tempWork);
		else if(i <= 12)
			itsWork[2].addObject(tempWork);
		else if(i <= 15)
			itsWork[1].addObject(tempWork);
		else
			itsWork[0].addObject(tempWork);*/

		tempHandle.addObject(tempWork);

	} while(antRead == sizeof(SaveWork));

	cout << i << endl;
	//antWork = i;
	//MB_INT(antRead)
	CloseHandle(fil);

	return 1;
}
