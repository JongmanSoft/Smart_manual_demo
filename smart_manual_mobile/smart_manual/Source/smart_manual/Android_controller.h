// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Android_controller.generated.h"

/**
 * 
 */
UCLASS()
class SMART_MANUAL_API AAndroid_controller : public APlayerController
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputMappingContext* MobileMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
    UInputAction* ZoomAction;

    UFUNCTION()
    void Zoom(const FInputActionValue& Value);

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
