// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "FGAI/AI/Sensing/FGHearingSenseComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::TakeDamage(FHitResult Hit, float Damage, AActor* DamageInstigator)
{
	//Reduce Health
	Health -= Damage;

	if (Health <= 0)
	{
		FstructDead Result;
		Result.Alive = false;
		IsDead.Broadcast(Result);
	}
	
	//Save Damage Info
	FSensesInfo DamageInfo;
	DamageInfo.SensedLocation = (Hit.TraceStart - Hit.ImpactPoint).GetSafeNormal();
	DamageInfo.SensedActor = DamageInstigator;
	DamageInfo.SensedHit = Hit;
	DamageInfo.bSensedActor = true;
	OnDamage.Broadcast(DamageInfo);	
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

