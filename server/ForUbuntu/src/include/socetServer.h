#pragma once
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <chrono>
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
    char *m_temp;
    
    sockaddr_in m_server_addr;
    socklen_t m_size;
    
    /*инициализация сервера*/
    void init ();
    
    /*преобразование из char* в Message*/
    Message parseMessage(std::string s);

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
    bool recerv ();
    
   
};
