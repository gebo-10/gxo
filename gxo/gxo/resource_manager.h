#ifndef _GXO_RESOURCE_MANAGER_H
#define _GXO_RESOURCE_MANAGER_H
#include"core.h"
#include"resource.h"
namespace gxo {
	class ResourceManager
	{
	private:
		struct ResourceItem {
			std::weak_ptr<Resource> resource;
			int timeout;
			int freqment;
		};
	public:
		std::map<UID, ResourceItem> resource_map;
	public:
		ResourceManager()
		{
			
		}

		~ResourceManager()
		{
		}
		ResourcePtr get(UID id, bool sync = true) {
			return resource_map[id].resource.lock();
		}
		ResourcePtr get(string_view &url, bool sync = true) {
			return get(Name::to_id(url).id, sync);
		}

	private:
		void resource_deleter(Resource * resource) {
			std::cout << "resource_deleter " << resource->uid .id<< std::endl;
		}
	};
}
#endif#pragma once
