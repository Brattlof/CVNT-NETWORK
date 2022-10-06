#include <iostream>

#include <Network/Network.hpp>

enum class CVNT::PacketType // Example
{
	EVENT
};

void Listener(CVNT::Packet packet)
{
	switch (packet.m_Type)
	{
		case CVNT::PacketType::EVENT:
		{
			LOGFMT("Client[%i] event packet", packet.m_ID);
			break;
		}

		default:
		{
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