#include <fstream>
#include <iostream>
 
using namespace std;
 
#include <MyUBArray.h>
#include <WCS_String.h>
 
class RAFile
    {
    public:
        enum ReturnCode {OK, FileAlreadyOpen, FileCannotBeOpened, BadFileFormat, FileNotOpen, IndexNotFound, FileEmpty};
    private:
        typedef unsigned long   ULong;
        struct RecInfo
            {
            ULong   Offset;
            ULong   Length;
            };
    public:
                    RAFile  ();
                    RAFile  (const WCS_String &);
                    ~RAFile ();
        void        Close   ();
        bool        NotOK   ();
        bool        IsOpen  ();
        bool        OpenOK  ();
        ULong       Size    ();
        ReturnCode  SeeAll  ();
        ReturnCode  Open    (const WCS_String &);
        ReturnCode  Read    (ULong, WCS_String &);
        ReturnCode  Replace (ULong, const WCS_String &);
        ReturnCode  Insert  (ULong, const WCS_String &);
        ReturnCode  Display (ULong);
    private:
                    RAFile      (const RAFile &);
        RAFile &    operator =  (const RAFile &);
 
        fstream                     MyFile;
        ULong                       NumRecords;
        ULong                       EndOfData;
        UBArray <RecInfo, ULong>  RecordInfo;
    };
 
inline bool RAFile::IsOpen ()
    {
    return MyFile.is_open ();
    }
 
inline bool RAFile::NotOK ()
    {
    return !MyFile.good ();
    }
 
inline bool RAFile::OpenOK ()
    {
    return MyFile.good ();
    }
