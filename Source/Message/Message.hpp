#pragma once


namespace CVNT
{
	typedef unsigned int ClientID;

	struct Message
	{
	public:
		enum Type
		{
			CONNECTED,
			DISCONNECTED
		};

	public:
		Type m_Type;
		ClientID m_ID;
	};
}