// Diagram.cpp: implementation of the CObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "diagram.h"

//////////////////////////////////////////////////////////////////////
//
// CLASS: CDIAGRAM
//
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDiagram::CDiagram()
{
	for(int i = 0; i < MAX_DIAGRAMDOTS; i++)
		itsValues[i] = 0;

	antValues = 0;

	itsText.setFlags(DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	itsText.setBgMode(TRANSPARENT);
}

CDiagram::~CDiagram()
{

}

void CDiagram::setDiagramDots(int *initPt, int initAnt)
{
	for(int i = 0; i < initAnt && i < MAX_DIAGRAMDOTS; i++)
		itsValues[i] = initPt[i];

	antValues = initAnt;
}

void CDiagram::draw(HDC hdc)
{
	if(antValues > 0)
	{
		// Calculate the spots and zoom of the diagram
		float maxValue = 0;
		for(int i = 0; i < antValues; i++)
			if(itsValues[i] > maxValue)
				maxValue = float(itsValues[i]);

		float addY = float(getHeight()/(maxValue*1.1));
		float addX = float(getWidth()/antValues);


		HPEN whitePen	= CreatePen(PS_SOLID, 0, RGB(255,255,255));
		HPEN redPen		= CreatePen(PS_SOLID, 0, RGB(255,  0,  0));
		HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));

		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH) );
		HPEN oldPen = (HPEN)SelectObject(hdc, whitePen);
		Rectangle(hdc, getLeft(), getTop(), getRight(), getBottom());

		for(int i = 1; i < antValues; i++)
		{
			MoveToEx(hdc, int(getLeft()+(i*addX)+1), int(getBottom()-(0.05*getHeight())), NULL);
			LineTo(hdc, int(getLeft()+(i*addX)+1), getBottom());
		}

		SelectObject(hdc, redPen);

		MoveToEx(hdc, getLeft()+1, int(getBottom()-(itsValues[0]*addY)-2), NULL);
		for(int i = 1; i < antValues; i++)
		{
			if((itsValues[i]*addY)-2 < getHeight())
				LineTo(hdc, int(getLeft()+(i*addX)+1), int(getBottom()-(itsValues[i]*addY)-2));
		}
		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(whitePen);
		DeleteObject(redPen);
		DeleteObject(blackBrush);
	}
	if(itsText.getTextLen() > 0)
		itsText.draw(hdc);
}

int CDiagram::getAntValues()
{
	return this->antValues;
}

void CDiagram::setPosition(int left, int top, int right, int bottom)
{
	CObject::setPosition(left, top, right, bottom);
	itsText.setPosition(left, top-30, right, top);
}

void CDiagram::setText(char* init)
{
	itsText.setText(init);
}