// Copyright Epic Games, Inc. All Rights Reserved.

#include "smart_manualGameMode.h"
#include "smart_manualCharacter.h"
#include "UObject/ConstructorHelpers.h"

Asmart_manualGameMode::Asmart_manualGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
