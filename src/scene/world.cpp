#include "pch.h"
#include "world.h"
#include "entity.h"
#include "../utils/time.h"

namespace Physx2D {
	World::World(const Window* targetWindow) {
		this->window = targetWindow;
		this->sceneCamera = Camera();
		this->manager = new ECSManager;

		const char* vs = "\
			#version 460 core\n\
			#define __l(x) layout(location=x) in \n\
			__l(0) vec2 vp;__l(1) vec2 tc;\
			__l(2) vec2 ps;__l(3) vec2 sc;__l(4) float a;__l(5) vec4 cl;__l(6) vec2 to;__l(7) vec2 tf;\
			out vdat{vec4 cl;vec2 uv;}vo;\
				uniform mat3 u_cam_matrices;\
				void main() {\
					float s = sin(a), c = cos(a);\
					vec2 p = mat2(c, s, -s, c) * (vp.xy * sc) + ps;\
					p = (u_cam_matrices * vec3(p, 1.0f)).xy;\
					vo.cl = cl; vo.uv = tc * tf + to;\
					gl_Position = vec4(p, 0.0f, 1.0f);\
			}\
		";

		const char* fs = "\
			#version 460 core\n\
			in vdat{vec4 cl;vec2 uv;}fsi;\
			out vec4 _;\
			uniform int u_num_textures;\
			uniform sampler2D u_textures[16];\
			void main(){\
				_=vec4(0.f);\
				for(int i=0; i<u_num_textures && i < 16; i++) _+=texture(u_textures[i], fsi.uv);\
				_/=max(1.f,float(u_num_textures));\
				_=fsi.cl+(_-fsi.cl)*_.a;\
			}";

		loadShader(vs, fs, DEFAULT, false);
	}

	World::~World()	{
		for (auto& ent : entities)
			delete ent;

		for (auto& shd : shaders)
			delete shd.second;

		for (auto& irnd : renderers)
			delete irnd.second;

		for (auto& txtv : textures) {
			for(auto& txt:txtv.second)
				delete txt;
		}
		delete manager;
	}

	void World::loadDefaultRenderer(RenderType type) {
		
		switch (type) {
			case LINE:
				addInstancedRenderer(LINE, initVectorFromArray(LINE_VERTICES, float), 2, GL_LINES);
				setDefaultLayout(LINE);
				break;

			case TRIANGLE:
				addInstancedRenderer(TRIANGLE, initVectorFromArray(TRIANGLE_VERTICES, float), 3, GL_TRIANGLES);
				setDefaultLayout(TRIANGLE);
				break;

			case CIRCLE:
				addInstancedRenderer(CIRCLE, initVectorFromArray(QUAD_VERTICES, float), 6, GL_TRIANGLES);
				setDefaultLayout(CIRCLE);
				break;

			case QUAD:
			case DEFAULT:
			default:
				addInstancedRenderer(QUAD, initVectorFromArray(QUAD_VERTICES, float), 6, GL_TRIANGLES);
				setDefaultLayout(QUAD);
				break;
		}
	}

	void World::Update(double delta_time) {
		PHSX2D_DBG_EXP(float time = TIME;)
		handleCollisions();
		PHSX2D_DBG_EXP(LOG_INFO("\nCollisions : %f\n", (TIME - time) * 1000.f); time = TIME;)
		sceneCamera.handleInputs(window->m_window, delta_time);
		handleScripts(delta_time);
		PHSX2D_DBG_EXP(LOG_INFO("Script Update : %f\n", (TIME - time) * 1000.f); time = TIME;)
		handlePhysics(delta_time);
		PHSX2D_DBG_EXP(LOG_INFO("Physics Update : %f\n", (TIME - time) * 1000.f); time = TIME;)
		updateRenderData();
		PHSX2D_DBG_EXP(LOG_INFO("RenderData update : %f\n", (TIME - time) * 1000.f); time = TIME;)
	}

	void World::updateRenderData() {
		for (auto& vec : renderData)
			vec.second.clear();

		std::vector<__comp_pair<Transform*, SpriteRenderer*>> comp;
		manager->getCompPair<Transform, SpriteRenderer>(comp);

		for (auto& _pr : comp) {
			renderData[_pr.__pair2->type].push_back({*_pr.__pair1, _pr.__pair2->color, _pr.__pair2->offset, _pr.__pair2->tiling});
		}

		for (auto& iter : shaders) {
			iter.second->use();
			sceneCamera.setValues(iter.second, vec2(window->GetWidth(), window->GetHeight()));
			iter.second->setFloat("u_time", TIME*1000);
		}
		
		for (auto& renderer : renderers) {
			auto& rd = renderData[renderer.first];
			if (rd.size() == 0) continue;
			renderer.second->InstanceData(rd.data(), rd.size(), sizeof(RenderData));
		}
	}

	void World::Render() {
		for (auto& iter : renderers) {
			auto& __sh = shaders.find(iter.first) != shaders.end()? shaders[iter.first] : shaders[DEFAULT];

			if (textures.find(iter.first) != textures.end()) {
				int sz = textures[iter.first].size();
				__sh->setInt("u_num_textures", sz);

				for (int i = 0; i < sz; i++) {
					auto& tex = textures[iter.first][i];
					tex->bind();
					std::string __unf = "u_textures[" + std::to_string(i) + "]";
					tex->texUnit(__sh , __unf.c_str());
				}
			}
			else __sh->setInt("u_num_textures", 0);

			iter.second->Draw(__sh);
		}
	}

	Entity* World::CreateEntity(const char* name) {
		Entity* ent = new Entity(manager->CreateEntity(), this);
		ent->AddComponent<Transform>();
		ent->AddComponent<Tag>(name);
		entities.push_back(ent);
		return ent;
	}

