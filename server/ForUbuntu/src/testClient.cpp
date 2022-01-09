#include "include/testClient.h"

TestClient ::TestClient(){
   
    m_portNum = 1500; // NOTE that the port number is same for both m_client and server
    m_bufsize = 1024;
    
    

    m_client = socket(AF_INET, SOCK_STREAM, 0);
    try{
      if (m_client < 0) {
        throw "client:Error establishing socket..." ;
        
      }
    }
    catch(char const *err){
         throw err; 
    }
    cout << "=> client:Socket testClient has been created..." << endl;
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(m_portNum);
    server_addr.sin_addr.s_addr =htons(INADDR_ANY);
   
    /* ---------- CONNECTING THE SOCKET ---------- */
    /* ---------------- connect() ---------------- */
    try{
    
    if (connect(m_client,(struct sockaddr *)&server_addr, sizeof(server_addr)) == 0)
        cout << "=> client:Connection to the server port number: " << m_portNum << endl;
    else throw "client:Error client connecting"; 
    }
    catch(char const *err){
         throw err; 
    }
    cout << "=> client:Conect to server" << endl; 
  


};
TestClient ::~TestClient(){
    close(m_client);
};

bool TestClient ::recerv(){


    if(recv(m_client, m_buffer, m_bufsize, 0)==0){
      std::cout << "=> client:Lost connect" << std::endl;
      return false;
    }  
  close(m_client);
    return true;
   


};
void TestClient ::sendFromClient(std::string s){

    strcpy(m_buffer, s.c_str());
    send(m_client, m_buffer, m_bufsize, 0);
    close(m_client);
};




    
    
