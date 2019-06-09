enum DataType
{
	DT_INVALD,
	DT_POINT,
	DT_INT,
	DT_SHORT,
	DT_CHAR,
	//DT_STRING,
	DT_STRUCT,
	DT_ARRAY,
	DT_CHAR_VIEW,
	DT_FUNCTION,

};
class Type
{
public:
	struct Attribute //成员  函数返回值和参数  指针指向类型
	{
		Type* type;
		int offset;
	};
	DataType data_type;
	int size;
	std::string type_name;
	std::map<std::string, Attribute> attr;

public:
	Attribute* get_field(std::string_view name) {
		return attr[name];
	}

	Attribute* get_function(std::string_view name) {
		return attr[name];
	}

	Attribute* get_point_type(std::string_view name) {
		return attr[name];
	}
};
