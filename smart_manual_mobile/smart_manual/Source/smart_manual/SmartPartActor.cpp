// Fill out your copyright notice in the Description page of Project Settings.


#include "SmartPartActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ASmartPartActor::ASmartPartActor()
{
    PrimaryActorTick.bCanEverTick = true;

    RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
    RootComponent = RootComp;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComp);

    PivotComp = CreateDefaultSubobject<USceneComponent>(TEXT("PivotComp"));
    PivotComp->SetupAttachment(RootComp);
}

// Called when the game starts or when spawned
void ASmartPartActor::BeginPlay()
{
	Super::BeginPlay();
	
    CurrentLocation = StartLocation;
    SetActorLocation(CurrentLocation);

    CurrentRotationX = CurrentRotationY = CurrentRotationZ = 0.f;

    SetActorTickEnabled(false);
}

// Called every frame
void ASmartPartActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bEnableMove)
    {
        Move(DeltaTime);
    }

    if (bEnableRotate)
    {
        Rotate(DeltaTime);
    }
}

void ASmartPartActor::Move(float DeltaTime)
{
    FVector TargetLocation = FVector::ZeroVector;
    CurrentLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
    SetActorLocation(CurrentLocation);

    if (CurrentLocation.Equals(TargetLocation, 1.f))
    {
        bEnableMove = false;
    }
}

void ASmartPartActor::Rotate(float DeltaTime)
{
    if (!MeshComp || !PivotComp) return;

    float Step = RotationSpeed * DeltaTime;
    FRotator DeltaRot = FRotator::ZeroRotator;

    if (bRotateX && FMath::Abs(CurrentRotationX) < FMath::Abs(TargetRotation))
    {
        DeltaRot.Roll = Step;
        CurrentRotationX += Step;
    }
    if (bRotateY && FMath::Abs(CurrentRotationY) < FMath::Abs(TargetRotation))
    {
        DeltaRot.Pitch = Step;
        CurrentRotationY += Step;
    }
    if (bRotateZ && FMath::Abs(CurrentRotationZ) < FMath::Abs(TargetRotation))
    {
        DeltaRot.Yaw = Step;
        CurrentRotationZ += Step;
    }

    FVector MeshLoc = MeshComp->GetRelativeLocation();
    FVector PivotLoc = PivotComp->GetRelativeLocation();

    FVector Offset = MeshLoc - PivotLoc;
    Offset = DeltaRot.RotateVector(Offset);

    MeshComp->SetRelativeLocation(PivotLoc + Offset);
    MeshComp->AddLocalRotation(DeltaRot);

    if ((bRotateX && FMath::Abs(CurrentRotationX) >= FMath::Abs(TargetRotation)) ||
        (bRotateY && FMath::Abs(CurrentRotationY) >= FMath::Abs(TargetRotation)) ||
        (bRotateZ && FMath::Abs(CurrentRotationZ) >= FMath::Abs(TargetRotation)))
    {
        bEnableRotate = false;
    }
}