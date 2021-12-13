#pragma once
#include <string.h>
//#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <stdlib.h>
//#include "chat.h"
#include <unistd.h>
#include "observer.h"
#include "message.h"


/*сервер для работы через сокеты*/
class SocetServer : public Observer {
 

    /*переменные из <sys/socket.h>*/
    
    int m_client;
    int m_server;
    int m_portNum;
    bool m_isExit;
    int m_bufSize;
    char *m_buffer; 

    /* ---------- INITIALIZING VARIABLES ---------- */

    /*  
       1. client/server are two file descriptors
       These two variables store the values returned 
       by the socket system call and the accept system call.
       2. portNum is for storing port number on which
       the accepts connections
       3. isExit is bool variable which will be used to 
       end the loop
       4. The server reads characters from the socket 
       connection into a dynamic variable (buffer).
       5. A sockaddr_in is a structure containing an internet 
       address. This structure is already defined in netinet/in.h, so
       we don't need to declare it again.
        DEFINITION:
        struct sockaddr_in
        {
          short   sin_family;
          u_short sin_port;
          struct  in_addr sin_addr;
          char    sin_zero[8];
        };
        6. serv_addr will contain the address of the server
        7. socklen_t  is an intr type of width of at least 32 bits
    */

    sockaddr_in m_server_addr;
    socklen_t m_size;
    
  

    public:
    SocetServer(Chat &chat);
    ~SocetServer();
    void connect ();

};
