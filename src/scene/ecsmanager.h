#pragma once

/*
	ECSManager is manager unit for Entity Component System of the engine.

	> Every entity has EntityID which is just an uint32_t
	> Data oriented approach is taken to reduce the problem of inheritance
*/

#include "../pch.h"

namespace Physx2D {
	using EntityID = uint32_t;

	template<class t1, class t2>
	struct __comp_pair {
		t1 __pair1;
		t2 __pair2;
	};

	class PHYSX2D_API ECSManager {

	public:

		const inline EntityID  CreateEntity() {
			return nextEntity++;
		}

		template<typename T>
		T* addComponent(EntityID entity, T* component) {
			PHSX2D_HARD_ASSERT(entity >= 0 && entity < nextEntity, "Invalid entity ID : %d", entity);

			std::vector<void*>& componentVector = cmpStrg[std::type_index(typeid(T))];
			if (entity >= componentVector.size()) {
				componentVector.resize((entity+1) * 1.5, nullptr);
			}

			if (componentVector[entity] != nullptr) 
				delete ((T*)componentVector[entity]);

			componentVector[entity] = component;
			return static_cast<T*>(componentVector[entity]);
		}

		template<typename T>
		void removeComponent(EntityID entity) {
			PHSX2D_HARD_ASSERT(entity >= 0 && entity < nextEntity, "Invalid entity ID : %d", entity);

			std::vector<void*>& componentVector = cmpStrg[std::type_index(typeid(T))];
			delete static_cast<T*>(componentVector[entity]);
		}

		template<typename T>
		inline bool hasComponent(EntityID entity) {
			PHSX2D_HARD_ASSERT(entity >= 0 && entity < nextEntity, "Invalid entity ID : %d", entity);

			std::vector<void*>& componentVector = cmpStrg[std::type_index(typeid(T))];
			return entity < componentVector.size() && componentVector[entity] ;
		}

		template<typename T>
		T* getComponent(EntityID entity) {
			PHSX2D_HARD_ASSERT(entity >= 0 && entity < nextEntity, "Invalid entity ID : %d", entity);

			std::vector<void*>& componentVector = cmpStrg[std::type_index(typeid(T))];

			if (entity < componentVector.size()) {
				return static_cast<T*>(componentVector[entity]);
			}
			return nullptr;
		}

		template<typename T>
		void getAllComponents(std::vector<T*>& comp_cont) {
			for (auto& cmp : cmpStrg[std::type_index(typeid(T))]) {
				if (cmp) comp_cont.push_back(static_cast<T*>(cmp));
			}
		}

		template<class t1, class t2>
		void getCompPair(std::vector<__comp_pair<t1*, t2*>>& comp_list) {
			auto& st1 = cmpStrg[std::type_index(typeid(t1))];
			auto& st2 = cmpStrg[std::type_index(typeid(t2))];
			for (EntityID id = 0; id < min(st1.size(), st2.size()); id++) {

				if (st1[id] && st2[id])
					comp_list.push_back({ static_cast<t1*>(st1[id]), static_cast<t2*>(st2[id]) });
			}
		}

		~ECSManager() {

		}

	private:
		EntityID nextEntity = 0;
		std::unordered_map<std::type_index, std::vector<void*>> cmpStrg;
	};
}
