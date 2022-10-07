#pragma once

#include <CVNT/CVNT.hpp>
#include <CVNT/Packet/Packet.hpp>

namespace CVNT
{
	class Client
	{
	public:
		Client(PCSTR ip, u_short port);
		~Client();

		bool Connect(void);

	public:
		PCSTR m_IP = NULL;
		u_short m_Port = NULL;

		SOCKET m_Socket = NULL;
	};
}