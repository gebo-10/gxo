#ifndef _GXO_RESOURCE_H
#define _GXO_RESOURCE_H
#include"gxo_id.h"
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
		//URL url;
	public:
		Resource()
		{
		}

		~Resource()
		{
		}
	};
}

#endif