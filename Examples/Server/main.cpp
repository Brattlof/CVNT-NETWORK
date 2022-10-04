#include <iostream>

#include "Network/Network.hpp"

void Listener(CVNT::Packet packet)
{
	switch (packet.m_Type)
	{
		case CVNT::Packet::DISCONNECTED:
		{
			LOGFMT("Client[%i] disconnect packet", packet.m_ID);
			break;
		}

		case CVNT::Packet::EVENT:
		{
			LOGFMT("Client[%i] event packet", packet.m_ID);
			break;
		}
		
		default:
		{
			LOGFMT("Client[%i] unknown packet", packet.m_ID);
			break;
		}
	}
}

int main(void)
{
	CVNT::Network Network(666);

	Network.SetListener(Listener);

	if (!Network.Start())
		return 0x1;

	return 0x0;
}