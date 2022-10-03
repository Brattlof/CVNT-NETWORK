#include "pch.hpp"

#include "Client.hpp"

using namespace CVNT;

Client::Client(PCSTR ip, PCSTR port) : m_IP(ip), m_Port(port)
{

}

Client::~Client()
{
	closesocket(m_Socket);
}

bool Client::Connect(void)
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

	struct addrinfo* result = nullptr, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(m_IP, m_Port, &hints, &result) != 0)
	{
		return false;
	}

	if (result->ai_family != AF_INET)
	{
		return false;
	}

	m_Socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (m_Socket == INVALID_SOCKET)
	{
		return false;
	}

	if (connect(m_Socket, result->ai_addr, (int)result->ai_addrlen) != 0)
	{
		return false;
	}

	Packet packet = { };

	if (packet.Receive(m_Socket) != 0)
	{
		return false;
	}

	packet.m_Type = Packet::CONNECTED;
	if (packet.Send(m_Socket) != 0)
	{
		return false;
	}

	return true;
}