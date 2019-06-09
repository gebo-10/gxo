#include"render_system.h"
#include"engine.h"

void gxo::RenderSystem::update()
{
	//
	//glBegin(GL_TRIANGLES);

	//glColor3f(1.0, 0.0, 0.0);    // Red
	//glVertex3f(0.0, 1.0, 0.0);

	//glColor3f(0.0, 1.0, 0.0);    // Green
	//glVertex3f(-1.0, -1.0, 0.0);

	//glColor3f(0.0, 0.0, 1.0);    // Blue
	//glVertex3f(1.0, -1.0, 0.0);

	//glEnd();

	Engine::instacne().tree_manager.visit_preorder([](TreeNode * node) -> bool{
		node->add_property(TAG, 10);
		return true;
	});

	Engine::instacne().window_system.swap_buffer();
	
}
