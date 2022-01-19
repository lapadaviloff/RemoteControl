#pragma once
#include <cstdlib>
#include <map>
extern "C" {
#include <xdo.h>
}
#include "observer.h"
#include "chat.h"
#include "observer.h"
#include "loadCommand.h"

/*эмулятор клавиатуры*/
class KeyboardEmularor : public Observer {
    const std::map<std::string, std::string> m_command; //список команд
    xdo_t * m_xdo;                                      // экземпляр для эмулятора клавиатуры


     /*действие при появлении сообщения */
    void update(const Message &messageFromChat) override;

public:
     KeyboardEmularor(Chat &chat);
     ~KeyboardEmularor();
};