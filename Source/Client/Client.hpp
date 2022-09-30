#pragma once

#include "pch.hpp"

#include "Packet/Packet.hpp"

namespace CVNT
{
	class Client
	{
	public:
		Client();
		Client(ClientID ID);
		~Client();

	public:
		ClientID m_ID;

		// TCP
		SOCKET m_TCPSocket;
		std::queue<Packet> m_TCPMessageQueue;
		char m_TCPWriteBuffer[sizeof(Packet)];
		int m_TCPWriteNum;
	};
}