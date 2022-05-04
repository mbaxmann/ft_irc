#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#define BUFSIZE 1024
#define SOCKET_ERROR -1
#define PORT 23
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

class server
{
    public:
	    server(void);
	    server(const server &cp);
	    ~server(void);
	    server &operator=(const server &cp);
	    int	start(void);
	    void run(void);
    private:
	    int	    _server;
	    bool    isExit;
	    char    buffer[BUFSIZE];
	    int	    client;
	    int	    clientCount;
	    struct sockaddr_in	csin;
	    socklen_t		crecsize;
};

#endif
