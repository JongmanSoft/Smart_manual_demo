// Fill out your copyright notice in the Description page of Project Settings.


#include "event_part_actor.h"	
#include "Kismet/GameplayStatics.h"
#include "UseManualManager.h"
// Sets default values
Aevent_part_actor::Aevent_part_actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Aevent_part_actor::BeginPlay()
{
	Super::BeginPlay();
	
    UWorld* World = GetWorld();
    if (World)
    {
        TArray<AActor*> FoundActors;
        UGameplayStatics::GetAllActorsOfClass(World, AUseManualManager::StaticClass(), FoundActors);

        if (FoundActors.Num() > 0)
        {
             Cast<AUseManualManager>(FoundActors[0])->add_event_part(this);
        }
    }

   

}

// Called every frame
void Aevent_part_actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

