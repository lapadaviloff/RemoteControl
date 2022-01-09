
#include "include/test.h"

using namespace std;

void test (){
    cout << "**********TEST START************" <<endl;
    int buffer = 1024; 
    Message m{"client","from testObserver"};
    try{
    Chat *chat = new Chat; 
    TestObserver * observ1 = new TestObserver(*chat); 
    SocetServer *server = new SocetServer (
      *chat,
      buffer);

    check (getMyIP()!="null" , "getMyIP");

    check (isIP(getMyIP()) , "getMyIP::isIP");
    
    std::thread t ([&](){ 
      
        server->connect();
        server->recerv();
      
      });
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    

    TestClient * client = new TestClient();
   
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    client->sendFromClient("testObserver:fromClient");

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    check (observ1->test , "testObserver:normal message");
    //observ1->sendMessageToChat(m);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    /*
    check (client->recerv() , "testClient");
    
    
    client->sendFromClient("#");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    check (observ1->test , "testObserver:NULL message");
    */
    t.join(); 
    delete chat;
    delete observ1;
    delete client;
    delete server;
   
    
    
    }

    catch (char const *err){
      std::cout << "\n=> " << err << std::endl;
       check (0, "all");
    }
    
    cout << endl << "**********TEST PASSED***********"  << endl;
    
}
/**************************************************************************************/
void check (bool passed, std::string s){
     if(passed) cout <<  "=> " << s << ": OK" << endl << endl; 

     else{
     cout << "**********TEST ERROR***********"  << endl;
     cout << "=> " << s << ": ERROR" << endl;
     exit (-1);
     }
}