#include "pch.h"
#include "framebuffer.h"
#include "../core/Log.h"

namespace Physx2D {
	FrameBuffer::FrameBuffer(int width, int height, uint32_t defaultSlot, GLenum _dtype) : m_vao(new VAO) {

		glGenFramebuffers(1, &m_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		m_texture = new Texture(NULL, "frame", defaultSlot, width, height);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->ID(), 0);
		attachRenderBuffer();
		attachVertexArray();
	}

	FrameBuffer::~FrameBuffer() {
		glDeleteFramebuffers(1, &m_ID);
		glDeleteRenderbuffers(1, &m_rbo);
		delete m_quad_buffer;
		delete m_vao;
		delete m_texture;
	}

	void FrameBuffer::attachRenderBuffer() {
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		glGenRenderbuffers(1, &m_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_texture->m_width, m_texture->m_height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			LOG_ERROR("Error while attaching framebuffer");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::attachVertexArray() {

		m_vao->bind();
		m_quad_buffer = new Buffer(GL_ARRAY_BUFFER);

		m_quad_buffer->setBufferData(&FRAME_QUAD, sizeof(FRAME_QUAD));

		m_vao->layout(0, 2, GL_FLOAT, 4 * sizeof(float), 0);
		m_vao->layout(1, 2, GL_FLOAT, 4 * sizeof(float), 2 * sizeof(float));

		m_vao->unbind();
	}
}
