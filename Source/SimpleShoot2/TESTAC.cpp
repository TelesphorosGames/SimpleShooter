// Fill out your copyright notice in the Description page of Project Settings.


#include "TESTAC.h"

// Sets default values for this component's properties
UTESTAC::UTESTAC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTESTAC::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Yes its working"));
	// ...
	 
}  


// Called every frame
void UTESTAC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
 

  
	// ...
}

