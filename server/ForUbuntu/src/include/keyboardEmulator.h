#pragma once
#include <cstdlib>
#include "observer.h"
#include "chat.h"
#include "observer.h"

/*эмулятор клавиатуры*/
class KeynoardEmularor : public Observer {
    
     /*действие при появлении сообщения */
    void update(const Message &messageFromChat) override;
public:
     KeynoardEmularor(Chat &chat);
     ~KeynoardEmularor();
};