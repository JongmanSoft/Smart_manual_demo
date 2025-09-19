// InteractControlComponent.cpp
#include "InteractControlComponent.h"

UInteractControlComponent::UInteractControlComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractControlComponent::BeginPlay()
{
	Super::BeginPlay();
	ResetState();
}

// ===== 가이드 =====
void UInteractControlComponent::BeginInteract()
{
	if (!bGuidingVisible)
	{
		BP_ShowGuide(static_cast<int32>(DefaultIcon), DefaultText);
		bGuidingVisible = true;
	}
	BP_SetProgress(Progress01);
}

void UInteractControlComponent::EndInteract()
{
	// 필요하면 BP에서 이 타이밍에 가이드 숨김/유지 결정
}

void UInteractControlComponent::SetGuide(EHintIcon Icon, FText Text)
{
	BP_UpdateGuide(static_cast<int32>(Icon), Text);
	bGuidingVisible = true;
}

void UInteractControlComponent::HideGuide()
{
	BP_HideGuide();
	bGuidingVisible = false;
}

void UInteractControlComponent::EnsureGuideVisible()
{
	if (!bGuidingVisible)
	{
		BP_ShowGuide(static_cast<int32>(DefaultIcon), DefaultText);
		bGuidingVisible = true;
	}
}

// ===== 입력 =====
void UInteractControlComponent::InputTap()
{
	if (bCompleted) return;

	EnsureGuideVisible();

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

	EnsureGuideVisible();

	float AxisValue = 0.f;
	if (AxisConstraint.X) AxisValue = Delta.X;
	else if (AxisConstraint.Y) AxisValue = Delta.Y;
	else
		AxisValue = (FMath::Abs(Delta.X) > FMath::Abs(Delta.Y)) ? Delta.X : Delta.Y;

	DragAccum += AxisValue;

	const float NeededPx = (RangeOrAngle > 0.f) ? RangeOrAngle : 300.f;
	Progress01 = FMath::Clamp(FMath::Abs(DragAccum) / NeededPx, 0.f, 1.f);
	BroadcastProgress();

	if (Progress01 >= 1.f) MarkCompleted();
}

void UInteractControlComponent::InputRotateDelta(float AngleDeltaDeg)
{
	if (bCompleted || InteractMode != EInteractMode::Rotate) return;

	EnsureGuideVisible();

	RotateAccumDeg += AngleDeltaDeg;
	const float TargetDeg = FMath::Max(5.f, RangeOrAngle);

	Progress01 = FMath::Clamp(FMath::Abs(RotateAccumDeg) / TargetDeg, 0.f, 1.f);
	BroadcastProgress();

	if (Progress01 >= 1.f) MarkCompleted();
}

// ===== 진행/리셋 =====
void UInteractControlComponent::ResetState()
{
	Progress01 = 0.f;
	DragAccum = 0.f;
	RotateAccumDeg = 0.f;
	bCompleted = false;
	BroadcastProgress();
}

void UInteractControlComponent::BroadcastProgress()
{
	OnProgress.Broadcast(Progress01);
	BP_SetProgress(Progress01); // 진행바는 BP에서
}

void UInteractControlComponent::MarkCompleted()
{
	bCompleted = true;
	OnCompleted.Broadcast();
	BP_OnCompleted(); // BP에서 “You did it!” / 성공연출 / 원복 처리
}

void UInteractControlComponent::ShowGuideBP(EHintIcon Icon, const FText& Text)
{
	BP_ShowGuide(static_cast<int32>(Icon), Text);
	bGuidingVisible = true;        // 내부 상태 갱신
}

void UInteractControlComponent::UpdateGuideBP(EHintIcon Icon, const FText& Text)
{
	BP_UpdateGuide(static_cast<int32>(Icon), Text);
	bGuidingVisible = true;
}

void UInteractControlComponent::HideGuideBP()
{
	BP_HideGuide();
	bGuidingVisible = false;
}

void UInteractControlComponent::SetProgressBP(float Percent01)
{
	Progress01 = FMath::Clamp(Percent01, 0.f, 1.f);
	BP_SetProgress(Progress01);
	OnProgress.Broadcast(Progress01); // 외부에서도 들을 수 있게
}

void UInteractControlComponent::FireCompletedBP()
{
	bCompleted = true;
	BP_OnCompleted();
	OnCompleted.Broadcast();
}