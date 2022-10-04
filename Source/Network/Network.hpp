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
		std::unordered_map<ClientID, SOCKET> m_Clients;

	private:
		u_short m_Port = NULL;
		//
		SOCKET m_Socket = NULL;
		//
		SOCKET m_AcceptSocket = NULL;

		ClientID m_NextClientID = NULL;

		void Accept(void);
		void Listen(void);
		std::function<void(Packet)> m_Listener;
	};
}