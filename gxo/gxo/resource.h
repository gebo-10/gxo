#ifndef _GXO_RESOURCE_H
#define _GXO_RESOURCE_H
#include"base.h"
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
		UID uid;
		URL url;
	public:
		Resource()
		{
		}

		~Resource()
		{
		}
	};
	typedef  std::shared_ptr<Resource> ResourcePtr;
}
#endif