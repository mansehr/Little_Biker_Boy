

class CPlayer
{
public:
	CPlayer();
	~CPlayer();
	
	void setAge(int initAge);
	void setStrength(int initStrength);
	void setHealth(int initHealth);
	void setBike(CBike initBike);
	void setName(char* initName);
	
private:
	int 	nAge;
	int 	nStrength;
	int 	nHealth;
	CBike 	itsBike;
	char 	szName[32];
};