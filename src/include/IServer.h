#pragma once
#include <iostream>
/*общий интерфейс сервера*/
class IServer {
  public:
    ~IServer(){};
    /*выдача сообщения, полученного сервероа с сокета */
    virtual std::string getMessage () = 0;
    
  
};