// Fill out your copyright notice in the Description page of Project Settings.


#include "Android_controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


void AAndroid_controller::BeginPlay()
{
    Super::BeginPlay();

    MobileMappingContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/input/InputMappingContext.InputMappingContext"));

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(MobileMappingContext, 0);//우선순위0?
        }
    }
}

void AAndroid_controller::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

void AAndroid_controller::Zoom(const FInputActionValue& Value)
{
}
