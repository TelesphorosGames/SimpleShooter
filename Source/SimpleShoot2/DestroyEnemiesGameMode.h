// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShoot2GameModeBase.h"
#include "DestroyEnemiesGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOT2_API ADestroyEnemiesGameMode : public ASimpleShoot2GameModeBase
{
	GENERATED_BODY()

		public:

	virtual void PawnKilled(APawn* PawnKilled) override;

	private:
	
	void EndGame(bool bIsPlayerWinner);
	
	
};
