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

#endif