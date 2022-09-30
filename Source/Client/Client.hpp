#pragma once

#include "pch.hpp"

#include "Message/Message.hpp"

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
		std::queue<Message> m_TCPMessageQueue;
		char m_TCPWriteBuffer[sizeof(Message)];
		int m_TCPWriteNum;
	};
}