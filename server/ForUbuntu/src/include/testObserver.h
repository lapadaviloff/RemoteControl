#pragma once
#include "observer.h"
#include "message.h"


class TestObserver : public Observer {
 
    /*действие при появлении сообщения */
    void update(const Message &messageFromChat) override;

public:
    
    TestObserver (Chat &chat); 
   
    bool test; 
};
