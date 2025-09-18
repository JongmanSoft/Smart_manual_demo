// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "MobileDemoController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;
class UInteractControlComponent;

UCLASS()
class SMART_MANUAL_API AMobileDemoController : public APlayerController
{
	GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* IMC_Mobile;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_Tap;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_Drag;          // Vector2
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_TwoFingerRotate;// Float (deg delta)

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    // 입력 핸들러
    void OnTap(const FInputActionValue& Value);
    void OnDrag(const FInputActionValue& Value);
    void OnRotate(const FInputActionValue& Value);

    // 현재 포커스된 컴포넌트(터치 시작 시 픽킹해 기억 → 드래그/회전 동안 유지)
    TWeakObjectPtr<UInteractControlComponent> FocusComp;

    // 헬퍼: 화면 좌표 → 월드 라인트레이스 → 컴포넌트
    UInteractControlComponent* PickInteractCompUnderScreenPos(FVector2D ScreenPos) const;
};
