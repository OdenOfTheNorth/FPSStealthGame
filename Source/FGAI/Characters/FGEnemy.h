#pragma once

#include "BaseEnemy.h"
#include "FGEnemy.generated.h"
/*
class USkeletalMeshComponent;
class UCapsuleComponent;
class UCameraComponent;
class UFGVisionSensingComponent;
class UFGNavMovementComponent;
class UFGHearingSenseComponent;
class UHealthComponent;
class UFGTargetingComponent;
class UFGStateMachineComponent;
class ABaseWeapon;
*/
UCLASS()
class AFGEnemy : public ABaseEnemy
{
	GENERATED_BODY()
public:
	AFGEnemy();
	
	virtual void BeginPlay();
	
	void RotateTowardsMovementDirection(const UFGNavMovementComponent* NavMoveComponent);
	void RotateTowardsDirection(FVector direction, float Speed);

	virtual float GetDefaultHalfHeight() const override;

	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable)
	//void Shot() override;

	
	float BaseDamage;
};

