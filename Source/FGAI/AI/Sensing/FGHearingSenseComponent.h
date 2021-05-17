// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGHearingSenseComponent.generated.h"


class ABaseEnemy;
class AFGNoiseActor;

USTRUCT(BlueprintType,BlueprintType)
struct FSensesInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	AActor* SensedActor;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FVector SensedLocation;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	bool bSensedActor = false;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float Range;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
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

	void CheakNoise(TArray<AFGNoiseActor*> FoundActors);
	
	UPROPERTY(BlueprintAssignable)
	FFGHearingSenseDelegate OnNoiseHeard;

	ABaseEnemy* Owner;

	//void GetAllNoiseActor(UWorld* World, TArray<AFGNoiseActor*>& Out);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
};
