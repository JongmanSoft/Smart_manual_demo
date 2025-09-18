// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractControlComponent.h"
#include "Components/MeshComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UInteractControlComponent::UInteractControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInteractControlComponent::BeginPlay()
{
	Super::BeginPlay();

	if (TargetMesh)
	{
		if (UMaterialInterface* M = TargetMesh->GetMaterial(0))
		{
			DynMID = TargetMesh->CreateAndSetMaterialInstanceDynamic(0);
			if (DynMID) { ApplyEmissive(0.f); }
		}
	}
}


void UInteractControlComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    GetWorld()->GetTimerManager().ClearTimer(HintTimer);
    Super::EndPlay(EndPlayReason);
}

void UInteractControlComponent::SetInteractMode(EInteractMode NewMode, FAxisConstraint Axis, float InRangeOrAngle)
{
    InteractMode = NewMode;
    AxisConstraint = Axis;
    RangeOrAngle = FMath::Max(1.f, InRangeOrAngle);
    ResetState();
}

void UInteractControlComponent::ApplyHighlight(bool bEnable, float BlinkHz)
{
    bHighlight = bEnable;
    BlinkSpeed = FMath::Max(0.1f, BlinkHz);
    EnableTickIfNeeded(bHighlight);
    if (!bHighlight && DynMID) ApplyEmissive(0.f);
}

void UInteractControlComponent::ShowHint(EHintIcon Icon, FText Text, float Duration)
{
    HintIcon = Icon;
    HintText = Text;

    // 여기서는 상태만 세팅. 실제 위젯 표시는 BP에서 이 변수 바인딩으로 처리
    // 자동 사라짐: Duration 후 아이콘/텍스트 초기화
    GetWorld()->GetTimerManager().ClearTimer(HintTimer);
    GetWorld()->GetTimerManager().SetTimer(HintTimer, [this]()
        {
            HintIcon = EHintIcon::None;
            HintText = FText::GetEmpty();
        }, Duration, false);
}

void UInteractControlComponent::InputTap()
{
    if (bCompleted) return;

    if (InteractMode == EInteractMode::Press || InteractMode == EInteractMode::Toggle)
    {
        Progress01 = 1.f;
        BroadcastProgress();
        MarkCompleted();
    }
}

void UInteractControlComponent::InputDragDelta(FVector2D Delta)
{
    if (bCompleted) return;
    if (InteractMode != EInteractMode::Slide) return;

    // 간단 스케일: 300px 드래그 = 100% (필요 시 프로젝트에 맞게 튜닝)
    float AxisValue = 0.f;
    if (AxisConstraint.X) AxisValue = Delta.X;
    else if (AxisConstraint.Y) AxisValue = Delta.Y;
    else if (AxisConstraint.Z) AxisValue = (FMath::Abs(Delta.X) > FMath::Abs(Delta.Y)) ? Delta.X : Delta.Y;

    DragAccum += AxisValue;
    const float NeededPx = 300.f; // ← “슬라이드 거리”를 px로 환산한 값
    Progress01 = FMath::Clamp(FMath::Abs(DragAccum) / NeededPx, 0.f, 1.f);
    BroadcastProgress();

    if (Progress01 >= 1.f)
    {
        MarkCompleted();
    }
}

void UInteractControlComponent::InputRotateDelta(float AngleDeltaDeg)
{
    if (bCompleted) return;
    if (InteractMode != EInteractMode::Rotate) return;

    RotateAccumDeg += AngleDeltaDeg;
    Progress01 = FMath::Clamp(FMath::Abs(RotateAccumDeg) / RangeOrAngle, 0.f, 1.f);
    BroadcastProgress();

    if (Progress01 >= 1.f)
    {
        MarkCompleted();
    }
}

void UInteractControlComponent::ResetState()
{
    Progress01 = 0.f;
    DragAccum = 0.f;
    RotateAccumDeg = 0.f;
    bCompleted = false;
    BroadcastProgress();
}

void UInteractControlComponent::UpdateHighlight(float DeltaTime)
{
    if (!bHighlight || !DynMID) return;
    const float T = GetWorld()->GetTimeSeconds();
    const float Blink = (FMath::Sin(T * 2.f * PI * BlinkSpeed) * 0.5f + 0.5f); // 0~1
    ApplyEmissive(Blink * EmissiveOnValue);
}

void UInteractControlComponent::ApplyEmissive(float Value)
{
    if (DynMID && EmissiveParam != NAME_None)
    {
        DynMID->SetScalarParameterValue(EmissiveParam, Value);
    }
}

void UInteractControlComponent::BroadcastProgress()
{
    OnProgress.Broadcast(Progress01);
}

void UInteractControlComponent::MarkCompleted()
{
    bCompleted = true;
    OnCompleted.Broadcast();
    // 여기서 “You did it!” 토스트/사운드/시퀀스 재생은 BP에서 이 델리게이트에 바인딩해서 실행
}

void UInteractControlComponent::EnableTickIfNeeded(bool bEnable)
{
    if (bEnable && !PrimaryComponentTick.bCanEverTick)
    {
        // 컴포넌트 틱을 켜지 않고, 경량 타이머 기반 루프(60fps)로 하이라이트만 갱신
        GetWorld()->GetTimerManager().SetTimerForNextTick([this]()
            {
                if (!IsValid(this)) return;
                GetWorld()->GetTimerManager().SetTimer(
                    /*inOutHandle*/HintTimer, /*InDelegate*/
                    FTimerDelegate::CreateUObject(this, &UInteractControlComponent::TickInternal),
                    /*Rate*/ 1.f / 60.f, /*bLoop*/ true
                );
            });
    }
    else if (!bEnable)
    {
        GetWorld()->GetTimerManager().ClearTimer(HintTimer); // 주: 위에서 힌트에도 씀 → 실제로는 별도 핸들이 더 좋음
    }
}

void UInteractControlComponent::TickInternal()
{
    UpdateHighlight(1.f / 60.f);
}