	InstancedRenderer* World::addInstancedRenderer(uint32_t type, std::vector<float> vertices, uint32_t numPoints,GLenum draw_mode) {
		
		if (renderers.find(type) != renderers.end())
			LOG_WARN("Renderer of the type %u already exists", type);
		else
			renderers[type] = new InstancedRenderer(vertices, numPoints, draw_mode);
		return renderers[type];
	}

	InstancedRenderer* World::addInstancedRenderer(uint32_t type, std::vector<float> vertices, std::vector<uint32_t> indices, GLenum draw_mode) {
		if (renderers.find(type) != renderers.end())
			LOG_WARN("Renderer of the type %u already exists", type);
		else
			renderers[type] =new InstancedRenderer(vertices, indices, draw_mode);
		return renderers[type];
	}

	void World::setDefaultLayout(uint32_t type) {
		renderers[type]->VertexDataLayout(0, 2, GL_FLOAT, 2 * sizeof(vec2), 0);						//vec2 vertex position
		renderers[type]->VertexDataLayout(1, 2, GL_FLOAT, 2 * sizeof(vec2), sizeof(vec2));			//vec2 texture coords

		renderers[type]->InstanceLayout(2, 2, GL_FLOAT, sizeof(RenderData), 0);						//vec2 position
		renderers[type]->InstanceLayout(3, 2, GL_FLOAT, sizeof(RenderData), 2 * sizeof(float));		//vec2 scale
		renderers[type]->InstanceLayout(4, 1, GL_FLOAT, sizeof(RenderData), 4 * sizeof(float));		//float rotation
		renderers[type]->InstanceLayout(5, 4, GL_FLOAT, sizeof(RenderData), 5 * sizeof(float));		//vec4 color
		renderers[type]->InstanceLayout(6, 2, GL_FLOAT, sizeof(RenderData), 9 * sizeof(float));		//texOffset
		renderers[type]->InstanceLayout(7, 2, GL_FLOAT, sizeof(RenderData), 11 * sizeof(float));	//Tiling factor
	}

	void World::handleScripts(float delta_time) {

		std::vector<ScriptComponent*> scripts;
		manager->getAllComponents<ScriptComponent>(scripts);

		for (auto& scr : scripts) {
			if (!scr->__setup) {
				scr->script->setup();
				scr->__setup = true;
			}
			else {
				scr->script->update(delta_time);
			}
		}
	}

	void World::handlePhysics(double delta_time) {
		std::vector<__comp_pair<Transform*, RigidBody2D*>> comp;
		manager->getCompPair<Transform, RigidBody2D>(comp);

		for (auto& cpair : comp) PhysicsHandler::updateRigidBody(cpair.__pair2, cpair.__pair1, delta_time);
	}

	void World::handleCollisions() {
		centerRect treesize = centerRect(vec2(0.f), vec2(WORLD_SIZE_X, WORLD_SIZE_Y)); //setup the bounds for quadtree
		vec2 range(0.f, 0.f);		//range upto which neighbour are valid
		
		QuadTree<Entity*> qtree(treesize);	//init quadtree
		
		//populate quadtree plus find the range of collision check
		for (auto& entity : entities) {
			if (entity->HasComponent<Collider>()) {
				Transform* tfr = entity->GetComponent<Transform>();
				Collider* cld = entity->GetComponent<Collider>();

				//ignore Bounding colliders on quadtree
				if (cld->typeIndex == std::type_index(typeid(AABB)) || cld->typeIndex == std::type_index(typeid(BoundingCircle)))
					continue;
				
				//find max range
				range.x = max(range.x, cld->getSize().x);
				range.y = max(range.y, cld->getSize().y);

				// insert entity on collider position on quadtree
				qtree.insert(tfr->Position + cld->Offset, entity);
			}
		}
		range *= 2.f;

		//collision check 
		for (auto& entity : entities) {
			if (entity->HasComponent<Collider>()) {
				Transform* tfr = entity->GetComponent<Transform>();
				Collider* cld = entity->GetComponent<Collider>();

				std::vector<Entity*> neighbours;

				bool isBound = (cld->typeIndex == std::type_index(typeid(AABB))) || (cld->typeIndex == std::type_index(typeid(BoundingCircle)));

				qtree.query(centerRect(tfr->Position + cld->Offset, isBound?cld->getSize()+range : range), neighbours);

				for (auto& nent : neighbours) {
					if (nent == entity) continue;
					
					Transform* ntfr = nent->GetComponent<Transform>();
					Collider* ncld = nent->GetComponent<Collider>();

					RigidBody2D* nrgb = nullptr;
					RigidBody2D* rgb = nullptr;

					if(entity->HasComponent<RigidBody2D>())
						rgb = entity->GetComponent<RigidBody2D>();
					if (nent->HasComponent<RigidBody2D>()) 
						nrgb = nent->GetComponent<RigidBody2D>();

					BodyType type1 = rgb ? rgb->Type : STATIC;
					BodyType type2 = nrgb ? nrgb->Type : KINETIC;

					CollisionData data = PhysicsHandler::checkCollision(cld, tfr, type1, ncld, ntfr, type2);
					if (data.status) {
						if (type1 == KINETIC)
							PhysicsHandler::collisionPhysics(data, rgb, nrgb);
						else if (type2 == KINETIC && nrgb)
							PhysicsHandler::collisionPhysics(data, nrgb, rgb);

						if (entity->HasComponent<ScriptComponent>()) {
							entity->GetComponent<ScriptComponent>()->script->OnCollisionDetected(data, nent);
						}
					}
				}
			}
		}
	}
}
