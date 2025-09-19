// InteractControlComponent.h
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractControlComponent.generated.h"

UENUM(BlueprintType)
enum class EInteractMode : uint8 { Press, Slide, Rotate, Toggle };

UENUM(BlueprintType, Blueprintable)
enum class EHintIcon : uint8 { None, Click, MoveUp, MoveDown, MoveLeft, MoveRight, Rotate };
							// 0	   1	  2			3		4	        5

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

UCLASS(BlueprintType, Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SMART_MANUAL_API UInteractControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractControlComponent();

	// ===== 모드/파라미터 =====
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	EInteractMode InteractMode = EInteractMode::Press;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	FAxisConstraint AxisConstraint;

	/** Slide: 목표 픽셀 / Rotate: 목표 각도(°) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact", meta = (ClampMin = "1.0"))
	float RangeOrAngle = 90.f;

	/** 최초 가이드(화살표+텍스트) 기본값 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guide")
	EHintIcon DefaultIcon = EHintIcon::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Guide")
	FText DefaultText;

	// ===== 입력 =====
	UFUNCTION(BlueprintCallable, Category = "Interact|Input") void BeginInteract();          // 집기/터치 시작
	UFUNCTION(BlueprintCallable, Category = "Interact|Input") void EndInteract();            // 손 뗄 때
	UFUNCTION(BlueprintCallable, Category = "Interact|Input") void InputTap();
	UFUNCTION(BlueprintCallable, Category = "Interact|Input") void InputDragDelta(FVector2D Delta);
	UFUNCTION(BlueprintCallable, Category = "Interact|Input") void InputRotateDelta(float AngleDeltaDeg);

	// ===== 진행/리셋 =====
	UFUNCTION(BlueprintPure, Category = "Interact") float GetProgressPercent() const { return Progress01; }
	UFUNCTION(BlueprintCallable, Category = "Interact") void ResetState();

	// ===== 가이드(화살표+텍스트) 제어 =====
	UFUNCTION(BlueprintCallable, Category = "Interact|Guide") void SetGuide(EHintIcon Icon, FText Text);
	UFUNCTION(BlueprintCallable, Category = "Interact|Guide") void HideGuide();

	// ===== 델리게이트 =====
	UPROPERTY(BlueprintAssignable) FOnInteractProgress OnProgress;
	UPROPERTY(BlueprintAssignable) FOnInteractCompleted OnCompleted;

	// ===== BP가 구현할 UI 훅 =====
	UFUNCTION(BlueprintImplementableEvent, Category = "Interact|UI") void BP_ShowGuide(int32 IconType, const FText& Text);
	UFUNCTION(BlueprintImplementableEvent, Category = "Interact|UI") void BP_UpdateGuide(int32 IconType, const FText& Text);
	UFUNCTION(BlueprintImplementableEvent, Category = "Interact|UI") void BP_HideGuide();
	UFUNCTION(BlueprintImplementableEvent, Category = "Interact|UI") void BP_SetProgress(float Percent01);
	UFUNCTION(BlueprintImplementableEvent, Category = "Interact|UI") void BP_OnCompleted();

	UFUNCTION(BlueprintCallable, Category = "Interact|UI", meta = (DisplayName = "Show Guide"))
	void ShowGuideBP(EHintIcon Icon, const FText& Text);

	UFUNCTION(BlueprintCallable, Category = "Interact|UI", meta = (DisplayName = "Update Guide"))
	void UpdateGuideBP(EHintIcon Icon, const FText& Text);

	UFUNCTION(BlueprintCallable, Category = "Interact|UI", meta = (DisplayName = "Hide Guide"))
	void HideGuideBP();

	UFUNCTION(BlueprintCallable, Category = "Interact|UI", meta = (DisplayName = "Set Progress (Guide)"))
	void SetProgressBP(float Percent01);

	UFUNCTION(BlueprintCallable, Category = "Interact|UI", meta = (DisplayName = "Fire Completed (Guide)"))
	void FireCompletedBP();

protected:
	virtual void BeginPlay() override;

private:
	// 내부 상태
	float Progress01 = 0.f;
	float DragAccum = 0.f;
	float RotateAccumDeg = 0.f;
	bool  bCompleted = false;
	bool  bGuidingVisible = false;

	// 헬퍼
	void BroadcastProgress();
	void MarkCompleted();
	void EnsureGuideVisible();
};
