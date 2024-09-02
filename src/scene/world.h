#pragma once

/*
	World is a global event handler for engine. It keeps track of all the entities, physics, collision, rendering, scripts, etc.
	Plus it tracks all the shaders and textures of the application..
*/

#include "pch.h"
#include "../window/window.h"
#include "ecsmanager.h"
#include "../physics/physics2d.h"
#include "../renderer/texture.h"
#include "../renderer/instancedRenderer.h"
#include "../utils/quadtree.h"
#include "camera.h"

namespace Physx2D {

	class PHYSX2D_API Entity;

	class PHYSX2D_API World {
		public:
			Camera sceneCamera;

			World(const Window* targetWindow);
			virtual ~World();

			void loadDefaultRenderer(RenderType type = DEFAULT);

			void Update(double delta_time);
			void Render();

			Entity* CreateEntity(const char* name = "Entity");

			InstancedRenderer* addInstancedRenderer(uint32_t type, std::vector<float> vertices, uint32_t numPoints, GLenum draw_mode);
			InstancedRenderer* addInstancedRenderer(uint32_t type, std::vector<float> vertices, std::vector<uint32_t> indices, GLenum draw_mode);


			inline void loadShader(const char* vert, const char* frag, uint32_t ID = DEFAULT, bool is_path = true) {
				/*
					Every Shader should have some default uniforms as of now.
					> u_time for time
					> u_textures[16] * for different texture samples(16 is max number of textures for each renderer)
					> u_num_textures * for actual number of textures bound
					> u_cam_matrices * for projection matrices
					> u_fov for field of view of camera (zoom level)
					> u_resolution for screen resolution
				*/
				if (shaders.find(ID) != shaders.end()) {
					LOG_WARN("Replacing existing shader with new one.. ID : (%u)\n", ID);
					delete shaders[ID];
				}
				shaders[ID] = new Shader(vert, frag, is_path);
			}

			inline void loadTexture(const char* path, const char* type, uint32_t ID = DEFAULT, int slot = -1) {
				uint32_t _id = ID == DEFAULT ? QUAD : ID;
				textures[_id].push_back(new Texture(path, type, slot < 0 ? textures[_id].size() : slot));
			}
		private:
			const Window* window;

			ECSManager* manager;
			std::vector<Entity*> entities;
			
			std::unordered_map<uint32_t, Shader*> shaders;
			std::unordered_map<uint32_t, std::vector<Texture*>> textures;

			std::unordered_map<uint32_t, InstancedRenderer*> renderers;

			std::unordered_map<uint32_t, std::vector<RenderData>> renderData;
			
			void handleScripts(float delta_time);
			void handlePhysics(double delta_time);
			void handleCollisions();
			void updateRenderData();
			void setDefaultLayout(uint32_t type);
			
			friend class Entity;
	};
}