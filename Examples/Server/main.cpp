#include <iostream>

#include "Network/Network.hpp"

void Listener(CVNT::Packet packet)
{
	printf("Recieved Packet\n");
}

int main(void)
{
	CVNT::Network Network(666);

	if (!Network.Start())
		return 0x1;

	while (true)
	{
	}

	return 0x0;
}