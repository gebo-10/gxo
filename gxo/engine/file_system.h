#ifndef GXO_FILESYSYTEM_H
#define GXO_FILESYSYTEM_H
#include"gxo_type.h"
#include"gxo_buffer.h"
#include<fstream>
namespace gxo {
	class FileSystem
	{
	public:
		FileSystem()
		{
		}

		~FileSystem()
		{
		}
		void init() {

		}

		void get_sync(string& path, Buffer& buffer) {
			std::ifstream filestr;
			filestr.open(path, std::ios::binary);
			auto pbuf = filestr.rdbuf();
			auto size = pbuf->pubseekoff(0, std::ios::end, std::ios::in);
			pbuf->pubseekpos(0, std::ios::in);
			buffer.malloc(size);
			pbuf->sgetn((char *)buffer.data, size);
			filestr.close();
		}
		void get_async(string_view path, Buffer& buffer) {

		}

		void* map_file(string_view path) {
			return nullptr;
		}
	private:

	};
}
#endif