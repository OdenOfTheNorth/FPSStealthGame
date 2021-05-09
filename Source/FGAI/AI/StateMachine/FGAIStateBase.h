#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "FGAI/Characters/BaseEnemy.h"

#include "FGAIStateBase.generated.h"

class UFGTargetingComponent;
class UFGNavMovementComponent;
class AActor;

UCLASS(BlueprintType, Blueprintable, DefaultToInstanced, EditInlineNew)
class UFGAIStateBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void Setup();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Setup();

	virtual FName TickActive(float DeltaTime);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_TickActive(float DeltaTime);

	virtual void OnActivated();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnActivated();

	virtual void OnDeactivated();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnDeactivated();

	virtual void OnRemoved();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnRemoved();

	UFUNCTION(BlueprintCallable)
	void ChangeState(FName NewPendingStateName);
	
	UPROPERTY(EditAnywhere)
	FName StateName;

	UFUNCTION(BlueprintPure)
	AActor* GetOwner() const;

	UPROPERTY(Transient)
	AActor* Owner = nullptr;

	bool ArrviedAttDestination();

	virtual void GetNerestOfficer();
	void SetNextLocation(FVector Origin, float Radius);
	void Move(FVector MoveLocation);
	
	FName PendingStateName;
	
	UFGNavMovementComponent* MovementComponent;
	UFGTargetingComponent* TargetingComponent;

	AAIController* Controller;
	ABaseEnemy* OwnerPawn;
	
	float TimeToChangeToPatrol;
	float WaitPatrol;
	float WaitTimeRemaining;
	float Wait;
	
	int TimesToLook;
	
	FVector LastHeardLoacation;
	FVector MoveLoacation;
	FVector RandomPoint;
	FVector OriginPos;
	bool bPatrolling;
};
