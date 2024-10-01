#pragma once

#include "Asset/AssetManager.h"

namespace Color
{
	class EditorAssetManager : public AssetManager
	{
	public:
		WeakRef<Asset> ImportAsset(std::string_view filepath);
		const AssetMetadata& GetAssetMetadata(AssetHandle handle) const;

		virtual WeakRef<Asset> GetAsset(AssetHandle handle) override;
		virtual bool UnloadAsset(AssetHandle handle) override;

		virtual AssetType GetAssetType(AssetHandle handle) const override;
		virtual bool IsAssetHandleValid(AssetHandle handle) const override;
		virtual bool IsAssetLoaded(AssetHandle handle) const override;

		void SerializeAssetRegistry();
		bool DeserializeAssetRegistry();
	private:
		AssetRegistry m_Registry;
		AssetMap m_Assets;
	};
}
