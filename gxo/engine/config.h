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

		static Config& instacne() {
			static Config config;
			return config;
		}

		Config(){}
		~Config(){}
		bool init() {
			//lua.open_libraries(sol::lib::base);
			lua.script_file("config.lua");
			data = lua["Config"];
			return true;
		}
		//int get_window_height();
		//int get_frame_limit();
	private:
		sol::state lua; //��������ͷ�luatable
	};

}
#endif