// Work.h: interface for the CWork class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORK_H__7AAB5A4D_7D1B_4C47_9680_1A2E9A6309BD__INCLUDED_)
#define AFX_WORK_H__7AAB5A4D_7D1B_4C47_9680_1A2E9A6309BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "object.h"

#define MAX_WORK 32
#define MAX_TEXT 1024
#define MAX_NAME 64

struct SaveWork  
{
	unsigned int id;
	int nFitnes;
	int nCostInfitness;
	int nWage;
	char text[MAX_TEXT];
	char name[MAX_NAME];
};

class CWork  
{
public:
	CWork();
	virtual ~CWork();

	int		Load(HANDLE fil, DWORD &antRead);

	int		getFitness();
	int		getCostInFitnes();
	int		getWage();
	char*	getText();
	char*	getName();
	int		getId();

private:
	SaveWork itsWork;
};

class CWorkHandler {
public:
	CWorkHandler();
	~CWorkHandler();

	void	addObject(CWork &init);
	void	deleteActiveObject(bool deleteIt = true);
	void	deleteLastObject(bool deleteIt = true);
	void	deleteObject(int init, bool deleteIt = true);

	CWork*	getActiveWorkpt();
	CWork	getActiveWork();
	CWork	getObject(int init);
	int		getActiveWorkNumber();
	int		getWorkNumber();

	void	setActiveWork(int init);

private:
	CWork itsWork[MAX_WORK];
	int activeWork;
	int nWork;
};

int UpdateWork(CStaticText* init, CWork initWork);

#endif // !defined(AFX_WORK_H__7AAB5A4D_7D1B_4C47_9680_1A2E9A6309BD__INCLUDED_)
