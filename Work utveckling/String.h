         ////////////////////////////////////////////////////////
         //                                                    //
         //       Fil: "SiTiString.h"                          //
         //                                                    //
         //       Författad av: Andreas Sehr 2002,01,19        //
         //                                                    //
         //       Senast ändrad: 2003,04,29                    //
         //                                                    //
         ////////////////////////////////////////////////////////
#ifndef Addes_String_H
#define Addes_String_H

// Grundläggande strängklass
class String
{
   public:
      //Konstruerare
      String();
      String(const char* const);
      String(const String &);
      String (unsigned short);
      ~String();

      //Överlagrade Operatorer
      char & operator [] (unsigned short offset);
      char operator [] (unsigned short offset) const;
      String operator + (const String&);
      void operator += (const String&);
      void operator += (const char);
      String & operator = (const String &);
      bool operator == (const String &);
      bool operator == (const char*);

      //Generälla åtkomstmetoder
      unsigned short getLen() const;
      char * getString();

      //Egna Funktioner Made by Ande_vega(Andreas Sehr)
      unsigned long int convertToInt();   //Klarar tyvär bara av positiva tal...
      void isSwe(bool initBool);
      void setToNull ();
      void putIn(char initChar, int initPlace);
      bool deleteChar(int initInt);
      bool deleteLastChar();
      void setLength(int initLen);
      void changeToSwe();
      char getChar(int initLoc) ;
      char getLastChar();
   private:
      char * itsString;
      unsigned short itsLen;
      bool sweString;
};

unsigned long int CharToInt(char* initString);
char* IntToChar(int init);
char* DoubleToChar(double init);

#endif /* !Addes_String_Hpp */