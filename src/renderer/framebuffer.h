#pragma once

/*
	FrameBuffer object can be used to draw any content on them instead of screen and post-process it.
	Functionalities : 
		> Construction : requires width, height of frame and defaultSlot (0->16) and finally 
			datatype for single element/pixel of framebuffer
		> del will clear all buffers and delete the framebuffer
		> Clear will clear the color in framebuffer
		> ActivateAsTexture will activate framebuffer's content as a texture in the defaultSlot or any slot(0->16) if provided
		> Bind will bind the framebuffer as target buffer for drawing
		> Unbind will unbind framebuffer and binds the default frame i.e. window
		> Draw will draw framebuffer on the screen with the shader specified in parameter

		Currently framebuffer is drawn on whole screen, so there is not much control on where to draw it, but it will be fixed soon.
*/

#include "texture.h"
#include "vao.h"
#include "Buffer.h"
#include "../utils/defaults.h"

namespace Physx2D {

	class PHYSX2D_API FrameBuffer {
	public:
		FrameBuffer(
			int width,
			int height,
			uint32_t defaultSlot = 0,
			GLenum _dtype = GL_UNSIGNED_BYTE
		);
		~FrameBuffer();

		inline void Bind() {
			glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		}

		inline void Unbind() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		inline void Clear(float r, float g, float b, float a){
			glClearColor(r, g, b, a);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		inline void ActivateAsTexture(int slot) {
			m_texture->bind(slot);
		}

		inline void Draw(Shader& shader) {
			shader.use();
			m_vao->bind();

			glDrawArrays(GL_TRIANGLES, 0, 6);

			m_vao->unbind();
			m_texture->unbind();
		}

	private:
		uint32_t m_ID = 0;
		uint32_t m_rbo = 0;
		uint32_t m_slot = 0;
		VAO* m_vao;
		Buffer* m_quad_buffer;
		Texture* m_texture;
		void attachVertexArray();
		void attachRenderBuffer();
	};
}
