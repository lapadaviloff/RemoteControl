 #include "include/observer.h"


    Observer::Observer(Chat &chat):m_chat(chat){
       m_messageToChat.m_to = "";
       m_messageToChat.m_message = "";
    this->m_chat.attach(this);
    std::cout << "Hi, I'm the Observer \"" << ++Observer::m_staticNumber \
    << "\".\n";
    this->m_number = Observer::m_staticNumber;
    }


    Observer::~Observer(){
    std::cout << "Goodbye, I was the Observer \"" << this->m_number << "\".\n";

    }

    /*отправка сообщения в общий чат*/
    void Observer::sendMessageToChat (const std::string &to, const std::string &message){
       Message m;
       m.m_to = to;
       m.m_message = message;
       m_chat.createMessage(m);

    }

    /*отсоеденится от чата*/
    void Observer::removeFromChat (){

    m_chat.detach(this);
    std::cout << "Observer \"" << m_number << "\" removed from the list.\n";

    }