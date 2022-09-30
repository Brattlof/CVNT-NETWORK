#include <iostream>

#include "Network/Network.hpp"

int main(void)
{
	CVNT::Network Network("127.0.0.1", "666");

	std::cout << "TCP: " << Network.m_TCPSocket << " UDP: " << Network.m_UDPSocket << "\n";

	return 0x0;
}