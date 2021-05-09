
#include "BaseWeapon.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "FGAI/Components/HealthComponent.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseWeapon::Fire()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{

	}
}

void ABaseWeapon::StartFire()
{

}

void ABaseWeapon::StopFire()
{

}

void ABaseWeapon::Tick(float DeltaSeconds)
{

}
