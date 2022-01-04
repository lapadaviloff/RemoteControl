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
#include "include/getMyIP.h"
#include "include/isIP.h"
#include "include/testObserver.h"
#include <chrono>
#include <thread>


int Observer::m_staticNumber = 0;


int main (int argc, char * argv[]){
std::string ip ="";
/*
 for (int i = 1; i < argc; i++){  
  
    if (strcmp(argv[i], "-local") == 0){       
            
            std::string ip = getMyIP();
            std::cout << "ip = "<<  getMyIP() << std::endl;         
            
        }
   if (strcmp(argv[i], "-h") == 0){       
           
            std::cout << "help "<< std::endl;          
            
        }
    
   if (i + 1 != argc){
        if (strcmp(argv[i], "-ip") == 0 && isIP(argv[i + 1])){ // This is your parameter name
           
            std::string ip = argv[i + 1];
            std::cout << "ip = "<<  argv[i + 1] << std::endl;  // The next value in the array is your value
            i++;    // Move to the next flag
        }
    }
}
*/
test ();
//std::cout <<"=> my IP : " <<  getMyIP() << std::endl; 
Chat *chat = new Chat; 
TestObserver * observ1 = new TestObserver(*chat); 

bool needConnect = true;  //необходимость соединения с клиентом
bool firstConnect = true; //первый запуск программы
int buffer = 1024;        //размер буфера сообщения клиент-сервер

try{
    SocetServer *server = new SocetServer (
    *chat,
    buffer); 
    std::thread t;
    
    do{
        if (needConnect){     //если нужно соединение с клиентом
          if (firstConnect)firstConnect = false;
          else t.join();        //соединить поток если не в первый раз
         needConnect = false;
         server->connect();
         t = std::thread ([&](){ //передача обмена с клиентом в поток
             server->send_recerv();
             needConnect = true;
         });
        
        }
    /*получение сообщений от других источников для клиента*/    
    observ1->sendMessageToChat("client","hello)");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    } while(1); // определить условие выхода!!!
t.join();
delete server;
}
catch (const char* err ){
    std::cout << "\n=> "<< err << std::endl;
  
}

delete chat;
std::cout << "\n=> main" << std::endl;

return 0;
}