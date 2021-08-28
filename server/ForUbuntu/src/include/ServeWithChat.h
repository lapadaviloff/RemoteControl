#pragma once
#include <iostream>
#include "include/IObserver.h"
#include"include/Chat.h"
/*общий интерфейс сервера*/
class ServerWithChat:public IObserver, Chat {
     private:
     std::string m_message;
     std::string m_messageFromChat;
     Chat &m_chat;
     static int m_staticMumber;
     int m_number;
 

  public:
    virtual ~ServerWithChat(){};
    /*выдача сообщения, полученного сервером с сети */
    std::string getMessage () ;
     /*действие при появлении сообщения */
    void update(const Message &messageFromChat) override;
    /*отправка сообщения в общий чат*/
    void sendMessageToChat () override;
    /*присоеденится к чату*/
    void attachToChat() override;
    /*отсоеденится от чата*/
    void removeFromChat () override;
   
   
  
};