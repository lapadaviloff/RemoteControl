#include "include/socetServer.h"


SocetServer::SocetServer(Chat &chat):Observer(chat), m_portNum (1500),\
m_isExit(false),m_bufSize(1024) 
{
    try{
    m_buffer = new char[m_bufSize];
    }
   catch(std::out_of_range const&)
    {    std ::cout <<  "Allocation failure " << std::endl;
          abort();
    }
}

SocetServer::~SocetServer () {

delete[] m_buffer;

}

void SocetServer::connect(){
  
    

    /* ---------- ESTABLISHING SOCKET CONNECTION ----------*/
    /* --------------- socket() function ------------------*/

    m_client = socket(AF_INET, SOCK_STREAM, 0);

    if (m_client < 0) 
    {
        std::cout << "\nError establishing socket..." << std::endl;
        exit(1);
    }

    /*
        The socket() function creates a new socket.
        It takes 3 arguments,
            a. AF_INET: address domain of the socket.
            b. SOCK_STREAM: Type of socket. a stream socket in 
            which characters are read in a continuous stream (TCP)
            c. Third is a protocol argument: should always be 0. The 
            OS will choose the most appropiate protocol.
            This will return a small integer and is used for all 
            references to this socket. If the socket call fails, 
            it returns -1.
    */

    std::cout << "\n=> Socket server has been created..." << std::endl;

    /* 
        The variable serv_addr is a structure of sockaddr_in. 
        sin_family contains a code for the address family. 
        It should always be set to AF_INET.
        INADDR_ANY contains the IP address of the host. For 
        server code, this will always be the IP address of 
        the machine on which the server is running.
        htons() converts the port number from host byte order 
        to a port number in network byte order.
    */

    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    m_server_addr.sin_port = htons(m_portNum);

    /* ---------- BINDING THE SOCKET ---------- */
    /* ---------------- bind() ---------------- */


    if ((bind(m_client, (struct sockaddr*)&m_server_addr,sizeof(m_server_addr))) \
    < 0) 
    {
        std::cout << "=> Error binding connection, the socket has already \
been established..." << std::endl;
        
    }

    /* 
        The bind() system call binds a socket to an address, 
        in this case the address of the current host and port number 
        on which the server will run. It takes three arguments, 
        the socket file descriptor. The second argument is a pointer 
        to a structure of type sockaddr, this must be cast to
        the correct type.
    */

    m_size = sizeof(m_server_addr);
    std::cout << "=> Looking for clients..." << std::endl;

    /* ------------- LISTENING CALL ------------- */
    /* ---------------- listen() ---------------- */

    listen(m_client, 1);

    /* 
        The listen system call allows the process to listen 
        on the socket for connections. 
        The program will be stay idle here if there are no 
        incomming connections.
        The first argument is the socket file descriptor, 
        and the second is the size for the number of clients 
        i.e the number of connections that the server can 
        handle while the process is handling a particular 
        connection. The maximum size permitted by most 
        systems is 5.
    */

    /* ------------- ACCEPTING CLIENTS  ------------- */
    /* ----------------- listen() ------------------- */

    /* 
        The accept() system call causes the process to block 
        until a client connects to the server. Thus, it wakes 
        up the process when a connection from a client has been 
        successfully established. It returns a new file descriptor, 
        and all communication on this connection should be done 
        using the new file descriptor. The second argument is a 
        reference pointer to the address of the client on the other 
        end of the connection, and the third argument is the size 
        of this structure.
    */

    int clientCount = 1;
    m_server = accept(m_client,(struct sockaddr *)&m_server_addr,&m_size);

    // first check if it is valid or not
    if (m_server < 0) 
        std::cout << "=> Error on accepting..." << std::endl;

    while (m_server > 0) 
    {
        strcpy(m_buffer, "=> Server connected...\n");
        send(m_server, m_buffer, m_bufSize, 0);
        std::cout << "=> Connected with the client #" << clientCount \
        << ", you are good to go..." << std::endl;
        std::cout << "\n=> Enter # to end the connection\n" << std::endl;

        /* 
            Note that we would only get to this point after a 
            client has successfully connected to our server. 
            This reads from the socket. Note that the read() 
            will block until there is something for it to read 
            in the socket, i.e. after the client has executed a 
            the send().
            It will read either the total number of characters 
            in the socket or 1024
        */

        std::cout << "Client: ";
        do {
            recv(m_server, m_buffer, m_bufSize, 0);
            std::cout << m_buffer << " ";
            if (*m_buffer == '#') {
                *m_buffer = '*';
                m_isExit = true;
            }
        } while (*m_buffer != '*');

        do {
            std::cout << "\nServer: ";
            do {
                std::cin >> m_buffer;
                send(m_server, m_buffer, m_bufSize, 0);
                if (*m_buffer == '#') {
                    send(m_server, m_buffer, m_bufSize, 0);
                    *m_buffer = '*';
                    m_isExit = true;
                }
            } while (*m_buffer != '*');

            std::cout << "Client: ";
            do {
                recv(m_server, m_buffer, m_bufSize, 0);
                std::cout << m_buffer << " ";
                if (*m_buffer == '#') {
                    *m_buffer = '*';
                    m_isExit = true;
                }
            } while (*m_buffer != '*');
        } while (!m_isExit);

        /* 
            Once a connection has been established, both ends 
            can both read and write to the connection. Naturally, 
            everything written by the client will be read by the 
            server, and everything written by the server will be 
            read by the client.
        */

        /* ---------------- CLOSE CALL ------------- */
        /* ----------------- close() --------------- */

        /* 
            Once the server presses # to end the connection,
            the loop will break and it will close the server 
            socket connection and the client connection.
        */

        // inet_ntoa converts packet data to IP, which was taken from client
        std::cout << "\n\n=> Connection terminated with IP " << inet_ntoa\
        (m_server_addr.sin_addr);
        close(m_server);
        std::cout << "\nGoodbye..." << std::endl;
        m_isExit = false;
        exit(1);
    }
    close(m_client);
    }