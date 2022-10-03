#pragma once

#include "pch.hpp"

#include "Packet/Packet.hpp"

namespace CVNT
{
	class Client
	{
	public:
		Client(PCSTR ip, PCSTR port);
		~Client();

		bool Connect(void);

	public:
		PCSTR m_IP = NULL;
		PCSTR m_Port = NULL;

		ClientID m_ID = NULL;
		SOCKET m_Socket = NULL;
	};
}