// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "smart_manualProjectile.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FHitResult;
#ifdef SMART_MANUAL_smart_manualProjectile_generated_h
#error "smart_manualProjectile.generated.h already included, missing '#pragma once' in smart_manualProjectile.h"
#endif
#define SMART_MANUAL_smart_manualProjectile_generated_h

#define FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnHit);


#define FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualProjectile_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAsmart_manualProjectile(); \
	friend struct Z_Construct_UClass_Asmart_manualProjectile_Statics; \
public: \
	DECLARE_CLASS(Asmart_manualProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/smart_manual"), NO_API) \
	DECLARE_SERIALIZER(Asmart_manualProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	Asmart_manualProjectile(Asmart_manualProjectile&&); \
	Asmart_manualProjectile(const Asmart_manualProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, Asmart_manualProjectile); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(Asmart_manualProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(Asmart_manualProjectile) \
	NO_API virtual ~Asmart_manualProjectile();


#define FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualProjectile_h_12_PROLOG
#define FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualProjectile_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualProjectile_h_15_INCLASS_NO_PURE_DECLS \
	FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SMART_MANUAL_API UClass* StaticClass<class Asmart_manualProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
