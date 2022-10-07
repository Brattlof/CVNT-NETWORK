#include <iostream>

#include <CVNT/Server/Server.h>

enum class CVNT::PacketType // Example
{
	EVENT,
	TEST
};

CVNT::Server Server(666);

void Listener(CVNT::Packet packet, unsigned int client_id)
{
	switch (packet.m_Type)
	{
		case CVNT::PacketType::EVENT:
		{
			LOGFMT("Client[%i] event packet socket[%Ii]", client_id, Server.m_Clients[client_id]);
			break;
		}

		case CVNT::PacketType::TEST:
		{
			LOGFMT("Client[%i] test packet socket[%Ii]", client_id, Server.m_Clients[client_id]);
			break;
		}

		default:
		{
			LOGFMT("Client[%i] unknown packet socket[%Ii]", client_id, Server.m_Clients[client_id]);
			break;
		}
	}
}

int main(void)
{
	Server.SetListener(Listener);

	if (!Server.Start())
		return 0x1;

	return 0x0;
}