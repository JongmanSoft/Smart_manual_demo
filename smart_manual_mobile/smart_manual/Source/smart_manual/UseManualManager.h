// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "event_part_actor.h"

#include "UseManualManager.generated.h"

UCLASS()
class SMART_MANUAL_API AUseManualManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUseManualManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	TArray <Aevent_part_actor*> event_arr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Play")
	TArray<FString> get_manual_list();

	UFUNCTION()
	void add_event_part(Aevent_part_actor* part);
};
