/*		this file: The price engine class plus the 
			money functions.
			
*/

/* -------------------	CPrice Class	------------------- 

Give the maxPrice And minPrice variable in decimal but small. min value betveen zero if you dont want a hughe inflation.
*/

#include "stdlib.h"

#ifndef __CPrice__
#define __CPrice__

class CPrice
{
public:
	CPrice();
	~CPrice();
	
	void setPrice(int initPrice) {nPrice = initPrice;}
	void setPrice(CPrice &init);
	void setMin(int initMin) {nMin = initMin;}
	void setMax(int initMax) {nMax = initMax;}
	
	void fixPrice();

	int		getPrice()	{return nPrice;}
	int		getMax()	{return nMax;}
	int		getMin()	{return nMin;}
	int		getIntervall()	{return nIntervall;}
	double	getChange() {return nChange;}
private:
	int nIntervall;
	int nPrice;
	double nChange;
	int nMin;
	int nMax;
};

#endif //__CPrice__
