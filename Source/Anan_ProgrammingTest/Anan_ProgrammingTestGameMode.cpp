// Copyright Epic Games, Inc. All Rights Reserved.

#include "Anan_ProgrammingTestGameMode.h"
#include "Anan_ProgrammingTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAnan_ProgrammingTestGameMode::AAnan_ProgrammingTestGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
