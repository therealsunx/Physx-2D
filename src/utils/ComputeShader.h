#pragma once

/*
	Compute shaders can be used to perform computational operations parallely in gpu to speed up some processes.
	Compute shader must be written in glsl and must follow the rules.
	
	Functionalities:
		> dispatch (...dims...) : dispatches  the compute shader to gpu
		> waitUntilFinish(barriesBits) : wait until the barrier is crossed
		> use : activate the compute shader program
		> set... : sets the uniform values
		> getter functions  :work group count , work group size, max local work group invocations
*/

#include "utils.h"
#include "math/math.h"

namespace Physx2D {
	
	class PHYSX2D_API ComputeShader {
		public:
			ComputeShader(const char* shader, bool is_path = true);
			~ComputeShader();

			
			inline void dispatch(uint32_t x, uint32_t y, uint32_t z = 1) {
				glUseProgram(m_ID);
				glDispatchCompute(x, y, z);
			}

			inline void waitUntilFinish(GLbitfield barrier) {
				glMemoryBarrier(barrier);
			}

			inline void use() {
				glUseProgram(m_ID);
			}

			inline void setInt(const char* u_name, int value) {
				if (glGetUniformLocation(m_ID, u_name) >= 0)
					glUniform1i(glGetUniformLocation(m_ID, u_name), value);
				PHSX2D_DBG_EXP(else
					LOG_WARN("WARNING : location of integer %s not found\n", u_name););
			}

			inline void setFloat(const char* u_name, float value) {
				if (glGetUniformLocation(m_ID, u_name) >= 0)
					glUniform1f(glGetUniformLocation(m_ID, u_name), value);
				PHSX2D_DBG_EXP(else
					LOG_WARN("WARNING : location of float %s not found\n", u_name););
			}

			inline tvec3<int> getWorkGrpCount() {
				tvec3<int> tmp;
				glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &tmp.x);
				glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &tmp.y);
				glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &tmp.z);

				return tmp;
			}

			inline tvec3<int> getWorkGrpSize() {
				tvec3<int> tmp;
				glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &tmp.x);
				glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &tmp.y);
				glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &tmp.z);

				return tmp;
			}

			inline int maxLocalWorkGrpInv() {
				GLint tmp;
				glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &tmp);
				return tmp;
			}

		private:
			uint32_t m_ID;
	};
}