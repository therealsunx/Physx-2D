#pragma once
/*
	Components and related enums are all defined here.

	> RenderData : Data struct for passing data required for rendering on screen
	> ScriptComponent : for adding custom scripts to entities.. Requires scriptobject
	> Tag : for tagging the entities, may require for filtering of entities
	> Transform : stores tranform of an object, every entities has it by default
	> SqriteRenderer : for rendering 2d object/sprites on screen
	> Rigidbody : for physics stuff
	> Collider : base struct for collision detection : AABB, CircleCollider, BoxCollider, BoundingCircle
*/

#include "../utils/defaults.h"

namespace Physx2D {
	class Entity;
	enum PHYSX2D_API BodyType  { STATIC = 0, KINETIC};
	enum PHYSX2D_API RenderType {DEFAULT = 0, LINE, TRIANGLE, QUAD, CIRCLE};

	class PHYSX2D_API ScriptObject {
	public:
		Entity* self = nullptr;

		ScriptObject() {}

		virtual void setup() = 0;
		virtual void update(float delta_time) = 0;
		virtual void OnCollisionDetected(CollisionData& data, Entity* other) {}
	};
	
	struct PHYSX2D_API Tag {
		const char* tag;

		Tag(const char* _tag = NULL) :tag(_tag) {}
	};

	struct PHYSX2D_API Transform {

		vec2 Position;
		vec2 Scale;
		float Rotation;

		Transform(vec2 position = vec2(0.0f), vec2 scale = vec2(1.0f), float rotation = 0.f) {
			Position = position;
			Scale = scale;
			Rotation = rotation;
		}
	};

	struct PHYSX2D_API SpriteRenderer {
		RenderType type;
		Color color;
		vec2 offset;
		vec2 tiling;

		SpriteRenderer(RenderType _type = QUAD, tvec4<float> _color = tvec4(1.0f), vec2 _offset = vec2(), vec2 _tiling = vec2(1.f), int _texSlot = 0) :
			type(_type), color(_color), offset(_offset), tiling(_tiling) {}
	};

	struct PHYSX2D_API RenderData {
		Transform transform;
		Color color;
		vec2 texOffset;
		vec2 tiling;
	};

	struct PHYSX2D_API RigidBody2D {
		BodyType Type;
		vec2 Velocity;
		vec2 Acceleration;

		float mass ;
		float coef_drag;
		float coef_restitution;

		RigidBody2D(BodyType type = STATIC,vec2 v = vec2(), vec2 a = vec2(), float m = 1.0f, float cd = 0.0f, float cr = 1.0f) 
			: Velocity(v), Acceleration(a), mass(m), coef_drag(cd), coef_restitution(cr), Type(type) {}
	};

	struct PHYSX2D_API Collider {

		std::type_index typeIndex;
		vec2 Offset;
		
		Collider(vec2 off, std::type_index ti) : Offset(off), typeIndex(ti) {}

		virtual vec2 getSize() = 0;
	};

	struct PHYSX2D_API BoundingCircle : Collider{

		float Radius;

		BoundingCircle(vec2 offset = vec2(0.f), float radius = 0.5f)
			:Radius(radius), Collider(offset, typeid(BoundingCircle)) {}

		virtual vec2 getSize() override {
			return vec2(Radius*2.f);
		}
	};

	struct PHYSX2D_API AABB : Collider{

		vec2 Size;

		AABB(vec2 offset = vec2(0.f), vec2 size = vec2(1.f))
			:Size(size), Collider(offset, typeid(AABB)) {}

		virtual vec2 getSize() override {
			return Size;
		}
	};

	struct PHYSX2D_API BoxCollider2D : Collider {

		vec2 Size;
		float Rotation;

		BoxCollider2D(vec2 offset = vec2(0.f), vec2 size = vec2(1.f), float rotation = 0.f) 
			:Size(size), Rotation(rotation), Collider(offset, typeid(BoxCollider2D)) {}

		virtual vec2 getSize() override {
			return Size;
		}
	};

	struct PHYSX2D_API CircleCollider : Collider{

		float Radius;

		CircleCollider(vec2 offset = vec2(0.f), float radius = 0.5f) 
			:Radius(radius), Collider(offset, typeid(CircleCollider)) {}

		virtual vec2 getSize() override {
			return vec2(Radius*2.f);
		}
	};

	struct PHYSX2D_API ScriptComponent {
		ScriptObject* script;
		bool __setup = false;

		ScriptComponent(ScriptObject* _script = nullptr) : script(_script) {}

		~ScriptComponent() {
			delete script;
		}
	};
}