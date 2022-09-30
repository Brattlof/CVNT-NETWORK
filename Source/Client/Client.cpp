#include "pch.hpp"

#include "Client.hpp"

using namespace CVNT;

Client::Client()
{

}

Client::Client(ClientID id)
{
	m_TCPSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_TCPSocket == INVALID_SOCKET) 
	{
		return;
	}
}

Client::~Client()
{

}