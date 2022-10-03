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

	public:
		PCSTR m_IP = NULL;
		PCSTR m_Port = NULL;

		SOCKET m_TCPSocket = NULL;
		SOCKET m_UDPSocket  = NULL;
		//
		SOCKET m_AcceptSocket = NULL;

	private:
		ClientID m_NextClientID = NULL;
		std::unordered_map<ClientID, SOCKET> m_Clients;

		void Accept(void);
		void Listen(void);
	};
}