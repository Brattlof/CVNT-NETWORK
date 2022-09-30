#pragma once

#include "pch.hpp"

#include "Client/Client.hpp"
#include "Message/Message.hpp"

namespace CVNT
{
	class Network
	{
	public:
		Network(PCSTR IP, PCSTR PORT);
		~Network(void);

	public:
		PCSTR m_IP;
		PCSTR m_Port;

		SOCKET m_TCPSocket;
		SOCKET m_UDPSocket;

	private:
		unsigned int m_ClientNum;
		std::unordered_map<SOCKET, ClientID> m_ClientSockets;
		std::unordered_map<ClientID, Client*> m_Clients;
	};
}