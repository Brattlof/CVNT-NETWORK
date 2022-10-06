#pragma once

#define DATASIZE 32

namespace CVNT
{
	typedef unsigned int ClientID;

	enum class PacketType;

	struct Packet
	{
		PacketType m_Type;
		ClientID m_ID;

		unsigned int m_DataSize;
		char* m_Data;

		int Send(SOCKET socket)
		{
			return send(socket, (char*)this, sizeof(*this), NULL);
		}

		int	Receive(SOCKET socket)
		{
			return recv(socket, (char*)this, sizeof(*this), NULL);
		}
	};
}