#include <iostream>

#include "Network/Network.hpp"

int main(void)
{
	CVNT::Network Network("127.0.0.1", "666");

	if (!Network.Start())
		return 0x1;

	std::cout << "TCP: " << Network.m_TCPSocket << " UDP: " << Network.m_UDPSocket << "\n";

	while (true)
	{
		//printf("Clients: %zi\n", Network.m_Clients.size());
	}

	return 0x0;
}