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

		bool Start(void);
		//
		bool Update(void);

	public:
		PCSTR m_IP = NULL;
		PCSTR m_Port = NULL;

		SOCKET m_TCPSocket = NULL;
		SOCKET m_UDPSocket  = NULL;
		//
		SOCKET m_AcceptSocket = NULL;

	private:
		ClientID m_NextClientID = NULL;
		unsigned int m_ClientNum = NULL;
		std::unordered_map<ClientID, SOCKET> m_Clients;
	};
}