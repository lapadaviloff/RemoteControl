/**
* сервер для удаленного управления клавиатурой с телефона 
* для работы необходимо установить xdotool
* 06.01.2022 
* Mitroshin Aleksey (miam.devsoft@yandex.ru, lapadaviloff@yandex.ru)
*/

#include <iostream>
#include <chrono>
#include <thread>
#include "include/test.h"
#include "include/socetServer.h"
#include "include/chat.h"
#include "include/observer.h"
#include "include/getMyIP.h"
#include "include/isIP.h"
#include "include/testObserver.h"
#include "include/message.h"
#include "include/keyboardEmulator.h"


int Observer::m_staticNumber = 0; 

int main (int argc, char * argv[]){
if(std::system("xdotool key space") == 32512){
  std::cout << "xdotool not install, use sudo apt install xdotool" << std::endl;
  exit(-1);

}
//test (); //выполнение тестов

std::cout <<"=> my IP : " <<  getMyIP() << std::endl; 

try{
Chat *chat = new Chat;
KeynoardEmularor * keyboardEmulator = new KeynoardEmularor(*chat);
bool needConnect = true;  //необходимость соединения с клиентом
bool firstConnect = true; //первый запуск программы
int buffer = 1024;        //размер буфера сообщения клиент-сервер
bool isExit = true;      //флаг завершения программы

    SocetServer *server = new SocetServer (
    *chat,
    buffer); 

    std::thread t;
     
    
    do{
        if (needConnect){     //если нужно соединение с клиентом
          
          if (firstConnect)firstConnect = false;
          else t.join();        //соединить поток если не в первый раз
                                //для гарантированного завершения
         
             needConnect = false;
         

         t = std::thread ([&](){ //передача обмена с клиентом в поток
             server->connect();
             isExit = server->recerv();
             needConnect = true;
             
             
         });
        
        }
   
    /*получение сообщений от других источников для клиента*/    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    } while(isExit); 

t.join();
delete server;
delete keyboardEmulator;
delete chat;

}
catch (char const *err ){
    std::cout << "\n=> " << err << std::endl;
  
}
std::cout << "main " << std::endl;
return 0;
}