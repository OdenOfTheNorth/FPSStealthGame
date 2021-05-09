// Fill out your copyright notice in the Description page of Project Settings.


#include "ImpaleProjectile.h"

#include "FGAI/Characters/FGCharacter.h"

// Sets default values
AImpaleProjectile::AImpaleProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SceneComponent"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AImpaleProjectile::BeginPlay()
{
	Super::BeginPlay();
	Velocity = GetActorForwardVector() * Speed;
}

// Called every frame
void AImpaleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult Hit;
	AddActorWorldOffset(Velocity * DeltaTime, true, &Hit);

	if (Hit.bBlockingHit)
	{
		AFGCharacter* player = Cast<AFGCharacter>(Hit.Actor);
		if (player)
		{
			player->HealthComponent->TakeDamage(Hit, 100, GetOwner());
		}		
	}
}

