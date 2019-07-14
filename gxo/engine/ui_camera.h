#ifndef GXO_UI_CAMERA_H
#define GXO_UI_CAMERA_H
#include"camera.h"
namespace gxo {
	class UiCamera
	{
	public:
		Camera a;
		UiCamera(int width, int height)
		{
			a.set_type(Camera::CameraType::ORTHO);
			a.set_ortho(0, 0, width, height);
			a.lookat(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));
		}

		~UiCamera()
		{
		}

	private:

	};

}
#endif
