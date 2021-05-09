// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "FGHearingSenseComponent.generated.h"


class AFGNoiseActor;
USTRUCT(BlueprintType)
struct FFGHearingInfo
{
	GENERATED_BODY()
public:
	AActor* NoiseInstigator;
	FVector NoiseLocation;
	bool bHeardNoise = false;
	float Range;
};

USTRUCT(BlueprintType)
struct FSensesInfo
{
	GENERATED_BODY()
public:
	AActor* SensedActor;
	FVector SensedLocation;
	bool bSensedActor = false;
	float Range;
	FHitResult SensedHit;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFGHearingSenseDelegate, const FSensesInfo&, Results);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FGAI_API UFGHearingSenseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFGHearingSenseComponent();

	UPROPERTY(EditAnywhere)
	float HearingRange = 1000.f;

	void CheakNoise();

	FSensesInfo HearingInfo;
	//FFGHearingInfo HearingInfo;
	UPROPERTY(BlueprintAssignable)
	FFGHearingSenseDelegate OnNoiseHeard;

	void FindAllNoiseActor(UWorld* World, TArray<AFGNoiseActor*>& Out);

	TArray<AFGNoiseActor*> FoundActors;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
