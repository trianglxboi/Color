#pragma once

#include "Asset/AssetMetadata.h"

namespace Color
{
	/**
	 * @brief AssetImporter class that unifies all of the importers within "Color/Asset/Importers" based on the type of assets they import.
	 * Only intented to be used with/by EditorAssetManager, since RuntimeAssetManager is incapable of importing new assets dynamically.
	 */
	struct AssetImporter
	{
		static Ref<Asset> ImportAsset(AssetHandle handle, const AssetMetadata& metadata);
	};
}
