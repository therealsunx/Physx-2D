#include "pch.h"
#include "math.h"

namespace Physx2D {

	const double Math::PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;	

	Random::Random(uint32_t seed) : seed_i(seed), seed_f(seed) {}

	mat3 mat3::operator+(mat3 u) {
		return {
			{_0[0] + u[0][0],_0[1] + u[0][1],_0[2] + u[0][2]},
			{_1[0] + u[1][0],_1[1] + u[1][1],_1[2] + u[1][2]},
			{_2[0] + u[2][0],_2[1] + u[2][1],_2[2] + u[2][2]}
		};
	}

	mat3 mat3::operator-(mat3 u) {
		return mat3{
			{_0[0] - u[0][0],_0[1] - u[0][1],_0[2] - u[0][2]},
			{_1[0] - u[1][0],_1[1] - u[1][1],_1[2] - u[1][2]},
			{_2[0] - u[2][0],_2[1] - u[2][1],_2[2] - u[2][2]}
		};
	}

	mat3 mat3::operator*(mat3 u)
	{
		mat3 res;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				for(int k = 0; k < 3; k++) {
					res[i][j] += (*this)[i][k] * u[k][j];
				}
			}
		}
		return res;
	}

	mat3 mat3::operator*(float x)
	{
		mat3 _;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				_[i][j] =(*this)[i][j] * x;
			}
		}
		return _;
	}
	
	mat3 mat3::operator/(float x)
	{
		mat3 _;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				_[i][j] = (*this)[i][j]/x;
			}
		}
		return _;
	}

	float* mat3::operator[](int i) {
		return (float*) this + 3*i;
	}

	template class PHYSX2D_API tvec2<int>;
	template class PHYSX2D_API tvec2<float>;

	template class PHYSX2D_API tvec3<int>;
	template class PHYSX2D_API tvec3<float>;

	template class PHYSX2D_API tvec4<int>;
	template class PHYSX2D_API tvec4<float>;
}
