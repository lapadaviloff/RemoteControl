#pragma once
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <stdlib.h>
//#include "chat.h"
#include <fcntl.h>
#include <unistd.h>
#include "observer.h"
#include "message.h"


/*сервер для работы через сокеты*/
class SocetServer : public Observer {
 

    /*переменные из <sys/socket.h>*/
    int m_sockfd;
    int m_server;
    int m_portNum;
    int m_bufSize;
    char *m_buffer; 
    
    sockaddr_in m_server_addr;
    socklen_t m_size;
    
    char *m_fromClient;  //сообщение от клиента
    char *m_toClient;    //сообщение для клиента.эти два сообщения для 
                         //внешней связи в thead 
    
    /*инициализация сервера*/
    void init ();

    public:
    
    SocetServer(
        Chat &chat, 
        char * fromClient,
        char * toClient,
        int bufSize);
    
    ~SocetServer();
   
    /*соединение с клиентом*/
    void connect ();
    /*отправка и прием сообщений*/
    void send_recerv ();
    

};
