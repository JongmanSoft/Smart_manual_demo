// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "smart_manualPickUpComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class Asmart_manualCharacter;
class UPrimitiveComponent;
struct FHitResult;
#ifdef SMART_MANUAL_smart_manualPickUpComponent_generated_h
#error "smart_manualPickUpComponent.generated.h already included, missing '#pragma once' in smart_manualPickUpComponent.h"
#endif
#define SMART_MANUAL_smart_manualPickUpComponent_generated_h

#define FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualPickUpComponent_h_12_DELEGATE \
SMART_MANUAL_API void FOnPickUp_DelegateWrapper(const FMulticastScriptDelegate& OnPickUp, Asmart_manualCharacter* PickUpCharacter);


#define FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualPickUpComponent_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnSphereBeginOverlap);


#define FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualPickUpComponent_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUsmart_manualPickUpComponent(); \
	friend struct Z_Construct_UClass_Usmart_manualPickUpComponent_Statics; \
public: \
	DECLARE_CLASS(Usmart_manualPickUpComponent, USphereComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/smart_manual"), NO_API) \
	DECLARE_SERIALIZER(Usmart_manualPickUpComponent)


#define FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualPickUpComponent_h_17_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	Usmart_manualPickUpComponent(Usmart_manualPickUpComponent&&); \
	Usmart_manualPickUpComponent(const Usmart_manualPickUpComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, Usmart_manualPickUpComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(Usmart_manualPickUpComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(Usmart_manualPickUpComponent) \
	NO_API virtual ~Usmart_manualPickUpComponent();


#define FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualPickUpComponent_h_14_PROLOG
#define FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualPickUpComponent_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualPickUpComponent_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualPickUpComponent_h_17_INCLASS_NO_PURE_DECLS \
	FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualPickUpComponent_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SMART_MANUAL_API UClass* StaticClass<class Usmart_manualPickUpComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_metaverse_studio_fan_demo_Smart_manual_demo_smart_manual_mobile_smart_manual_Source_smart_manual_smart_manualPickUpComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
