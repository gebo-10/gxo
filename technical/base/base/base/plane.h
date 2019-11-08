#ifndef GXO_PLANE_H
#define GXO_PLANE_H

#include"mesh.h"

	class Plane :public Mesh
	{
	public:
		float vertices[20] = {  //TODO ¸ÄÎªstatic
			// Positions			// coord
			-0.5f, -0.5f,0.0f,		0.0f, 0.0f,
			0.5f, -0.5f,0.0f,		1.0f, 0.0f,
			-0.5f, 0.5f,0.0f,		0.0f, 1.0f,
			0.5f, 0.5f,0.0f,		1.0f, 1.0f,
		};
		unsigned short index[6] = { 0,1,2, 2,3,1 };
		Plane()
		{
			vertex.data = (byte*)vertices;
			vertex.size = sizeof(vertices);

			indices.data = (byte*)index;
			indices.size = sizeof(index);
			element_size = 6;

			add_default_attr(VAT_POSITION);
			add_default_attr(VAT_UV0);

			build();
		}

		~Plane()
		{
		}

	private:

	};

#endif