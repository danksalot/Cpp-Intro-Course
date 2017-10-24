//////////////////////////////////////////
//                                      //
//      Jacob Danks     02/10/2011      //
//                                      //
//////////////////////////////////////////
 
#include <iostream>
#include <string.h>
 
using namespace std;
 
#include "MyUBArray.h"
 
void Func (const UBArray <int, int> &);
 
char * EXCEPT [5] = {"NoList", "NoCurrent", "NoNextElement", "NoPreviousElement", "IndexNotFound"};
 
void main ()
    {
    //Create
        UBArray <int, int>                IntInt;
        UBArray <WCS_String, float>       StringFloat;
        UBArray <double, WCS_String>  DoubleString;
     
    //Use Subscript
        IntInt [3] = 12345;
        IntInt [6] = 67890;
 
        StringFloat [6.089] = "Jacob";
        StringFloat [8.3]   = "Danks";
 
        WCS_String Larry ("Larry");
        WCS_String Donna ("Donna");
        WCS_String Marge ("Marge");
        WCS_String Hal ("Hal");
        DoubleString [Larry] = 4.9776;
        DoubleString [Donna] = 5.98;
     
    //Use At
        cout << IntInt.At (3) << endl;
        cout << IntInt.At (6) << endl;
 
        cout << StringFloat.At (6.089) << endl;
        cout << StringFloat.At (8.3) << endl;
        cout << StringFloat.At (10.4) << endl;
 
        cout << DoubleString.At (Larry) << endl;
        cout << DoubleString.At (Donna) << endl;
        cout << DoubleString.At (Marge) << endl;
 
    //Use Size and Remove       
        cout << IntInt.Size () << endl;
        cout << IntInt.Remove (6) << endl;
        cout << IntInt.Remove (4) << endl;
        cout << IntInt.Size () << endl;
 
        cout << StringFloat.Size () << endl;
        cout << StringFloat.Remove (8.3) << endl;
        cout << StringFloat.Remove (66) << endl;
        cout << StringFloat.Size () << endl;
 
        cout << DoubleString.Size () << endl;
        cout << DoubleString.Remove (Donna) << endl;
        cout << DoubleString.Remove (Hal) << endl;
        cout << DoubleString.Size () << endl;
 
    //Use Get First and Get Last
        cout << IntInt.GetFirst () << endl;
        cout << IntInt.GetLast () << endl;
 
        cout << StringFloat.GetFirst () << endl;
        cout << StringFloat.GetLast () << endl;
 
        cout << DoubleString.GetFirst () << endl;
        cout << DoubleString.GetLast () << endl;
 
    //Use Get Next and Get Previous
        try {cout << IntInt.GetPrev () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << IntInt.GetNext () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << IntInt.GetNext () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
 
        try {cout << StringFloat.GetPrev () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << StringFloat.GetNext () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << StringFloat.GetNext () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
 
        try {cout << DoubleString.GetPrev () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << DoubleString.GetNext () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << DoubleString.GetNext () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
 
    //Use Clear All
        IntInt.ClearAll ();
        StringFloat.ClearAll ();
        DoubleString.ClearAll ();
 
    //Fail Get First and Get Last
        try {cout << IntInt.GetFirst () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << IntInt.GetLast () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
 
        try {cout << StringFloat.GetFirst () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << StringFloat.GetLast () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
 
        try {cout << DoubleString.GetFirst () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << DoubleString.GetLast () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
     
    //Fail Get Next and Get Previous
        try {cout << IntInt.GetPrev () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << IntInt.GetNext () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << IntInt.GetNext () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
 
        try {cout << StringFloat.GetPrev () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << StringFloat.GetNext () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << StringFloat.GetNext () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
 
        try {cout << DoubleString.GetPrev () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << DoubleString.GetNext () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
        try {cout << DoubleString.GetNext () << endl;}
        catch (Exception E) {cout << EXCEPT [E] << endl;}
    }
 
void Func (const UBArray <int, int> & U)
    {
    int x;
 
    cout << U [5] << endl;
    x = U.GetFirst ();
    cout << x << endl;
    }
