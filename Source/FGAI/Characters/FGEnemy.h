#pragma once

#include "BaseEnemy.h"
#include "FGEnemy.generated.h"
class AFGAIGameMode;
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
	virtual void BeginDestroy() override;
	
	virtual void BeginPlay() override;
	
	void RotateTowardsMovementDirection(const UFGNavMovementComponent* NavMoveComponent);
	void RotateTowardsDirection(FVector direction, float Speed);

	virtual float GetDefaultHalfHeight() const override;

	virtual void Tick(float DeltaTime) override;


	
	//static TArray<AFGEnemy*> FGEnemys;
	//static void GetAllFGEnemys(TArray<AFGEnemy*> out);
	
	float BaseDamage;
};

