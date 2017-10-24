#include <fstream>
#include <iostream>
 
using namespace std;
 
#include "RAFile.h"
 
//CONSTRUCTORS AND DECONSTRUCTOR
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
    cout << "Database has been updated and Stored" << endl;
    }
 
//FILE METHODS
void RAFile::Close ()
    {
    MyFile.seekp (0);
    MyFile.write (reinterpret_cast <char *> (&NumRecords), sizeof (NumRecords));
    MyFile.seekp (EndOfData);
 
 
    for (ULong i = 0; i < NumRecords; i++)
        {
        MyFile.write (reinterpret_cast <char *> (&RecordInfo [i]), sizeof (RecordInfo [i]));
        }
    }
 
RAFile::ULong   RAFile::Size ()
    {
    return NumRecords;
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
                            ULong   Zero (0);
                            MyFile.write (reinterpret_cast <char *> (&Zero), sizeof (Zero));
                            MyFile.close ();
                            MyFile.open ((const char *) Str, ios_base::in | ios_base::out | ios_base::ate | ios_base::binary);
                            }
                    }
            if (MyFile.tellg () >= sizeof (ULong))
                    {
                    MyFile.seekg (0);
                    MyFile.read (reinterpret_cast <char *> (&NumRecords), sizeof (NumRecords));
                    MyFile.seekg (- static_cast <long> (NumRecords * (sizeof (RecInfo))), ios_base::end);
                    EndOfData = MyFile.tellg ();
                    if (MyFile.tellg () >= sizeof (ULong))
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
                else
                    {
                    MyFile.close ();
                    return BadFileFormat;
                    }
            }
    return OK;
    }
 
//DATA METHODS
RAFile::ReturnCode RAFile::Display (ULong Index)
    {
    char temp [81];
    if (!MyFile.is_open ())
            return FileNotOpen;
        else
            if (Index >= NumRecords)
                    return IndexNotFound;
                else
                    {
                    MyFile.seekg (RecordInfo [Index].Offset);
                    MyFile.read (temp, RecordInfo [Index].Length);
                    temp [RecordInfo [Index].Length] = '\0';
                    cout << temp << endl;
                    return OK;
                    }
    }
 
RAFile::ReturnCode RAFile::SeeAll ()
    {
    if (!MyFile.is_open ())
            return FileNotOpen;
        else
            if (NumRecords == 0)
                    return FileEmpty;
                else
                    {
                    cout << endl;
                    for (int i = 0; i < NumRecords; i++)
                        {
                        cout << "Record " << i << ") ";
                        Display (i);
                        }
                    cout << endl;
                    }
    }
 
 
RAFile::ReturnCode RAFile::Replace (ULong Index, const WCS_String & S)
    {
    if (MyFile.is_open ())
            {
            if (Index < NumRecords)  //replace an existing record
                    {
                    if (RecordInfo [Index].Length <= S.Length ())
                            {
                            MyFile.seekp (RecordInfo [Index].Offset);
                            MyFile.write ((const char *) S, S.Length ());
                            RecordInfo [Index].Length = S.Length ();
                            return OK;
                            }
                        else
                            {
                            MyFile.seekp (EndOfData);
                            RecordInfo [Index].Offset = EndOfData;
                            RecordInfo [Index].Length = S.Length ();
                            MyFile.write ((const char *) S, S.Length ());
                            EndOfData = MyFile.tellp ();
                            return OK;
                            }
                    }
                else   // create a new record
                    {
                    for (ULong i = NumRecords; i < Index; i++)
                        {
                        RecordInfo [i].Length = 0;
                        RecordInfo [i].Offset = 0;
                        }
                    MyFile.seekp (EndOfData);
                    RecordInfo [Index].Offset = EndOfData;
                    RecordInfo [Index].Length = S.Length ();
                    MyFile.write ((const char *) S, S.Length ());
                    EndOfData += S.Length ();
                    NumRecords = Index + 1;
                    return OK;
                    }
            }
        else
            return FileNotOpen;
    }
 
RAFile::ReturnCode RAFile::Read (ULong I, WCS_String & S)
    {
    if (MyFile.is_open ())
            {
            if (I < NumRecords)
                    if (RecordInfo [I].Length > 0)
                            {
                            char * pChar = new char [RecordInfo [I].Length + 1];
                            MyFile.seekg (RecordInfo [I].Offset);
                            MyFile.read (pChar, RecordInfo [I].Length);
                            pChar [RecordInfo [I].Length] = '\0';
                            S = pChar;
                            delete [] pChar;
                            return OK;
                            }
                        else
                            {
                            S = "";
                            return OK;
                            }
                else
                    return IndexNotFound;
            }
            else
                return FileNotOpen;
    }
 
RAFile::ReturnCode RAFile::Insert (ULong Index, const WCS_String & S)
    {
    if (MyFile.is_open ())
        {
        if (Index < NumRecords) // insert where current record is
                {
                for (int i = NumRecords + 1; i > Index; i--)
                    {
                    RecordInfo [i].Offset = RecordInfo [i - 1].Offset;
                    RecordInfo [i].Length = RecordInfo [i - 1].Length;
                    }
                MyFile.seekp (EndOfData);
                RecordInfo [Index].Offset = EndOfData;
                RecordInfo [Index].Length = S.Length ();
                MyFile.write ((const char *) S, S.Length ());
                EndOfData = MyFile.tellp ();
                NumRecords++;
                return OK;
                }
            else   // create a new record
                {
                for (ULong i = NumRecords; i < Index; i++)
                    {
                    RecordInfo [i].Length = 0;
                    RecordInfo [i].Offset = 0;
                    }
                MyFile.seekp (EndOfData);
                RecordInfo [Index].Offset = EndOfData;
                RecordInfo [Index].Length = S.Length ();
                MyFile.write ((const char *) S, S.Length ());
                EndOfData += S.Length ();
                NumRecords = Index + 1;
                return OK;
                }
            }
        else
            return FileNotOpen;
    }
