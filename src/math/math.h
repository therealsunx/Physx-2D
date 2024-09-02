#pragma once
/*
	Extra math functions available in the applications are listed as :
		> vec2
		> ivec2
		> vec3
		> ivec3
		> vec4
		> ivec4
		> centerRect which is a rect defined with center and size
		> mat3 which is a 3x3 matrix of floats
		> Random : seeded random number generator with auto seed change at each generation
		> Math class which contains few static functionalities like random numbers, dot product,
		getOrtho2D, getView2D, etc.
*/
#include "pch.h"
#include "core/core.h"

namespace Physx2D {

	class Math;

	template <class T>
	struct PHYSX2D_API tvec2 {
		T x;
		T y;

		tvec2(T a = 0.0f) : x(a), y(a) {}
		tvec2(T _x, T _y): x(_x), y(_y) {}

		inline tvec2 normalized() {
			float _l = length();
			return _l<1e-6?tvec2():(*this)/_l;
		}
		inline float length(){
			return sqrt(x * x + y * y);
		}
		inline tvec2 rotate(T a) {
			float c = cos(a);
			float s = sin(a);
			return tvec2(x * c - y * s, x * s + y * c);
		}
		inline tvec2 operator =(tvec2 v) {
			x = v.x;
			y = v.y;
			return v;
		}
		inline tvec2 operator -() {
			return tvec2<T>(-x, -y);
		}
		inline tvec2 operator +(tvec2 v){
			return tvec2<T>(x + v.x, y + v.y);
		}
		inline tvec2 operator +=(tvec2 v){
			x += v.x;
			y += v.y;
			return *this;
		}
		inline tvec2 operator -(tvec2 v){
			return tvec2(x - v.x, y - v.y);
		}
		inline tvec2 operator -=(tvec2 v) {
			x -= v.x;
			y -= v.y;
			return *this;
		}
		inline tvec2 operator *(tvec2 v) {
			return tvec2(x * v.x, y * v.y);
		}
		inline tvec2 operator /(tvec2 v) {
			return tvec2(x / v.x, y / v.y);
		}
		inline tvec2 operator *= (tvec2 a){
			x *= a.x;
			y *= a.y;
			return *this;
		}
		inline tvec2 operator /= (tvec2 a) {
			x /= a.x;
			y /= a.y;
			return *this;
		}
		bool operator<(const tvec2<T>& v) const{
			return y == v.y ? x < v.x : y < v.y;
		}
	};

	template<class T>
	struct PHYSX2D_API tvec3 {
		T x;
		T y;
		T z;

		tvec3(T a = 0) : x(a), y(a),z(a) {}
		tvec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

		inline tvec3 normalized() {
			float _l = length();
			return _l<1e-6?tvec3():(*this)/_l; 
		}
		inline float length() {
			return sqrt(x * x + y * y + z * z);
		}
		inline tvec3 operator =(tvec3 v) {
			x = v.x, y = v.y, z = v.z;
			return *this;
		}
		inline tvec3 operator -() {
			return tvec3(-x, -y, -z);
		}
		inline tvec3 operator +(tvec3 v) {
			return tvec3(x + v.x, y + v.y, z + v.z);
		}
		inline tvec3 operator +=(tvec3 v) {
			x += v.x, y += v.y, z += v.z;
			return *this;
		}
		inline tvec3 operator -(tvec3 v) {
			return tvec3(x - v.x, y - v.y, z - v.z);
		}
		inline tvec3 operator -=(tvec3 v) {
			x -= v.x, y -= v.y, z -= v.z;
			return *this;
		}
		inline tvec3 operator *(tvec3 v) {
			return tvec3(x * v.x, y * v.y, z * v.z);
		}
		inline tvec3 operator *=(tvec3 a) {
			x * -a.x, y *= a.y, z *= a.z;
			return *this;
		}
		inline tvec3 operator /(tvec3 v) {
			return tvec3<T>(x / v.x, y / v.y, z/v.z);
		}
		inline void operator /=(tvec3 v) {
			x /= v.x;
			y /= v.y;
		}
		bool operator<(const tvec3<T>& v) const {
			return z == v.z ? (y==v.y?x<v.x:y<v.y) : z<v.z;
		}
	};

	template<class T>
	struct PHYSX2D_API tvec4 {
		float x;
		float y;
		float z;
		float w;

		tvec4(T a = 0) : x(a), y(a), z(a), w(a) {}
		tvec4(T _x, T _y, T _z, T _w) :x(_x), y(_y), z(_z), w(_w) {}

