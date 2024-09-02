#pragma once
#include "vao.h"
#include "Buffer.h"
#include "shader.h"

namespace Physx2D {
	class PHYSX2D_API Renderer2D {
	public:
		GLenum m_renderMode;

		Renderer2D();
		Renderer2D(std::vector<float> vertices, std::vector<uint32_t> indices, GLenum mode = GL_TRIANGLES);
		Renderer2D(std::vector<float> &vertices, uint32_t numPoints, GLenum mode = GL_TRIANGLES);
		~Renderer2D();

		void VertexDataLayout(uint32_t location, uint32_t count, GLenum type, GLsizei stride, uint32_t offset);
		virtual void Draw(Shader* shader);

	protected:
		VAO *m_vao;
		Buffer *m_vbo, *m_ebo;
		uint32_t p_count;
		bool arrayMode = true;
	};
}