#pragma once
/*
	Physics part of the application is handled here. Functions like checkCollision, collisionPhysics and updateRigidbody are 
	defined here inside PhysicsHandler. The working of the functions is rather data oriented than object oriented.

	> checkCollision : checks the collision between two colliders and resolves the collision and returns CollisionData
	> collisionPhysics : handles the physics of the collision if the rigidbody is attached to both colliders
	> updateRigidBody : updates the transform nad rigidbody components according to rigidbody component
*/
#include "../scene/components.h"

namespace Physx2D{
		
	class PhysicsHandler {
		
	public:
		static CollisionData checkCollision(Collider* c1, Transform* t1, BodyType s1, Collider* c2, Transform* t2, BodyType s2);

		static void collisionPhysics(CollisionData data, RigidBody2D* dynamicBody, RigidBody2D* body2);

		static void updateRigidBody(RigidBody2D* body, Transform* transform, float delta_time);

	private:

		static CollisionData _check(CircleCollider* c1, Transform* t1, CircleCollider* c2, Transform* t2);
		static CollisionData _check(CircleCollider* c1, Transform* t1, BoundingCircle* c2, Transform* t2);
		static CollisionData _check(CircleCollider* c1, Transform* t1, AABB* c2, Transform* t2);
		static CollisionData _check(CircleCollider* c1, Transform* t1, BoxCollider2D* c2, Transform* t2);

		static CollisionData _check(BoxCollider2D* c1, Transform* t1, BoxCollider2D* c2, Transform* t2);

		static CollisionData _check(BoxCollider2D* c1, Transform* t1, AABB* c2, Transform* t2);
		static CollisionData _check(BoxCollider2D* c1, Transform* t1, BoundingCircle* c2, Transform* t2);
	};
}
