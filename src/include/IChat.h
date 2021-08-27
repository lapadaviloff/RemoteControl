#pragma once
#include "include/IObserver.h"
/*интерфейс чата для обмена при возникновении сообщения в классе*/
class IChat {
 public:
  virtual ~IChat(){};
  /*добавить класс в чат*/
  virtual void Attach(IObserver *observer) = 0;
  /*удалмть класс из чата*/
  virtual void Detach(IObserver *observer) = 0;
  /*рассылка сообщений*/
  virtual void Notify() = 0;
};