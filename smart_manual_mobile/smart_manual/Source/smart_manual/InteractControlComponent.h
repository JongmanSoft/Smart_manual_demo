// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractControlComponent.generated.h"

UENUM(BlueprintType)
enum class EInteractMode : uint8 { Press, Slide, Rotate, Toggle };

UENUM(BlueprintType)
enum class EHintIcon : uint8 { None, Click, Grab, RotateCW, RotateCCW, MoveUp, MoveDown, MoveLeft, MoveRight };

USTRUCT(BlueprintType)
struct FAxisConstraint
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool X = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool Y = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool Z = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractProgress, float, Progress01);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractCompleted);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SMART_MANUAL_API UInteractControlComponent : public UActorComponent
{
	GENERATED_BODY()
public:
    UInteractControlComponent();

    // 1) 모드/파라미터 설정
    UFUNCTION(BlueprintCallable, Category = "Interact")
    void SetInteractMode(EInteractMode NewMode, FAxisConstraint Axis, float InRangeOrAngle);

    // 2) 하이라이트(형광 깜빡임)
    UFUNCTION(BlueprintCallable, Category = "Interact")
    void ApplyHighlight(bool bEnable, float BlinkHz = 1.f);

    // 3) 힌트 UI
    UFUNCTION(BlueprintCallable, Category = "Interact")
    void ShowHint(EHintIcon Icon, FText Text, float Duration = 1.5f);

    // 4) 터치 입력(컨트롤러에서 전달)
    UFUNCTION(BlueprintCallable, Category = "Interact|Input")
    void InputTap();

    UFUNCTION(BlueprintCallable, Category = "Interact|Input")
    void InputDragDelta(FVector2D Delta);

    UFUNCTION(BlueprintCallable, Category = "Interact|Input")
    void InputRotateDelta(float AngleDeltaDeg);

    // 5) 진행률/리셋
    UFUNCTION(BlueprintPure, Category = "Interact")
    float GetProgressPercent() const { return Progress01; }

    UFUNCTION(BlueprintCallable, Category = "Interact")
    void ResetState();

public:
    // 에디터 노출 (보고서 기획과 동일)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
    EInteractMode InteractMode = EInteractMode::Press;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
    FAxisConstraint AxisConstraint;

    // Slide: 목표 거리(cm 단위 가정) / Rotate: 목표 각도(°)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact", meta = (ClampMin = "1.0"))
    float RangeOrAngle = 90.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hint")
    EHintIcon HintIcon = EHintIcon::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hint")
    FText HintText;

    // 머티리얼 하이라이트 제어(선택)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    UMeshComponent* TargetMesh = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    FName EmissiveParam = "EmissivePower";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    float EmissiveOnValue = 10.f;

    // 델리게이트: 진행률/완료
    UPROPERTY(BlueprintAssignable) FOnInteractProgress OnProgress;
    UPROPERTY(BlueprintAssignable) FOnInteractCompleted OnCompleted;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    // 내부 상태
    float Progress01 = 0.f;
    float DragAccum = 0.f;       // px → cm로 바꾸고 싶으면 스케일 상수 조정
    float RotateAccumDeg = 0.f;  // ° 누적
    bool  bCompleted = false;

    // 하이라이트용
    UMaterialInstanceDynamic* DynMID = nullptr;
    bool bHighlight = false;
    float BlinkSpeed = 1.f;

    FTimerHandle HintTimer;

    // 내부 헬퍼
    void UpdateHighlight(float DeltaTime);
    void ApplyEmissive(float Value);
    void BroadcastProgress();
    void MarkCompleted();

    // Tick 대용(컴포넌트는 기본 Tick off → 필요 시만)
    void EnableTickIfNeeded(bool bEnable);
    UFUNCTION() void TickInternal();
		
};
