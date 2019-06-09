#ifndef _GXO_EVENT_SYSTEM_H
#define _GXO_EVENT_SYSTEM_H
#include "gxo_event_queue.h"
#include <functional>
namespace gxo {
	class MouseStatus {
		int button;
		int button_status;
		int x;
		int y;
	};
	class Action {
		int delay;
		std::function<void(Event*)> fun;
	};
	class Trigger
	{
	public:
		std::vector<std::function<void (Event*)>> actions;
		
	private:
	};
	class EventSystem
	{
	public:
		MouseStatus mouse_status;
		EventQueue event_queue;
		

		EventSystem()
		{
		}

		~EventSystem()
		{

		}

		bool init() {
			return true;
		}

		void update() {
			while (!event_queue.empty())
			{
				
			}
		}


	private:

	};

}
#endif