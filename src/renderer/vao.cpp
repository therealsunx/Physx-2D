#include "pch.h"
#include "vao.h"

namespace Physx2D {
	VAO::VAO() {
		glGenVertexArrays(1, &m_ID);
	}

	VAO::~VAO() {
		glDeleteVertexArrays(1, &m_ID);
	}
}