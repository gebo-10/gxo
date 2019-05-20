#ifndef _GXO_WINDOW_SYSTEM_H
#define _GXO_WINDOW_SYSTEM_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
		}

		void update() {
			
			if (!glfwWindowShouldClose(window))
			{
				/* Draw a triangle */
				glBegin(GL_TRIANGLES);

				glColor3f(1.0, 0.0, 0.0);    // Red
				glVertex3f(0.0, 1.0, 0.0);

				glColor3f(0.0, 1.0, 0.0);    // Green
				glVertex3f(-1.0, -1.0, 0.0);

				glColor3f(0.0, 0.0, 1.0);    // Blue
				glVertex3f(1.0, -1.0, 0.0);

				glEnd();

				/* Swap front and back buffers */
				glfwSwapBuffers(window);

				/* Poll for and process events */
				glfwPollEvents();
			}
		}

	private:

	};

}
#endif