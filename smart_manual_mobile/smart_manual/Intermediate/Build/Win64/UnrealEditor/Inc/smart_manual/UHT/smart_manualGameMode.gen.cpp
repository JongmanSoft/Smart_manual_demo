// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "smart_manual/smart_manualGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodesmart_manualGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
SMART_MANUAL_API UClass* Z_Construct_UClass_Asmart_manualGameMode();
SMART_MANUAL_API UClass* Z_Construct_UClass_Asmart_manualGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_smart_manual();
// End Cross Module References

// Begin Class Asmart_manualGameMode
void Asmart_manualGameMode::StaticRegisterNativesAsmart_manualGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(Asmart_manualGameMode);
UClass* Z_Construct_UClass_Asmart_manualGameMode_NoRegister()
{
	return Asmart_manualGameMode::StaticClass();
}
struct Z_Construct_UClass_Asmart_manualGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "smart_manualGameMode.h" },
		{ "ModuleRelativePath", "smart_manualGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<Asmart_manualGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_Asmart_manualGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_smart_manual,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_Asmart_manualGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_Asmart_manualGameMode_Statics::ClassParams = {
	&Asmart_manualGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_Asmart_manualGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_Asmart_manualGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_Asmart_manualGameMode()
{
	if (!Z_Registration_Info_UClass_Asmart_manualGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_Asmart_manualGameMode.OuterSingleton, Z_Construct_UClass_Asmart_manualGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_Asmart_manualGameMode.OuterSingleton;
}
template<> SMART_MANUAL_API UClass* StaticClass<Asmart_manualGameMode>()
{
	return Asmart_manualGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(Asmart_manualGameMode);
Asmart_manualGameMode::~Asmart_manualGameMode() {}
// End Class Asmart_manualGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_Asmart_manualGameMode, Asmart_manualGameMode::StaticClass, TEXT("Asmart_manualGameMode"), &Z_Registration_Info_UClass_Asmart_manualGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(Asmart_manualGameMode), 1426774899U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualGameMode_h_3733246921(TEXT("/Script/smart_manual"),
	Z_CompiledInDeferFile_FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
