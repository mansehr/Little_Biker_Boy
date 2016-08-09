#include "stdafx.h"
#include "price.h"

CPrice::~CPrice()
{
	nIntervall = 0;
	nPrice = 0;
	nChange = 0;
	nMin = 0;
	nMax = 0;
}

CPrice::CPrice()
{
	nIntervall = 0;
	nPrice = 0;
	nChange = 0;
	nMin = 0;
	nMax = 0;
}

void CPrice::setPrice(CPrice &init) 
{
	nPrice = init.getPrice();
	nIntervall = init.getIntervall();
	nChange = init.getChange();
	nMax = init.getMax();
	nMin = init.getMin();
}

void CPrice::fixPrice()
{
	nIntervall--;					// Decrease one day
	if(nIntervall < 0) 		// Have the time limit passed 
	{
		nIntervall = rand()%5; // Same change for maximum 5 days.		
		nChange = rand()%(nMax) - nPrice; // Fix Change variable
		if(nChange == 0)
			nChange = 1;
		else
			nChange = 1 + (nChange/10);
		
		//nChange = (nPrice * nChange) - nPrice;
		//if(int(nChange) > nMoneyChangeMax && nMoneyChangeMax != 0)
		//	nChange = nMoneyChangeMax;
	}
	nPrice = int(nPrice + nChange);		// Add the change in the price
	if(nPrice > nMax)
		nPrice = nMax;
	else if(nPrice < nMin)
		nPrice = nMin;
}