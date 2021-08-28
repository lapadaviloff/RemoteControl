#pragma once
#include <list>
#include "include/IChat.h"
class Chat:public IChat{
    private:
    std::list<IObserver *> m_listObserver;
    std::string m_messageToChat;

    public: 

    /*добавить класс в чат*/
    void attach(IObserver *observer) override;
    /*удалмть класс из чата*/
    void detach(IObserver *observer) override;
    /*рассылка сообщений*/
    void notify() override;
};