#pragma once

#include "Core/Base.h"
#include "Asset/EditorAssetManager.h"

namespace Color
{
	struct ProjectConfig
	{
		std::string Name;
		std::string AssetDirectory;
		std::string AssetRegistryPath; // PrjPath / AssetDirectory / ...
	};

	class Project
	{
	public:
		static Ref<Project> New(bool setAsActive = true);
		static Ref<Project>& GetActive() { return s_ActiveProject; }

		static Ref<Project> Load(std::string_view path);
		static bool SaveActive(std::string_view path);

		const std::string& GetProjectDirectory() const { return m_ProjectDirectory; }
		const ProjectConfig& GetConfig() const { return m_Config; }
		ProjectConfig& GetConfig() { return m_Config; }

		AssetManager* GetAssetManager() const { return m_AssetManager.get(); }
		EditorAssetManager* GetEditorAssetManager() const { return dynamic_cast<EditorAssetManager*>(GetAssetManager()); }
	private:
		std::string m_ProjectDirectory;
		ProjectConfig m_Config;

		Scope<AssetManager> m_AssetManager;
	private:
		inline static Ref<Project> s_ActiveProject;
	};

	struct ActiveProject
	{
		static ProjectConfig& GetConfig() { return Project::GetActive()->GetConfig(); }

		static AssetManager* GetAssetManager() { return Project::GetActive()->GetAssetManager(); }
		static EditorAssetManager* GetEditorAssetManager() { return Project::GetActive()->GetEditorAssetManager(); }

		static const std::string& GetName() { return GetConfig().Name; }
		static const std::string& GetProjectDirectory() { return Project::GetActive()->GetProjectDirectory(); }

		static std::string GetAssetDirectory();
		static std::string GetAssetRegistryPath();
		static std::string GetPathOfAsset(std::string_view assetPath);
	};
}
