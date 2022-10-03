#include "pch.hpp"

#include "Network.hpp"

using namespace CVNT;

Network::Network(const char* ip, const char* port) : m_IP(ip), m_Port(port), m_NextClientID(1) { }

Network::~Network(void)
{
	WSACleanup();
}

bool Network::Start(void)
{
	WSADATA wsa;
	int error = WSAStartup(0x0202, &wsa);

	if (error != 0)
	{
		return false;
	}

	if (wsa.wVersion != 0x0202)
	{
		return false;
	}

	m_TCPSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_TCPSocket == INVALID_SOCKET)
	{
		return false;
	}

	m_UDPSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_UDPSocket == INVALID_SOCKET)
	{
		return false;
	}

	struct addrinfo* ai = nullptr;
	if (getaddrinfo(m_IP, m_Port, nullptr, &ai) != 0)
	{
		return false;
	}

	if (ai->ai_family != AF_INET)
	{
		return false;
	}

	if (bind(m_TCPSocket, ai->ai_addr, (int)ai->ai_addrlen) != 0)
	{
		return false;
	}

	if (listen(m_TCPSocket, SOMAXCONN) != 0)
	{
		return false;
	}

	if (bind(m_UDPSocket, ai->ai_addr, (int)ai->ai_addrlen) != 0)
	{
		return false;
	}

	std::thread(&Network::Accept, this).join();

	return true;
}

void Network::Accept(void)
{
	std::thread listener(&Network::Listen, this);

	while (true)
	{
		m_AcceptSocket = accept(m_TCPSocket, NULL, NULL);

		if (m_AcceptSocket != INVALID_SOCKET)
		{
			m_Clients.insert({ m_NextClientID, m_AcceptSocket });
			m_NextClientID++;
		}
	}

	listener.join();
}

void Network::Listen(void)
{
	while (true)
	{

	}
}