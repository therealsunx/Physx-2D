#pragma once

/*
 * Camera has features for movements, zoom and escape for closing camera (window closing) only
*/

#include "../renderer/shader.h"
#include "../math/math.h"
#include <GLFW/glfw3.h>

namespace Physx2D {
	class PHYSX2D_API Camera {

		public:
			vec2 position;
			float fov = 1.0f;
			float sensitivity = 0.2f;

			vec2 speed = vec2(1.f);

			Camera(vec2 position = vec2(), float fov = 1.0f);

			inline mat3 get_matrices(vec2 res) {
				mat3 mat = Math::get_ortho2d(vec2(), res * fov) * Math::get_view2d(position);
				return mat;
			}

			inline void setValues(Shader* shader, vec2 res) {
				shader->setMat3("u_cam_matrices", get_matrices(res));
				shader->setVec2("u_resolution", res);
				shader->setFloat("u_fov", fov);
			}
			void handleInputs(GLFWwindow* window, float delta_time);
	};
}
