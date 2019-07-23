#include "resource_manager.h"
#include"file_system.h"
#include"env.h"
#include"texture.h"
#include"plane.h"
#include"engine.h"


#include "stb_image.h"

void gxo::ResourceManager::register_default()
{
	auto plane = std::make_shared<Plane>();
	add_resource("default/plane", plane );
	env.render->gpu_load(plane);
}
void gxo::ResourceManager::load_package(string& package)
{
	sol::state& lua = Config::instacne().lua;
	auto p = package + "/resource.lua";
	lua.script_file(p);
	sol::table resource_config = lua["Resource"];

 	
	load_texture(package, resource_config["Texture"]);
	load_shader(package, resource_config["Shader"]);
	load_material(package, resource_config["Material"]);
}

void gxo::ResourceManager::load_texture(string package,sol::table textures)
{
	stbi_set_flip_vertically_on_load(true);
	for (auto config : textures) {
		auto item=config.second.as<sol::table>();
		string image=item["image"];

		//std::shared_ptr<Texture> texture(new Texture(), resource_deleter);
		auto texture = std::make_shared<Texture>();

		Buffer buffer;
		auto path = package + "/" + image;
		env.engine->file_system.get_sync(path,buffer);

		int w, h, n;
		buffer.data=stbi_load_from_memory(buffer.data, buffer.size, &w, &h, &n, 0);
		buffer.size = w * h * n;
		texture->width = w;
		texture->height = h;
		if (n == 3) {
			texture->format = GL_RGB;
		}
		else if (n == 4) {
			texture->format = GL_RGBA;
		}



		texture->create(path, buffer);

		string name = item["name"];
		name= package + "/texture/" + name;
		resource_map[name] = texture;

		env.render->gpu_load(texture);
	}

}

void gxo::ResourceManager::load_shader(string package, sol::table shader)
{
	for (auto config : shader) {
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

void gxo::ResourceManager::load_material(string package, sol::table materials)
{
	for (auto config : materials) {
		auto item = config.second.as<sol::table>();
		string name = item["name"];
		string shader = item["shader"];
		sol::table uniforms = item["uniform"];

		auto material = std::make_shared<Material>();
		material->set_shader(get<Shader>(shader));

		for (auto uniform_config : uniforms) {
			auto unifrom = uniform_config.second.as<sol::table>();
			string name = unifrom[1];
			int type = unifrom[2];
			auto value = unifrom[3];
			Uniform uf;
			uf.data_type = (GPUDataType)type;
			uf.name = Name(name);
			uf.value = load_uniform_value((GPUDataType)type,unifrom);
			material->uniforms.push_back(uf);
		}
		name = package + "/material/" + name;
		resource_map[name] = material;
	}

}

std::any gxo::ResourceManager::load_uniform_value(GPUDataType type,  sol::table unifrom)
{
	switch (type)
	{
	case gxo::GPU_BYTE:
		break;
	case gxo::GPU_SHORT:
		break;
	case gxo::GPU_USHORT:
		break;
	case gxo::GPU_INT:
		break;
	case gxo::GPU_UINT:
		break;
	case gxo::GPU_HALF_FLOAT:
		break;
	case gxo::GPU_FLOAT:
		break;
	case gxo::GPU_VEC2:
		break;
	case gxo::GPU_VEC3:
		break;
	case gxo::GPU_VEC4:
		break;
	case gxo::GPU_MAT3:
		break;
	case gxo::GPU_MAT4:
		break;
	case gxo::GPU_SAMPLE2D: {
		string v = unifrom[3];
		auto tex = get<Texture>(v);
		return std::any(tex);
		break;
	}
	default:
		break;
	}
}
