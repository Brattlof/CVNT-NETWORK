#ifndef __PACKET__H
#define __PACKET__H

#include <CVNT/CVNT.h>

#define DATASIZE 32

namespace CVNT
{
	enum class PacketType;

	struct Packet
	{
		PacketType m_Type;

		char* m_Data;
		unsigned int m_DataSize;

		int Send(SOCKET socket)
		{
			return send(socket, (char*)this, sizeof(Packet), NULL);
		}

		int	Receive(SOCKET socket)
		{
			return recv(socket, (char*)this, sizeof(Packet), NULL);
		}
	};
}

#endif