		inline tvec4 normalized() {
			float _l = length();
			return _l<1e-6?tvec4():(*this)/_l;
		}
		inline float length() {
			return sqrt(x * x + y * y + z * z + w * w);
		}
		inline tvec4 operator +(tvec4 v){
			return tvec4(x + v.x, y + v.y, z + v.z, w + v.w);
		}
		inline void operator +=(tvec4 v) {
			x += v.x, y += v.y, z += v.z, w += v.w;
		}
		inline tvec4 operator -(tvec4 v) {
			return tvec4(x - v.x, y - v.y, z - v.z, w - v.w);
		}
		inline void operator -=(tvec4 v){
			x -= v.x, y -= v.y, z -= v.z, w -= v.w;
		}
		inline tvec4 operator *(tvec4 v){
			return tvec4(x * v.x, y * v.y, z * v.z, w * v.w);
		}
		inline void operator *= (tvec4 a){
			x *= a.x,y *= a.y,z *= a.z,w *= a.w;
		}
		inline tvec4 operator /(tvec4 v) {
			return tvec4(x / v.x, y / v.y, z / v.z, w / v.w);
		}
		inline void operator /= (tvec4 v) {
			x /= v.x, y /= v.y, z /= v.z, w /= v.w;
		}
		bool operator<(const tvec4<T>& v) const {
			return w == v.w ? (z == v.z ? (y == v.y ? x < v.x : y < v.y) : z < v.z) : w < v.w;
		}
	};

	using vec2 = tvec2<float>;
	using vec3 = tvec3<float>;
	using vec4 = tvec4<float>;

	using ivec2 = tvec2<int>;
	using ivec3 = tvec3<int>;
	using ivec4 = tvec4<int>;

	struct PHYSX2D_API centerRect {
		float x;
		float y;
		float w;
		float h;

		centerRect(float x_, float y_, float w_, float h_) :x(x_), y(y_), w(w_), h(h_) {}
		centerRect(tvec2<float> cen, tvec2<float> res) :x(cen.x), y(cen.y), w(res.x), h(res.y) {}

		inline bool contains(tvec2<float> point){
			return point.x > (x - w * 0.5f) && point.x<(x + w * 0.5f) && point.y >(y - h * 0.5f) && point.y < (h * 0.5f + y);
		}
		inline bool intersects(centerRect n) {
			return abs(x - n.x) < ((w + n.w) * 0.5f) && abs(y - n.y) < ((h + n.h) * 0.5f);
		}
		inline centerRect getPart(float xp, float yp) {
			return centerRect(x + xp * 0.5f * w, y + yp * 0.5f * h, abs(xp) * w, abs(yp) * h);
		}
	};
		
	struct PHYSX2D_API mat3 {
		float _0[3]{ 0.f,0.f,0.f };
		float _1[3]{ 0.f,0.f,0.f };
		float _2[3]{ 0.f,0.f,0.f };

		mat3 operator +(mat3 u);
		mat3 operator -(mat3 u);
		mat3 operator *(mat3 u);
		mat3 operator *(float x);
		mat3 operator /(float x);

		float* operator[](int i);
	};

	class PHYSX2D_API Math {
	public:
		static const double PI;


		static inline float dot(tvec2<int> u, tvec2<int> b){
			return u.x * b.x + u.y * b.y;
		}
		static inline float dot(tvec2<float> u, tvec2<float> b) {
			return u.x * b.x + u.y * b.y;
		}

		static inline mat3 get_ortho2d(vec2 center, vec2 area){
			vec2 b_l = center - area * 0.5f;
			vec2 t_r = center + area * 0.5f;

			return {
				{2.0f / (t_r.x - b_l.x), 0.f, 0.f},
				{0.f, 2.0f / (t_r.y - b_l.y), 0.f},
				{ -(b_l.x + t_r.x) / (b_l.x - t_r.x),   -(b_l.y + t_r.y) / (b_l.y - t_r.y), 1.f}
			};
		}
		static inline mat3 get_view2d(tvec2<float> pos){
			return {
				{1.f, 0.f, 0.f},
				{0.f, 1.f, 0.f},
				{-pos.x, -pos.y,1.f}
			};
		}

		static inline float random_i(uint32_t seed){
			seed = seed * 747796405 + 2891336453;
			uint32_t result = ((seed >> ((seed >> 28) + 4)) ^ seed) * 277803737;
			result = (result >> 22) ^ result;

			return result;
		}
		static inline float random_f(uint32_t seed) {
			return random_i(seed) / 0xffffffff;
		}

		static inline int randomr_i(int a, int b) {
			float x = (random_f(a) + random_f(b)) / 2.f;
			return a + (int)(x * (b - a));
		}
		static inline float randomr_f(float a, float b){
			float x = (random_f(a * 1000) + random_f(b * 2000)) / 2.f;
			return a + x * (b - a);
		}	
	};

	class PHYSX2D_API Random {
		public:
			Random(uint32_t seed);

			inline uint32_t rand_i(){
				return Math::random_i(seed_i++);
			}
			inline int randr_i(int a, int b) {
				return a + Math::random_f(seed_i++) * (b - a);
			}

			inline float rand_f(){
				return Math::random_f(seed_f++);
			}
			inline float randr_f(float a, float b){
				return a + Math::random_f(seed_f++) * (b - a);
			}

		private:
			uint32_t seed_i;
			uint32_t seed_f;
	};

}
