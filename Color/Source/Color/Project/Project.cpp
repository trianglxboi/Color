#include "ColorPCH.h"
#include "Project.h"

#include "Project/ProjectSerializer.h"
#include "Utils/FileSystem.h"

namespace Color
{
	Ref<Project> Project::New(bool setAsActive)
	{
		Ref<Project> project = CreateRef<Project>();
		if (setAsActive)
		{
			s_ActiveProject = project;
			s_ActiveProject->m_AssetManager = CreateScope<EditorAssetManager>();
		}
		return project;
	}

	Ref<Project> Project::Load(std::string_view path)
	{
		Ref<Project> project = CreateRef<Project>();
		ProjectSerializer serializer(project);

		if (serializer.Deserialize(path))
		{
			project->m_ProjectDirectory = FileSystem::WithoutFilename(path);
			s_ActiveProject = project;
			s_ActiveProject->m_AssetManager = CreateScope<EditorAssetManager>();
			s_ActiveProject->GetEditorAssetManager()->DeserializeAssetRegistry();
			return project;
		}

		return nullptr;
	}

	bool Project::SaveActive(std::string_view path)
	{
		ProjectSerializer serializer(s_ActiveProject);

		if (serializer.Serialize(path))
		{
			s_ActiveProject->m_ProjectDirectory = FileSystem::WithoutFilename(path);
			return true;
		}

		return false;
	}

	std::string ActiveProject::GetAssetDirectory()
	{
		return FileSystem::CombinePaths(GetProjectDirectory(), GetConfig().AssetDirectory);
	}

	std::string ActiveProject::GetAssetRegistryPath()
	{
		return FileSystem::CombinePaths(GetAssetDirectory(), GetConfig().AssetRegistryPath);
	}

	std::string ActiveProject::GetPathOfAsset(std::string_view assetPath)
	{
		return FileSystem::CombinePaths(GetAssetDirectory(), assetPath);
	}
}
