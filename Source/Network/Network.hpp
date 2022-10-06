#ifndef __NETWORK__H
#define __NETWORK__H

#include <CVNT.hpp>

#include "Client/Client.hpp"
#include "Packet/Packet.hpp"

namespace CVNT
{
	class Network
	{
	public:
		Network(u_short port);
		~Network(void);

		void SetListener(std::function<void(Packet, unsigned int /* CLIENT ID */)> listener);
		bool Start(void);

	public:
		std::unordered_map<unsigned int /* CLIENT ID */, SOCKET> m_Clients;

	private:
		u_short m_Port = NULL;
		//
		SOCKET m_Socket = NULL;
		//
		SOCKET m_AcceptSocket = NULL;

		unsigned int m_NextClientID = NULL;

		void Accept(void);
		void Listen(void);
		std::function<void(Packet, unsigned int /* CLIENT ID */)> m_Listener;
	};
}

#endif