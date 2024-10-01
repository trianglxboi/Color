#include "ColorPCH.h"
#include "SceneImporter.h"

#include "Scene/SceneSerializer.h"
#include "Project/Project.h"
#include "Utils/FileSystem.h"

namespace Color
{
	Ref<Scene> SceneImporter::ImportScene(AssetHandle handle, const AssetMetadata& metadata)
	{
		Ref<Scene> scene = LoadScene(ActiveProject::GetPathOfAsset(metadata.Filepath));
		scene->Handle = handle;
		return scene;
	}

	Ref<Scene> SceneImporter::LoadScene(std::string_view filepath)
	{
		Ref<Scene> scene = CreateRef<Scene>();

		SceneSerializer serializer(scene);
		try
		{
			serializer.Deserialize(filepath);
		}
		catch (...)
		{
			return nullptr;
		}

		return scene;
	}

	bool SceneImporter::SaveScene(Ref<Scene>& scene, std::string_view path)
	{
		SceneSerializer serializer(scene);
		return serializer.Serialize(FileSystem::CombinePaths(Project::GetActive()->GetConfig().AssetDirectory, path));
	}
}
