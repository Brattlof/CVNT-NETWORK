#include "pch.hpp"

#include "Network.hpp"

using namespace CVNT;

Network::Network(const char* ip, const char* port)
{
	WSADATA rWSA;

	int rError = WSAStartup(0x0202, &rWSA);

	if (rError != 0) 
	{
		return;
	}

	if (rWSA.wVersion != 0x0202) 
	{
		return;
	}

	m_TCPSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_TCPSocket == INVALID_SOCKET)
	{
		return;
	}

	m_UDPSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_UDPSocket == INVALID_SOCKET)
	{
		return;
	}

	struct addrinfo* ai = nullptr;
	if (getaddrinfo(ip, port, nullptr, &ai) != 0)
	{
		return;
	}

	if (ai->ai_family != AF_INET) 
	{
		return;
	}

	if (bind(m_TCPSocket, ai->ai_addr, (int)ai->ai_addrlen) != 0)
	{
		return;
	}

	if (listen(m_TCPSocket, 1) != 0)
	{
		return;
	}

	if (bind(m_UDPSocket, ai->ai_addr, (int)ai->ai_addrlen) != 0)
	{
		return;
	}

	m_IP = ip;
	m_Port = port;
}

Network::~Network()
{
	while (m_Clients.begin() != m_Clients.end())
	{
		delete m_Clients.begin()->second;
		m_Clients.erase(m_Clients.begin()->first);
	}

	WSACleanup();
}