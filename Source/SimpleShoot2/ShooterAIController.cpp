// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterChar.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    ClearFocus(EAIFocusPriority::Gameplay);

  MyPlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
   

     if (AIBehavior != nullptr)
     {

         RunBehaviorTree(AIBehavior);

 
         GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
     }


}

void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if(LineOfSightTo(MyPlayerPawn))
    {
        SetFocus(MyPlayerPawn);
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), MyPlayerPawn->GetActorLocation());
        GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), MyPlayerPawn->GetActorLocation());
          
        



    // MoveToActor(MyPlayerPawn, 500);

    }

    else
    {

        GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));


        ClearFocus(EAIFocusPriority::Gameplay);

        // StopMovement();
        
        
        }


}

bool AShooterAIController::IsDead() const
{
    AShooterChar* ControlledCharacter = Cast<AShooterChar>(GetPawn());
    if (ControlledCharacter != nullptr)
    {
        return ControlledCharacter->bIsDead();
    }

    return true;
}
