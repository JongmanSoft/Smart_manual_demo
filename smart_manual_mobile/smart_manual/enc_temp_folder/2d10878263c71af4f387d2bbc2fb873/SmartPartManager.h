// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SmartPartActor.h"
#include "SmartPartManager.generated.h"

UCLASS()
class SMART_MANUAL_API ASmartPartManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASmartPartManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parts")
    TArray<ASmartPartActor*> PartList;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parts")
    int32 CurrentIndex;

    UFUNCTION(BlueprintCallable, Category = "Parts")
    void ActivatePart(int32 Index);

    UFUNCTION(BlueprintCallable, Category = "Parts")
    void NextPart();

    UFUNCTION(BlueprintCallable, Category = "Parts")
    void PrevPart();

    UFUNCTION(BlueprintCallable, Category = "Parts")
    void DeactivateAll();

    UFUNCTION(BlueprintCallable, Category = "desc")
    TArray<FString> get_cheak_list_desc();

    UFUNCTION(BlueprintCallable, Category = "desc")
    FString get_current_desc_text() const;

    

};
