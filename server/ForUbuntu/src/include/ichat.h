#pragma once
#include "include/iobserver.h"
/*интерфейс чата для обмена при возникновении сообщения в классе*/
class IChat {
 
 public:
 
  virtual ~IChat(){};
  /*добавить класс в чат*/
  virtual void attach(IObserver *observer) = 0;
  /*удалмть класс из чата*/
  virtual void detach(IObserver *observer) = 0;
  /*рассылка сообщений*/
  virtual void notify() = 0;
};