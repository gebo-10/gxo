// base.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib, "glew32sd.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "assimp-vc140-mt.lib")


#include<iostream>

#include "log.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "module.h"

#include "clearcolor.h"
#include "cube_module.h"
#include "fbo_module.h"
#include "blur_module.h"
#include"model_load_module.h"
#include "phong_module.h"
#include "hdr_module.h"

#include "shader_map_module.h"

Module* module=nullptr;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		module->key(key);
	}
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		module->mouse(button, action, xpos, ypos);
	
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	module->mouse(0,0, xpos, ypos);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	module->set_size(width, height);
}

int main()
{

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	GLenum result = glewInit();
	if (result != GLEW_OK)
	{
		error("glewInit failed");
		abort();
	}


	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);


	//module = new ClearColor();
	//module = new CubeModule();
	//module = new FboModule();
	//module = new BlurModule();
	//module = new ModelLoadModule();
	//module = new LightModule();
	//module = new HdrModule();
	module = new ShadowMapModule();

	module->window_height = 800;
	module->window_width = 800;
	module->init();
	/* Loop until the bind()r closes the window */
	while (!glfwWindowShouldClose(window))
	{
		module->render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}