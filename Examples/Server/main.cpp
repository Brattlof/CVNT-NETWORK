#include <iostream>

#include "Network/Network.hpp"

void Listener(CVNT::Packet packet)
{
	printf("Recieved Packet\n");
}

int main(void)
{
	CVNT::Network Network("127.0.0.1", "666");

	Network.SetListener(Listener);

	if (!Network.Start())
		return 0x1;

	return 0x0;
}