#ifndef GXO_RESOURCE_H
#define GXO_RESOURCE_H
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

		//enum CacheState
		//{
		//	DYNAMIC,
		//	ALWAYS,
		//	NEWER,
		//};
		//CacheState cache_type;

		int resource_type;
		//UID uid;

		string url;
		
		Buffer ram;
		
		bool lock; //提交状态 设置为true cmd处理完成设置为false 并且notify_all resource manager  如果修改需要循环判断是否锁定 如果锁定就wait resource manager

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


		virtual void gpu_load() {

		}

		virtual void gpu_unload() {

		}
		virtual void ram_load() {

		}
		virtual void ram_unload() {

		}
		
	};
	typedef  shared_ptr<Resource> ResourcePtr;
}

#endif