#ifndef CLIENT_HPP
# define CLIENT_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define PORT 23
#define BUFSIZE 1024
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

class	client
{
    public:
	    client(void);
	    client(const client &cp);
	    ~client(void);
	    client &operator=(const client &cp);
	    int	start(void);
	    void run(void);
    private:
	    int	_client;
	    struct sockaddr_in server;
	    char    buffer[BUFSIZE];
	    bool    isExit;
};
#endif
