#pragma once

#include "Scene/ECS.h"

namespace Color
{
	class Scene;

	// A convenience wrapper around a Color::ECS::Entity residing in a Color::Scene.
	class Entity
	{
	public:
		// Please, do not name any entity with this name, ever. It's a special value. If you do name one, you suck as a person.
		inline static std::string NO_NAME_COMPONENT_FOUND = "__NO_NAME_COMPONENT_FOUND__";
	public:
		Entity() = default;
		Entity(const Entity&) = default;
		Entity& operator=(const Entity&) = default;
		Entity(const Scene* scene, ECS::EntityID id);

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return GetRef()->AddComponent<T, Args...>(std::forward<Args>(args)...);
		}

		template <typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args)
		{
			return GetRef()->AddOrReplaceComponent<T, Args...>(std::forward<Args>(args)...);
		}

		template <typename T>
		void RemoveComponent()
		{
			GetRef()->RemoveComponent<T>();
		}

		void RemoveAllComponents()
		{
			GetRef()->RemoveAllComponents();
		}

		template <typename T, typename... Args>
		T& GetOrAddComponent(Args&&... args)
		{
			return GetRef()->GetOrAddComponent<T, Args...>(std::forward<Args>(args)...);
		}

		template <typename T>
		T& GetComponent()
		{
			return GetRef()->GetComponent<T>();
		}

		template <typename T>
		bool HasComponent()
		{
			return GetRef()->HasComponent<T>();
		}

		// Returns "GetComponent<NameComponent>().Name" if "HasComponent<NameComponent>()" evaluates to true, returns "Color::Entity::NO_NAME_COMPONENT_FOUND" otherwise.
		const std::string& GetName();
		ECS::Entity* GetRef();

		const Scene* GetScene() { return m_Scene; }
		ECS::EntityID GetID() { return m_ID; }

		// Checks if this entity is still valid in the scene it resides in. Behavior is undefined if the scene itself has been deleted.
		bool IsValid();
	private:
		const Scene* m_Scene = nullptr;
		ECS::EntityID m_ID = 0;
	private:
		friend class Scene;
	};
}
