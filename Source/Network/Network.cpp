#include "pch.hpp"

#include "Network.hpp"

using namespace CVNT;

Network::Network(u_short port) : m_Port(port), m_NextClientID(1) { }

Network::~Network(void)
{
	closesocket(m_AcceptSocket);
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
	if (!m_Listener)
	{
		LOG("Please set a listener function");
		return false;
	}

	WSAData wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		LOG("WSAStartup failed\n");
		return false;
	}
	//
	m_Socket = socket(AF_INET, SOCK_STREAM, NULL);
	if (m_Socket == INVALID_SOCKET)
	{
		LOG("Failed creating socket");
		return false;
	}

	u_long im = 1;
	if (ioctlsocket(m_Socket, FIONBIO, &im) == SOCKET_ERROR)
	{
		LOG("Failed ioctlsocket");
		return false;
	}
	//
	sockaddr_in hint = { };
	ZeroMemory(&hint, sizeof(hint));
	//
	hint.sin_family = AF_INET;
	hint.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	hint.sin_port = htons(m_Port);
	//
	if (bind(m_Socket, (sockaddr*)&hint, sizeof(hint)) != 0)
	{
		LOG("Failed bind");
		return false;
	}
	//
	if (listen(m_Socket, SOMAXCONN) != 0)
	{
		LOG("Failed listen");
		return false;
	}
	//
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
			char value = 1;
			setsockopt(m_AcceptSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
			//
			SOCKADDR_IN accept;
			int temp = sizeof(accept);
			getsockname(m_AcceptSocket, (SOCKADDR*)&accept, &temp);
			//
			LOGFMT("New connection[%i] from %s", m_NextClientID, inet_ntoa(accept.sin_addr));
			//
			m_Clients.insert({ m_NextClientID, m_AcceptSocket });
			//
			Packet packet = { };
			packet.m_ID = m_NextClientID;
			packet.Send(m_AcceptSocket);
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

		for (auto x : m_Clients)
		{
			if (packet.Receive(x.second) > 0)
			{
				m_Listener(packet);
			}
		}
	}
}