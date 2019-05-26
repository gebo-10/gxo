#ifndef ENTRY
#define ENTRY
#include <map>
#include <any>
#include <cassert>
namespace gxo {
	typedef  int PropertyType;
	class Entity {
		Entity* m_base;
		std::map<PropertyType, std::any> m_property;
	public:
		std::any& operator[](PropertyType type) {
			auto itr = m_property.find(type);
			if (itr == m_property.end())
			{
				return (*m_base)[type];
			}
			else {
				return m_property[type];
			}
		}

		template<typename T>
		T operator[](PropertyType type) {
			auto itr = m_property.find(type);
			return std::any_cast<T>(m_property[type]);
		}
		template<typename T>
		T get(PropertyType type) {
			auto itr = m_property.find(type);
			if (itr == m_property.end())
			{
				return std::any_cast<T>((*m_base)[type]);
			}
			else {
				return std::any_cast<T>(m_property[type]);
			}
		}

		template<typename T>
		bool overlap(PropertyType type, T t) {
			auto itr = m_property.find(type);
			if (itr == m_property.end())
			{
				(*m_base)[type] = t;
			}
			else {
				m_property[type] = t;
			}
			return true;
		}

		template<typename T>
		bool set(PropertyType type, T t) {
			m_property[type] = t;
			return true;
		}

		bool  remove_property(PropertyType type) {
			auto itr = m_property.find(type);
			if (itr != m_property.end())
			{
				m_property.erase(itr);
				return true;
			}
			return false;

		}
		bool add_property(PropertyType type, std::any property) {
			auto itr = m_property.find(type);
			if (itr != m_property.end())
			{
				assert("Entry: same property type");
				return false;
			}
			m_property[type] = property;
			return true;
		}

	};
}
#endif // ENTRY

