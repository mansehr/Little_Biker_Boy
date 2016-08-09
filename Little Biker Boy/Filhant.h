// Filhant.h: interface for the CFilhant class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __FILHANT_H__
#define __FILHANT_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "String.h"
#include "Object.h"
#include "StatusObject.h"
//#include <fstream.h>

class CReadSiTiFile {
	public:
		CReadSiTiFile();
		~CReadSiTiFile();
		void	close();
		bool	open(char*);
		char*	get(char*);
		int		getAsInt(char*);
	private:
		HANDLE fileHandle;
		bool fileIsOpen;
		String itsString;
		String fileString;
};

/*int SaveString(ofstream *file, String *string);
String LoadString(ifstream *file);//, String *string);*/
int LoadPosition(CObject* theObject, String fileName);
int LoadInfoText(CStatusObject* theObject, String fileName);

#endif // __FILHANT_H__
