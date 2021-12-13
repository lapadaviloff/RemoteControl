#pragma once
#include <iostream>
#include "iobserver.h"
#include "chat.h"
/**/
class Observer:public IObserver {
     
    private:
    std::string m_message;
    std::string m_messageFromChat;
    Chat &m_chat;
    static int m_staticNumber;
    int m_number;
 

  public:
    /*выдача сообщения, полученного сервером с сети */
    std::string getMessage () ;

    Observer(Chat &chat);
    ~Observer();

     /*действие при появлении сообщения */
    void update(const Message &messageFromChat) override;
    /*отправка сообщения в общий чат*/
    void sendMessageToChat ();
    /*присоеденится к чату*/
    void attachToChat();
    /*отсоеденится от чата*/
    void removeFromChat ();
};