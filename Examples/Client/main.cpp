#include <iostream>

#include <Client/Client.hpp>

int main(void)
{
	CVNT::Client Client("127.0.0.1", 666);

	LOG("Connecting to server...");
	if (!Client.Connect())
		return 0x1;

	while (true)
	{
		CVNT::Packet packet = { };
		packet.m_Type = CVNT::Packet::EVENT;
		//packet.Send(Client.m_Socket);
	}

	return 0x0;
}