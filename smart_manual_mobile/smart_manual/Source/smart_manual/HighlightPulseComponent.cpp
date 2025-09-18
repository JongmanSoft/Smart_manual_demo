// Fill out your copyright notice in the Description page of Project Settings.


#include "HighlightPulseComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UHighlightPulseComponent::UHighlightPulseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHighlightPulseComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (!TargetMesh)
	{
		TargetMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	}
	BaseMesh = TargetMesh;

	EnsureOverlayReady();
}

void UHighlightPulseComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopPulse();
	TeardownOverlay();
	Super::EndPlay(EndPlayReason);
}

void UHighlightPulseComponent::EnsureOverlayReady()
{
	if (OverlayMesh || !BaseMesh) return;

	// 오버레이 메쉬 생성
	OverlayMesh = NewObject<UStaticMeshComponent>(GetOwner(), TEXT("HighlightOverlay"));
	if (!OverlayMesh) return;

	OverlayMesh->SetupAttachment(BaseMesh);
	OverlayMesh->RegisterComponent();

	// 동일 스태틱메쉬 적용 + 살짝 스케일업
	OverlayMesh->SetStaticMesh(BaseMesh->GetStaticMesh());
	OverlayMesh->SetRelativeTransform(FTransform::Identity);
	OverlayMesh->SetRelativeScale3D(FVector(OverlayScale));
	OverlayMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	OverlayMesh->SetCastShadow(false);
	OverlayMesh->SetVisibility(false, true);

	// 머티리얼 MID 생성
	if (OverlayMaterial)
	{
		OverlayMID = UMaterialInstanceDynamic::Create(OverlayMaterial, this);
		OverlayMesh->SetMaterial(0, OverlayMID);

		if (OverlayMID && EmissiveColorParam != NAME_None)
		{
			OverlayMID->SetVectorParameterValue(EmissiveColorParam, OverlayColor);
		}
		if (OverlayMID && EmissiveParam != NAME_None)
		{
			OverlayMID->SetScalarParameterValue(EmissiveParam, 0.f);
		}
	}
}

void UHighlightPulseComponent::TeardownOverlay()
{
	if (UWorld* W = GetWorld())
	{
		W->GetTimerManager().ClearTimer(PulseTimer);
	}

	if (OverlayMesh)
	{
		OverlayMesh->DestroyComponent();
		OverlayMesh = nullptr;
	}
	OverlayMID = nullptr;
}

void UHighlightPulseComponent::PlayPulse(float Duration, float Peak)
{
	EnsureOverlayReady();
	if (!OverlayMesh || !OverlayMID) return;

	PulseDuration = FMath::Max(0.2f, Duration);
	PulsePeak = FMath::Max(0.1f, Peak);
	PulseTime = 0.f;

	OverlayMesh->SetVisibility(true, true);

	if (UWorld* W = GetWorld())
	{
		// 30fps면 충분히 부드러움
		W->GetTimerManager().SetTimer(
			PulseTimer,
			this, &UHighlightPulseComponent::TickPulse,
			1.f / 30.f, true
		);
	}
}

void UHighlightPulseComponent::StopPulse()
{
	if (UWorld* W = GetWorld())
	{
		W->GetTimerManager().ClearTimer(PulseTimer);
	}
	if (OverlayMID && EmissiveParam != NAME_None)
	{
		OverlayMID->SetScalarParameterValue(EmissiveParam, 0.f);
	}
	if (OverlayMesh)
	{
		OverlayMesh->SetVisibility(false, true);
	}
	PulseTime = 0.f;
}

void UHighlightPulseComponent::TickPulse()
{
	if (!OverlayMID) { StopPulse(); return; }

	PulseTime += 1.f / 30.f;

	// t: 0→1, 코사인 이징으로 0→1→0 (눈 편한 펄스)
	const float t = FMath::Clamp(PulseTime / PulseDuration, 0.f, 1.f);
	const float alpha = 0.5f * (1.f - FMath::Cos(PI * t)); // 부드러운 곡선
	const float v = alpha * PulsePeak;

	if (EmissiveParam != NAME_None)
	{
		OverlayMID->SetScalarParameterValue(EmissiveParam, v);
	}

	if (t >= 1.f)
	{
		StopPulse();
	}
}

void UHighlightPulseComponent::SetParamNames(FName InEmissiveParam, FName InColorParam)
{
	EmissiveParam = InEmissiveParam;
	EmissiveColorParam = InColorParam;

	if (OverlayMID && EmissiveColorParam != NAME_None)
	{
		OverlayMID->SetVectorParameterValue(EmissiveColorParam, OverlayColor);
	}
}

void UHighlightPulseComponent::SetOverlayColor(FLinearColor InColor)
{
	OverlayColor = InColor;
	if (OverlayMID && EmissiveColorParam != NAME_None)
	{
		OverlayMID->SetVectorParameterValue(EmissiveColorParam, OverlayColor);
	}
}

void UHighlightPulseComponent::StartBreathing(float Period, float Peak)
{
	EnsureOverlayReady();
	if (!OverlayMesh || !OverlayMID) return;

	BreathePeriod = FMath::Max(0.3f, Period);
	BreathePeak = FMath::Max(0.1f, Peak);
	BreatheTime = 0.f;
	bBreathing = true;

	OverlayMesh->SetVisibility(true, true);

	if (UWorld* W = GetWorld())
	{
		// 30fps로 충분히 부드럽게
		W->GetTimerManager().SetTimer(
			BreatheTimer,
			this, &UHighlightPulseComponent::TickBreathing,
			1.f / 30.f, true
		);
	}
}

void UHighlightPulseComponent::StopBreathing()
{
	bBreathing = false;
	if (UWorld* W = GetWorld())
	{
		W->GetTimerManager().ClearTimer(BreatheTimer);
	}
	if (OverlayMID && EmissiveParam != NAME_None)
	{
		OverlayMID->SetScalarParameterValue(EmissiveParam, 0.f);
	}
	if (OverlayMesh)
	{
		OverlayMesh->SetVisibility(false, true);
	}
}

void UHighlightPulseComponent::TickBreathing()
{
	if (!bBreathing || !OverlayMID) { StopBreathing(); return; }

	BreatheTime += 1.f / 30.f;

	// 부드러운 숨쉬기: 0→1→0 반복 (눈 편한 코사인)
	const float w = 2.f * PI / BreathePeriod;             // 각속도
	const float alpha = 0.5f * (1.f - FMath::Cos(w * BreatheTime));
	const float v = alpha * BreathePeak;

	if (EmissiveParam != NAME_None)
	{
		OverlayMID->SetScalarParameterValue(EmissiveParam, v);
	}
}