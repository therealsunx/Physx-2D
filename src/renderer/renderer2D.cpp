#include "pch.h"
#include "renderer2D.h"

namespace Physx2D {
	Renderer2D::Renderer2D() {
		p_count = 0;
		m_renderMode = 0;
		m_vao = new VAO;
	}

	Renderer2D::Renderer2D(std::vector<float> vertices, std::vector<uint32_t> indices, GLenum mode) :
		m_renderMode(mode), p_count(indices.size()), arrayMode(false), m_vao(new VAO)
	{
		m_vao->bind();

		m_vbo = new Buffer(GL_ARRAY_BUFFER);
		m_vbo->setBufferData(vertices.data(), vertices.size() * sizeof(vertices[0]));

		m_ebo = new Buffer(GL_ELEMENT_ARRAY_BUFFER);
		m_ebo->setBufferData(indices.data(), indices.size() * sizeof(indices[0]));

		m_vao->unbind();
		m_vbo->unbind();
		m_ebo->unbind();
	}

	Renderer2D::Renderer2D(std::vector<float> &vertices, uint32_t numPoints, GLenum mode) 
		:m_renderMode(mode), arrayMode(true), p_count(numPoints), m_vao(new VAO), m_ebo(nullptr)
	{
		m_vao->bind();

		m_vbo = new Buffer(GL_ARRAY_BUFFER);
		m_vbo->setBufferData(vertices.data(), vertices.size() * sizeof(vertices[0]));

		m_vao->unbind();
		m_vbo->unbind();
	}

	void Renderer2D::VertexDataLayout(uint32_t location, uint32_t count, GLenum type, GLsizei stride, uint32_t offset) {
		m_vao->bind();
		m_vbo->bind();

		m_vao->layout(location, count, type, stride, offset);

		m_vao->unbind();
		m_vbo->unbind();
	}

	void Renderer2D::Draw(Shader* shader) {
		shader->use();
		m_vao->bind();
		if(arrayMode) glDrawArrays(m_renderMode, 0, p_count);
		else glDrawElements(m_renderMode, p_count, GL_UNSIGNED_INT, 0);
		m_vao->unbind();
	}

	Renderer2D::~Renderer2D(){
		delete m_ebo;
		delete m_vbo;
		delete m_vao;
	}
}