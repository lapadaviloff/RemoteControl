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
    
    /*инициализация сервера*/
    void init ();

protected:
   
    
    /*действие при появлении сообщения */
    void update(const Message &messageFromChat) override;

public:
    SocetServer(
        Chat &chat, 
        int bufSize);
    ~SocetServer();
    /*соединение с клиентом*/
    void connect ();
    /*отправка и прием сообщений*/
    void send_recerv ();
};
