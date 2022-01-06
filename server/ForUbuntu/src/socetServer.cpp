#include "include/socetServer.h"


SocetServer::SocetServer(
  Chat &chat, 
  int bufSize):
  Observer(chat), 
  m_portNum (1500),
  m_bufSize(bufSize){ 
    try{
    m_temp = new char[m_bufSize];
    m_buffer = new char[m_bufSize];

    
    
    }
    catch(std::bad_alloc const &err){

         throw "server:Allocation m_buffer failure";  
    }

    init ();
}

SocetServer::~SocetServer (){

    delete[] m_buffer;
    delete[] m_temp;
    close(m_server);
    close(m_sockfd);
    

}
/*инициализация сервера*/
void SocetServer::init(){

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
    /* --------------- socket() function ------------------*/

    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    try{

    if (m_sockfd < 0) throw "server:Error establishing socket...";  
    
    }
      catch(char const *err){

         throw err; 
      }

    std::cout << "=> server:Socket server has been created..."  << std::endl;
    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = htons(m_portNum);
    m_server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    
    /* ---------- BINDING THE SOCKET ---------- */
    /* ---------------- bind() ---------------- */
    try {

      if ((bind( m_sockfd, (struct sockaddr*)&m_server_addr, sizeof(m_server_addr)))\
      < 0){
         
       throw "server:Error binding connection, the socket has already been established..."; 
      }
    }

    catch(char const *err){
         throw err; 
    }
}

/*соединение с клиентом */
void SocetServer::connect(){

    std::cout << "=> server:Looking for clients..." << std::endl;

    /* ------------- LISTENING CALL ------------- */
    /* ---------------- listen() ---------------- */

    listen(m_sockfd, 1);

    /* ------------- ACCEPTING CLIENTS  ------------- */
    /* ----------------- listen() ------------------- */

    m_server = accept(m_sockfd,(struct sockaddr *)(&m_server_addr),&m_size);

    std::cout << "=> server:Connected client "  << std::endl;
    // first check if it is valid or not
    
    if (m_server < 0)std::cout << "=> server:Error on accepting..." << std::endl;
  
}

  /*отправка и прием сообщений*/
    bool SocetServer::recerv (){
    do{
       
      if(recv(m_server, m_buffer, m_bufSize, 0)==0){
        std::cout << "=> server:Lost connect" << std::endl;
        close(m_server);
        
        return false;
      }
    
      /*получаем сообщение от клиента и отправляем в чат*/
      sendMessageToChat(parseMessage(m_buffer));
    //std::this_thread::sleep_for(std::chrono::milliseconds(200));
    strcpy(m_temp,m_buffer);
    strcpy(m_buffer, "NULL");
    if(send(m_server,m_buffer,m_bufSize, 0) == -1) recv(m_server, m_buffer, m_bufSize, 0);
    } while (*m_temp != '#'); // остановка приема
    std::cout << "=> server:Connect closed " << std::endl;
    return true;
}
void SocetServer::update(const Message &messageFromChat) {
  
  /*если пришло сообщение клиенту, отправляем сообщение */
  if(messageFromChat.m_to =="client"){
    std::string s;
    s = messageFromChat.m_to + ":" + messageFromChat.m_message;
    if(send(m_server,s.c_str(),m_bufSize, 0) == -1) recv(m_server, m_buffer, m_bufSize, 0) ;
  }
}

/*преобразование из char* в Message*/
Message SocetServer::parseMessage(std::string s){
Message m;

/*если отсутствует спец символ */
if (s.find(':') == std::string::npos){
    m.m_to = "NULL";
    m.m_message = "message error";
    return m;
}

m.m_to = s.substr(0,s.find(':')); 
m.m_message = s.erase(0, s.find(':')+1);
return m;
}
