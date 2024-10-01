#pragma once

#include "Asset/AssetMetadata.h"
#include "Scene/Scene.h"

namespace Color
{
	struct SceneImporter
	{
		static Ref<Scene> ImportScene(AssetHandle handle, const AssetMetadata& metadata);

		static Ref<Scene> LoadScene(std::string_view filepath);
		static bool SaveScene(Ref<Scene>& scene, std::string_view path);
	};
}
