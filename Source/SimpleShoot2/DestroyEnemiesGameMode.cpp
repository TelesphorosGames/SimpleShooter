// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyEnemiesGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void ADestroyEnemiesGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }


    for (AShooterAIController* ShooterAI : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!ShooterAI->IsDead())
        {
            return;
        }
    }
    EndGame(true);
    
    

    
    // For loop over ShooterAI in world:
        // Is not dead?
            // return

    // End Game



}

void ADestroyEnemiesGameMode::EndGame(bool bIsPlayerWinner)
{
   for (AController* Controller : TActorRange<AController>(GetWorld()))
   {
       
        bool bIsPlayerController = Controller->IsPlayerController();
        if (bIsPlayerWinner)
       {
           Controller->GameHasEnded(Controller->GetPawn(), bIsPlayerController);
       }
       else
       {
           Controller->GameHasEnded(Controller->GetPawn(), !bIsPlayerController);
       }
   }
}

