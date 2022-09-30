#pragma once

#include "pch.hpp"

#include "Client/Client.hpp"
#include "Packet/Packet.hpp"

namespace CVNT
{
	class Network
	{
	public:
		Network(PCSTR ip, PCSTR port);
		~Network(void);

		bool Start();

	public:
		PCSTR m_Ip = NULL;
		PCSTR m_Port = NULL;

		SOCKET m_TCPSocket = NULL;
		SOCKET m_UDPSocket  = NULL;

	private:
		unsigned int m_ClientNum = NULL;
		std::unordered_map<SOCKET, ClientID> m_ClientSockets;
		std::unordered_map<ClientID, Client*> m_Clients;
	};
}