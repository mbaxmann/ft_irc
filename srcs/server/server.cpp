#include "server.hpp"

server::server(void) : isExit(false), clientCount(1), crecsize(sizeof(csin)) {
}

server::server(const server &cp) {
    *this = cp;
}

server::~server(void) {
    std::cout << "Close the socket server" << std::endl;
    close(_server);
    std::cout << "Close the socket client" << std::endl;
    close(client);
    std::cout << "Server closing is done" << std::endl;
}

server &server::operator=(const server &cp) {
    if (this != &cp)
	*this = cp;
    return (*this);
}

int server::start(void) {
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == -1)
    {
	std::cout << "Error sock creation" << std::endl;
	return (EXIT_FAILURE);
    }

    std::cout << "Socket: " << client << " is now opened in TCP/IP" << std::endl;
    csin.sin_addr.s_addr = htonl(INADDR_ANY);
    csin.sin_family = AF_INET;
    csin.sin_port = htons(PORT);

    int sock_err = bind(client, (struct sockaddr*)&csin, sizeof(csin));
    if (sock_err == SOCKET_ERROR)
    {
	std::cout << "Error bind" << std::endl;
	return (EXIT_FAILURE);
    }

    sock_err = listen(client, 5);
    std::cout << "listage du port: " << "23" << std::endl;
    if (sock_err == SOCKET_ERROR)
    {
	std::cout << "Error listen" << std::endl;
	return (EXIT_FAILURE);
    }
    std::cout << "Please wait, the client is connecting to the port:" << PORT << std::endl;
    return (EXIT_SUCCESS);
}

void server::run(void) {
    _server = accept(client, (struct sockaddr*)&csin, &crecsize);
    std::cout << "Client is connecting with the socket " << _server << " from:" << inet_ntoa(csin.sin_addr) << std::endl;
    if (_server > 0)
    {
        while (isExit == false && _server > 0) 
        {
            strcpy(buffer, "=> Server connected...\n");
            send(_server, buffer, BUFSIZE, 0);
            std::cout << "=> Connected with the client #" << clientCount << ", you are good to go..." << std::endl;
            std::cout << "\n=> Enter # to end the connection\n" << std::endl;
       
            std::cout << "Client: ";
            while (1)
            {
                recv(_server, buffer, BUFSIZE, 0);
                std::cout << buffer << " ";
                if (*buffer == '#') {
                    *buffer = '*';
                    isExit = true;
                }
                if (*buffer == '*')
                    break;
            }
            if (isExit == true)
                break;
    
            while (!isExit)
            {
               std::cout << "\nServer: ";
                while (1)
                {
                    std::cin >> buffer;
                    send(_server, buffer, BUFSIZE, 0);
                    if (*buffer == '#') {
                        send(_server, buffer, BUFSIZE, 0);
                        *buffer = '*';
                        isExit = true;
                    }
                    if (*buffer == '*')
                        break;
                } 
                if (isExit == true)
                break;
                std::cout << "Client: ";
                while (1)
                {
                    recv(_server, buffer, BUFSIZE, 0);
                    std::cout << buffer << " ";
                    if (*buffer == '#')
                    {
                        *buffer = '*';
                        isExit = true;
                    }
                    if (*buffer == '*')
                        break;
                } 
                if (isExit == true)
                break;
            } 
        }
    }
}
