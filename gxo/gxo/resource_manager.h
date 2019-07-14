#ifndef GXO_RESOURCE_MANAGER_H
#define GXO_RESOURCE_MANAGER_H
#include"resource.h"
#include"gxo_type.h"
#include"config.h"
#include"gxo_log.h"
namespace gxo {
	class ResourceManager
	{
	private:
		//struct ResourceItem {
		//	//std::weak_ptr<Resource> resource;
		//	ResourcePtr resource;
		//	int timeout;
		//	int freqment;
		//};
	public:
		std::map<string, ResourcePtr> resource_map;
	public:
		ResourceManager()
		{
			resource_map.clear();
		}

		~ResourceManager()
		{
		}
		void init() {
			register_default();
			load_resource();
		}
		void load_resource() {
			sol::table tb=Config::instacne().data["resource"];
		
			for (auto package : tb) {
				string name = package.second.as<string>();
				load_package(name);
			}
			
		}
		void load_package(string& path);

		bool add_resource(const string& url, ResourcePtr res) {
			if (resource_map.find(url) != resource_map.end()) {
				error("add same resource");
				return false;
			}
			resource_map[url] = res;
			return true;
		}

		//void check_res

		//ResourcePtr get(UID id, bool sync = true) {
		//	return resource_map[id].resource.lock();
		//}
		ResourcePtr get(string& url, bool sync = true) {
			return resource_map[url];
		}
		template<class T>
		shared_ptr<T> get(const string& url, bool sync = true) {
			return std::dynamic_pointer_cast<T>( resource_map[url]);
		}

		//template<class T>
		//shared_ptr<T> get(string url, bool sync = true) {
		//	return std::dynamic_pointer_cast<T>(resource_map[url]);
		//}

	private:
		//static void resource_deleter(Resource * resource) {
		//	std::cout << "resource_deleter " << resource->url<< std::endl;
		//}


		void register_default();
		////////////////////////////////////////////////////////////////////////////
		void load_texture(string package, sol::table textures);
		void load_shader(string package, sol::table textures);
		void load_material(string package, sol::table materials);
		std::any load_uniform_value(GPUDataType type, sol::table unifrom);
	};
}
#endif
