#pragma once
/*
	Contains some utility functions for the engine
*/
#include <glad/glad.h>

namespace Physx2D {
	std::string PHYSX2D_API get_file_content(const char* filename);
	uint32_t PHYSX2D_API compile_shader(const char* source, GLenum type);
	inline PHYSX2D_API void  ShowError()	{
		LOG_ERROR("ERROR : %d\n", glGetError());
	}
}