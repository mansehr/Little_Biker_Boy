// Diagram.h: interface for the CObject class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __DIAGRAM_H__
#define __DIAGRAM_H__

#include "Object.h"			// Used by the name

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_DIAGRAMDOTS 100

class CDiagram : public CObject
{
public:
	CDiagram();
	virtual ~CDiagram();

	void	setDiagramDots(int *initPt, int initAnt);
	void	draw(HDC hdc);

	void	setText(char* init);
	void	setPosition(int left, int top, int right, int bottom);
	int		getAntValues();
private:
	int itsValues[MAX_DIAGRAMDOTS];
	int antValues;
	CStaticText itsText;
};

#endif