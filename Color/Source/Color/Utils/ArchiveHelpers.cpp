#include "ColorPCH.h"
#include "ArchiveHelpers.h"

void FArchiveHelpers::SetVec2Field(FArchive& Archive, const FString& FieldName, const glm::vec2& Value)
{
	FArchiveFieldValue AFV(AFV_Group);

	AFV.AsGroup().SetField(ARCHIVEHELPERS_VECFIELDS_X, Value.x);
	AFV.AsGroup().SetField(ARCHIVEHELPERS_VECFIELDS_Y, Value.y);

	Archive.SetField(FieldName, MoveTemp(AFV));
}

void FArchiveHelpers::SetVec3Field(FArchive& Archive, const FString& FieldName, const glm::vec3& Value)
{
	FArchiveFieldValue AFV(AFV_Group);

	AFV.AsGroup().SetField(ARCHIVEHELPERS_VECFIELDS_X, Value.x);
	AFV.AsGroup().SetField(ARCHIVEHELPERS_VECFIELDS_Y, Value.y);
	AFV.AsGroup().SetField(ARCHIVEHELPERS_VECFIELDS_Z, Value.z);

	Archive.SetField(FieldName, MoveTemp(AFV));
}

void FArchiveHelpers::SetVec4Field(FArchive& Archive, const FString& FieldName, const glm::vec4& Value)
{
	FArchiveFieldValue AFV(AFV_Group);

	AFV.AsGroup().SetField(ARCHIVEHELPERS_VECFIELDS_X, Value.x);
	AFV.AsGroup().SetField(ARCHIVEHELPERS_VECFIELDS_Y, Value.y);
	AFV.AsGroup().SetField(ARCHIVEHELPERS_VECFIELDS_Z, Value.z);
	AFV.AsGroup().SetField(ARCHIVEHELPERS_VECFIELDS_W, Value.w);

	Archive.SetField(FieldName, MoveTemp(AFV));
}

FArchiveHelpers::EGetResult FArchiveHelpers::GetVec2Field(const FArchive& Archive, const FString& FieldName, glm::vec2& OutValue)
{
	if (!Archive.HasField(FieldName))
	{
		return EGetResult::TotalFailure;
	}

	const FArchiveFieldValue& Value = Archive.GetField(FieldName);
	if (Value.GetType() != AFV_Group)
	{
		return EGetResult::TotalFailure;
	}

	const FArchiveFieldValue::FGroupType& Group = Value.AsGroup();
	int32 NumFailures = 0;

	if (Group.HasFieldWithType(ARCHIVEHELPERS_VECFIELDS_X, AFV_Float))
	{
		OutValue.x = (float) Group.GetField(ARCHIVEHELPERS_VECFIELDS_X).AsFloat();
	}
	else
	{
		NumFailures++;
	}

	if (Group.HasFieldWithType(ARCHIVEHELPERS_VECFIELDS_Y, AFV_Float))
	{
		OutValue.y = (float) Group.GetField(ARCHIVEHELPERS_VECFIELDS_Y).AsFloat();
	}
	else
	{
		NumFailures++;
	}

	return NumFailures == 0 ? EGetResult::TotalSuccess : NumFailures == 2 ? EGetResult::TotalFailure : EGetResult::PartialSuccess;
}

FArchiveHelpers::EGetResult FArchiveHelpers::GetVec3Field(const FArchive& Archive, const FString& FieldName, glm::vec3& OutValue)
{
	if (!Archive.HasField(FieldName))
	{
		return EGetResult::TotalFailure;
	}

	const FArchiveFieldValue& Value = Archive.GetField(FieldName);
	if (Value.GetType() != AFV_Group)
	{
		return EGetResult::TotalFailure;
	}

	const FArchiveFieldValue::FGroupType& Group = Value.AsGroup();
	int32 NumFailures = 0;

	if (Group.HasFieldWithType(ARCHIVEHELPERS_VECFIELDS_X, AFV_Float))
	{
		OutValue.x = (float) Group.GetField(ARCHIVEHELPERS_VECFIELDS_X).AsFloat();
	}
	else
	{
		NumFailures++;
	}

	if (Group.HasFieldWithType(ARCHIVEHELPERS_VECFIELDS_Y, AFV_Float))
	{
		OutValue.y = (float) Group.GetField(ARCHIVEHELPERS_VECFIELDS_Y).AsFloat();
	}
	else
	{
		NumFailures++;
	}

	if (Group.HasFieldWithType(ARCHIVEHELPERS_VECFIELDS_Z, AFV_Float))
	{
		OutValue.z = (float) Group.GetField(ARCHIVEHELPERS_VECFIELDS_Z).AsFloat();
	}
	else
	{
		NumFailures++;
	}

	return NumFailures == 0 ? EGetResult::TotalSuccess : NumFailures == 3 ? EGetResult::TotalFailure : EGetResult::PartialSuccess;
}

FArchiveHelpers::EGetResult FArchiveHelpers::GetVec4Field(const FArchive& Archive, const FString& FieldName, glm::vec4& OutValue)
{
	if (!Archive.HasField(FieldName))
	{
		return EGetResult::TotalFailure;
	}

	const FArchiveFieldValue& Value = Archive.GetField(FieldName);
	if (Value.GetType() != AFV_Group)
	{
		return EGetResult::TotalFailure;
	}

	const FArchiveFieldValue::FGroupType& Group = Value.AsGroup();
	int32 NumFailures = 0;

	if (Group.HasFieldWithType(ARCHIVEHELPERS_VECFIELDS_X, AFV_Float))
	{
		OutValue.x = (float) Group.GetField(ARCHIVEHELPERS_VECFIELDS_X).AsFloat();
	}
	else
	{
		NumFailures++;
	}

	if (Group.HasFieldWithType(ARCHIVEHELPERS_VECFIELDS_Y, AFV_Float))
	{
		OutValue.y = (float) Group.GetField(ARCHIVEHELPERS_VECFIELDS_Y).AsFloat();
	}
	else
	{
		NumFailures++;
	}

	if (Group.HasFieldWithType(ARCHIVEHELPERS_VECFIELDS_Z, AFV_Float))
	{
		OutValue.z = (float) Group.GetField(ARCHIVEHELPERS_VECFIELDS_Z).AsFloat();
	}
	else
	{
		NumFailures++;
	}

	if (Group.HasFieldWithType(ARCHIVEHELPERS_VECFIELDS_W, AFV_Float))
	{
		OutValue.w = (float) Group.GetField(ARCHIVEHELPERS_VECFIELDS_W).AsFloat();
	}
	else
	{
		NumFailures++;
	}

	return NumFailures == 0 ? EGetResult::TotalSuccess : NumFailures == 4 ? EGetResult::TotalFailure : EGetResult::PartialSuccess;
}
