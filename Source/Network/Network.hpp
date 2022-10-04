#pragma once

#include "pch.hpp"

#include "Client/Client.hpp"
#include "Packet/Packet.hpp"

namespace CVNT
{
	class Network
	{
	public:
		Network(u_short port);
		~Network(void);

		void SetListener(std::function<void(Packet)> listener);
		bool Start(void);

	public:
		u_short m_Port = NULL;
		//
		SOCKET m_Socket = NULL;
		//
		SOCKET m_AcceptSocket = NULL;

	public:
		ClientID m_NextClientID = NULL;
		std::unordered_map<ClientID, SOCKET> m_Clients;

		void Accept(void);
		void Listen(void);
		std::function<void(Packet)> m_Listener;
	};
}