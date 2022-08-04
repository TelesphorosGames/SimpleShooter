// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterChar.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShoot2GameModeBase.h"



// Sets default values
AShooterChar::AShooterChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterChar::BeginPlay()
{
	Super::BeginPlay();

	Health=MaxHealth;
	
	

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, (TEXT("WeaponSocket")));
	Gun->SetOwner(this);
	
}

// Called every frame
void AShooterChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void AShooterChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterChar::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterChar::LookRight);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterChar::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterChar::Shoot);

}

float AShooterChar::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
	{
		float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		
		DamageApplied = FMath::Min(Health, DamageApplied);
		Health -= DamageApplied;
		UE_LOG(LogTemp, Warning, TEXT("Player health %f"), Health);

		if (bIsDead())
		{
			
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			ASimpleShoot2GameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShoot2GameModeBase>();
			if (GameMode != nullptr)
			{
				GameMode->PawnKilled(this);
			}
			DetachFromControllerPendingDestroy();

		}

		return DamageApplied;





	}


void AShooterChar::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterChar::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AShooterChar::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterChar::Shoot()
{
	Gun->PullTrigger();

}

bool AShooterChar::bIsDead() const
{
	if (Health == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

FRotator AShooterChar::GetAim()
{
	return GetViewRotation();
}

float AShooterChar::GetHealthPercentage()
	{
		return Health / MaxHealth; 
	}





// void AShooterChar::LookUp(float AxisValue)
// {
// 	AddControllerPitchInput(AxisValue);
// }


