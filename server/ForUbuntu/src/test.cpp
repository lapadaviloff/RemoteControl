
#include "include/test.h"

using namespace std;

void test (){
    
    cout << "**********TEST START************" <<endl;
   
    check (getMyIP()!="null" , "getMyIP");

    check (isIP(getMyIP()) , "getMyIP::isIP");
    
    cout << "**********TEST PASSED***********" <<endl;
}

/**************************************************************************************/
void check (bool passed, std::string s){
     if(passed) cout << "=> " << s << ": OK" << endl;

     else{
     cout << "**********TEST ERROR***********"  << endl;
     cout << "=> " << s << ": ERROR" << endl;
     exit (-1);
     }
}