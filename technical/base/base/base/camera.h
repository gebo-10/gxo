#ifndef GXO_CAMERA_H
#define GXO_CAMERA_H
#include"core_base.h"

	class Camera {
	public:
		enum CameraType {
			ORTHO,
			PERSPECTIVE,
		};
		CameraType type = PERSPECTIVE;
		//int width = 100;
		//int height = 100;
		//Rectf ortho_rect;
		vec4 ortho_rect=vec4(-1,1,-1,1);
		float fov = 60.f;
		float znear = 0.1f;
		float zfar = 100.f;

		vec3 position{ 0.f };
		vec3 target{ 0.f };
		mat4 projection{ 1.f };
		mat4 view_matrix{ 1.f };

		bool dirty = true;

		Camera() {}

		void lookat(vec3 position, vec3 target, vec3 up) {
			position = position;
			target = target;
			view_matrix = glm::lookAt(position, target, up);

		}

		mat4 matrix() {
			if (dirty) {
				update_matrix();
			}
			return projection * view_matrix;
		}

		mat4 get_p() {
			if (dirty) {
				update_matrix();
			}
			return projection;
		}

		mat4 get_v() {
			return view_matrix;
		}

		void update_matrix() {
			switch (type)
			{
			case Camera::ORTHO: {
				projection = ortho(ortho_rect.x, ortho_rect.y, ortho_rect.z, ortho_rect.w, znear, zfar);
				break;
			}
			case Camera::PERSPECTIVE:
				projection = perspective(radians(fov), (ortho_rect.y - ortho_rect.x) / (ortho_rect.w - ortho_rect.z), znear, zfar);
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

		void set_ortho(float left, float right, float bottom, float top) {
			ortho_rect.x = left;
			ortho_rect.y = right;
			ortho_rect.z = bottom;
			ortho_rect.w = top;
			dirty = true;
		}

		void set_type(CameraType type) {
			this->type = type;
			dirty = true;
		}

		void set_near(float in_near) {
			this->znear = in_near;
			dirty = true;
		}

		void set_far(float in_far) {
			this->zfar = in_far;
			dirty = true;
		}

	};
	typedef shared_ptr<Camera> CameraPtr;

#endif