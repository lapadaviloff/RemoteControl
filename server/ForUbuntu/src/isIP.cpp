#include "include/isIP.h"


bool isIP (std::string s){


int n(0);
while (s.find('.')!=std::string::npos){
    if(!is_number(s.substr(0,s.find('.')))) return false;
    s.erase(0, s.find('.')+1);
    ++n;
}
if(!is_number(s.substr(0,s.find('.'))) || n !=3  ) return false;
return true;

}


bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}