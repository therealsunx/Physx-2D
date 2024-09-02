#pragma once

/*
	Shader object currently manages the vertex and fragment shaders only. Shaders can 
	written in any file format but the language must be glsl.
	Functionalities : 
		> use : use the current shader
		> del : delete the shader program
		> set**** : set the **** value of uniform variable
*/

#include <glad/glad.h>
#include "../math/math.h"
#include "pch.h"

namespace Physx2D {

	class PHYSX2D_API Shader {
	public:
		Shader();
		Shader(const char* vertexPath, const char* fragmentPath, bool is_path = true);
		~Shader();
		inline void use() {
			glUseProgram(m_ID);
		}

		inline void setBool(const char* name, bool value) {
			glUniform1i(getUniformLocation(name), (int)value);
		}

		inline void setInt(const char* name, int value) {
			glUniform1i(getUniformLocation(name), value);
		}

		inline void setFloat(const char* name, float value) {
			glUniform1f(getUniformLocation(name), value);
		}

		inline void setVec2(const char* name, vec2 vec) {
			glUniform2f(getUniformLocation(name), vec.x, vec.y);
		}

		inline void setMat3(const char* name, mat3 mat) {
			glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, (float*) & mat);
		}

	private:
		uint32_t m_ID;
		std::unordered_map<const char*, GLint> m_uniformCache;
		GLint getUniformLocation(const char* loc);
	};
}