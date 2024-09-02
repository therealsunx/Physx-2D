#include "pch.h"
#include "Buffer.h"


namespace Physx2D {
	Buffer::Buffer(GLenum type) {
		glGenBuffers(1, &m_ID);
		this->m_type = type;
	}

	Buffer::~Buffer() {
		glDeleteBuffers(1, &m_ID);
	}
}