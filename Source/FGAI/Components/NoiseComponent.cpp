// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseComponent.h"

#include "EngineUtils.h"
#include "FGAI/FGNoiseActor.h"
#include "FGAI/Characters/FGEnemy.h"
#include "FGAI/Components/NoiseComponent.h"
#include "FGAI/AI/Sensing/FGHearingSenseComponent.h"
#include "FGAI/AI/Sensing/FGTargetingComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UNoiseComponent::UNoiseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNoiseComponent::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AFGAIGameMode>(UGameplayStatics::GetGameMode(this));

	if (GameMode == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameMode == nullptr , NoiseComponent.cpp"))
	}
}

void UNoiseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
}

void UNoiseComponent::SpawnNoise() 
{
	//ABaseEnemy::GetAllBaseEnemys(EnemyArray);
	
	AFGNoiseActor* NoiseActor = GetWorld()->SpawnActor<AFGNoiseActor>(GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
	NoiseActor->Radius = NoiseRadius;
	NoiseActor->NoiseInstigator = GetOwner();

	if (GameMode == nullptr) return;
	
	GameMode->NoiseActorsList.Add(NoiseActor);
	
	for (ABaseEnemy* Enemy : GameMode->BaseEnemys)
	{
		if (Enemy == nullptr) continue;
	
		Enemy->HearingSensingComponent->CheakNoise(GameMode->NoiseActorsList);	//FindAllNoiseActors(GetWorld(), Enemy->HearingSensingComponent->FoundActors);
	}
}

