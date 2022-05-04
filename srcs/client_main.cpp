#include "client/client.hpp"

int main(void)
{
    client  my_client;

    if (my_client.start() == 1)
	return (EXIT_FAILURE);
    my_client.run();
    return (0);
}
