#pragma once


namespace CVNT
{
	typedef unsigned int ClientID;

	struct Message
	{
		enum Type
		{
			CONNECTED,
			DISCONNECTED
		};

		Type m_Type;
		ClientID m_ID;

		void Serialize(char* data)
		{
			memcpy(data, this, sizeof(Message));
		}

		void Deserialize(char* data)
		{
			memcpy(this, data, sizeof(Message));
		}
	};
}