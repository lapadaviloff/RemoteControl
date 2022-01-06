#include "include/keyboardEmulator.h"
KeynoardEmularor::KeynoardEmularor(Chat &chat):Observer(chat){}
KeynoardEmularor::~KeynoardEmularor(){}

/*действие при появлении сообщения */
void KeynoardEmularor::update(const Message &messageFromChat) {
    
    if (messageFromChat.m_to == "keyboardEmulator") {
   
     std::string s = "xdotool key "+messageFromChat.m_message;
     std::system(s.c_str());
    }
}