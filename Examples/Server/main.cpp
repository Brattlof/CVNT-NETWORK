#include <iostream>

#include <Network/Network.hpp>

enum class CVNT::PacketType // Example
{
	EVENT,
	TEST
};

void Listener(CVNT::Packet packet, unsigned int client_id)
{
	switch (packet.m_Type)
	{
		case CVNT::PacketType::EVENT:
		{
			LOGFMT("Client[%i] event packet", client_id);
			break;
		}

		case CVNT::PacketType::TEST:
		{
			LOGFMT("Client[%i] test packet", client_id);
			break;
		}

		default:
		{
			LOGFMT("Client[%i] unknown packet", client_id);
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