#include "include/keyboardEmulator.h"
KeyboardEmularor::KeyboardEmularor(Chat &chat):
Observer(chat), 
m_command (loadCommand())
{
    
    m_xdo = xdo_new(":0.0");    

}
KeyboardEmularor::~KeyboardEmularor(){}

/*действие при появлении сообщения */
void KeyboardEmularor::update(const Message &messageFromChat) {
     
    
    if (messageFromChat.m_to == "keyboardEmulator") {
      if (m_command.find(messageFromChat.m_message) != m_command.end() ) 
      xdo_send_keysequence_window(m_xdo,
      CURRENTWINDOW, 
      m_command.at (messageFromChat.m_message).c_str(), 0);
      else std::cout << "=> KeyboardEmularor:command not found" << std::endl;

    }
} 