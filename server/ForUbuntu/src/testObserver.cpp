#include "include/testObserver.h"
TestObserver::TestObserver (Chat &chat):Observer(chat),test(false){

}
/*тестовый наблюдатель*/
void TestObserver::update(const Message &messageFromChat) {
    test = true;
    std::cout << std::endl << "=> message to: " << messageFromChat.m_to << " message: " <<\
    messageFromChat.m_message << std::endl;
    
    if (messageFromChat.m_to == "testObserver") test = true;

    if (messageFromChat.m_to == "NULL") test = true;
    

}