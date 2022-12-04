// Copyright Epic Games, Inc. All Rights Reserved.

#include "FractureGameMode.h"
#include "FractureCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFractureGameMode::AFractureGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
