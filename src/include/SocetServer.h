#pragma once
//#include <string.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <stdlib.h>
//#include <unistd.h>
#include "include/IServer.h"
#include "include/IObserver.h"
#include "include/Message.h"
/*сервер для работы через сокеты*/
class SocetServer : public IServer , public IObserver {
    private:
    std::string m_mesage;
    int client, server;
    int portNum ;
    bool isExit ;
    int bufsize ;
    char buffer[];    
    
    public:
    /*действие при появлении сообщения */
    virtual void Update(const Message &messageFromChat) override;
    /*отправка сообщения в общий чат*/
    virtual void sendMessageToChat () override;
    /*присоеденится к чату*/
    virtual void attachToChat() override;
    /*отсоеденится от чата*/
    virtual void removeFromChat () override;
    /*выдача сообщения по запросу, полученного сервером с сокета */
    virtual std::string getMessage () override; 
    
};