#include <fstream>
#include <iostream>
 
using namespace std;
 
#include "RAFile.h"
 
RAFile::RAFile (): NumRecords (0)
    {
    }
 
RAFile::RAFile (const WCS_String & Str)
    {
    ReturnCode Ret;
 
    Ret = Open (Str);
    if (Ret != OK)
            throw (Ret);
        else;
    }
 
RAFile::~RAFile ()
    {
    Close ();
    }
 
void RAFile::Close ()
    {
    }
 
RAFile::ReturnCode RAFile::Open (const WCS_String & Str)
    {
    if (MyFile.is_open ())
            return FileAlreadyOpen;
        else
            {
            MyFile.open ((const char *) Str, ios_base::in | ios_base::out | ios_base::ate | ios_base::binary);
            if (!MyFile.is_open ())
                    {
                    MyFile.clear ();
                    MyFile.open ((const char *) Str, ios_base::out);
                    if (!MyFile.is_open ())
                            return FileCannotBeOpened;
                        else
                            {
                            ULong Zero (0);
                            MyFile.write ((const char *) & Zero, sizeof (ULong));
                            MyFile.close ();
                            MyFile.open ((const char *) Str, ios_base::in | ios_base::out | ios_base::ate | ios_base::binary);
                            }
                    }
            if (MyFile.tellg () > sizeof (ULong))  //make sure it has num of records data
                {
                MyFile.seekg (0);  // go to beginning
                MyFile.read ((char *) &NumRecords, sizeof (NumRecords));  //read num of records
                MyFile.seekg (- static_cast <long> (NumRecords * (sizeof (RecInfo))), ios_base::end);  //go to end and back up to the beginning of record info
                EndOfData = MyFile.tellg ();
                if (MyFile.tellg () > sizeof (ULong))
                        {
                        for (ULong i = 0; i < NumRecords; i++)
                            MyFile.read (reinterpret_cast <char *> (&RecordInfo [i]), sizeof (RecInfo));
                        }
                    else
                        {
                        MyFile.close ();
                        return BadFileFormat;
                        }
                    }
            }
    }
 
RAFile::ReturnCode RAFile::Replace (ULong I, const WCS_String & S)
    {
    if (MyFile.is_open ())
            {
            if (I < NumRecords)  //replace an existing record
                    {
                    if (RecordInfo [I].Length () <= S.Length ())
                            {
                            MyFile.seekp (RecordInfo [I].Offset);
                            MyFile.write ((const char *) S, S.Length ());
                            RecordInfo [I].Length = S.Length ();
                            }
                        else
                            {
                            MyFile.seekp (EndOfData);
                            RecordInfo [I].Offset = EndOfData;
                            RecordInfo [I].Length = S.Length ();
                            MyFile.write ((const char *) S, S.Length ());
                            EndOfData = MyFile.tellp ();
                            }
                    }
                else
                    {
                    for (ULong i = NumRecords; i < I; i++)
                        {
                        RecordInfo [i].Length = 0;
                        RecordInfo [i].Offset = 0;
                        }
                    MyFile.seekp (EndOfData);
                    RecordInfo [I].Offset = EndOfData;
                    RecordInfo [I].Length = S.Length ();
                    MyFile.write ((const char *) S, S.Length ());
                    EndOfData += S.Length ();
                    NumRecords = I + 1;
                    }
 
            }
        else
            return FileNotOpen;
    }
 
RAFile::ReturnCode RAFile::Read (ULong I, WCS_String & S)
    {
    if (MyFile.is_open ())
            {
            if (I < NumRecords)  //check if index exists
                {
                if (RecordInfo [I] > 0)
                        {
                        char * pChar = new char [RecordInfo [I].Length + 1];
                        MyFile.seekg (RecordInfo [I].Offset);
                        MyFile.read (pChar, RecordInfo [I].Length);
                        pChar [RecordInfo [I].Length] = '/0';
                        S = pChar;
                        delete [] pChar;
                        }
                    else
                        S = "";
                 
            }
        else
            return FileNotOpen;
    }
