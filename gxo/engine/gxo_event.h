#ifndef _GXO_EVENT_TYPE_H
#define _GXO_EVENT_TYPE_H
namespace gxo {
	enum EventType
	{
		Event_Mouse,
		Event_Key,
		Event_Char,
	};
	class Event {
	public:
		int type;
	};


	class EventMouse :public Event
	{
	public:
		int target;
		int pop_catch;
		EventMouse()
		{
		}

		~EventMouse()
		{
		}

	private:

	};

	class EventClick: public EventMouse
	{
	public:
		EventClick()
		{
		}

		~EventClick()
		{
		}

	private:

	};


	class EventKey :public Event
	{
	public:
		EventKey()
		{
		}

		~EventKey()
		{
		}

	private:

	};

	class EventChar :public Event
	{
	public:
		EventChar()
		{
		}

		~EventChar()
		{
		}

	private:

	};
}
#endif