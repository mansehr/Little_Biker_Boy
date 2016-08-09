         ////////////////////////////////////////////////////////
         //                                                    //
         //       Fil: "SiTiString.cpp"                        //
         //                                                    //
         //       F�rfattad av: Andreas Sehr 2002,01,19        //
         //                                                    //
         //       Senast �ndrad: 2003,04,29                    //
         //                                                    //
         ////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "String.h"

//Standard konstruerare skapar en str�ng p� 0 bytes
String::String()
{
   itsString = new char[1];
   itsString[0] = '\0';
   itsLen = 0;
   sweString = false;
}

//Privat (hj�lp-) konstruerare, som anv�nds endast av klassmetoder
//f�r att skapa en ny str�ng av en angiven storlek. Null-utfylld.
String::String(unsigned short len)
{
   itsString = new char[len+1];
   for (unsigned short i = 0; i <= len; ++i)
      itsString[i] = '\0';
   itsLen = len;
}

//Omvandlar en vektor av tecken till en string
String::String(const char * const cString)
{
   itsLen = strlen(cString);
   itsString = new char[itsLen+1];
   for (unsigned short i = 0; i < itsLen; ++i)
      itsString[i] = cString[i];
   itsString[itsLen] = '\0';
}

//Kopieringskonstruerare
String::String(const String & rhs)
{
   itsLen = rhs.getLen();
   itsString = new char[itsLen+1];
   for (unsigned short i = 0; i < itsLen; i++)
      itsString[i] = rhs[i];
   itsString[itsLen] = '\0';
}

//Destruerare, l�mmnar tillbaka reserverat minne
String::~String()
{
   delete [] itsString;
   itsLen = 0;
}

//Operator =, l�mmnar tillbaka existerande minne, kopierar sedan str�ngen och storleken
String & String::operator = (const String & rhs)
{
   if (this == &rhs)
      return *this;
   delete [] itsString;
   itsLen = rhs.getLen();
   itsString = new char[itsLen+1];
   for (unsigned short i = 0; i < itsLen; i++)
      itsString[i] = rhs[i];
   itsString[itsLen] = '\0';
   return *this;
}

//Icke konstant indexoperator, returnerar en referens till teknet s� att det g�r att �ndra
char & String::operator [] (unsigned short offset)
{
   if (offset  > itsLen)
      return itsString[itsLen-1];
   else
      return itsString[offset];
}

//Const indexoperator f�r annv�ndning p� const-objekt ( se kopieringkonstruerare)
char String::operator [] (unsigned short offset) const
{
   if (offset  > itsLen)
      return itsString[itsLen-1];
   else
      return itsString[offset];
}

//Skapar en ny str�ng genom att l�gga rhs till den aktuella str�ngen.
String String::operator + ( const String& rhs)
{
   unsigned short totalLen = itsLen + rhs.getLen();
   String temp(totalLen);
   unsigned short i;
   for ( i = 0; i < itsLen; ++i)
      temp[i] = itsString[i];
   for (unsigned short j = 0; j < rhs.getLen(); ++j, ++i)
      temp[i] = rhs[j];
   temp[totalLen] = '\0';
   return temp;
}

//�ndrar den aktuella str�ngen, returnerar ingenting
void String::operator += (const String& rhs)
{
   unsigned short rhsLen = rhs.getLen();
   unsigned short totalLen = itsLen + rhsLen;
   String temp(totalLen);
   unsigned short i;
   for (i = 0; i < itsLen; ++i)
      temp[i] = itsString[i];
   for (unsigned short j = 0; j < rhs.getLen(); ++j, ++i)
      temp[i] = rhs[i-itsLen];
   temp[totalLen] = '\0';
   *this = temp;
}
//L�gger till en cha och ut�kar str�ngens storlek
void String::operator += (const char initChar)
{
   itsLen += 1;
   String temp(itsLen);
   temp = *this;

   temp[itsLen-1] = initChar;
   temp[itsLen] = '\0';
   *this = temp;
}
//Kollar om tv� st�ngar �r likadana
bool String::operator == (const String& rhs)
{
   if (rhs.getLen() != this->getLen())
      return false;

   char ch1, ch2;
   for (int i=0; i < this->getLen(); ++i )
   {
      ch1 = itsString[i];
      ch2 = rhs[i];

      if (ch1 != ch2)
         return false;
   }
   return true;
}
//Testar en str�ng och en char pekare
bool String::operator == (const char * initChar)
{
   for (int i=0; i < this->getLen(); ++i )
   {
      if (itsString[i] != initChar[i] || initChar[i] == '\0')
         return false;
   }

   if (initChar[this->getLen()] != '\0')  //Testar om char pekaren �r l�ngre �n string objektet
      return false;
   else
      return true;
}
unsigned short String::getLen() const 
{
	return itsLen;
}
char* String::getString() 
{
	return itsString;
}
void String::isSwe(bool initBool) 
{ 
	sweString = initBool;
}
char String::getChar(int initLoc) 
{ 
	return (initLoc <= itsLen && initLoc >= 0) ?  itsString[initLoc] : itsString[0];
}
char String::getLastChar() 
{ 
	return itsString[itsLen]; 
}
//S�tter st�ngens l�ngd
void String::setLength(int initLen)
{
   if ( (initLen - itsLen) < 0)
      return;
   else
   {
      itsString = new char[initLen-itsLen];
      for (unsigned short i = itsLen - 1; i <= initLen - itsLen; ++i)
         itsString[i] = '\0';
      itsLen = initLen;
   }
}

