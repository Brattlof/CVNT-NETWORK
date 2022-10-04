#include <iostream>

#include <Client/Client.hpp>

int main(void)
{
	CVNT::Client* Client = new CVNT::Client("127.0.0.1", 666);

	LOG("Connecting to server...");
	if (!Client->Connect())
	{
		delete Client;
		return 0x1;
	}

	LOG("Connected");

	CVNT::Packet packet;
	packet.m_ID = Client->m_ID;
	packet.m_Type = CVNT::Packet::EVENT;

	while (true)
	{
		std::string input;
		std::cin >> input;

		if (input == "exit") break;

		packet.Send(Client->m_Socket);
	}

	delete Client;

	return 0x0;
}