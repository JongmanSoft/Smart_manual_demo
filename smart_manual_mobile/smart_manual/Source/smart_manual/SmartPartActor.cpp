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

    bInitEnableMove = bEnableMove;
    bInitEnableRotate = bEnableRotate;

    InitialMeshRelLocation = MeshComp ? MeshComp->GetRelativeLocation() : FVector::ZeroVector;
    InitialMeshRelRotation = MeshComp ? MeshComp->GetRelativeRotation() : FRotator::ZeroRotator;
	
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

    if (bIsPlaying && !bEnableMove && !bEnableRotate)
    {
        bIsPlaying = false;
        SetActorTickEnabled(false);
        bReverseMode = false;
    }
}

void ASmartPartActor::Move(float DeltaTime)
{
    const FVector Target = bReverseMode ? StartLocation : FVector::ZeroVector;

    CurrentLocation = FMath::VInterpConstantTo(CurrentLocation, Target, DeltaTime, MoveSpeed);
    SetActorLocation(CurrentLocation);

    if (CurrentLocation.Equals(Target, 1.f))
    {
        bEnableMove = false;
    }
}

void ASmartPartActor::Rotate(float DeltaTime)
{
    if (!MeshComp || !PivotComp) { bEnableRotate = false; return; }

    const float Step = RotationSpeed * DeltaTime;

    const float Tx = bRotateX ? (bReverseMode ? 0.f : TargetRotation) : CurrentRotationX;
    const float Ty = bRotateY ? (bReverseMode ? 0.f : TargetRotation) : CurrentRotationY;
    const float Tz = bRotateZ ? (bReverseMode ? 0.f : TargetRotation) : CurrentRotationZ;

    const float Dx = FMath::Clamp(Tx - CurrentRotationX, -Step, Step);
    const float Dy = FMath::Clamp(Ty - CurrentRotationY, -Step, Step);
    const float Dz = FMath::Clamp(Tz - CurrentRotationZ, -Step, Step);

    FRotator DeltaRot(Dy, Dz, Dx);

    const FVector MeshLoc = MeshComp->GetRelativeLocation();
    const FVector PivotLoc = PivotComp->GetRelativeLocation();
    FVector Offset = MeshLoc - PivotLoc;
    Offset = DeltaRot.RotateVector(Offset);

    MeshComp->SetRelativeLocation(PivotLoc + Offset);
    MeshComp->AddLocalRotation(DeltaRot);

    CurrentRotationX += Dx;
    CurrentRotationY += Dy;
    CurrentRotationZ += Dz;

    const bool DoneX = !bRotateX || FMath::IsNearlyEqual(CurrentRotationX, Tx, 0.5f);
    const bool DoneY = !bRotateY || FMath::IsNearlyEqual(CurrentRotationY, Ty, 0.5f);
    const bool DoneZ = !bRotateZ || FMath::IsNearlyEqual(CurrentRotationZ, Tz, 0.5f);

    if (DoneX && DoneY && DoneZ)
    {
        bEnableRotate = false;
    }
}

void ASmartPartActor::ResetTransforms()
{
    CurrentRotationX = CurrentRotationY = CurrentRotationZ = 0.f;

    if (MeshComp)
    {
        MeshComp->SetRelativeLocation(InitialMeshRelLocation);
        MeshComp->SetRelativeRotation(InitialMeshRelRotation);
    }

    CurrentLocation = StartLocation;
    SetActorLocation(CurrentLocation);
}

void ASmartPartActor::StartForward()
{
    ResetTransforms();
    bReverseMode = false;
    bIsPlaying = true;
    bEnableMove = bInitEnableMove;
    bEnableRotate = bInitEnableRotate;
    SetActorTickEnabled(true);
}

void ASmartPartActor::StartReverse()
{
    bReverseMode = true;
    bIsPlaying = true;
    bEnableMove = bInitEnableMove;
    bEnableRotate = bInitEnableRotate;
    SetActorTickEnabled(true);
}