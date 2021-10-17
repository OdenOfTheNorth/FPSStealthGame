// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "FGAI/AI/Sensing/FGVisionSensingTargetComponent.h"
#include "GameFramework/Pawn.h"
#include "BaseEnemy.generated.h"

class AFGAIGameMode;
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
class UNoiseComponent;


UCLASS()
class FGAI_API ABaseEnemy : public APawn
{
	GENERATED_BODY()

public:
	ABaseEnemy();
	virtual void BeginDestroy() override;
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh;

	//Senses
	UPROPERTY(VisibleDefaultsOnly, Category = Senses)			//Vision
	UFGVisionSensingComponent* VisionSensingComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Senses)			//Hearing
	UFGHearingSenseComponent* HearingSensingComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Senses)			//Targeting 
	UFGTargetingComponent* TargetingComponent;

	//Components
	UPROPERTY(VisibleDefaultsOnly, Category = Movement)			//Movement
	UFGNavMovementComponent* NavMovementComponent;	
	UPROPERTY(VisibleDefaultsOnly, Category = Health)			//Health 
	UHealthComponent* HealthComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = State)			//StateMachine
	UFGStateMachineComponent* StateMachine;
	UPROPERTY(VisibleDefaultsOnly, Category = Noise)			//Noise Component
	UNoiseComponent* NoiseComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Noise)			//Vision Target Component
	UFGVisionSensingTargetComponent* VisionTargetComponent;
	
	//Weapon
	//UPROPERTY(VisibleDefaultsOnly, Category = Weapon)			//EquippedWeapon
	//TSubclassOf<ABaseWeapon> EquippedWeapon;		
	//ABaseWeapon* WeaponPtr;										//WeaponPtr
	
	void RotateTowardsMovementDirection(const UFGNavMovementComponent* NavMoveComponent);
	virtual float GetDefaultHalfHeight() const override;
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable)
	//void RemoveFromBaseEnemys();

	UPROPERTY()
	AFGAIGameMode* GameMode;

	FCollisionQueryParams QueryParams;	

	//Get Components
	UHealthComponent* GetHealthComponent()					{	return HealthComponent;			}	
	UFGHearingSenseComponent* GetHearingSensingComponent()	{	return HearingSensingComponent;	}
	UFGVisionSensingComponent* GetVisionSensingComponent()	{	return VisionSensingComponent;	}
	UNoiseComponent* GetNoiseComponent()					{	return NoiseComponent;			}
	UFGNavMovementComponent* GetNavMovementComponent()		{	return NavMovementComponent;	}
	UFGTargetingComponent* GetTargetingComponent()			{	return TargetingComponent;		}
	UFGStateMachineComponent* GetStateMachineComponent()	{	return StateMachine;			}

	FVector PositionToMoveToVector;
	UPROPERTY(EditDefaultsOnly)	
	float RotationSpeed = 1;
	
	protected:
	virtual void BeginPlay();
	UCapsuleComponent* GetCapsule() const { return Capsule; }

public:
	//static TArray<ABaseEnemy*> BaseEnemys;
	//static void GetAllBaseEnemys(TArray<ABaseEnemy*> out);
};
