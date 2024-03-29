#pragma once
#include <list>
#include "ichat.h"
#include "message.h"

/*чат для обмена при возникновении сообщения в классе*/
class Chat:public IChat{
    
private:
    std::list<IObserver *> m_listObserver;
    Message m_messageToChat;


public: 
    Chat();
    ~Chat();

    /*добавить класс в чат*/
    void attach(IObserver *observer) override;

    /*удалмть класс из чата*/
    void detach(IObserver *observer) override;

    /*рассылка сообщений*/
    void notify() override;

     /*создание сообщения в чат */
    void createMessage(const Message &message);
};
