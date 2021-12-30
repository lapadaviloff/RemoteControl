#include "include/testObserver.h"
TestObserver::TestObserver (Chat &chat):Observer(chat){

}
void TestObserver::update(const Message &messageFromChat) {
std::cout << "message from: " << messageFromChat.m_to << " message: " <<\
messageFromChat.m_message << std::endl;

}

void TestObserver::createMessage(const std::string &message){\

m_messageToChat.m_to = "from testObserver";
m_messageToChat.m_message = message;
m_chat.createMessage(m_messageToChat);
}
