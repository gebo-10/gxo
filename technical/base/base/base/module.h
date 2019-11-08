#ifndef MODULE_H
#define MODULE_H
#include "shader.h"
#include "model.h"
#include "plane.h"
#include "cube.h"
#include "texture_material.h"
#include "render_target.h"
#include "texture_plane_model.h"
#include "blur_material.h"
#include "phong_material.h"
#include "ground.h"
#include "hdr_texture.h"
#include "hdr_render_target.h"

#include "blit_pass.h"
#include "screen_target.h"
#include "blur_pass.h"
#include "texture_blit_pass.h"
#include "msaa_render_target.h"
#include "msaa_rtt_pass.h"
#include "times_blur_pass.h"
#include "depth_render_target.h"
#include "shadow_ground.h"
#include "bone_material.h"
#include "bone_model.h"
//#include "fbx_model.h"
#include "gltf_model.h"

class Module
{
public:
	Module()
	{
	}

	~Module()
	{
	}
	int window_width;
	int window_height;
	virtual void init() {}
	virtual void render(){}

	virtual void key(int key){}

	virtual void mouse(int button, int action, int x, int y){}

	virtual void on_size(int width, int height) {}

	void set_size(int w, int h) {
		window_width = w;
		window_height = h;
		on_size(w, h);
	}
private:

};

#endif
