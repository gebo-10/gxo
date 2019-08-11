#ifndef SHADER_H
#define SHADER_H
#include "core_base.h"
#include "mmap.h"
class Shader{
public:
	GPUID gpu_id = 0;

	Shader(string_view vs_file, string_view fs_file, string_view gs_file="", string_view ts_control_file = "", string_view ts_evaluation_file = "")
	{
		Mmap vs(vs_file);
		Mmap fs(fs_file);

		string_view gs_source = "";
		if (!gs_file.empty())
		{
			Mmap gs(gs_file);
			gs_source = gs.memery;
		}
		string_view ts_control_source = "";
		string_view ts_evaluation_source = "";
		if (!ts_control_file.empty() && !ts_evaluation_file.empty())
		{
			Mmap ts_control(ts_control_file);
			ts_control_source = ts_control.memery;
			Mmap ts_evaluation(ts_evaluation_file);
			ts_evaluation_source = ts_evaluation.memery;
		}

		build(vs.memery, fs.memery, gs_source, ts_control_source, ts_evaluation_source);
	}

	void build(string_view vs_source, string_view fs_source, string_view gs_source = "", string_view ts_control_source = "", string_view ts_evaluation_source = "")
	{
		auto vs = build_shader(GL_VERTEX_SHADER, vs_source);
		auto fs = build_shader(GL_FRAGMENT_SHADER, fs_source);
		auto gs = build_shader(GL_GEOMETRY_SHADER, gs_source);
		auto ts_control = build_shader(GL_TESS_CONTROL_SHADER, ts_control_source);
		auto ts_evaluation = build_shader(GL_TESS_EVALUATION_SHADER, ts_evaluation_source);
		auto succ = build_program(vs,fs,gs,ts_control, ts_evaluation);
		if (succ)
		{
			info("build shader success");
		}
	}

	~Shader()
	{
		glDeleteProgram(gpu_id);
	}

	void bind() {
		glUseProgram(gpu_id);
	}

	//void attach_geometry_shader(string_view gs_file) {}
	//void attach_geometry_shader(string_view gs) {}
	//void attach_tesselation_shader(string_view ts_control_file, string_view ts_evaluation_file) {}
	//void attach_tesselation_shader(string_view ts_control, string_view ts_evaluation) {}

private:
	GPUID build_shader(int shader_type, string_view source) {
		if (source.empty())
		{
			return 0;
		}
		GPUID shader = glCreateShader(shader_type);

		if (0 == shader)
		{
			error("Create vertex shader failed :{}", source);
			return 0;
		}

		const GLchar* vCodeArray[1] = { source.data() };
		glShaderSource(shader, 1, vCodeArray, NULL);
		glCompileShader(shader);

		GLint compileResult;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
		if (GL_FALSE == compileResult)
		{
			GLint logLen;

			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
			if (logLen > 0)
			{
				char* log = (char*)malloc(logLen);
				GLsizei written;
				glGetShaderInfoLog(shader, logLen, &written, log);
				error("vertex shader compile log : {}", log);
				free(log);
			}
			return 0;
		}
		return shader;
	}

	bool build_program(GPUID fs, GPUID vs, GPUID gs, GPUID ts_control, GPUID ts_evaluation) {
		if (fs == 0 || vs == 0)
		{
			error("build_program error :fs == 0 || vs == 0");
			return false;
		}

		GLuint program = glCreateProgram();
		if (!program)
		{
			error("create program failed");
			return false;
		}

		glAttachShader(program, fs);
		glAttachShader(program, vs);
		if (gs != 0) {
			glAttachShader(program, gs);
		}
		if (ts_control !=0 && ts_evaluation!= 0) {
			glAttachShader(program, ts_control);
			glAttachShader(program, ts_evaluation);
		}

		glLinkProgram(program);

		//int block_index = glGetUniformBlockIndex(program, "Global");
		//glUniformBlockBinding(program, block_index, 0);

		//block_index = glGetUniformBlockIndex(program, "Light");
		//glUniformBlockBinding(program, block_index, 1);


		GLint linkStatus;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (GL_FALSE == linkStatus)
		{
			error("ERROR : link shader program failed");
			GLint logLen;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
			if (logLen > 0)
			{
				char* log = (char*)malloc(logLen);
				GLsizei written;
				glGetProgramInfoLog(program, logLen,
					&written, log);
				error("Program log :{}", log);
			}
			glDeleteProgram(program);
			gpu_id = 0;
			return false;
		}

		//delete_shader(vs);
		//delete_shader(fs);
		//delete_shader(gs);
		//delete_shader(ts_control);
		//delete_shader(ts_evaluation);

		gpu_id = program;
		return true;
	}

	void delete_shader(GPUID id) {
		if (id!=0)
		{
			glDeleteShader(id);
		}
	}
};
typedef shared_ptr<Shader> ShaderPtr;

#endif