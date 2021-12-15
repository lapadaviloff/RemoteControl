 #include "include/observer.h"


    Observer::Observer(Chat &chat):m_chat(chat){
    this->m_chat.attach(this);
    std::cout << "Hi, I'm the Observer \"" << ++Observer::m_staticNumber \
    << "\".\n";
    this->m_number = Observer::m_staticNumber;
    }


    Observer::~Observer(){


    }


     /*действие при появлении сообщения */
    void Observer::update(const Message &messageFromChat) {


    }


    /*отправка сообщения в общий чат*/
    void Observer::sendMessageToChat (){


    }


    /*присоеденится к чату*/
    void Observer::attachToChat(){


    }


    /*отсоеденится от чата*/
    void Observer::removeFromChat (){



    }