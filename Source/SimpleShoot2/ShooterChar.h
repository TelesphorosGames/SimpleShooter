// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterChar.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOT2_API AShooterChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	float GetHealthPercentage();

	UFUNCTION(BlueprintPure)
	bool bIsDead() const;

	UPROPERTY(BlueprintReadOnly)
	AGun* Gun;

	void Shoot();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:

	void MoveForward(float AxisValue);
	void LookRight(float AxisValue);
	void MoveRight(float AxisValue);
	// void LookUp(float AxisValue);

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	float RotationRate = 10.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UFUNCTION(BlueprintCallable)
	FRotator GetAim();



	


	

};
