#ifndef __CLIENT__H
#define __CLIENT__H

#include <CVNT/CVNT.h>
#include <CVNT/Packet/Packet.h>

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

#endif