#include <CVNT.hpp>

#include <Client/Client.hpp>

using namespace CVNT;

Client::Client(PCSTR ip, u_short port) : m_IP(ip), m_Port(port)
{

}

Client::~Client()
{
	closesocket(m_Socket);
}

bool Client::Connect(void)
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		LOG("WSAStartup failed");
		return false;
	}
	//
	m_Socket = socket(AF_INET, SOCK_STREAM, NULL);
	if (m_Socket == INVALID_SOCKET)
	{
		LOG("Failed creating socket");
		return false;
	}
	//
	sockaddr_in hint = { };
	ZeroMemory(&hint, sizeof(hint));
	//
	hint.sin_family = AF_INET;
	hint.sin_port = htons(m_Port);
	if (inet_pton(AF_INET, m_IP, &hint.sin_addr) <= 0)
	{
		LOG("Invalid IP");
		return false;
	}

	if (connect(m_Socket, (sockaddr*)&hint, sizeof(hint)) != 0)
	{
		LOG("Failed connecting");
		return false;
	}

	Packet packet = { };
	packet.Receive(m_Socket);
	m_ID = packet.m_ID;

	u_long im = 1;
	if (ioctlsocket(m_Socket, FIONBIO, &im) == SOCKET_ERROR)
	{
		LOG("Failed ioctlsocket");
		return false;
	}

	char value = 1;
	setsockopt(m_Socket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));

	return true;
}