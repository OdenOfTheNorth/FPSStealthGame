// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGAI/Characters/FGAIGameMode.h"

#include "NoiseComponent.generated.h"

class AFGEnemy;
class AFGNoiseActor;
class NoiseActor;
class ABaseEnemy;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FGAI_API UNoiseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNoiseComponent();

	UPROPERTY(EditAnywhere)
	float NoiseRadius = 300;

	void SpawnNoise();

	AFGAIGameMode* GameMode;

	//void UNoiseComponent::FindAllNoiseActors(UWorld* World, TArray<AFGNoiseActor*>& Out);

	//TArray<ABaseEnemy*> EnemyArray;
	
	protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
};
