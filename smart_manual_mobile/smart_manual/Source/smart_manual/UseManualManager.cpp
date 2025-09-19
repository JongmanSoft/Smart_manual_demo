// Fill out your copyright notice in the Description page of Project Settings.


#include "UseManualManager.h"

// Sets default values
AUseManualManager::AUseManualManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUseManualManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUseManualManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FString> AUseManualManager::get_manual_list()
{
	return TArray<FString>();
}

void AUseManualManager::add_event_part(Aevent_part_actor* part)
{
	event_arr.Add(part);
}

