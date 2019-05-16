#ifndef _GXO_RESOURCE_H
#define _GXO_RESOURCE_H
#include"id.h"
#include<string>
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
		UUID m_uuid;
		URL m_url;
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