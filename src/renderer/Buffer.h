#pragma once
/*
	Buffer is a general class for any type of buffer objects in the program. This is a wrapper class
	for opengl's buffer objects. 
	Functionalities : 
		> setBufferData
		> bind
		> bindBase at index
		> del
*/

#include <glad/glad.h>

namespace Physx2D {
	class PHYSX2D_API Buffer {
	public:

		Buffer(GLenum type);
		~Buffer();

		inline void setBufferData(const void* data, size_t size, GLenum useMode = GL_STATIC_DRAW) {
			glBindBuffer(m_type, m_ID);
			glBufferData(m_type, size, data, useMode);
		}

		inline void bind() {
			glBindBuffer(m_type, m_ID);
		}

		inline void bindBase(uint32_t index) {
			glBindBufferBase(m_type, index, m_ID);
		}

		inline void unbind() {
			glBindBuffer(m_type, 0);
		}

	private:
		GLenum m_type;
		uint32_t m_ID;
	};
}