#ifndef GROUND_H
#define GROUND_H
#include "model.h"
#include "texture_material.h"
class Ground :public Model
{
public:
	Ground() :Model("main/mesh/plane.gltf")
	{
		this->material = std::make_shared<TextureMaterial>(std::make_shared<Texture>("main/texture/grid20.jpg"));
		transform.scale = vec3(2, 0, 2);
		transform.position = vec3(0, -1, 0);
	}

	void set_texture(TexturePtr texture) {
		std::dynamic_pointer_cast<TextureMaterial>(material)->set_texture(texture);
	}

};
typedef shared_ptr<Ground> GroundlPtr;

#endif
