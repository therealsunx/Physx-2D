#include "pch.h"
#include "entity.h"

Physx2D::Entity::Entity(EntityID id, World* world_) : m_ID(id), m_world(world_){
	
}

Physx2D::Entity::~Entity() {
	
	if(HasComponent<Transform>())
		RemoveComponent<Transform>();

	if (HasComponent<Tag>())
		RemoveComponent<Tag>();

	if (HasComponent<RigidBody2D>())
		RemoveComponent<RigidBody2D>();

	if (HasComponent<SpriteRenderer>())
		RemoveComponent<SpriteRenderer>();

	if (HasComponent<ScriptComponent>())
		RemoveComponent<ScriptComponent>();

	if (HasComponent<Collider>()) {
		Collider* cldr = GetComponent<Collider>();

		if (cldr->typeIndex == std::type_index(typeid(CircleCollider)))
			delete ((CircleCollider*)cldr);
		else if (cldr->typeIndex == std::type_index(typeid(BoxCollider2D)))
			delete ((BoxCollider2D*)cldr);
		else if (cldr->typeIndex == std::type_index(typeid(BoundingCircle)))
			delete ((BoundingCircle*)cldr);
		else if (cldr->typeIndex == std::type_index(typeid(AABB)))
			delete ((AABB*)cldr);
		else
			PHSX2D_HARD_ASSERT(false, "Invalid Collider");
	}
}
