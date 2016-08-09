#pragma once
#include "object.h"

class CPile :
	public CObject
{
public:
	CPile(void);
	~CPile(void);

	void draw(HDC hdc);
	void draw(HWND hWnd);

	void setValue(int init);
	void setCompareValue(int init);
	void setCompLarger(bool init);
	void setChange(int init);
	void setMultiply(float init);

private:
	int itsChange;
	int itsValue;
	int itsCompareValue;
	float itsMultiply;
	bool compLarger;
	CStaticText itsValueText;
	CStaticText itsCompareText;
	CStaticText itsChangeText;
};
