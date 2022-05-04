#include "client.hpp"

client::client(void) : isExit(false) {
}

client::client(const client &cp) {
    *this = cp;
}

client::~client(void) {
    close(_client);
}

client &client::operator=(const client &cp) {
    if (this != &cp)
	*this = cp;
    return (*this);
}

int client::start(void) {
    _client = socket(AF_INET, SOCK_STREAM, 0);
    if (_client == -1)
    {
	std::cout << "Error socket creation" << std::endl;
	return (EXIT_FAILURE);
    }

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    return (EXIT_SUCCESS);
}

void	client::run(void) {
    if(connect(_client, (struct sockaddr*)&server, sizeof(server)) != -1)
    {
        std::cout << "Connexion on " << inet_ntoa(server.sin_addr) << " on port " << htons(server.sin_port) << std::endl;
        while (1)
        {
          std::cout << "Client: ";
          while (1)
          {
              std::cin >> buffer;
              send(_client, buffer, BUFSIZE, 0);
              if (*buffer == '#')
              {
                  send(_client, buffer, BUFSIZE, 0);
                  *buffer = '*';
                  isExit = true;
              }
              if (*buffer == '*')
                break;
          }
          if (isExit == true)
            break;
          std::cout << "Server: ";
          while (1)
          {
              recv(_client, buffer, BUFSIZE, 0);
              std::cout << buffer << " ";
              if (*buffer == '#')
              {
                  *buffer = '*';
                  isExit = true;
              }
              if (*buffer == '*')
                break;
          }
          std::cout << std::endl;
          if (isExit == true)
            break;
        }
    }
    else
    {
       std::cout << "Connexion impossible" << std::endl;
        exit(EXIT_FAILURE);
    }
}
