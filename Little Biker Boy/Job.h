#include "SiTiString"

class CJob
{
public:
	CJob();
	~CJob();

	void	setName(char* initName);
	void	setStrength(int initStrength);
	void	setText(char* initText);
	void	setWage(int initWage);
		
	char* 	getName();
	int 	getStrength();
	char* 	getText();
	int 	getWage();
	
private:
	int 		nWage;
	int 		nStrength;
	String 	stText;
	char 		szName[32];
};