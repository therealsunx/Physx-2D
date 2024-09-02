#include "pch.h"
#include "texture.h"
#include "../core/Log.h"

namespace Physx2D {
	Texture::Texture(const char* path, const char* type, unsigned int slot, GLenum src_type, GLenum target_format, int _width, int _height) {
		unsigned char* data;
		GLenum src_format = GL_RGBA;

		m_type = type;
		m_slot = slot;

		if (path == NULL) {
			data = NULL;
			m_width = _width;
			m_height = _height;
		}
		else {
			int nrChannels = 1;
			stbi_set_flip_vertically_on_load(true);
			data = stbi_load(path, &m_width, &m_height, &nrChannels, 0);
			PHSX2D_HARD_ASSERT(data, "ERROR : while loading the path %s\n", path);

			if (nrChannels == 1)
				src_format = GL_RED;
			else if (nrChannels == 3)
				src_format = GL_RGB;
			else if (nrChannels == 4)
				src_format = GL_RGBA;
		}

		glGenTextures(1, &m_ID);
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		
		glTexImage2D(GL_TEXTURE_2D, 0, target_format, m_width, m_height, 0, src_format, src_type, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		if (data)
			stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture() {
		glDeleteTextures(1, &m_ID);
	}
}