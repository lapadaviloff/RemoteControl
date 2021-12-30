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

   
     /*действие при появлении сообщения */
   /*
    void Observer::update(const Message &messageFromChat) {


    }
    */


    /*отправка сообщения в общий чат*/
    void Observer::sendMessageToChat (Message &message){
       m_chat.createMessage(message);

    }

    /*отсоеденится от чата*/
    void Observer::removeFromChat (){

    m_chat.detach(this);
    std::cout << "Observer \"" << m_number << "\" removed from the list.\n";

    }