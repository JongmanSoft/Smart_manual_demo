// Fill out your copyright notice in the Description page of Project Settings.


#include "MobileDemoController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "InteractControlComponent.h"

void AMobileDemoController::BeginPlay()
{
    Super::BeginPlay();

    if (ULocalPlayer* LP = GetLocalPlayer())
    {
        if (auto* Subsys = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (IMC_Mobile) Subsys->AddMappingContext(IMC_Mobile, 1);
        }
    }

    bShowMouseCursor = false;
    bEnableClickEvents = true;
    bEnableTouchEvents = true;
}

void AMobileDemoController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (auto* EIC = Cast<UEnhancedInputComponent>(InputComponent))
    {
        if (IA_Tap)            EIC->BindAction(IA_Tap, ETriggerEvent::Triggered, this, &AMobileDemoController::OnTap);
        if (IA_Drag)           EIC->BindAction(IA_Drag, ETriggerEvent::Triggered, this, &AMobileDemoController::OnDrag);
        if (IA_TwoFingerRotate)EIC->BindAction(IA_TwoFingerRotate, ETriggerEvent::Triggered, this, &AMobileDemoController::OnRotate);
    }
}

UInteractControlComponent* AMobileDemoController::PickInteractCompUnderScreenPos(FVector2D ScreenPos) const
{
    FVector World, Dir;
    DeprojectScreenPositionToWorld(ScreenPos.X, ScreenPos.Y, World, Dir);

    const FVector Start = World;
    const FVector End = Start + Dir * 5000.f;

    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(InteractPick), true, GetPawn());
    GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);

    if (Hit.GetActor())
    {
        if (UActorComponent* C = Hit.GetActor()->GetComponentByClass(UInteractControlComponent::StaticClass()))
        {
            return Cast<UInteractControlComponent>(C);
        }
    }
    return nullptr;
}

void AMobileDemoController::OnTap(const FInputActionValue& Value)
{
    // 터치 스크린 좌표 가져오기
    FVector2D Pos;
    if (!GetMousePosition(Pos.X, Pos.Y)) return;

    // 시작 시점에 픽킹
    FocusComp = PickInteractCompUnderScreenPos(Pos);
    if (FocusComp.IsValid())
    {
        FocusComp->InputTap();
    }
}

void AMobileDemoController::OnDrag(const FInputActionValue& Value)
{
    const FVector2D Delta = Value.Get<FVector2D>();
    if (!FocusComp.IsValid())
    {
        // 드래그 첫 프레임이면, 현재 포인터 위치에서 픽킹 시도
        FVector2D Pos;
        if (GetMousePosition(Pos.X, Pos.Y))
        {
            FocusComp = PickInteractCompUnderScreenPos(Pos);
        }
    }
    if (FocusComp.IsValid())
    {
        FocusComp->InputDragDelta(Delta);
    }
}

void AMobileDemoController::OnRotate(const FInputActionValue& Value)
{
    const float DeltaDeg = Value.Get<float>();
    if (FocusComp.IsValid())
    {
        FocusComp->InputRotateDelta(DeltaDeg);
    }
}
