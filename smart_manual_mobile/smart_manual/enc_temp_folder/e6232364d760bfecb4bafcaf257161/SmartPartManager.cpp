// Fill out your copyright notice in the Description page of Project Settings.


#include "SmartPartManager.h"

// Sets default values
ASmartPartManager::ASmartPartManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CurrentIndex = -1;
}

// Called when the game starts or when spawned
void ASmartPartManager::BeginPlay()
{
	Super::BeginPlay();
	
	DeactivateAll();
}

void ASmartPartManager::ActivatePart(int32 Index)
{
    if (!PartList.IsValidIndex(Index))
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid part index: %d"), Index);
        return;
    }

    if (PartList.IsValidIndex(CurrentIndex))
    {
        PartList[CurrentIndex]->SetActorTickEnabled(false);
    }

    CurrentIndex = Index;
    PartList[CurrentIndex]->SetActorTickEnabled(true);

    UE_LOG(LogTemp, Log, TEXT("Activated part index: %d"), CurrentIndex);
}

void ASmartPartManager::NextPart()
{
    int32 NewIndex = CurrentIndex + 1;
    if (PartList.IsValidIndex(NewIndex))
    {
        ActivatePart(NewIndex);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Already at last part."));
    }
}

void ASmartPartManager::PrevPart()
{
    int32 NewIndex = CurrentIndex - 1;
    if (PartList.IsValidIndex(NewIndex))
    {
        ActivatePart(NewIndex);
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Already at first part."));
    }
}

void ASmartPartManager::DeactivateAll()
{
    for (ASmartPartActor* Part : PartList)
    {
        if (Part)
        {
            Part->SetActorTickEnabled(false);
        }
    }
    CurrentIndex = -1;
}

TArray<FText> ASmartPartManager::get_cheak_list_desc()
{
    TArray<FText> cheak_list_parts;
    cheak_list_parts.Reset();
    for (ASmartPartActor* Part : PartList)
    {
        if (Part)
        {
            cheak_list_parts.Add(Part->cheak_list_text);
        }
    }

    return cheak_list_parts;
}

const FText& ASmartPartManager::get_current_desc_text()
{

    UE_LOG(LogTemp, Log, TEXT("%s"), *PartList[CurrentIndex]->Desc_text.ToString());
    return PartList[CurrentIndex]->Desc_text;
}


