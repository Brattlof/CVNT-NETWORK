#include "pch.hpp"

#include "Client.hpp"

using namespace CVNT;

Client::Client(PCSTR ip, PCSTR port) : m_IP(ip), m_Port(port)
{

}

Client::~Client()
{

}

bool Client::Start(void)
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

	struct addrinfo* ai = nullptr;
	if (getaddrinfo(m_IP, m_Port, nullptr, &ai) != 0)
	{
		return false;
	}

	if (ai->ai_family != AF_INET)
	{
		return false;
	}

	m_TCPSocket = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
	if (m_TCPSocket == INVALID_SOCKET)
	{
		return false;
	}

	if (connect(m_TCPSocket, ai->ai_addr, (int)ai->ai_addrlen) != 0)
	{
		return false;
	}

	return true;
}