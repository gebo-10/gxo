#ifndef	GXO_SHADER_H
#define	GXO_SHADER_H
#include"gxo_type.h"
#include"gxo_name.h"
#include"gpu_header.h"
#include<any>
namespace gxo {
	class Uniform
	{
	public:
		Name name;
		int location;
		GPUDataType data_type;
		std::any value;

		Uniform(){}
		~Uniform(){}
	};

	//class UniformBlock
	//{
	//public:
	//	int location;
	//	Meta data_type;
	//	UniformBlock() {}
	//	~UniformBlock() {}
	//};



	class Shader
	{
	public:
		GLuint id;
		std::vector<Uniform> uniforms;
		Shader()
		{
		}

		~Shader()
		{
		}

	private:
		
	};
	typedef shared_ptr<Shader> ShaderPtr;
}

#endif