
    #include "include/chat.h"
    

    Chat::Chat(){}
    Chat::~Chat(){};


    /*добавить класс в чат*/
    void Chat::attach(IObserver *observer) {
m_listObserver.push_back(observer);
    }


    /*удалмть класс из чата*/
    void Chat::detach(IObserver *observer) {
m_listObserver.remove(observer);
    }


    /*рассылка сообщений*/
    void Chat::notify() {
 std::list<IObserver *>::iterator iterator = m_listObserver.begin();
   // HowManyObserver();
    while (iterator != m_listObserver.end()) {
      (*iterator)->update(m_messageToChat);
      ++iterator;
    }

    }
  /*создание сообщения в чат */
 void Chat::createMessage(Message message){
 this->m_messageToChat = message;
    notify();

 }

