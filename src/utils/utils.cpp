#include "pch.h"
#include "utils.h"

namespace Physx2D {
	std::string get_file_content(const char* filename) {
		std::ifstream in(filename, std::ios::binary);

		if(in) {
			std::string contents;
			in.seekg(0, std::ios::end);
			contents.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&contents[0], contents.size());
			in.close();
			return contents;
		}
		LOG_ERROR("ERROR : Invalid file path %s\n", filename);
    PHSX2D_HARD_ASSERT(false, "Only valid filepath accepted");
	}

	uint32_t compile_shader(const char* source, GLenum type) {
		unsigned int  id;
		int success;
		char infoLog[512];

		id = glCreateShader(type);
		glShaderSource(id, 1, &source, NULL);
		glCompileShader(id);

		PHSX2D_DBG_EXP(
			glGetShaderiv(id, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(id, 512, NULL, infoLog);
				LOG_ERROR("ERROR: Shader :: Type :: ( %d ) did not compiled successfully\n LOG : %s\n", type, infoLog);
			}
		);
		return id;
	}
}
