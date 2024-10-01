#pragma once

#include "Core/Base.h"

namespace Color
{
	using AssetHandle = size_t;
	inline constexpr AssetHandle INVALID_ASSET_HANDLE = 0;
	AssetHandle GenerateAssetHandle();

	enum class AssetType : uint16_t
	{
		None = 0,
		Scene
	};

	std::string_view AssetTypeToString(AssetType type);
	AssetType AssetTypeFromString(std::string_view type);

	// Every class that derives from Asset must provide a function as follows:
	//   static AssetType GetStaticAssetType()
	// It must return the same type as GetAssetType() pure virtual method.
	// CL_ASSET_CLASS_IMPL() macro can be used to make it easier.
	class Asset
	{
	public:
		AssetHandle Handle = INVALID_ASSET_HANDLE;
		virtual AssetType GetAssetType() const = 0;
	};

	#define CL_ASSET_CLASS_IMPL(type) static ::Color::AssetType GetStaticAssetType() { return ::Color::AssetType::##type; } \
									  virtual ::Color::AssetType GetAssetType() const override { return GetStaticAssetType(); }
}
