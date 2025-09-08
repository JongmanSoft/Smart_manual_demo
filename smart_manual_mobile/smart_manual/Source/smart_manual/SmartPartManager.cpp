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
    if (!PartList.IsValidIndex(Index) || PartList[Index] == nullptr)
    {
        // UE_LOG(LogTemp, Warning, TEXT("Invalid part index: %d"), Index);
        return;
    }

    if (PartList.IsValidIndex(CurrentIndex) && PartList[CurrentIndex])
    {
        PartList[CurrentIndex]->SetActorTickEnabled(false);
        PartList[CurrentIndex]->bIsPlaying = false;
    }

    CurrentIndex = Index;

    PartList[CurrentIndex]->StartForward();

    // UE_LOG(LogTemp, Log, TEXT("Activated part index: %d"), CurrentIndex);
}

void ASmartPartManager::NextPart()
{
    if (PartList.IsValidIndex(CurrentIndex))
    {
        PartList[CurrentIndex]->SetTargetTransforms();
    }
    int32 NewIndex = CurrentIndex + 1;
    if (PartList.IsValidIndex(NewIndex))
    {
        ActivatePart(NewIndex);
    }
}

void ASmartPartManager::PrevPart()
{
    if (!PartList.IsValidIndex(CurrentIndex) || PartList[CurrentIndex] == nullptr)
    {
        return;
    }

    PartList[CurrentIndex]->StartReverse();

    CurrentIndex = FMath::Max(CurrentIndex - 1, -1);
}

void ASmartPartManager::DeactivateAll()
{
    for (ASmartPartActor* Part : PartList)
    {
        if (Part)
        {
            Part->SetActorTickEnabled(false);
            Part->bIsPlaying = false;
        }
    }
    CurrentIndex = -1;
}

void ASmartPartManager::SetPartStateByIndex(int32 TargetIndex)
{
    if (!PartList.IsValidIndex(TargetIndex) || PartList[TargetIndex] == nullptr)
    {
        // UE_LOG(LogTemp, Warning, TEXT("Invalid target index: %d"), TargetIndex);
        return;
    }

    // Process all parts
    for (int32 i = 0; i < PartList.Num(); i++)
    {
        if (!PartList[i])
        {
            continue;
        }

        if (i < TargetIndex)
        {
            // Parts before TargetIndex: Set to completed state
            PartList[i]->bReverseMode = false;
            PartList[i]->SetTargetTransforms();
            PartList[i]->SetActorTickEnabled(false);
            PartList[i]->bIsPlaying = false;
        }
        else if (i == TargetIndex)
        {
            // Part at TargetIndex: Start playing forward
            PartList[i]->SetActorTickEnabled(false);
            PartList[i]->bIsPlaying = false;
            PartList[i]->StartForward();
        }
        else
        {
            // Parts after TargetIndex: Reset to initial state
            PartList[i]->bReverseMode = true;
            PartList[i]->ResetTransforms();
            PartList[i]->SetActorTickEnabled(false);
            PartList[i]->bIsPlaying = false;
        }
    }

    CurrentIndex = TargetIndex;
}

TArray<FString> ASmartPartManager::get_cheak_list_desc()
{
    TArray<FString> cheak_list_parts;
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

FString ASmartPartManager::get_current_desc_text() const
{
    if (!PartList.IsValidIndex(CurrentIndex) || PartList[CurrentIndex] == nullptr)
    {
        return FString();
    }
    return PartList[CurrentIndex]->Desc_text;
}


