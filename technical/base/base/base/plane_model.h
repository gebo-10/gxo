#ifndef PLANE_MODEL_H
#define PLANE_MODEL_H
#include "model.h"
#include "plane.h"
#include "texture_material.h"
class PlaneModel :public Model
{
public:
	PlaneModel(MaterialPtr mat) :Model(nullptr, nullptr)
	{
		this->material = mat;
		this->mesh = std::make_shared<Plane>();
	}

};
typedef shared_ptr<PlaneModel> PlaneModelPtr;

#endif
