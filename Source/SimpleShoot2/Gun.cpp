// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("GunRoot"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));

	Mesh->SetupAttachment(Root);
	
	

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;
	bool LineTraceShooter = GunTrace(Hit, ShotDirection);
	if(LineTraceShooter)
	{
	//DrawDebugCamera(GetWorld(), ViewLoc, ViewRot, 90, 2, FColor::Red, false, 3.f);
	//DrawDebugSphere(GetWorld(), Hit.Location, 20, 5, FColor::Red, false, 2.5f);
	
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitSpotFlash, Hit.Location, ShotDirection.Rotation());



	AActor* ActorHit = Hit.GetActor();
	if (ActorHit != nullptr)
	{
	
		FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
		AController* OwnerController = GetOwnerController();
		ActorHit->TakeDamage(Damage, DamageEvent, OwnerController, this);
	}

	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.ImpactPoint);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}


bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return false;
	
	

	FVector ViewLoc;
	FRotator ViewRot;

	OwnerController->GetPlayerViewPoint(ViewLoc, ViewRot);
	ShotDirection = -ViewRot.Vector();

	FVector End = ViewLoc + ViewRot.Vector() * MaxRange ;

	Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, ViewLoc, End, ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
		APawn* OwnerPawn = Cast<APawn>(GetOwner());

		if(OwnerPawn == nullptr) return nullptr;

		return OwnerPawn->GetController();
	

}
