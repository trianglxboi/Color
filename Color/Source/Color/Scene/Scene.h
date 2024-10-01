#pragma once

#include "Asset/Asset.h"

#include "Scene/Entity.h"
#include "Misc/Timestep.h"

#include <vector>

namespace Color
{
	class Scene : public Asset
	{
	public:
		CL_ASSET_CLASS_IMPL(Scene);
	public:
		Scene(const std::string& name = "Untitled");
		~Scene();

		// Creates an identical copy of the given scene.
		static Ref<Scene> Copy(Ref<Scene>& scene, std::string_view name = nullptr);

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

		const std::string& GetName() const { return m_Name; }
		void SetName(std::string_view name) { m_Name = name; }

		bool IsRunning() const { return m_Running; }
		bool IsPaused() const { return m_Paused; }
	private:
		std::string m_Name;

		bool m_Running = false;
		bool m_Paused = false;

		std::unordered_map<ECS::EntityID, ECS::Entity> m_Entities;
	private:
		friend class SceneSerializer;
	};
}
