#pragma once

/*
	Entity class : Has every functionality related to entity, like adding component, removing, checking if it has a component, etc
*/

#include "world.h"
#include "components.h"
#include "../core/Log.h"

namespace Physx2D {
	class PHYSX2D_API World;

	class PHYSX2D_API Entity {
		public:
			World* m_world = nullptr;

			Entity() = default;
			Entity(EntityID id, World* world_);

			~Entity();

			template<typename T, typename... Args>
			T* AddComponent(Args... args) {

				if constexpr(std::is_base_of_v<Collider, T>) {
					PHSX2D_HARD_ASSERT(!m_world->manager->hasComponent<Collider>(m_ID) , "Component already exists");
					return  static_cast<T*>(m_world->manager->addComponent<Collider>(m_ID, new T(args...)));
				}
				else {
					PHSX2D_HARD_ASSERT(!m_world->manager->hasComponent<T>(m_ID), "Component already exists");
					T* comp = new T(args...);
					if constexpr (std::is_same_v<T, ScriptComponent>)
						comp->script->self = this;
					return  m_world->manager->addComponent<T>(m_ID, comp);
				}
			}

			template<typename T, typename... Args>
			T* Add_ReplaceComponent(Args... args) {
				if constexpr(std::is_base_of_v<Collider, T>) 
					return m_world->manager->addComponent<Collider>(m_ID, new T(args...));
				else {
					T* comp = new T(args...);
					if constexpr (std::is_same_v<T, ScriptComponent>)
						comp->script->self = this;
					return m_world->manager->addComponent<T>(m_ID, comp);
				}
			}

			template<typename T>
			void RemoveComponent() {
				
				if constexpr(std::is_base_of_v<Collider, T>) {
					PHSX2D_HARD_ASSERT(m_world->manager->hasComponent<Collider>(m_ID), "Component does not exist");
					m_world->manager->removeComponent<Collider>(m_ID);
				}
				else {
					PHSX2D_HARD_ASSERT(m_world->manager->hasComponent<T>(m_ID), "Component does not exist");
					m_world->manager->removeComponent<T>(m_ID);
				}
			}

			template<typename T>
			bool HasComponent() {
				if constexpr(std::is_base_of_v<Collider, T>)
					return m_world->manager->hasComponent<Collider>(m_ID);
				return m_world->manager->hasComponent<T>(m_ID);
			}

			template<typename T>
			T* GetComponent() {
				T* cptr;
				if constexpr(std::is_base_of_v<Collider, T>) {
					cptr = m_world->manager->getComponent<Collider>(m_ID);
					PHSX2D_HARD_ASSERT(cptr, "Component does not exist");
				}
				else {
					cptr = m_world->manager->getComponent<T>(m_ID);
					PHSX2D_HARD_ASSERT(cptr, "Component does not exist");
				}
				return cptr;
			}

			bool operator == (Entity nen) {
				return m_ID == nen.m_ID;
			}

		private:
			EntityID m_ID = 0;
	};
}
