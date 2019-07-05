#ifndef GXO_CAMERA_H
#define GXO_CAMERA_H
#include"gxo_math.h"
namespace gxo {
	class Camera  {
	public:
		enum CameraType {
			ORTHO,
			PERSPECTIVE,
		};
		CameraType type = ORTHO;
		int width=100;
		int height=100;
		float fov = 45.f;
		float znear = 0.001f;
		float zfar = 1000.f;

		vec3 position{ 4.f };
		vec3 target{ 0.f };
		mat4 projection{ 1.f };
		mat4 view_matrix{ 1.f };

		bool dirty = false;

		Camera(){}

		void lookat(vec3 position, vec3 target,vec3 up) {
			position = position;
			target = target;
			view_matrix=lookAt(position, target, up);
		}

		mat4 matrix() {
			if (dirty) {
				update_matrix();
			}
			return projection * view_matrix;
		}

		mat4 get_projectionx(){
			if (dirty) {
				update_matrix();
			}
			return projection;
		}

		void Camera::update_matrix() {
			switch (type)
			{
			case gxo::Camera::ORTHO:
				float half_w = width / 2.0f;
				//float aspect = (float)height / (float)width;
				float half_h = height / 2.0f;
				projection = ortho(-half_w, half_w, -half_h, half_h, znear, zfar);
				break;
			case gxo::Camera::PERSPECTIVE:
				projection = perspective(radians(fov), (float)width / (float)height, znear, zfar);
				break;
			default:
				break;
			}
			dirty = false;
		}
	
		void set_fov(float fov) {
			this->fov = fov;
			dirty = true;
		}

		void set_ortho(int width, int height) {
			this->width = width;
			this->height = height;
			dirty = true;
		}

		void set_near(float near) {
			this->znear = near;
			dirty = true;
		}

		void set_far(float far) {
			this->znear = far;
			dirty = true;
		}

	};

}
#endif