#pragma once

#include "Asset/AssetMetadata.h"
#include "Asset/Asset.h"

namespace Color
{
	using AssetRegistry = std::unordered_map<AssetHandle, AssetMetadata>;
	using AssetMap      = std::unordered_map<AssetHandle, Ref<Asset>>;

	// The base class for asset managers.
	class AssetManager
	{
	public:
		virtual ~AssetManager() = default;

		virtual WeakRef<Asset> GetAsset(AssetHandle handle) = 0;
		virtual bool UnloadAsset(AssetHandle handle) = 0;

		virtual AssetType GetAssetType(AssetHandle handle) const = 0;
		virtual bool IsAssetHandleValid(AssetHandle handle) const = 0;
		virtual bool IsAssetLoaded(AssetHandle handle) const = 0;
	};
}
