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
	//scrool
	class KeyStatus {
		int key;
		char c;
		bool ctrl;
		bool alt;
		bool shift;
	};

	
	
	class EventSystem
	{
	public:
		PointerStatus pointer_status;
		KeyStatus	key_status;
		EventQueue event_queue;
		

		EventSystem()
		{
		
		}

		~EventSystem()
		{

		}

		void init() {
			return;
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