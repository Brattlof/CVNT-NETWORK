#include <iostream>

#include <Client/Client.hpp>

enum class CVNT::PacketType // Example
{
	EVENT,
	TEST
};

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

	while (true)
	{
		std::string input;
		std::cin >> input;

		if (input == "exit") break;

		CVNT::Packet packet = { };
		packet.m_Type = CVNT::PacketType::TEST;
		
		packet.Send(Client->m_Socket);
	}

	delete Client;

	return 0x0;
}