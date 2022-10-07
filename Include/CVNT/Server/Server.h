#ifndef __SERVER__H
#define __SERVER__H

#include <CVNT/CVNT.h>
#include <CVNT/Packet/Packet.h>

namespace CVNT
{
	class Server
	{
	public:
		Server(u_short port);
		~Server(void);

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