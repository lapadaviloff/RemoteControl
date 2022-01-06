 #include "include/observer.h"


Observer::Observer(Chat &chat):m_chat(chat){
    m_messageToChat.m_to = "";
    m_messageToChat.m_message = "";
    this->m_chat.attach(this);
   
    this->m_number = Observer::m_staticNumber;
}


Observer::~Observer(){
   

}

/*отправка сообщения в общий чат*/
void Observer::sendMessageToChat (const Message &message){
    
    m_chat.createMessage(message);

}

/*отсоеденится от чата*/
void Observer::removeFromChat (){

    m_chat.detach(this);
    std::cout << "Observer \"" << m_number << "\" removed from the list.\n";

}