#pragma once
#include "observer.h"
#include "message.h"


class TestObserver : public Observer {
 

    /*действие при появлении сообщения */
    void update(const Message &messageFromChat) override;
    public:
    void createMessage(const std::string &message ="empty");
    TestObserver (Chat &chat); 

};
