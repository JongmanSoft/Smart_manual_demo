// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "event_part_actor.generated.h"

UCLASS()
class SMART_MANUAL_API Aevent_part_actor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	Aevent_part_actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString display_name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString part_desc;


};
