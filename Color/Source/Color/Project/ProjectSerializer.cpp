#include "ColorPCH.h"
#include "ProjectSerializer.h"

#include "Utils/FileSystem.h"

#include <yaml-cpp/yaml.h>

namespace Color
{
	ProjectSerializer::ProjectSerializer(const Ref<Project>& project)
		: m_Project(project)
	{
	}

	bool ProjectSerializer::Serialize(std::string_view filepath) const
	{
		const ProjectConfig& config = m_Project->GetConfig();

		YAML::Emitter out;
		{
			out << YAML::BeginMap;
			out << YAML::Key << "Project" << YAML::Value;
			{
				out << YAML::BeginMap;
				out << YAML::Key << "Name" << YAML::Value << config.Name;
				out << YAML::Key << "AssetDirectory" << YAML::Value << config.AssetDirectory;
				out << YAML::Key << "AssetRegistryPath" << YAML::Value << config.AssetRegistryPath;
				out << YAML::EndMap;
			}
			out << YAML::EndMap;
		}

		return FileSystem::Write(filepath, out.c_str());
	}

	bool ProjectSerializer::Deserialize(std::string_view filepath)
	{
		ProjectConfig& config = m_Project->GetConfig();

		YAML::Node nRoot;
		try
		{
			nRoot = YAML::LoadFile(filepath.data());
		}
		catch (YAML::ParserException e)
		{
			CL_CORE_ERROR("Failed to load project file '{}'\n.	{}", filepath, e.what());
			return false;
		}

		YAML::Node nProject = nRoot["Project"];
		if (!nProject)
		{
			CL_CORE_ERROR("Project file '{}' has no root node!", filepath);
			return false;
		}

		config.Name = nProject["Name"].as<std::string>();
		config.AssetDirectory = nProject["AssetDirectory"].as<std::string>();
		config.AssetRegistryPath = nProject["AssetRegistryPath"].as<std::string>();

		return true;
	}
}
