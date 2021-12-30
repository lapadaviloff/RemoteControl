#include "include/testObserver.h"
TestObserver::TestObserver (Chat &chat):Observer(chat){

}
void TestObserver::update(const Message &messageFromChat) {
std::cout << "message to: " << messageFromChat.m_to << " message: " <<\
messageFromChat.m_message << std::endl;

}

