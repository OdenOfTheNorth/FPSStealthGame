// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "FGScreamer.generated.h"

class AFGAIGameMode;
UCLASS()
class FGAI_API AFGScreamer : public ABaseEnemy
{
	GENERATED_BODY()

	public:
	AFGScreamer();
	
	void RotateTowardsMovementDirection(const UFGNavMovementComponent* NavMoveComponent);
	virtual float GetDefaultHalfHeight() const override;
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;
	void RotateTowardsDirection(FVector direction, float Speed);
	
	protected:
	//virtual void BeginPlay();
	UCapsuleComponent* GetCapsule() const { return Capsule; }


};