//Returerar (om str�ngen best�r av bara siffror) en unsigned int som �r likadan som str�ngen fast en int
unsigned long int String::convertToInt()
{
   unsigned long int returnInt = 0;
   int tempInt = 0;
   if (itsLen > 10)  //Om str�ngen �r l�ngre �n tio kan inte variabeln unsigned int hantera den
      { return 0; }
   for (int i = itsLen - 1; i >= 0 ; --i)
   {
      switch (itsString[i])
      {
         case '0': tempInt = 0; break;
         case '1': tempInt = 1; break;
         case '2': tempInt = 2; break;
         case '3': tempInt = 3; break;
         case '4': tempInt = 4; break;
         case '5': tempInt = 5; break;
         case '6': tempInt = 6; break;
         case '7': tempInt = 7; break;
         case '8': tempInt = 8; break;
         case '9': tempInt = 9; break;
         default: return 0;   //Om den inneh�ll ett tecken avslutas funktionen
      }
      int tioPotens = 10;
   //Obs om utr�kningen inte blir noll utf�rs ber�kningen
      if (!(itsLen - 1 - i == 0))
      {
         for (int j = 1; j < itsLen - 1 - i; ++j)
            { tioPotens *= 10; }
         tempInt *= tioPotens;   //R�knar ut tio potensen
      }
      returnInt += tempInt;
   }
   return returnInt;
}

void String::putIn(char initChar, int initPlace)
{
   if (initChar != '\0' && initPlace <= itsLen)
   {
      itsLen += 1;
	  int i;
      char* temp = new char[itsLen + 1];
      for (i = 0; i < initPlace; i++)
         { temp[i] = itsString[i]; }
      temp[initPlace] = initChar;
      for (i = initPlace; i < itsLen; i++)
         { temp[i+1] = itsString[i]; }
      delete[] itsString;
      itsString = temp;
   }
}

bool String::deleteChar(int initInt)
{
   if (initInt <= itsLen && itsLen > 0 && initInt > 0)
   {
      itsLen -= 1;
	  int i;
      char* temp = new char[itsLen+1];
      for (i = 0; i < initInt-1; i++)
         { temp[i] = itsString[i]; }
      for (i = initInt; i < itsLen+1; i++)
         { temp[i-1] = itsString[i]; }
      temp[itsLen] = '\0';
      delete[] itsString;
      itsString = temp;
      return true;
   }
   else
   {  return false;  }
}

bool String::deleteLastChar()
{
   if(itsLen > 0)
   {
      itsLen -= 1;
      char* tempString = new char[itsLen+1];
      for (int i = 0; i < itsLen; i++)
         { tempString[i] = itsString[i]; }
      tempString[itsLen] = '\0';
      delete[] itsString;
      itsString = tempString;
      return true;
   }
   else
   {  return false; }
}

void String::setToNull()
{
	delete [] itsString;
	itsLen = 0;
	itsString = new char[1];
	itsString [0] = '\0';
}

void String::changeToSwe()
{
   for ( int i = 0; i < itsLen; i++)
   {
      switch (itsString[i])
      {
         case '�': itsString[i] = char(134); break;  //Det �r det nummer som annv�nds
         case '�': itsString[i] = char(143); break;  //i den svenska tecken tabellen.
         case '�': itsString[i] = char(132); break;
         case '�': itsString[i] = char(142); break;
         case '�': itsString[i] = char(148); break;
         case '�': itsString[i] = char(153); break;
      }
      }
}

