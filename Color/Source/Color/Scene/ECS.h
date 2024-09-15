#pragma once

#include "Core/Assert.h"

#include <unordered_map>

namespace Color
{
	namespace ECS
	{
		typedef size_t EntityID;
		EntityID GenerateEntityID();

		/**
		 * @brief Most integral part of Color's ECS system, the entity.
		 * It itself only contains two things, its own identifier ID and an array, well, in this case, a map of components.
		 * It can be used independently but it's designed for use with the Scene system and Color::Entity (not Color::ECS::Entity) abstraction.
		 *
		 * It "requires" every component type to provide two functions:
		 *   static const char* GetCompTypeId()
		 *   const char* GetCompId() const
		 * GetCompTypeId must return a unique string for each component type. It should probably be the type name of the class, but the string itself can be anything, as long as it's unique.
		 * GetCompId is just a non-static method version, it must return the exact value as GetCompTypeId.
		 * The components above can be easily implemented via the helper macro "CL_COMPONENT_DEFDEFS" (abbreviation of COLOR_COMPONENT_DEFINE_DEFAULTS).
		 *
		 * As long as components respect these rules, they will work flawlessly with the ECS system.
		 */
		struct Entity
		{
			EntityID ID = 0;
			std::unordered_map<const char*, void*> Components;

			template <typename T, typename... Args>
			T& AddComponent(Args&&... args)
			{
				checkf(!HasComponent<T>(), "Entity with ID {} got a request to add component '{}', but said component already exists on the entity.");
				return AddOrReplaceComponent<T, Args...>(std::forward<Args>(args)...);
			}

			template <typename T, typename... Args>
			T& AddOrReplaceComponent(Args&&... args)
			{
				return *(T*)(Components[T::GetCompTypeId()] = new T(std::forward<Args>(args)...));
			}

			template <typename T>
			void RemoveComponent()
			{
				checkf(HasComponent<T>(), "Entity with ID {} got a request to remove component '{}', but said component doesn't exist on the entity.");

				T* entity = (T*) Components[T::GetCompTypeId()];
				Components.erase(T::GetCompTypeId());
				delete entity;
			}

			void RemoveAllComponents()
			{
				for (auto&& [id, component] : Components)
				{
					delete component;
				}

				Components.clear();
			}

			template <typename T, typename... Args>
			T& GetOrAddComponent(Args&&... args)
			{
				if (HasComponent<T>())
				{
					return GetComponent<T>();
				}

				return AddComponent<T, Args...>(std::forward<Args>(args)...);
			}

			template <typename T>
			T& GetComponent() const
			{
				checkf(HasComponent<T>(), "Entity with ID {} got a request to return component '{}', but said component doesn't exist on the entity.");
				return *(T*)(Components.at(T::GetCompTypeId()));
			}

			template <typename T>
			bool HasComponent() const
			{
				return Components.find(T::GetCompTypeId()) != Components.end();
			}
		};
	}
}
