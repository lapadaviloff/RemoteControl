#include <iostream>
class IServer {
  public:
    virtual void sendMessageToChat () = 0;
    virtual std::string getMessage () = 0;
};