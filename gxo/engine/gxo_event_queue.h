#ifndef _GXO_EVENT_QUEUE_H
#define _GXO_EVENT_QUEUE_H
#include "gxo_event.h"
#include <queue>
//需要线程安全
namespace gxo {
	class EventQueue :public std::queue<Event *>
	{
	public:
		EventQueue()
		{
		}

		~EventQueue()
		{
		}

	private:

	};
}
#endif