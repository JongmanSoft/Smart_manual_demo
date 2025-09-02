// Copyright Epic Games, Inc. All Rights Reserved.

#include "smart_manualPickUpComponent.h"

Usmart_manualPickUpComponent::Usmart_manualPickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void Usmart_manualPickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &Usmart_manualPickUpComponent::OnSphereBeginOverlap);
}

void Usmart_manualPickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	Asmart_manualCharacter* Character = Cast<Asmart_manualCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
