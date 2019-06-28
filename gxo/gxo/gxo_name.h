#ifndef _GXO_NAME_H
#define _GXO_NAME_H
#include"gxo_type.h"
#include"gxo_id.h"
namespace gxo {
	class Name {
	public:
		Name(): name_id(0) {}

		Name(string name) {
			name_id = NameMap::instance().add(name);
		}
		UID ID() {
			return UID(name_id);
		}
		string to_string() {
			return NameMap::instance().to_string(name_id);
		}

		static UID to_id(std::string name) {
			return UID(NameMap::instance().to_id(name));
		}

	private:
		uint32 name_id;
		class NameMap {
		public:
			static NameMap &instance() {
				static NameMap name_map;
				return name_map;
			}
			string to_string(uint32 id) {
				return id_to_name[id];
			}

			uint32 to_id(std::string name) {
				return name_to_id[name];
			}

			uint32 add(std::string name) {
				auto itr = name_to_id.find(name);
				if (itr == name_to_id.end()) {
					return itr->second;
				};

				auto new_id = UID::gen().id;
				id_to_name[new_id] = name;
				name_to_id[name] = new_id;
				return new_id;
			}

		private:
			//uint32 index; use UID
			std::map<uint32, std::string> id_to_name;
			std::map<std::string, uint32> name_to_id;
			NameMap() {
				//index = 0;
				id_to_name.clear();
				name_to_id.clear();
			}
		};
	};
}
#endif