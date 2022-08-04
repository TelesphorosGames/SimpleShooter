// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleShoot2GameModeBase.generated.h"

/**
 * 
 */ 
UCLASS()
class SIMPLESHOOT2_API ASimpleShoot2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	public:

	virtual void PawnKilled(APawn* PawnKilled);
	
};
