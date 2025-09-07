// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SmartPartActor.generated.h"

UCLASS()
class SMART_MANUAL_API ASmartPartActor : public AActor
{
	GENERATED_BODY()
	
public:
    ASmartPartActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
    USceneComponent* RootComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
    USceneComponent* PivotComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
    UStaticMeshComponent* MeshComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
    bool bEnableMove = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
    FVector StartLocation = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
    float MoveSpeed = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
    bool bEnableRotate = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
    bool bRotateX = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
    bool bRotateY = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
    bool bRotateZ = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
    float RotationSpeed = 45.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
    float TargetRotation = 90.f;

private:
    FVector CurrentLocation;
    float CurrentRotationX;
    float CurrentRotationY;
    float CurrentRotationZ;

    void Move(float DeltaTime);
    void Rotate(float DeltaTime);

};
