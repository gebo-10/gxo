#ifndef GXO_WINDOW_SYSTEM_H
#define GXO_WINDOW_SYSTEM_H
#include "gpu_header.h"
#include <GLFW/glfw3.h>
#include<iostream>
#include "gxo_rect.h"
#include "config.h"
namespace gxo {
	class WindowSystem
	{
	public:
		GLFWwindow * window;
		Rect rect;
		WindowSystem()
		{
		}

		~WindowSystem()
		{
			glfwTerminate();
		}

		void init() {
			if (!glfwInit())
				return;

			//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
			//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_SAMPLES, 32);

			//glfwWindowHint(GLFW_SAMPLES, 0);
			//glfwWindowHint(GLFW_RED_BITS, 8);
			//glfwWindowHint(GLFW_GREEN_BITS, 8);
			//glfwWindowHint(GLFW_BLUE_BITS, 8);
			//glfwWindowHint(GLFW_ALPHA_BITS, 8);
			//glfwWindowHint(GLFW_STENCIL_BITS, 8);
			glfwWindowHint(GLFW_DEPTH_BITS, 24);
			//glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);


			/* Create a windowed mode window and its OpenGL context */
			std::string name = Config::instacne().data["name"];
			rect.width = Config::instacne().data["width"];
			rect.height = Config::instacne().data["height"];
			window = glfwCreateWindow(rect.width, rect.height , name.c_str(), NULL, NULL);
			if (!window)
			{
				glfwTerminate();
				return;
			}

	

			/* Make the window's context current */
			//glfwMakeContextCurrent(window);

			glfwSetMouseButtonCallback(window, mouse_button_callback);
			glfwSetWindowSizeCallback(window, window_size_callback);
			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
			glfwSetWindowCloseCallback(window, window_close_callback);
			return;
		}
		void make_current() {
			glfwMakeContextCurrent(window);
		}
		void swap_buffer() {
			//glfwSwapInterval(16);
			glfwSwapBuffers(window);
		}

		void update() {
			glfwPollEvents();
			//if (!glfwWindowShouldClose(window))
			//{
			//	glfwPollEvents();
			//}
		}
		
		void stop() {
			glfwDestroyWindow(window);
			glfwTerminate();
		}
	private:
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
				std::cout << "right button press" << std::endl;
				//popup_menu();
		}

		static void window_size_callback(GLFWwindow* window, int width, int height);
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void window_close_callback(GLFWwindow* window);

	};

}
#endif