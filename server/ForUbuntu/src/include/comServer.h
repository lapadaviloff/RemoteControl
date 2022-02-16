#pragma once
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h> 
#include <cstring>
#include <sstream>
#include <algorithm>
#include "comServerIni.h"
#include "message.h"
#include "observer.h"
class ComServer : public Observer {

    int m_fd;
    struct termios m_term;
    
    int m_res;
    int m_countBuf = 0;
    int m_countTempBuf = 0;
    std::string m_command;
    unsigned char m_buf[512];
    unsigned char m_tempBuf[512];
    
   std::string decToHex (unsigned char dec);

protected:
      
    /*действие при появлении сообщения */
    void update(const Message &messageFromChat) override;

public:
   ComServer(Chat &chat);
   void run (); 
};