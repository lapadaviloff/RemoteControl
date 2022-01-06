#pragma once
#include <iostream>
#include "iobserver.h"
#include "chat.h"

/*слушатель чата*/
class Observer:public IObserver {
     
private:

    static int m_staticNumber;
    int m_number;
 
protected:

   Message m_messageToChat; //сообщение для чата
   Chat &m_chat;

    Observer(Chat &chat);
    ~Observer();

    /*выдача сообщения, полученного сервером с сети */
    std::string getMessage () ;
    
    /*действие при появлении сообщения */
    virtual void update(const Message &messageFromChat) = 0;
    
public:

    /*отправка сообщения в общий чат*/
    void sendMessageToChat (const Message &message);
    
    /*отсоеденится от чата*/
    void removeFromChat ();
};