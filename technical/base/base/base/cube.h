#ifndef GXO_CUBE_H
#define GXO_CUBE_H
#include"mesh.h"

/**
 * The following illustrates the orientation of the
 * bounding box in local space
 *
 * <pre>
 *
 * y  z
 * | /
 * |/
 * .-----X
 *
 *
 *     2----------6
 *    /|         /|
 *   / |        / |
 *  1----------5  |
 *  |  |       |  |
 *  |  3-------|--7
 *  | /        | /
 *  |/         |/
 *  0----------4
 * </pre>
 */


	class Cube :public Mesh
	{
	public:
		float vertices[120] = {
			// Positions			// coord
			-0.5f, 0.5f, 0.5f,     0.0f, 0.0f, // ǰ���� 0
			 -0.5f, -0.5f, 0.5f,    0.0f, 1.0f, // ǰ���� 1
			 0.5f, -0.5f, 0.5f,     1.0f, 1.0f, // ǰ���� 2
			 0.5f, 0.5f, 0.5f,      1.0f, 0.0f, // ǰ���� 3
			// ����
			 -0.5f, 0.5f, -0.5f,     1.0f, 0.0f, // ������ 4
			 -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, // ������ 5
			 0.5f, -0.5f, -0.5f,     0.0f, 1.0f, // ������ 6
			 0.5f, 0.5f, -0.5f,      0.0f, 0.0f, // ������ 7
			// ����
			 -0.5f, 0.5f, -0.5f,     0.0f, 0.0f, // ������ 8
			 -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, // ������ 9
			 -0.5f, 0.5f, 0.5f,     1.0f, 0.0f, // ǰ���� 10
			 -0.5f, -0.5f, 0.5f,    1.0f, 1.0f, // ǰ���� 11
			// ����
			 0.5f, 0.5f, 0.5f,      0.0f, 0.0f, // ǰ���� 12
			 0.5f, -0.5f, 0.5f,     0.0f, 1.0f, // ǰ���� 13
			 0.5f, -0.5f, -0.5f,     1.0f, 1.0f, // ������ 14
			 0.5f, 0.5f, -0.5f,      1.0f, 0.0f, // ������ 15
			// ����
			 -0.5f, 0.5f, -0.5f,     0.0f, 0.0f, // ������ 16
			 -0.5f, 0.5f, 0.5f,     0.0f, 1.0f, // ǰ���� 17
			 0.5f, 0.5f, 0.5f,      1.0f, 1.0f, // ǰ���� 18
			 0.5f, 0.5f, -0.5f,      1.0f, 0.0f, // ������ 19
			// ����
			 -0.5f, -0.5f, 0.5f,    0.0f, 0.0f, // ǰ���� 20
			 0.5f, -0.5f, 0.5f,     1.0f, 0.0f, // ǰ���� 21
			 -0.5f, -0.5f, -0.5f,    0.0f, 1.0f, // ������ 22
			 0.5f, -0.5f, -0.5f,     1.0f, 1.0f, // ������ 23
		};
		unsigned short index[36] = {
			0, 1, 2,
			0, 2, 3,
			// ����
			4, 5, 6,
			4, 6, 7,
			// ����
			8, 9, 11,
			8, 11, 10,
			// ����
			12, 13, 14,
			12, 14, 15,
			// ����
			16, 17, 18,
			16, 18, 19,
			// ����
			20, 22, 23,
			20, 23, 21,
		};

		float vertices2[120] = {
			-1.0f,  1.0f, -1.0f, 0.0f,  1.0f,/* Back. */
			 1.0f,  1.0f, -1.0f, 1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f, 0.0f,  0.0f,
			 1.0f, -1.0f, -1.0f, 1.0f,  0.0f,

			-1.0f,  1.0f,  1.0f, 0.0f,  1.0f,/* Front. */
			 1.0f,  1.0f,  1.0f, 1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f, 0.0f,  0.0f,
			 1.0f, -1.0f,  1.0f, 1.0f,  0.0f,

			-1.0f,  1.0f, -1.0f, 1.0f,  0.0f, /* Left. */
			-1.0f, -1.0f, -1.0f, 0.0f,  0.0f,
			-1.0f, -1.0f,  1.0f, 0.0f,  1.0f,
			-1.0f,  1.0f,  1.0f, 1.0f,  1.0f,

			 1.0f,  1.0f, -1.0f, 1.0f,  0.0f,/* Right. */
			 1.0f, -1.0f, -1.0f, 0.0f,  0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,  1.0f,
			 1.0f,  1.0f,  1.0f, 1.0f,  1.0f,

			-1.0f, -1.0f, -1.0f, 0.0f,  0.0f,/* Top. */
			-1.0f, -1.0f,  1.0f, 0.0f,  1.0f,
			 1.0f, -1.0f,  1.0f, 1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f, 1.0f,  0.0f,

			-1.0f,  1.0f, -1.0f, 0.0f,  0.0f,/* Bottom. */
			-1.0f,  1.0f,  1.0f, 0.0f,  1.0f,
			 1.0f,  1.0f,  1.0f, 1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f, 1.0f,  0.0f
		};
		unsigned short index2[36] = {
			0, 2, 3, 0, 1, 3,
			4, 6, 7, 4, 5, 7,
			8, 9, 10, 11, 8, 10,
			12, 13, 14, 15, 12, 14,
			16, 17, 18, 16, 19, 18,
			20, 21, 22, 20, 23, 22
		};

		Cube()
		{
			vertex.data = (byte*)vertices;
			vertex.size = sizeof(vertices);

			indices.data = (byte*)index;
			indices.size = sizeof(index);
			element_size = 36;

			add_default_attr(VAT_POSITION);
			add_default_attr(VAT_UV0);

			build();
		}

		~Cube()
		{
		}

	private:

	};
	typedef shared_ptr< Cube> CubePtr;
#endif