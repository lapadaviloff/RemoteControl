#pragma once
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;
/*тестовый клиент*/
class TestClient {
    int m_client;
    int m_portNum ; 
    int m_bufsize ;
    struct sockaddr_in server_addr;
    char m_buffer[1024];
public:
    TestClient();
    ~TestClient();
    
    /*прием данных от сервера*/
    bool recerv();
    
    /*отправка данных серверу*/
    void sendFromClient (std::string s);
};

