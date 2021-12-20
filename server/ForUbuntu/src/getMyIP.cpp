
#include "include/getMyIP.h"

std::string getMyIP(){
ifaddrs * ifAddrStruct=NULL;
ifaddrs * ifa=NULL;
void * tmpAddrPtr=NULL;      

    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa ->ifa_addr->sa_family==AF_INET) 
          
        { // check it is IP4 is a valid IP4 Address
            tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addressBuffer[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
           
            if (ifa->ifa_name[0] !='l' && ifa->ifa_name[1] !='o')  return addressBuffer; 
           
          }
    }
  return "null";
}