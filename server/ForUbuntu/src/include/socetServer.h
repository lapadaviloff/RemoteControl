#pragma once
//#include <string.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <stdlib.h>
//#include <unistd.h>
#include "include/serverWithChat.h"

#include "include/message.h"
/*сервер для работы через сокеты*/
class SocetServer : public ServerWithChat {
 

    /*переменные из <sys/socket.h>*/
    int m_client;
    int m_server;
    int m_portNum ;
    bool m_isExit ;
    int m_bufsize ;
    char m_buffer[];    
    
    public:
    void connect ();

};
