#include <iostream>

#include "Network/Network.hpp"

void Listener(CVNT::Packet packet)
{
	LOG(packet.m_Type);
}

int main(void)
{
	CVNT::Network Network(666);

	Network.SetListener(Listener);

	if (!Network.Start())
		return 0x1;

	return 0x0;
}