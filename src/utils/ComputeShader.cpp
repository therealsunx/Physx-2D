#include "pch.h"
#include "ComputeShader.h"
#include <glad/glad.h>

namespace Physx2D {
	ComputeShader::ComputeShader(const char* compute_shader, bool is_path) {
		uint32_t shader;

		if (is_path) {
			std::string c_ = get_file_content(compute_shader);
			const char* src = c_.c_str();
			shader = compile_shader(src, GL_COMPUTE_SHADER);
		}
		else {
			shader = compile_shader(compute_shader, GL_COMPUTE_SHADER);
		}

		m_ID = glCreateProgram();

		glAttachShader(m_ID, shader);
		glLinkProgram(m_ID);

		PHSX2D_DBG_EXP({
			// Link status check
			int success;
			char infoLog[512];

			glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
				LOG_ERROR("ERROR : Compute Shader program did not link successfully, path : %s\nLOG:%s\n", compute_shader, infoLog);
			}
		});
		glDeleteShader(shader);
	}

	ComputeShader::~ComputeShader() {
		glDeleteProgram(m_ID);
	}
}