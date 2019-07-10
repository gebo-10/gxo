#include"render_system.h"
#include"engine.h"
#include"ui_node.h"
#include"evn.h"
#include"camera.h"
#include "gpu_type.h"
void gxo::RenderSystem::init()
{
	
	render.init();

	return ;
}

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
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(-1, 1, -1, 1, -4, 4000);
	//glViewport(0, 0, Engine::instacne().window_system.rect.width-300, Engine::instacne().window_system.rect.height);



	//glClearColor(0.f, 0.f, 0.f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
	//auto rect = Rect(0, 0, 500, 500);
	//Engine::instacne().tree_manager.screen.on_layout(rect);

	//Engine::instacne().tree_manager.visit_preorder([](TreeNode * node) -> bool{
	//	return node->on_render();
	//});
	//Engine::instacne().window_system.swap_buffer();




	//auto rect = Rect(0, 0, 500, 500);
	//Engine::instacne().tree_manager.screen.on_layout(rect);
	//Engine::instacne().tree_manager.screen.on_render();
	//render.rcmd(RCMD_SWAPBUFFER);
	static float r = 0.0f;
	r += 0.001;
	render.rcmd(RCMD_CLEAR, Color(r, 1 - r, 1.0, 1.0));


	Camera a;
	a.set_type(Camera::PERSPECTIVE);
	a.set_ortho(500, 500);
	a.set_fov(60);
	a.lookat(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 0, 1));
	auto p = a.get_p();
	auto v = a.get_v();


	static float vertices[] = {
		// Positions         // Colors
		0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // Bottom Left
		0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f   // Top 
	};
	static unsigned short index[] = { 2, 1, 0 };
	auto mesh = std::make_shared<Mesh>();
	mesh->vertex.data = (byte*)vertices;
	mesh->vertex.size = sizeof(vertices);

	mesh->indices.data = (byte*)index;
	mesh->indices.size = sizeof(index);
	mesh->size = 3;

	mesh->vertex_attr.push_back(GPU_VEC3);
	mesh->vertex_attr.push_back(GPU_VEC3);

	render.gpu_load(mesh);


	string name = "main/material/Default";
	auto material = env.engine->resource_manager.get<Material>(name);
	render.gpu_load(material);

	auto pipe = std::make_shared<Pipeline>();

	
	pipe->material = *material;
	pipe->viewport = Rect(0, 0, 500, 500);
	pipe->target = std::make_shared<RenderTarget>();

	pipe->P = p;
	pipe->V = v;

	render.rcmd(RCMD_SET_PIPELINE, pipe);

	render.rcmd(RCMD_MESH, mesh, mat4{ 1.0 });


	



	render.rcmd(RCMD_SWAPBUFFER);
	//Sleep(100);
}


