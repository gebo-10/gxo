#ifndef GXO_TRANSFORM_H
#define GXO_TRANSFORM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
using namespace glm;
namespace gxo {
	class Transform2d
	{
	public:
		vec2  position{0};
		vec2  rotate{0};
		vec2  scale{1};
		Transform2d() {}
		~Transform2d() {}
	};
	class Transform3d
	{
	public:
		vec3  position{ 0 };
		vec3  rotate{ 0 };
		vec3  scale{ 1 };
		Transform3d(){}
		~Transform3d() {}
		mat4 matrix() {
			mat4 identity(1.f);
			mat4 matrix = translate(identity, position)* mat4_cast(quat(radians(rotate))) * glm::scale(identity, scale);
			return matrix;
		}
	};
}
#endif