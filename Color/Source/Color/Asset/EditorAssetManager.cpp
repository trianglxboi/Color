#include "ColorPCH.h"
#include "EditorAssetManager.h"

#include "Asset/AssetImporter.h"
#include "Project/Project.h"
#include "Utils/FileSystem.h"

#include <yaml-cpp/yaml.h>

namespace Color
{
	static std::unordered_map<std::string_view, AssetType> s_AssetExtensionMap =
	{
		{ ".clsc", AssetType::Scene }
	};

	WeakRef<Asset> EditorAssetManager::ImportAsset(std::string_view filepath)
	{
		std::string fileExtension = FileSystem::GetFileExtension(filepath);

		if (s_AssetExtensionMap.find(fileExtension) == s_AssetExtensionMap.end())
		{
			CL_CORE_ERROR("EditorAssetManager::ImportAsset -> Asset import failure, couldn't determine the type of asset '{}'.", filepath);
			return {};
		}

		AssetHandle handle = GenerateAssetHandle();
		AssetMetadata metadata;

		metadata.Filepath = filepath;
		metadata.Type = s_AssetExtensionMap[fileExtension];
		metadata.Version = k_LatestAssetVersions.at(metadata.Type);

		CL_CORE_TRACE("EditorAssetManager::ImportAsset -> Importing asset of type {} with version {}:'{}'.",
			AssetTypeToString(metadata.Type), metadata.Version, k_AssetVersionDescriptors.at({ metadata.Type, metadata.Version }));

		Ref<Asset> asset = AssetImporter::ImportAsset(handle, metadata);
		if (!asset)
		{
			CL_CORE_ERROR("EditorAssetManager::ImportAsset -> Asset import failure, AssetImporter::ImportAsset retured nullptr.");
			return {};
		}

		m_Assets[handle] = asset;
		m_Registry[handle] = metadata;
		SerializeAssetRegistry();

		return asset;
	}

	const AssetMetadata& EditorAssetManager::GetAssetMetadata(AssetHandle handle) const
	{
		if (!IsAssetHandleValid(handle))
		{
			CL_CORE_FATAL("EditorAssetManager error, GetAssetMetadata called with handle {} which doesn't exist within the registry.", handle);
		}

		return m_Registry.at(handle);
	}

	WeakRef<Asset> EditorAssetManager::GetAsset(AssetHandle handle)
	{
		if (IsAssetLoaded(handle))
		{
			return m_Assets[handle];
		}

		if (!IsAssetHandleValid(handle))
		{
			CL_CORE_FATAL("Tried to call GetAsset with handle {}, but the specified asset doesn't exist within the registry, nor was it found in the asset map.", handle);
			return {};
		}

		AssetMetadata& metadata = m_Registry.at(handle);
		Ref<Asset> asset = AssetImporter::ImportAsset(handle, metadata);

		if (!asset)
		{
			CL_CORE_ERROR("GetAsset failure, AssetImporter::ImportAsset failed.");
			return {};
		}

		m_Assets[handle] = asset;
		m_Registry[handle] = metadata;

		return asset;
	}

	bool EditorAssetManager::UnloadAsset(AssetHandle handle)
	{
		if (!IsAssetLoaded(handle))
		{
			CL_CORE_WARN("Tried to unload an asset with handle {}, but the specified asset is already unloaded. Performing no action.");
			return false;
		}

		m_Assets[handle].reset();
		m_Assets.erase(handle);

		return true;
	}

	AssetType EditorAssetManager::GetAssetType(AssetHandle handle) const
	{
		return GetAssetMetadata(handle).Type;
	}

	bool EditorAssetManager::IsAssetHandleValid(AssetHandle handle) const
	{
		return m_Registry.find(handle) != m_Registry.end();
	}

	bool EditorAssetManager::IsAssetLoaded(AssetHandle handle) const
	{
		return m_Assets.find(handle) != m_Assets.end();
	}
	
	void EditorAssetManager::SerializeAssetRegistry()
	{
		YAML::Emitter out;
		{
			out << YAML::BeginMap;
			out << YAML::Key << "AssetRegistry" << YAML::Value;
			out << YAML::BeginSeq;
			for (auto&& [handle, metadata] : m_Registry)
			{
				out << YAML::BeginMap;
				out << YAML::Key << "Handle" << YAML::Value << handle;
				out << YAML::Key << "Type" << YAML::Value << AssetTypeToString(metadata.Type).data();
				out << YAML::Key << "Version" << YAML::Value << metadata.Version;
				out << YAML::Key << "Filepath" << YAML::Value << metadata.Filepath;
				out << YAML::EndMap;
			}
			out << YAML::EndSeq;
			out << YAML::EndMap;
		}

		FileSystem::Write(ActiveProject::GetAssetRegistryPath(), out.c_str());
	}

	bool EditorAssetManager::DeserializeAssetRegistry()
	{
		const std::string& regPath = ActiveProject::GetAssetRegistryPath();

		YAML::Node nRoot;
		try
		{
			nRoot = YAML::LoadFile(regPath.data());
		}
		catch (...)
		{
			CL_CORE_ERROR("Failed to load asset registry '{}'.", regPath);
			return false;
		}

		YAML::Node nAssetRegistry = nRoot["AssetRegistry"];
		if (!nAssetRegistry)
		{
			return false;
		}

		for (const YAML::Node& node : nAssetRegistry)
		{
			AssetHandle handle = node["Handle"].as<AssetHandle>();
			AssetMetadata& metadata = m_Registry[handle];
			metadata.Type = AssetTypeFromString(node["Type"].as<std::string>());
			metadata.Version = node["Version"].as<size_t>();
			metadata.Filepath = node["Filepath"].as<std::string>();
		}

		return true;
	}
}
