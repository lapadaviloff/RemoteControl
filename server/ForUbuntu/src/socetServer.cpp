#include "include/socetServer.h"


SocetServer::SocetServer(
  Chat &chat, 
  char * fromClient,
  char * toClient,
  int bufSize):

  Observer(chat), 
  m_portNum (1500),
  m_bufSize(bufSize),
  m_fromClient(fromClient),
  m_toClient(toClient)


{ 
    try{
    
    m_buffer = new char[m_bufSize];
    
    }
    catch(std::bad_alloc const &err){

         throw "Allocation m_buffer failure";  
    }

    init ();
}

SocetServer::~SocetServer () {

    delete[] m_buffer;
    close(m_sockfd);

}
void SocetServer::init() {

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
    /* --------------- socket() function ------------------*/

    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    try{

    if (m_sockfd < 0) throw "Error establishing socket...";  
    
    }
      catch(const char* err){

         throw err; 
       }

     std::cout << "\n=> Socket server has been created..."  << std::endl;

    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = htons(m_portNum);
    m_server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    
    /* ---------- BINDING THE SOCKET ---------- */
    /* ---------------- bind() ---------------- */
    try {

    if ((bind( m_sockfd, (struct sockaddr*)&m_server_addr, sizeof(m_server_addr)))\
     < 0) 
    {
       throw "Error binding connection, the socket has already been established..."; 
    }
    }

    catch(const char* err){

         throw err; 
       }
}
    void SocetServer::connect(){

    std::cout << "=> Looking for clients..." << std::endl;

    /* ------------- LISTENING CALL ------------- */
    /* ---------------- listen() ---------------- */

    listen(m_sockfd, 1);

    /* ------------- ACCEPTING CLIENTS  ------------- */
    /* ----------------- listen() ------------------- */

    m_server = accept(m_sockfd,(struct sockaddr *)(&m_server_addr),&m_size);

       std::cout << "=> Connected client "  << std::endl;
    // first check if it is valid or not
    if (m_server < 0) 
        std::cout << "=> Error on accepting..." << std::endl;

}


void SocetServer::send_recerv (){
       
       do{
       
        if(recv(m_server, m_buffer, m_bufSize, 0)==0){
           std::cout << "=> lost connect" << std::endl;
           close(m_server);
           break;
        }
        strcpy(m_fromClient, m_buffer);
        std::cout << m_fromClient << std::endl;
        strcpy(m_buffer, m_toClient);
        
        send(m_server, m_buffer, m_bufSize, 0);

       } while (m_fromClient[0] != '#');
        std::cout << "=> connect closed " << std::endl;
        /* ---------------- CLOSE CALL ------------- */
        /* ----------------- close() --------------- */
 close(m_server);
}
