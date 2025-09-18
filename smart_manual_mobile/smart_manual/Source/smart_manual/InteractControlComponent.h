// InteractControlComponent.h
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

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SMART_MANUAL_API UInteractControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractControlComponent();

	// 설정
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void SetInteractMode(EInteractMode NewMode, FAxisConstraint Axis, float InRangeOrAngle);

	// 힌트
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void ShowHint(EHintIcon Icon, FText Text, float Duration = 1.5f);

	// 입력
	UFUNCTION(BlueprintCallable, Category = "Interact|Input")
	void InputTap();

	UFUNCTION(BlueprintCallable, Category = "Interact|Input")
	void InputDragDelta(FVector2D Delta);

	UFUNCTION(BlueprintCallable, Category = "Interact|Input")
	void InputRotateDelta(float AngleDeltaDeg);

	// 진행률/리셋
	UFUNCTION(BlueprintPure, Category = "Interact")
	float GetProgressPercent() const { return Progress01; }

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void ResetState();

public:
	// 에디터 노출
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	EInteractMode InteractMode = EInteractMode::Press;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	FAxisConstraint AxisConstraint;

	// Slide: px 환산 거리 / Rotate: 목표 각도(°)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact", meta = (ClampMin = "1.0"))
	float RangeOrAngle = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hint")
	EHintIcon HintIcon = EHintIcon::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hint")
	FText HintText;

	// 델리게이트
	UPROPERTY(BlueprintAssignable) FOnInteractProgress OnProgress;
	UPROPERTY(BlueprintAssignable) FOnInteractCompleted OnCompleted;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	// 내부 상태
	float Progress01 = 0.f;
	float DragAccum = 0.f;
	float RotateAccumDeg = 0.f;
	bool  bCompleted = false;

	FTimerHandle HintTimer; // 힌트 자동 숨김만 사용

	// 헬퍼
	void BroadcastProgress();
	void MarkCompleted();
};
