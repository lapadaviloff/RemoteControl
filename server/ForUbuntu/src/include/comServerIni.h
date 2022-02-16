#pragma once
#include <map>
#define  B0	    0000000		/* скорость сом-порта */
#define  B50	0000001
#define  B75	0000002
#define  B110	0000003
#define  B134	0000004
#define  B150	0000005
#define  B200	0000006
#define  B300	0000007
#define  B600	0000010
#define  B1200	0000011
#define  B1800	0000012
#define  B2400	0000013
#define  B4800	0000014
#define  B9600	0000015
#define  B19200	0000016
#define  B38400	0000017

struct {
    int numBit = 34;
    const char* comPort = "/dev/ttyUSB0";
    unsigned int speed = B9600;
    
    std:: map<std::string, std::string> HexToCommannd {
        {"00 f0 f0 f0 f0 f0 f0 f0 f0 00 00 00 00 00 00 00 00 00 f0 00 f0 f0 f0 f0 f0 f0 00 f0 00 00 00 00 00 00 ", "VolUp"},
        {"00 f0 f0 f0 f0 f0 f0 f0 f0 00 00 00 00 00 00 00 00 f0 00 f0 f0 f0 f0 f0 f0 00 f0 00 00 00 00 00 00 00 ", "VolDown"},
        {"00 f0 f0 f0 f0 f0 f0 f0 f0 00 00 00 00 00 00 00 00 f0 f0 f0 f0 f0 f0 00 f0 00 00 00 00 00 00 f0 00 00 ", "FullScreen"},
        {"00 f0 f0 f0 f0 f0 f0 f0 f0 00 00 00 00 00 00 00 00 f0 00 f0 00 f0 f0 f0 f0 00 f0 00 f0 00 00 00 00 00 ", "RL"},
        {"00 f0 f0 f0 f0 f0 f0 f0 f0 00 00 00 00 00 00 00 00 f0 00 00 00 00 f0 f0 f0 00 f0 f0 f0 f0 00 00 00 00 ", "RR"},
        {"00 f0 f0 f0 f0 f0 f0 f0 f0 00 00 00 00 00 00 00 00 00 f0 f0 00 f0 f0 f0 f0 f0 00 00 f0 00 00 00 00 00 ", "Play"},
        {"00 f0 f0 f0 f0 f0 f0 f0 f0 00 00 00 00 00 00 00 00 00 f0 00 00 00 f0 f0 f0 f0 00 f0 f0 f0 00 00 00 00 ", "Next"},
        {"00 f0 f0 f0 f0 f0 f0 f0 f0 00 00 00 00 00 00 00 00 f0 00 00 f0 00 f0 f0 f0 00 f0 f0 00 f0 00 00 00 00 ", "Mute"}
         };
      
     
} comServerIni;