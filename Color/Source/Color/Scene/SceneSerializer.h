#pragma once

#include "Scene/Scene.h"

namespace Color
{
	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		bool Serialize(std::string_view path) const;
		bool Deserialize(std::string_view path);
	private:
		Ref<Scene> m_Scene;
	};
}
