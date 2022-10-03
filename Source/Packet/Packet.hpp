#pragma once


namespace CVNT
{
	typedef unsigned int ClientID;

	struct Packet
	{
		enum Type
		{
			CONNECTED,
			DISCONNECTED,
			EVENT
		};

		Type m_Type;
		ClientID m_ID;

		void Serialize(char* data)
		{
			memcpy(data, this, sizeof(Packet));
		}

		void Deserialize(char* data)
		{
			memcpy(this, data, sizeof(Packet));
		}

		int Send(SOCKET socket)
		{
			return send(socket, (char*)this, sizeof(Packet), 0);
		}

		int	Receive(SOCKET socket)
		{
			return recv(socket, (char*)this, sizeof(Packet), 0);
		}
	};
}