#ifndef GXO_RESOURCE_MANAGER_H
#define GXO_RESOURCE_MANAGER_H
#include"resource.h"
#include"gxo_type.h"
#include"config.h"

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

		bool add_resource(Resource * res) {

		}

		//void check_res

		//ResourcePtr get(UID id, bool sync = true) {
		//	return resource_map[id].resource.lock();
		//}
		ResourcePtr get(string& url, bool sync = true) {
			return resource_map[url];
		}
		template<class T>
		shared_ptr<T> get(string& url, bool sync = true) {
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



		////////////////////////////////////////////////////////////////////////////
		void load_texture(string package, sol::table textures);
		void load_shader(string package, sol::table textures);
		void load_material(string package, sol::table materials);
	};
}
#endif
