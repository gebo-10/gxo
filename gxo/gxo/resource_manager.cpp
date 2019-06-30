#include "resource_manager.h"
#include"file_system.h"
#include"env.h"
void gxo::ResourceManager::load_package(string& package)
{
	sol::state& lua = Config::instacne().lua;
	auto p = package + "/resource.lua";
	lua.script_file(p);
	sol::table resource_config = lua["Resource"];

	load_shader(package, resource_config["Shader"]);
	load_texture(package, resource_config["Texture"]);
	
}
void gxo::ResourceManager::load_texture(string package,sol::table textures)
{
	for (auto config : textures) {
		auto item=config.second.as<sol::table>();
		string image=item["image"];
		
		//std::shared_ptr<Texture> texture(new Texture(), resource_deleter);
		auto texture = std::make_shared<Texture>();
		Buffer buffer;
		auto path = package + "/" + image;
		env.engine->file_system.get_sync(path,buffer);
		texture->create(path, buffer);

		string name = item["name"];
		name= package + "/texture/" + name;
		resource_map[name] = texture;
	}

}

void gxo::ResourceManager::load_shader(string package, sol::table textures)
{
	for (auto config : textures) {
		auto item = config.second.as<sol::table>();
		string name = item["name"];
		string vs = item["vs"];
		string fs = item["fs"];

		auto shader = std::make_shared<Shader>();

		auto vs_path = package + "/" + vs;
		env.engine->file_system.get_sync(vs_path, shader->vs_source);

		auto fs_path = package + "/" + fs;
		env.engine->file_system.get_sync(fs_path, shader->fs_source);

		name = package + "/shader/" + name;
		resource_map[name] = shader;
	}

}

