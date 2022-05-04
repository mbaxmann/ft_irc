#include "server/server.hpp"

int main(void)
{
    server  my_server;

    if (my_server.start() == EXIT_FAILURE)
	return (EXIT_FAILURE);
    my_server.run();
    return (EXIT_SUCCESS);
}
