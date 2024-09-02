#include "pch.h"
#include "defaults.h"

namespace Physx2D {
	float QUAD_VERTICES[24]{
		-.5f, -.5f,		0.f, 0.f,
		 .5f, -.5f,		1.f, 0.f,
		-.5f,  .5f,		0.f, 1.f,

		 .5f, -.5f,		1.f, 0.f,
		 .5f,  .5f,		1.f, 1.f,
		-.5f,  .5f,		0.f, 1.f
	};

	float FRAME_QUAD[24]{
		-1.f, -1.f,		0.f, 0.f,
		 1.f, -1.f,		1.f, 0.f,
		-1.f,  1.f,		0.f, 1.f,

		 1.f, -1.f,		1.f, 0.f,
		 1.f,  1.f,		1.f, 1.f,
		-1.f,  1.f,		0.f, 1.f
	};


	vec2 UNIT_RECT[4]{
			vec2(-.5f, -.5f),
			vec2(.5f, -.5f),
			vec2(.5f,  .5f),
			vec2(-.5f,  .5f)
	};

	float TRIANGLE_VERTICES[12]{
		  0.5f,    0.000f,   1.0f,  0.5f,
		 -0.25f,   0.433f,   0.25f, 0.933f,
		 -0.25f,  -0.433f,   0.25f, 0.066f
	};

	float LINE_VERTICES[8]{
		0.0f, 0.f,		0.f, 0.f,
		1.0f, 0.f,		1.f, 0.f
	};
}