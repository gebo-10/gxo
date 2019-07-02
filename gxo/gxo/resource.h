#ifndef _GXO_RESOURCE_H
#define _GXO_RESOURCE_H
#include"gxo_id.h"
#include"gxo_buffer.h"
#include"gpu_header.h"
namespace gxo {
	class Resource
	{
	public:
		enum CacheType
		{
			DYNAMIC,
			ALWAYS,
			NEWER,
		};
		CacheType cache_type;

		enum MemeryType
		{
			GPU,
			RAM,
			GPURAM,
		};
		MemeryType memery_type;

		int resource_type;
		//UID uid;

		string url;
		
		Buffer ram;
		
	public:
		Resource()
		{
		}

		virtual ~Resource()
		{
		}
		void create(string &in_url,Buffer& in_ram) {
			url = in_url;
			ram = in_ram;
			on_load();
		}

		virtual void on_load() {

		}

		virtual void unload_gpu() {

		}
		virtual void unload_ram() {

		}
	};
	typedef  shared_ptr<Resource> ResourcePtr;
}

#endif