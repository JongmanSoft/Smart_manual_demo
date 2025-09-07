// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodesmart_manual_init() {}
	SMART_MANUAL_API UFunction* Z_Construct_UDelegateFunction_smart_manual_OnPickUp__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_smart_manual;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_smart_manual()
	{
		if (!Z_Registration_Info_UPackage__Script_smart_manual.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_smart_manual_OnPickUp__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/smart_manual",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0x8F1E060C,
				0x8DC12A25,
				METADATA_PARAMS(0, nullptr)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_smart_manual.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_smart_manual.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_smart_manual(Z_Construct_UPackage__Script_smart_manual, TEXT("/Script/smart_manual"), Z_Registration_Info_UPackage__Script_smart_manual, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x8F1E060C, 0x8DC12A25));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
