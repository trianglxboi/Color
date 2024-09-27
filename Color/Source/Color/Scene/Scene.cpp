#include "ColorPCH.h"
#include "Scene.h"

#include "Scene/Components.h"

namespace Color
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::StartRuntime()
	{
		m_Running = true;
	}

	void Scene::UpdateRuntime(Timestep ts)
	{
		if (!m_Running)
		{
			return;
		}

		if (!m_Paused)
		{
			// Update stuff that happen only during m_Paused=false.
		}

		// Update stuff that happen even during pauses.
	}

	void Scene::StopRuntime()
	{
		m_Running = false;
	}

	void Scene::SetPaused(bool paused)
	{
		m_Paused = paused;
	}

	Entity Scene::CreateRawEntity()
	{
		return CreateRawEntityWithID(ECS::GenerateEntityID());
	}

	Entity Scene::CreateRawEntityWithID(ECS::EntityID id)
	{
		if (HasEntity(id))
		{
			CL_CORE_ERROR("An entity with an ID of {} already exists within the scene.", id);
			return {};
		}

		m_Entities[id] = ECS::Entity { id };
		return { this, id };
	}

	Entity Scene::CreateEntity(std::string_view name)
	{
		return CreateEntityWithID(ECS::GenerateEntityID(), name);
	}

	Entity Scene::CreateEntityWithID(ECS::EntityID id, std::string_view name)
	{
		Entity e = CreateRawEntityWithID(id);

		e.AddComponent<NameComponent>(name);
		e.AddComponent<TransformComponent>();

		return e;
	}

	Entity Scene::DuplicateEntity(ECS::EntityID id)
	{
		if (!HasEntity(id))
		{
			CL_CORE_WARN("Tried to duplicate an entity with an ID of {}, but said entity doesn't exist in the scene.", id);
			return {};
		}

		ECS::EntityID genId = ECS::GenerateEntityID();

		ECS::Entity& original = m_Entities[id];
		ECS::Entity& duplicate = m_Entities[genId] = ECS::Entity();

		for (auto&& [id, component] : original.Components)
		{
		#define DuplicateComponent(type) if (original.HasComponent<type>()) { duplicate.AddComponent<type>(original.GetComponent<type>()); }
			DuplicateComponent(NameComponent);
			DuplicateComponent(TransformComponent);
		#undef DuplicateComponent
		}

		return { this, genId };
	}

	Entity Scene::DuplicateEntity(Entity entity)
	{
		if (!OwnsEntity(entity))
		{
			CL_CORE_WARN("Tried to duplicate an entity with an ID of {}, but said entity doesn't exist in the scene.", entity.GetID());
			return {};
		}

		return DuplicateEntity(entity.GetID());
	}

	bool Scene::DeleteEntity(ECS::EntityID id)
	{
		if (!HasEntity(id))
		{
			CL_CORE_WARN("Tried to remove an entity with an ID of {}, but said entity doesn't exist in the scene.", id);
			return false;
		}

		m_Entities[id].RemoveAllComponents();
		m_Entities.erase(id);

		return true;
	}

	bool Scene::DeleteEntity(Entity entity)
	{
		if (!OwnsEntity(entity))
		{
			CL_CORE_WARN("Tried to remove an entity with an ID of {}, but said entity doesn't exist in the scene.", entity.GetID());
			return false;
		}

		return DeleteEntity(entity.GetID());
	}

	Entity Scene::GetEntityByID(ECS::EntityID id) const
	{
		if (!HasEntity(id))
		{
			CL_CORE_ERROR("Tried to access an entity with an ID of {}, but said entity doesn't exist in the scene. Returning an invalid Entity handle.", id);
			return {};
		}

		return { this, id };
	}

	Entity Scene::GetFirstEntityByName(std::string_view name) const
	{
		for (auto&& [id, entity] : m_Entities)
		{
			if (entity.HasComponent<NameComponent>())
			{
				NameComponent& nc = entity.GetComponent<NameComponent>();

				if (nc.Name == name)
				{
					return { this, id };
				}
			}
		}

		return {};
	}

	std::vector<Entity> Scene::GetAllEntitiesByName(std::string_view name) const
	{
		std::vector<Entity> entities;

		for (auto&& [id, entity] : m_Entities)
		{
			if (entity.HasComponent<NameComponent>())
			{
				NameComponent& nc = entity.GetComponent<NameComponent>();

				if (nc.Name == name)
				{
					entities.emplace_back(this, id);
				}
			}
		}

		return entities;
	}

	bool Scene::HasEntity(ECS::EntityID id) const
	{
		return m_Entities.find(id) != m_Entities.end();
	}

	bool Scene::OwnsEntity(Entity entity) const
	{
		return entity.GetScene() == this && HasEntity(entity.GetID());
	}

	ECS::Entity* Scene::GetEntityRef(ECS::EntityID id)
	{
		checkf(HasEntity(id), "Tried to get the EntityRef of entity with an ID of {}, but said entity doesn't exist in the scene.", id);
		return &m_Entities.at(id);
	}
}
