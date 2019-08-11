#ifndef TEXTURE_PLANE_MODEL_H
#define TEXTURE_PLANE_MODEL_H
#include "model.h"
#include "plane.h"
#include "texture_material.h"
class TexturePlaneModel :public Model
{
public:
	TexturePlaneModel( TexturePtr texture):Model(nullptr,nullptr)
	{
		this->material=std::make_shared<TextureMaterial>(texture);
		this->mesh = std::make_shared<Plane>();
	}


	void set_texture(TexturePtr texture) {
		std::dynamic_pointer_cast<TextureMaterial>(material)->set_texture(texture);
	}

};
typedef shared_ptr<TexturePlaneModel> TexturePlaneModelPtr;

#endif
