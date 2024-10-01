#include "ColorPCH.h"
#include "Asset.h"

#include "Misc/Random.h"

namespace Color
{
	AssetHandle GenerateAssetHandle()
	{
		static RandomGenerator rng = RandomGenerator::SeededWithTime();
		return rng.Range<AssetHandle>();
	}

	std::string_view AssetTypeToString(AssetType type)
	{
		switch (type)
		{
		case AssetType::None:  return "AssetType::None";
		case AssetType::Scene: return "AssetType::Scene";
		}

		unreachable();
		return "AssetType::<?>";
	}

	AssetType AssetTypeFromString(std::string_view type)
	{
		if (type == "AssetType::None")  return AssetType::None;
		if (type == "AssetType::Scene") return AssetType::Scene;

		return AssetType::None;
	}
}
