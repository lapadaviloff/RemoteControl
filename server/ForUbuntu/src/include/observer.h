#pragma once
#include <iostream>
#include "iobserver.h"
#include "chat.h"
/**/
class Observer:public IObserver {
     
    private:
    //std::string m_message;
    //std::string m_messageFromChat;
   
    static int m_staticNumber;
    int m_number;
 
  public:
   Message m_messageToChat;
   Chat &m_chat;

    /*выдача сообщения, полученного сервером с сети */
    std::string getMessage () ;

    Observer(Chat &chat);
    ~Observer();

     /*действие при появлении сообщения */
    virtual void update(const Message &messageFromChat) = 0;
    /*отправка сообщения в общий чат*/
    void sendMessageToChat (Message &message);
    /*отсоеденится от чата*/
    void removeFromChat ();
};