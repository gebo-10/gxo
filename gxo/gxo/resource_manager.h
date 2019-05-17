#ifndef _GXO_RESOURCE_MANAGER_H
#define _GXO_RESOURCE_MANAGER_H
#include"base.h"
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
		ResourcePtr get(UID id, bool sync) {
			return resource_map[id].resource.lock();
		}
		ResourcePtr get(URL url, bool sync) {

		}

	private:
		void resource_deleter(Resource * resource) {
			std::cout << "resource_deleter " << resource->uid << std::endl;
		}
	};
}
#endif#pragma once
