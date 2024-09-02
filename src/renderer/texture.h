#pragma once

/*
	Textures can be loaded from file or just be allocated for future. 
	If the path is specified, there is no need for specifying width and height of the texture.
	The source and target format also can be specified or use the default value.

	Functionalities :
		> bindImageTextureMode bind the image texture in specified mode i.e. write_only, read_only, read_write_mode, etc
			type is the data type in which the texture image is binded and slot is the texture slot(0->16) in which texture
			is to be bound.
		> unbindImagetextureMode unbinds image texture
		> texUnit sets the uniform variable of sampler2D or image2D in the shader to the texture's slot
		> bind : binds the texture in the specified slot
		> unbind : unbind the texture in the slot
		> del : deletes the shader program
		> setProperty sets the texture's property
		> ID returns the ID of the texture
*/

#include "shader.h"
#include<stb/stb_image.h>

namespace Physx2D {

	class PHYSX2D_API Texture {
	public:

		const char* m_type;
		unsigned int m_slot;
		int m_width, m_height;
		
		Texture(
			const char* path,
			const char* type,
			unsigned int slot,
			GLenum src_type = GL_UNSIGNED_BYTE,
			GLenum target_format = GL_RGBA,
			int _width = 800,
			int _height = 800
		);
		~Texture();

		inline void bind(int slot = -1) {
		
			glActiveTexture(GL_TEXTURE0 + (slot<0?m_slot:slot));
			glBindTexture(GL_TEXTURE_2D, m_ID);
		}

		inline void bindImageTextureMode(GLenum mode, GLenum type, int slot = -1) {
			bind();
			glBindImageTexture(slot<0?m_slot:slot, m_ID, 0, GL_FALSE, 0, mode, type);
			unbind();
		}

		inline void unbindImageTextureMode(GLenum mode, GLenum type, int slot = -1) {
			glBindImageTexture(slot < 0 ? m_slot : slot, 0, 0, GL_FALSE, 0, mode, type);
		}

		inline void texUnit(Shader* shader, const char* uniform) {
			shader->use();
			shader->setInt(uniform, m_slot);
		}

		inline void unbind() {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		inline void set_property(GLenum target, GLenum pname, GLenum parameter) {
			glTexParameteri(target, pname, parameter);
		}

		inline uint32_t ID() {
			return m_ID;
		}

	private:
		GLuint m_ID;

	};
}