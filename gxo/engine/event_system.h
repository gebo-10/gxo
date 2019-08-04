#ifndef GXO_EVENT_SYSTEM_H
#define GXO_EVENT_SYSTEM_H
#include "gxo_event_queue.h"
#include "gxo_input_define.h"
#include <functional>
namespace gxo {
	class PointerStatus {
		int x;
		int y;
		bool hover;
		bool button1;
		bool button2;
		bool button3; //center
	};
	class KeyStatus {
		int key;
		char c;
		bool ctrl;
		bool alt;
		bool shift;
	};

	typedef std::function<void(Event*)> EventProcess;

	class EventSystem
	{
	public:
		PointerStatus pointer_status;
		KeyStatus	key_status;
//		EventQueue event_queue;
		std::map<uint32, std::vector<EventProcess> > event_hub;

		EventSystem()
		{
			event_hub.clear();
		}

		~EventSystem()
		{

		}

		void init() {
			
		}

		void update() {
			//while (!event_queue.empty())
			//{
			//	
			//}
		}

		void process_event(Event * event) {
			auto itr = event_hub.find(event->type);
			if (itr != event_hub.end())
			{
				for (auto item : itr->second)
				{
					item(event);
				}
			}
		}

		void add_event_process(int event_type, EventProcess process) {
			auto itr = event_hub.find(event_type);
			if (itr == event_hub.end())
			{
				std::vector<EventProcess> events;
				events.push_back(process);
				event_hub[event_type] = events;
			}
			else {
				itr->second.push_back(process);
			}
			
		}

		void remove_event_process(int event_type, EventProcess process) {
			auto itr = event_hub.find(event_type);
			if (itr != event_hub.end())
			{
				for (auto item= itr->second.begin();item!=itr->second.end();item++)
				{
					if (item->target<void(Event*)>()==process.target<void(Event*)>())
					{
						itr->second.erase(item);
					}
				}
			}
		
		}

	private:

	};

}
#endif