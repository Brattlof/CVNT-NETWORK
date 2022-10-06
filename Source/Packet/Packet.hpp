#pragma once

#define DATASIZE 32

namespace CVNT
{
	typedef unsigned int ClientID;

	struct Packet
	{
		enum Type
		{
			DISCONNECTED,
			EVENT
		};

		struct EventData
		{
			char Event[32] = { 0 };
		};

		Type m_Type;
		ClientID m_ID;

		union
		{
			EventData m_EventData;
		};

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