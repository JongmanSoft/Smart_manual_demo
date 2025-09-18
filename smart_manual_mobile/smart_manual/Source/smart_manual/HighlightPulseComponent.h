// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HighlightPulseComponent.generated.h"

class UStaticMeshComponent;
class UMaterialInterface;
class UMaterialInstanceDynamic;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SMART_MANUAL_API UHighlightPulseComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UHighlightPulseComponent();

	/** 펄스 1회 재생 (Duration: 총 길이, Peak: 최대 밝기) */
	UFUNCTION(BlueprintCallable, Category = "Highlight")
	void PlayPulse(float Duration = 1.2f, float Peak = 1.5f);

	/** 진행 중인 펄스를 즉시 중단하고 숨김 */
	UFUNCTION(BlueprintCallable, Category = "Highlight")
	void StopPulse();

	/** 펄스 머티리얼 파라미터명을 변경(디폴트: EmissivePower) */
	UFUNCTION(BlueprintCallable, Category = "Highlight")
	void SetParamNames(FName InEmissiveParam, FName InColorParam);

	/** 오버레이 색 변경(디폴트: 초록) */
	UFUNCTION(BlueprintCallable, Category = "Highlight")
	void SetOverlayColor(FLinearColor InColor);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** 자동 탐색이 싫다면 직접 지정 가능 (우선순위: TargetMesh -> AutoFind) */
	UPROPERTY(EditAnywhere, Category = "Highlight")
	UStaticMeshComponent* TargetMesh = nullptr;

	/** 오버레이에 적용할 머티리얼(Translucent + Unlit 추천) */
	UPROPERTY(EditAnywhere, Category = "Highlight")
	UMaterialInterface* OverlayMaterial = nullptr;

	/** 오버레이 메쉬를 원본보다 살짝 키워 겹침/깜박임 방지 */
	UPROPERTY(EditAnywhere, Category = "Highlight", meta = (ClampMin = "1.0", UIMin = "1.0"))
	float OverlayScale = 1.01f;

	/** 파라미터명 (머티리얼에 존재해야 함) */
	UPROPERTY(EditAnywhere, Category = "Highlight")
	FName EmissiveParam = "EmissivePower";

	UPROPERTY(EditAnywhere, Category = "Highlight")
	FName EmissiveColorParam = "EmissiveColor";

	/** 기본 색 (초록 형광) */
	UPROPERTY(EditAnywhere, Category = "Highlight")
	FLinearColor OverlayColor = FLinearColor::Green;

	UFUNCTION(BlueprintCallable, Category = "Highlight")
	void StartBreathing(float Period = 1.6f, float Peak = 1.2f);

	UFUNCTION(BlueprintCallable, Category = "Highlight")
	void StopBreathing();

	FTimerHandle BreatheTimer;
	float BreatheTime = 0.f;
	float BreathePeriod = 1.6f;  // 초 (느긋하게)
	float BreathePeak = 1.2f;  // 최대 밝기 (과하지 않게)
	bool  bBreathing = false;

	// 내부 헬퍼
	void TickBreathing();

private:
	// 내부 관리
	UPROPERTY(Transient) UStaticMeshComponent* BaseMesh = nullptr;
	UPROPERTY(Transient) UStaticMeshComponent* OverlayMesh = nullptr;
	UPROPERTY(Transient) UMaterialInstanceDynamic* OverlayMID = nullptr;

	FTimerHandle PulseTimer;
	float PulseTime = 0.f;
	float PulseDuration = 1.2f;
	float PulsePeak = 1.5f;

	// 내부 헬퍼
	void EnsureOverlayReady();
	void TeardownOverlay();
	void TickPulse();
		
};
