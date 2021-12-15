/**
* сервер для удаленного управления клавиатурой с телефона 
* 27.09.2021
* 
* Mitroshin Aleksey (miam.devsoft@yandex.ru, lapadaviloff@yandex.ru)
*/

#include <iostream>
#include "include/test.h"
#include "include/socetServer.h"
#include "include/chat.h"
#include "include/observer.h"

int Observer::m_staticNumber = 0;

int main (int arg, char ** argv){

test ();

Chat *chat = new Chat; 
try{
SocetServer *server = new SocetServer(*chat);
server->connect();
}
catch (const char* err ){
    std::cout << "\n=> "<< err << std::endl;
}
std::cout << "\n=> main" << std::endl;
return 0;
}