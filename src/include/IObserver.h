#pragma once
#include <iostream>
#include "include/Message.h"
/*интерфейс сервера для обмена сообщений между классами (шаблон observer)*/
class IObserver {
 public:
  virtual ~IObserver(){};
  /*действие при появлении сообщения */
  virtual void Update(const Message &messageFromChat) = 0;
  /*отправка сообщения в общий чат*/
  virtual void sendMessageToChat () = 0;
  /*присоеденится к чату*/
  virtual void attachToChat() = 0;
  /*отсоеденится от чата*/
  virtual void removeFromChat () = 0;
};