unsigned long int CharToInt(char* initString)
{
   unsigned long int returnInt = 0;
   int itsLen = strlen(initString);
   int tempInt = 0;
   if (itsLen > 10)  //Om str�ngen �r l�ngre �n tio kan inte variabeln unsigned int hantera den
      { return 0; }
   for (int i = itsLen - 1; i >= 0 ; --i)
   {
      switch (initString[i])
      {
         case '0': tempInt = 0; break;
         case '1': tempInt = 1; break;
         case '2': tempInt = 2; break;
         case '3': tempInt = 3; break;
         case '4': tempInt = 4; break;
         case '5': tempInt = 5; break;
         case '6': tempInt = 6; break;
         case '7': tempInt = 7; break;
         case '8': tempInt = 8; break;
         case '9': tempInt = 9; break;
         default: return 0;   //Om den inneh�ll ett tecken avslutas funktionen
      }
      int tioPotens = 10;
   //Obs om utr�kningen inte blir noll utf�rs ber�kningen
      if (!(itsLen - 1 - i == 0))
      {
         for (int j = 1; j < itsLen - 1 - i; ++j)
            { tioPotens *= 10; }
         tempInt *= tioPotens;   //R�knar ut tio potensen
      }
      returnInt += tempInt;
   }
   return returnInt;
}

char* IntToChar(int init)
{
	String tempString("");
	int tempInt;
	bool negative;
	if(init < 0)			// Negativt tal?
		negative = true;
	else
	   negative = false;

	do
	{
		tempInt = init%10;			// F� fram sista siffran
		init -= tempInt;			// Dra bort sista siffran
		init /= 10;					// Ta bort nollan som blir d�r

		switch (tempInt)
		{
		 case 0: tempString += "0"; break;
		 case 1: tempString += '1'; break;
		 case 2: tempString += '2'; break;
		 case 3: tempString += '3'; break;
		 case 4: tempString += '4'; break;
		 case 5: tempString += '5'; break;
		 case 6: tempString += '6'; break;
		 case 7: tempString += '7'; break;
		 case 8: tempString += '8'; break;
		 case 9: tempString += '9'; break;
		}
	} while(init != 0);

	char* ret;
	if(negative)
	{
		ret = new char[tempString.getLen()+2];
		ret[0] = '-';
		for(int i = 1, j = tempString.getLen()-1; j >= 0; j--, i++)//tempString.getLen() != 0)
			ret[i] = tempString.getChar(j);

		ret[tempString.getLen()+1] = '\0';
	}
	else
	{
 		ret= new char[tempString.getLen()+1];

		for(int i = 0, j = tempString.getLen()-1; j >= 0; j--, i++)//tempString.getLen() != 0)
			ret[i] = tempString.getChar(j);

		ret[tempString.getLen()] = '\0';
	}
	return ret;
}

char* DoubleToChar(double init)
{
	String tempString("");
	double tempInit = init;
	int tempInt;
	bool negative;
	if(init < 0)			// Negativt tal?
		negative = true;
	else
	   negative = false;

	int dot = 0;
	if((init - int(init)) == 0)			// Finns det n�gon decimal?
		dot = -1;						// S� kan inte for loopen s�tta decimalen sen
	else
	{	// R�kna ut var decimalen �r
		for(int i = 0; int(tempInit) > 0 && i < 100; i++)
			tempInit /= 10;

		dot = i;

	
		// G�r om talet till int liknande
		do
		{
			tempInt = int(init);	
			tempInit = init - double(tempInt);
			init *= 10;
		} while(tempInit > 0);
	}
	do
	{
		tempInt = int(init)%10;			// F� fram sista siffran
		init -= tempInt;			// Dra bort sista siffran
		init /= 10;					// Ta bort nollan som blir d�r

		switch (tempInt)
		{
		 case 0: tempString += "0"; break;
		 case 1: tempString += '1'; break;
		 case 2: tempString += '2'; break;
		 case 3: tempString += '3'; break;
		 case 4: tempString += '4'; break;
		 case 5: tempString += '5'; break;
		 case 6: tempString += '6'; break;
		 case 7: tempString += '7'; break;
		 case 8: tempString += '8'; break;
		 case 9: tempString += '9'; break;
		}
	} while(init != 0);

	char* ret;
	if(negative)
	{
		ret = new char[tempString.getLen()+2];
		ret[0] = '-';
		for(int i = 1, j = tempString.getLen()-1; j >= 0; j--, i++)
		{
			if(i-1 == dot)
			{
				ret[i] = '.';
				j++;
			}
			else
				ret[i] = tempString.getChar(j);
		}

		ret[tempString.getLen()+1] = '\0';
	}
	else
	{
 		ret= new char[tempString.getLen()+1];

		for(int i = 0, j = tempString.getLen()-1; j >= 0; j--, i++)
		{
			if(i == dot)
			{
				ret[i] = '.';
				j++;
			}
			else
				ret[i] = tempString.getChar(j);
		}

		ret[tempString.getLen()] = '\0';
	}
	return ret;
}