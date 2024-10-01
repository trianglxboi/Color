#pragma once

#include "Asset/Asset.h"

#include <map>

namespace Color
{
	struct AssetMetadata
	{
		// The type of the asset, pretty self-explanatory.
		AssetType Type = AssetType::None;

		// Version of the asset. Should be incremented each time the structure of the asset changes.
		// Loading assets of older versions should be handled properly if possible for backwards compatability.
		size_t Version = 0;

		// Where the asset resides.
		std::string Filepath;
	};

	inline const std::unordered_map<AssetType, size_t> k_LatestAssetVersions =
	{
		{ AssetType::None,  0 },
		{ AssetType::Scene, 0 }
	};

	struct AssetVersionDescriptorRequestData
	{
		AssetType Type = AssetType::None;
		size_t Version = 0;

		bool operator<(const AssetVersionDescriptorRequestData other) const
		{
			return Type < other.Type && Version < other.Version;
		}
	};

	inline const std::map<AssetVersionDescriptorRequestData, std::string_view> k_AssetVersionDescriptors =
	{
		// None
		{ { AssetType::None,  1 }, "None"              },

		// Scene
		{ { AssetType::Scene, 1 }, "SceneSerialFormat" }
	};
}
