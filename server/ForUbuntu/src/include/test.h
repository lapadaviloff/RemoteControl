#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include "getMyIP.h"
#include "isIP.h"
#include "socetServer.h"
#include "chat.h"
#include "observer.h"
#include "testObserver.h"
#include "message.h"
#include "testClient.h"

/*тестирование кода*/
void test();

/* passed - условие, s - чье условие проверяется*/ 
void check(bool passed, std::string s);
