#ifndef GXO_EVENT_TYPE_H
#define GXO_EVENT_TYPE_H
#include <any>
#include "gxo_type.h"
namespace gxo {
	enum EventType
	{
		GXO_EVENT_INVALUD,
		/* Application events */
		GXO_EVENT_QUIT = 0x100, /**< User-requested quit */

		/* Window events */
		GXO_EVENT_WINDOWEVENT = 0x200, /**< Window state change */
		GXO_EVENT_RESIZE,
		GXO_EVENT_SYSWMEVENT,             /**< System specific event */

		/* Keyboard events */
		GXO_EVENT_KEYDOWN = 0x300, /**< Key pressed */
		GXO_EVENT_KEYUP,                  /**< Key released */
		GXO_EVENT_TEXTEDITING,            /**< Keyboard text editing (composition) */
		GXO_EVENT_TEXTINPUT,              /**< Keyboard text input */

		/* Mouse events */
		GXO_EVENT_MOUSEMOTION = 0x400, /**< Mouse moved */
		GXO_EVENT_MOUSEBUTTONDOWN,        /**< Mouse button pressed */
		GXO_EVENT_MOUSEBUTTONUP,          /**< Mouse button released */
		GXO_EVENT_MOUSEWHEEL,             /**< Mouse wheel motion */

		/* Drag and drop events */
		GXO_EVENT_DROPFILE = 0x1000, /**< The system requests a file open */

		/** Events ::GXO_EVENT_USEREVENT through ::GXO_EVENT_LASTEVENT are for your use,
		*  and should be allocated with GXO_EVENT_RegisterEvents()
		*/
		GXO_EVENT_USEREVENT = 0x8000,

		/**
		*  This last event is only for bounding internal arrays
		*/
		GXO_EVENT_LASTEVENT = 0xFFFF
	};

	struct EventCommon {
		uint32 type = GXO_EVENT_INVALUD;
		uint32 timestamp;
	};

	/**
	 *  \brief Window state change event data (event.window.*)
	 */
	struct EventWindow
	{
		uint32 type = GXO_EVENT_WINDOWEVENT;        /**< ::SDL_WINDOWEVENT */
		uint32 timestamp;
		
	};

	struct EventWindowResize
	{
		uint32 type = GXO_EVENT_RESIZE;        /**< ::SDL_WINDOWEVENT */
		uint32 timestamp;
		int width;
		int height;
	};

	/**
	 *  \brief Keyboard button event structure (event.key.*)
	 */
	struct EventKey
	{
		uint32 type;        /**< ::SDL_KEYDOWN or ::SDL_KEYUP */
		uint32 timestamp;
		
		uint8 state;        /**< ::SDL_PRESSED or ::SDL_RELEASED */
		uint8 repeat;       /**< Non-zero if this is a key repeat */
		uint8 padding2;
		uint8 padding3;
		
	};

	struct EventPointer
	{
		uint32 type;   
		uint32 timestamp;
		int target;
		int pop_catch;
	};

	struct EventClick
	{

	};


	struct EventChar
	{

	};

	union Event
	{
	public:
		Event(){}
		uint32 type;
		EventCommon common;
		EventWindowResize resize;
		uint8 padding[32];
	};
}
#endif