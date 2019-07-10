#include "shader.h"
#include"gxo_log.h"
using namespace gxo;

bool Shader::BuildVertexShader(char * source)
{
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);

	if (0 == vertex_shader)
	{
		error("Create vertex shader failed");
		return false;
	}

	const GLchar *vCodeArray[1] = { source };
	glShaderSource(vertex_shader, 1, vCodeArray, NULL);


	glCompileShader(vertex_shader);


	GLint compileResult;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;

		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			glGetShaderInfoLog(vertex_shader, logLen, &written, log);
			error("vertex shader compile log : {}", log); 
			free(log);
		}
		return false;
	}
	return true;
}

bool Shader::BuildFragShader(char * source)
{

	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	if (0 == frag_shader)
	{
		error(" Create fragment shader failed");
		return false;
	}


	const GLchar *fCodeArray[1] = { source };
	glShaderSource(frag_shader, 1, fCodeArray, NULL);

	glCompileShader(frag_shader);

	GLint compileResult;
	glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;

		glGetShaderiv(frag_shader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;

			glGetShaderInfoLog(frag_shader, logLen, &written, log);
			error("fragment shader compile log : {}",log); 
			free(log);
		}
		return false;
	}
	return true;
}

bool Shader::BuildProgram()
{
	if (vertex_shader ==0 || frag_shader==0)
	{
		return false;
	}

	GLuint program = glCreateProgram();
	if (!program)
	{
		error("ERROR : create program failed");
		return false;
	}

	glAttachShader(program, vertex_shader);
	glAttachShader(program, frag_shader);

	
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
		glGetProgramiv(program, GL_INFO_LOG_LENGTH,&logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(program, logLen,
				&written, log);
			error("Program log :{}" , log);
		}
		return false;
	}
	info("build shader success");
	gpu_id = program;
	return true;
}
