// InteractControlComponent.cpp
#include "InteractControlComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"

UInteractControlComponent::UInteractControlComponent()
{
	PrimaryComponentTick.bCanEverTick = false; // 타이머만 사용
}

void UInteractControlComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractControlComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* W = GetWorld())
	{
		W->GetTimerManager().ClearTimer(HintTimer);
	}
	Super::EndPlay(EndPlayReason);
}

// ------------------ 설정 ------------------

void UInteractControlComponent::SetInteractMode(EInteractMode NewMode, FAxisConstraint Axis, float InRangeOrAngle)
{
	InteractMode = NewMode;
	AxisConstraint = Axis;
	RangeOrAngle = FMath::Max(1.f, InRangeOrAngle);
	ResetState();
}

// ------------------ 힌트 ------------------

void UInteractControlComponent::ShowHint(EHintIcon Icon, FText Text, float Duration)
{
	HintIcon = Icon;
	HintText = Text;

	if (UWorld* W = GetWorld())
	{
		W->GetTimerManager().ClearTimer(HintTimer);
		W->GetTimerManager().SetTimer(HintTimer, [this]()
			{
				HintIcon = EHintIcon::None;
				HintText = FText::GetEmpty();
			}, Duration, false);
	}
}

// ------------------ 입력 ------------------

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
	if (bCompleted || InteractMode != EInteractMode::Slide) return;

	float AxisValue = 0.f;
	if (AxisConstraint.X)      AxisValue = Delta.X;
	else if (AxisConstraint.Y) AxisValue = Delta.Y;
	else if (AxisConstraint.Z) AxisValue = (FMath::Abs(Delta.X) > FMath::Abs(Delta.Y)) ? Delta.X : Delta.Y;

	DragAccum += AxisValue;

	// 기준 300px = 100% (필요시 조정)
	const float NeededPx = 300.f;
	Progress01 = FMath::Clamp(FMath::Abs(DragAccum) / NeededPx, 0.f, 1.f);
	BroadcastProgress();

	if (Progress01 >= 1.f) MarkCompleted();
}

void UInteractControlComponent::InputRotateDelta(float AngleDeltaDeg)
{
	if (bCompleted || InteractMode != EInteractMode::Rotate) return;

	RotateAccumDeg += AngleDeltaDeg;
	Progress01 = FMath::Clamp(FMath::Abs(RotateAccumDeg) / RangeOrAngle, 0.f, 1.f);
	BroadcastProgress();

	if (Progress01 >= 1.f) MarkCompleted();
}

// ------------------ 상태 ------------------

void UInteractControlComponent::ResetState()
{
	Progress01 = 0.f;
	DragAccum = 0.f;
	RotateAccumDeg = 0.f;
	bCompleted = false;
	BroadcastProgress();
}

// ------------------ 헬퍼 ------------------

void UInteractControlComponent::BroadcastProgress()
{
	OnProgress.Broadcast(Progress01);
}

void UInteractControlComponent::MarkCompleted()
{
	bCompleted = true;
	OnCompleted.Broadcast();
}
