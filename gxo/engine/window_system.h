#ifndef _GXO_WINDOW_SYSTEM_H
#define _GXO_WINDOW_SYSTEM_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
namespace gxo {
	class WindowSystem
	{
	public:
		GLFWwindow * window;
		WindowSystem()
		{
		}

		~WindowSystem()
		{
			glfwTerminate();
		}

		bool init() {
			if (!glfwInit())
				return false;
			/* Create a windowed mode window and its OpenGL context */
			window = glfwCreateWindow(480, 320, "Hello World", NULL, NULL);
			if (!window)
			{
				glfwTerminate();
				return false;
			}

			/* Make the window's context current */
			glfwMakeContextCurrent(window);

			glfwSetMouseButtonCallback(window, mouse_button_callback);
		}

		void swap_buffer() {
			glfwSwapBuffers(window);
		}

		void update() {
			glfwPollEvents();
			//if (!glfwWindowShouldClose(window))
			//{
			//	glfwPollEvents();
			//}
		}

	private:
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
				std::cout << "right button press" << std::endl;
				//popup_menu();
		}
	};

}
#endif