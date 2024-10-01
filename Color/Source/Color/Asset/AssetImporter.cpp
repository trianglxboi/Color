#include "ColorPCH.h"
#include "AssetImporter.h"

#include "Importers/SceneImporter.h"

namespace Color
{
	typedef std::function<Ref<Asset>(AssetHandle handle, const AssetMetadata& metadata)> AssetImportFn;
	static const std::unordered_map<AssetType, AssetImportFn> sk_AssetImportFunctions =
	{
		{ AssetType::Scene, SceneImporter::ImportScene }
	};
	
	Ref<Asset> AssetImporter::ImportAsset(AssetHandle handle, const AssetMetadata& metadata)
	{
		if (sk_AssetImportFunctions.find(metadata.Type) == sk_AssetImportFunctions.end())
		{
			CL_CORE_ERROR("AssetImporter::ImportAsset -> Couldn't find an import function for asset of type '{}'.", AssetTypeToString(metadata.Type));
			return nullptr;
		}

		return sk_AssetImportFunctions.at(metadata.Type)(handle, metadata);
	}
}
