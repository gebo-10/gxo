#ifndef _GXO_CONFIG_H
#define _GXO_CONFIG_H
#include<string>
#include<any>
#include<map>

#include"sol.hpp"
namespace gxo {
	class Config
	{
	public:
		
		sol::table data;
		sol::state lua; //析构后会释放luatable
		static Config& instacne() {
			static Config config;
			return config;
		}

		Config(){}
		~Config(){}
		void init() {
			//lua.open_libraries(sol::lib::base);
			lua.script_file("config.lua");
			data = lua["Config"];
		}
		//int get_window_height();
		//int get_frame_limit();
	private:
		
	};

}
#endif