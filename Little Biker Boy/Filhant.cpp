// Filhant.cpp: implementation of the CFilhant class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Filhant.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CReadSiTiFile::CReadSiTiFile()
{
	fileIsOpen = FALSE;
	fileHandle = NULL;
}

CReadSiTiFile::~CReadSiTiFile()
{
	close();
}

void CReadSiTiFile::close()
{
	if (fileIsOpen)
	{
		CloseHandle(fileHandle);
		fileIsOpen = false;
	}
}

bool CReadSiTiFile::open(char* initFile)
{
	fileHandle = CreateFile(initFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if(fileHandle == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "Error opening file", "File Error", MB_OK);
		fileIsOpen = false;
		return false;
	}
	else
	{
		char cBuffer[512];		
		BOOL fileStatus;
		DWORD nRead;
		do
		{
			fileStatus 		 = ReadFile(fileHandle, &cBuffer, sizeof(cBuffer)-1, &nRead, NULL);
			cBuffer[nRead++] = '\0';				//Kopierar filen tilll ett sträng objekt
			fileString 		+= cBuffer;				//som är lättare att hantera
			if(fileStatus == FALSE)
			{
				MessageBox(NULL, "Error reading file", "File Error", MB_OK);
				return false;
			}
		} while(nRead == sizeof(cBuffer));
		fileIsOpen = true;
		return true;
	}
}

int CReadSiTiFile::getAsInt(char* initGet)
{
	return CharToInt(get(initGet));
}

char* CReadSiTiFile::get(char* initGet)
{
	if (fileIsOpen) {
		String testString("");
		String theString("");

		for (int i=0; i < fileString.getLen(); i++) //Går igenom sträng objektet tecken för tecken
		{
			if (fileString[i] == '[')
			{
				if (fileString[i+1] != '/')
				{	
					for(i=i+1;i < fileString.getLen() && fileString[i] != ']'; i++)
					{	testString += fileString[i];	}
					if(testString == initGet)
					{
						bool STOPCOPY = false;
						i++;
						while(!STOPCOPY)
						{
							for(;i < fileString.getLen() && fileString[i] != '['; i++)
							{	theString += fileString[i];	}

							if ((fileString[i] == '[' && fileString[i+1] == '/'
								&& fileString[i+2] == ']') ||  i > fileString.getLen())
							{	STOPCOPY = true;	}
						}
					}
					else
					{
						testString.setToNull();
						continue;
					}
				}
			}
		}
		itsString = theString;
		return itsString.getString();
	}
	return "FILE NOT OPEN";
}

/*int SaveString(ofstream *file, String *string)
{
	for(int i = 0; i < string->getLen(); i++)
		file->put(string->getChar(i));
	file->put('\0');
	return true;
}*/

/*String LoadString(ifstream *file)//, String *string)
{
	char ch;
	String tempStr;
	int i = 0;
	do
	{
		file->get(ch);
		tempStr += ch;
		i++;
	} while(ch != '\0' && !file->eof());
	//*string = tempStr;
	return tempStr;
}*/

int LoadPosition(CObject* theObject, String fileName)
{
	int x, y, bottom, right;
	CReadSiTiFile fCord;
	String tempString;
	if(fCord.open(fileName.getString()) == false)
	{
		Logg("Coulnt open cordinates file", fileName.getString());
		MessageBox(NULL, theObject->getName(), "Coulnt load cordinates", MB_OK);
		return 0;
	}
	tempString.setToNull();
	tempString = tempString + theObject->getName() + "X";
	x = fCord.getAsInt(tempString.getString());
	tempString.setToNull();
	tempString = tempString + theObject->getName() + "Y";
	y = fCord.getAsInt(tempString.getString());
	tempString.setToNull();
	tempString = tempString+theObject->getName()+"H";
	bottom = fCord.getAsInt(tempString.getString());
	if(bottom != 0)			// Hittade position?
		bottom += y;
	tempString.setToNull();
	tempString = tempString+theObject->getName()+"W";
	right = fCord.getAsInt(tempString.getString());
	if(right != 0)			// Hittade position?
		right += x;
	theObject->setPosition(x, y, right, bottom);

	fCord.close();

#ifdef DEBUGHIG
	Logg("LoadPosition Top", y);
	Logg("LoadPosition <u>Done</u>", theObject->getName());
#endif

	return 1;
}

int LoadInfoText(CStatusObject* theObject, String fileName)
{
#ifdef DEBUGHIG
	Logg("LoadInfoText", theObject->getName());
#endif

	CReadSiTiFile file;
	String tempString;
	if(file.open(fileName.getString()) == false)
	{
		Logg("Coulnt open infotext file", fileName.getString());
		MessageBox(NULL, theObject->getName(), "Coulnt open infotext file", MB_OK);
		return 0;
	}
	tempString.setToNull();
	tempString = tempString + theObject->getName() + "T";

	theObject->setInfoText(file.get(tempString.getString()));

	file.close();

#ifdef DEBUGHIG
	Logg("LoadInfoText <u>Done</u>");
#endif

	return 1;
}
