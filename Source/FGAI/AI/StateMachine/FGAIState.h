// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGAIStateBase.h"
#include "FGAI/AI/Movement/FGNavMovementComponent.h"
#include "FGAIState.generated.h"

//--------------------------------------------------------------------------------------------------------------------//
//UUFG_AI_Idle
//--------------------------------------------------------------------------------------------------------------------//

class UFGTargetingComponent;

UCLASS()
class FGAI_API UUFG_AI_Idle : public UFGAIStateBase
{
	GENERATED_BODY()
	public:
		//StateName = "UUFG_AI_Idle";	
		virtual void Setup() override;
		virtual FName TickActive(float DeltaTime) override;
		virtual void OnActivated() override;
		virtual void OnDeactivated() override;	
	private:
		UPROPERTY(EditAnywhere)
		float SearchRadius = 2000.f;
		float WaitTimeRemaining = 5.f;
};

//--------------------------------------------------------------------------------------------------------------------//
// UFG_AI_Suspicious
//--------------------------------------------------------------------------------------------------------------------//

UCLASS()
class FGAI_API UFG_AI_Suspicious : public UFGAIStateBase
{
	GENERATED_BODY()	
	public:
		//StateName = "UFG_AI_Suspicious";
		virtual void Setup() override;
		virtual FName TickActive(float DeltaTime) override;
		virtual void OnActivated() override;
};

//--------------------------------------------------------------------------------------------------------------------//
// UFG_AI_Patrolling
//--------------------------------------------------------------------------------------------------------------------//

UCLASS()
class FGAI_API UFG_AI_Patrolling : public UFGAIStateBase
{
	GENERATED_BODY()
	public:	
		//StateName = "UFG_AI_Patrolling";		
		virtual void Setup() override;
		virtual FName TickActive(float DeltaTime) override;
		virtual void OnActivated() override;
};

//--------------------------------------------------------------------------------------------------------------------//
// UFG_AI_Attacking
//--------------------------------------------------------------------------------------------------------------------//

UCLASS()
class FGAI_API UFG_AI_Attacking : public UFGAIStateBase
{
	GENERATED_BODY()
	public:	
		//StateName = "UFG_AI_Attacking";		
		virtual void Setup() override;
		virtual FName TickActive(float DeltaTime) override;
		virtual void OnActivated() override;
		virtual void OnDeactivated();
};

//--------------------------------------------------------------------------------------------------------------------//
// UFG_AI_Running	Screamer
//--------------------------------------------------------------------------------------------------------------------//

UCLASS()
class FGAI_API UFG_AI_Running : public UFGAIStateBase
{
	GENERATED_BODY()
	public:	
	//StateName = "UFG_AI_Attacking";		
	virtual void Setup() override;
	virtual FName TickActive(float DeltaTime) override;
	virtual void OnActivated() override;
	
	float WaitTimeRemaining;
	virtual void GetNerestOfficer() override;
	bool Running;
};