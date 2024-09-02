#include "pch.h"
#include "quadtree.h"
#include "../scene/entity.h"

namespace Physx2D {
	template class PHYSX2D_API QuadTree<uint32_t>;
	template class PHYSX2D_API QuadTree<Entity*>;
	template class PHYSX2D_API QuadTree<void*>;
}