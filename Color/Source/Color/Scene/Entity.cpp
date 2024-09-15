#include "ColorPCH.h"
#include "Entity.h"

#include "Components/NameComponent.h"
#include "Scene/Scene.h"

namespace Color
{
	Entity::Entity(const Scene* scene, ECS::EntityID id)
		: m_Scene(scene), m_ID(id)
	{
	}

	const std::string& Entity::GetName()
	{
		ECS::Entity* ref = GetRef();
		if (!ref->HasComponent<NameComponent>())
		{
			return NO_NAME_COMPONENT_FOUND;
		}

		return ref->GetComponent<NameComponent>().Name;
	}

	ECS::Entity* Entity::GetRef()
	{
		return ((Scene*) m_Scene)->GetEntityRef(m_ID);
	}

	bool Entity::IsValid()
	{
		return m_Scene->OwnsEntity(*this);
	}
}
