#pragma once
#include <iostream>
#include "message.h"
/*интерфейс сервера для обмена сообщений между классами (шаблон observer)*/
class IObserver {
 
 public:
 
  virtual ~IObserver(){};
  /*действие при появлении сообщения */
  virtual void update(const Message &messageFromChat) = 0;
 
};