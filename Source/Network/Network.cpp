#include "pch.hpp"

#include "Network.hpp"

using namespace CVNT;

Network::Network(const char* ip, const char* port) : m_IP(ip), m_Port(port), m_NextClientID(1) { }

Network::~Network(void)
{
	closesocket(m_Socket);
	//
	WSACleanup();
}

void Network::SetListener(std::function<void(Packet)> listener)
{
	m_Listener = listener;
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

	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Socket == INVALID_SOCKET)
	{
		return false;
	}

	struct addrinfo* result = nullptr, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(m_IP, m_Port, &hints, &result) != 0)
	{
		return false;
	}

	if (result->ai_family != AF_INET)
	{
		return false;
	}

	if (bind(m_Socket, result->ai_addr, (int)result->ai_addrlen) != 0)
	{
		return false;
	}

	if (listen(m_Socket, SOMAXCONN) != 0)
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
		m_AcceptSocket = accept(m_Socket, NULL, NULL);

		if (m_AcceptSocket != INVALID_SOCKET)
		{
			SOCKADDR_IN accept;
			int temp = sizeof(accept);
			getsockname(m_AcceptSocket, (SOCKADDR*)&accept, &temp);
			//
			LOGFMT("New connection from %s", inet_ntoa(accept.sin_addr));
			//
			m_Clients.insert({ m_NextClientID, m_AcceptSocket });
			//
			Packet packet = { };
			packet.m_ID = m_NextClientID;
			packet.Send(m_Socket);
			//
			m_NextClientID++;
		}
	}

	listener.join();
}

void Network::Listen(void)
{
	while (true)
	{
		Packet packet = { };
		
		if (packet.Receive(m_Socket) <= 0) continue;
		
		m_Listener(packet);
	}
}