#pragma once

#include "Scene/Entity.h"
#include "Misc/Timestep.h"

#include <vector>

namespace Color
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void StartRuntime();
		void UpdateRuntime(Timestep ts);
		void StopRuntime();

		void SetPaused(bool paused);

		Entity CreateRawEntity();
		Entity CreateRawEntityWithID(ECS::EntityID id);

		Entity CreateEntity(std::string_view name = "Unnamed Entity");
		Entity CreateEntityWithID(ECS::EntityID id, std::string_view name = "Unnamed Entity");

		Entity DuplicateEntity(ECS::EntityID id);
		Entity DuplicateEntity(Entity entity);

		bool DeleteEntity(ECS::EntityID id);
		bool DeleteEntity(Entity entity);

		Entity GetEntityByID(ECS::EntityID id) const;
		Entity GetFirstEntityByName(std::string_view name) const;
		std::vector<Entity> GetAllEntitiesByName(std::string_view name) const;

		bool HasEntity(ECS::EntityID id) const;
		bool OwnsEntity(Entity entity) const;

		ECS::Entity* GetEntityRef(ECS::EntityID id);

		bool IsRunning() const { return m_Running; }
		bool IsPaused() const { return m_Paused; }
	private:
		bool m_Running = false;
		bool m_Paused = false;

		std::unordered_map<ECS::EntityID, ECS::Entity> m_Entities;
	};
}
