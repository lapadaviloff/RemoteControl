
#pragma once
#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string> 

/*получение локального IP адпеса*/
std::string getMyIP ();