#ifndef GXO_PLANE_H
#define GXO_PLANE_H
#include"gxo_type.h"
#include"mesh.h"
namespace gxo {
	class Plane :public Mesh
	{
	public:
		float vertices[20] = {
			// Positions			// coord
			0.0f, 0.0f,0.0f,		0.0f, 1.0f,
			1.0f, 0.0f,0.0f,		1.0f, 1.0f,
			0.0f, 1.0f,0.0f,		0.0f, 0.0f,
			1.0f, 1.0f,0.0f,		1.0f, 0.0f,
		};
		unsigned short index[6] = { 0,1,2, 2,3,1 };
		Plane()
		{
			vertex.data = (byte*)vertices;
			vertex.size = sizeof(vertices);

			indices.data = (byte*)index;
			indices.size = sizeof(index);
			size = 6;

			vertex_attr.push_back(GPU_VEC3);
			vertex_attr.push_back(GPU_VEC2);
		}

		~Plane()
		{
		}

	private:

	};

}
#endif