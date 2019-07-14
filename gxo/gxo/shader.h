#ifndef	GXO_SHADER_H
#define	GXO_SHADER_H
#include"gxo_type.h"
#include"gxo_name.h"
#include"gpu_header.h"
#include<any>
#include"resource.h"
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



	class Shader:public Resource
	{
	public:
		GPUID gpu_id=0;
		//std::vector<Uniform> uniforms;
		GPUID vertex_shader=0;
		GPUID frag_shader=0;

		Buffer vs_source;
		Buffer fs_source;
		Shader()
		{
		}

		~Shader()
		{
		}
		
		void use() {
			glUseProgram(gpu_id);
		}

		void gpu_load() override {
			BuildVertexShader((char *)vs_source.data);
			BuildFragShader((char*)fs_source.data);
			BuildProgram();
		}
	private:
		bool BuildVertexShader(char* source);
		bool BuildFragShader(char* source);
		bool BuildProgram();
	};
	typedef shared_ptr<Shader> ShaderPtr;
}

#endif