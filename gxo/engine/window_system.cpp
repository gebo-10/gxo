#include "window_system.h"
#include "gxo_event.h"
#include "env.h"
void gxo::WindowSystem::window_size_callback(GLFWwindow* window, int width, int height)
{
	
}

void gxo::WindowSystem::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	if (width == 0 && height == 0)
	{
		return;
	}
	Event event;
	event.type = GXO_EVENT_RESIZE;
	event.resize.width = width;
	event.resize.height = height;
	env.event->process_event(&event);
}

void gxo::WindowSystem::window_close_callback(GLFWwindow* window)
{
	//glfwSetWindowShouldClose(window, GLFW_FALSE);
	env.engine->stop();
	//glfwSetWindowShouldClose(window, true);
}
