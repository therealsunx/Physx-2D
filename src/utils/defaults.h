#pragma once

/*
	Contains some default values used in many places in engine..
*/

#include "../math/math.h"

#define DEF_SCREEN_WIDTH 1280
#define DEF_SCREEN_HEIGHT 760

#define WORLD_SIZE_X 1e8f
#define WORLD_SIZE_Y 1e8f

#define arrayLength(a) (sizeof(a)/sizeof(a[0]))
#define initVectorFromArray(arr, type) std::vector<type>(arr, arr + arrayLength(arr))
#define max(a, b) (a>b?a:b)
#define min(a, b) (a<b?a:b)

namespace Physx2D {
	typedef vec4 Color;

	extern float PHYSX2D_API QUAD_VERTICES[24];

	extern float PHYSX2D_API FRAME_QUAD[24];

	extern vec2 PHYSX2D_API UNIT_RECT[4];

	extern float PHYSX2D_API TRIANGLE_VERTICES[12];

	extern float PHYSX2D_API LINE_VERTICES[8];

	struct PHYSX2D_API WindowProps {
		int WIDTH, HEIGHT;
		const char* TITLE;

		WindowProps(
			uint32_t width = DEF_SCREEN_WIDTH,
			uint32_t height = DEF_SCREEN_HEIGHT,
			const char* title = "Physx2D Window"
		) {
			WIDTH = width;
			HEIGHT = height;
			TITLE = title;
		}
	};

	struct PHYSX2D_API CollisionData {
		bool status;
		vec2 axis;

		CollisionData(bool status = false, vec2 axis = vec2(0.f)) {
			this->status = status;
			this->axis = axis;
		}
	};
}