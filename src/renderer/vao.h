#pragma once

/*
	VAO is the wrapper class for opengl's vertex array objects. VAO keeps track of all buffer data set when the vao is bound.
	
	Functionalities:
		> bind : binds the VAO
		> unbind : unbinds the VAO
		> layout : specifies the layout of the data in array buffer bound inside current vao.
			; location : location of data in vao (used in vertex shaders)
			; count : number of data
			; type : data_type
			; stride : gap between two consecutive data
			; offset : offset of the data from start
*/

#include "../core/core.h"
#include <glad/glad.h>

namespace Physx2D {
	class PHYSX2D_API VAO {
	public:
		GLuint m_ID;

		VAO();
		~VAO();

		inline void layout(GLuint location, GLuint count, GLenum type, GLuint stride, unsigned int offset) {
			glEnableVertexAttribArray(location);
			glVertexAttribPointer(location, count, type, GL_FALSE, stride, (void*)offset);
		}

		inline void bind() {
			glBindVertexArray(m_ID);
		}

		inline void unbind() {
			glBindVertexArray(0);
		}
	};
}