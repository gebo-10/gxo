#ifndef _GXO_NAME_MANAGER_H
#define _GXO_NAME_MANAGER_H
#include"name.h"
namespace gxo {
	class NameManager {
	public:
		std::map<UID, Name> name;
		std::map<std::string, UID> name;
		string to_string() {

		}
	};

}
#endif