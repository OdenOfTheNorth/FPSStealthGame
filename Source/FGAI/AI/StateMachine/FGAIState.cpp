// Fill out your copyright notice in the Description page of Project Settings.


#include "FGAIState.h"

#include <algorithm>
#include <string>

#include "NavigationSystem.h"
#include "FGAI/AI/Movement/FGNavMovementComponent.h"
#include "FGAI/AI/Sensing/FGTargetingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"
#include "FGAI/Characters/FGScreamer.h"
#include "FGAI/Components/NoiseComponent.h"
#include "FGAI/Weapons/BaseWeapon.h"
#include "Math/NumericLimits.h"

//--------------------------------------------------------------------------------------------------------------------//
//	Idle
//--------------------------------------------------------------------------------------------------------------------//

void UUFG_AI_Idle::Setup()
{
	OwnerPawn = Cast<ABaseEnemy>(Owner);		
	TargetingComponent = OwnerPawn->GetTargetingComponent();
	MovementComponent = OwnerPawn->GetNavMovementComponent();	
	StateName = "Idle";
	OriginPos = OwnerPawn->GetActorLocation();
}

FName UUFG_AI_Idle::TickActive(float DeltaTime)
{
	//TODO Make This not ugly, sleep on it.
	UE_LOG(LogTemp,Warning,TEXT("StateName : %s"),*StateName.ToString());

	if (OwnerPawn->GetActorLocation() != OriginPos)
	{
		TargetingComponent->Move(OriginPos);	
	}	
	
	return PendingStateName;
}

void UUFG_AI_Idle::OnActivated()
{
	//WaitTimeRemaining = Wait;
	//TargetingComponent->bNoiseHeard = false;
	//TargetingComponent->bSeenPlayer = false;
}

void UUFG_AI_Idle::OnDeactivated()
{
	PendingStateName = NAME_None;
}

//--------------------------------------------------------------------------------------------------------------------//
//	Suspicious
//--------------------------------------------------------------------------------------------------------------------//

void UFG_AI_Suspicious::Setup()
{
	OwnerPawn = Cast<ABaseEnemy>(Owner);		
	TargetingComponent = OwnerPawn->GetTargetingComponent();
	MovementComponent = OwnerPawn->GetNavMovementComponent();	
	Wait = 5;
	WaitPatrol = 15;
	StateName = "Sus";
}

FName UFG_AI_Suspicious::TickActive(float DeltaTime)
{
	//TODO Make This not ugly, sleep on it.

	UE_LOG(LogTemp,Warning,TEXT("StateName : %s"),*StateName.ToString());
	
	WaitTimeRemaining -= GetWorld()->DeltaTimeSeconds;
	
	UE_LOG(LogTemp,Warning,TEXT("WaitTimeRemaining : %f"),WaitTimeRemaining);
	
	if (WaitTimeRemaining < 0)
	{
		WaitTimeRemaining = Wait;
		SetNextLocation(TargetingComponent->SensesInfo.SensedLocation, 1000);
	}	
	
	return PendingStateName;
}

void UFG_AI_Suspicious::OnActivated()
{
	WaitTimeRemaining = Wait;
	TimeToChangeToPatrol = WaitPatrol;
	TimesToLook = 0;
	
	UE_LOG(LogTemp,Warning,TEXT("WaitTimeRemaining : %f"),WaitTimeRemaining);
	UE_LOG(LogTemp,Warning,TEXT("TimeToChangeToPatrol : %f"),TimeToChangeToPatrol);
	TargetingComponent->Move(TargetingComponent->SensesInfo.SensedLocation);
}

//--------------------------------------------------------------------------------------------------------------------//
//	UFG_AI_Patrolling
//--------------------------------------------------------------------------------------------------------------------//

void UFG_AI_Patrolling::Setup()
{
	OwnerPawn = Cast<ABaseEnemy>(Owner);		
	TargetingComponent = OwnerPawn->GetTargetingComponent();
	MovementComponent = OwnerPawn->GetNavMovementComponent();	
	Wait = 3;
	StateName = "Patrol";
	bPatrolling = true;
	RandomPoint = OwnerPawn->GetActorLocation();
}

FName UFG_AI_Patrolling::TickActive(float DeltaTime)
{
	Super::TickActive(DeltaTime);

	UE_LOG(LogTemp,Warning,TEXT("StateName : %s"),*StateName.ToString());
	UE_LOG(LogTemp,Warning,TEXT("WaitTimeRemaining : %f"),WaitTimeRemaining);
	
	WaitTimeRemaining -= GetWorld()->DeltaTimeSeconds;
	if(WaitTimeRemaining < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"),WaitTimeRemaining);
		WaitTimeRemaining = Wait;
		SetNextLocation(OwnerPawn->GetActorLocation(), 2000);
	}
	
	return PendingStateName;
}

void UFG_AI_Patrolling::OnActivated()
{
	WaitTimeRemaining = Wait;
}

//--------------------------------------------------------------------------------------------------------------------//
// UFG_AI_Attacking
//--------------------------------------------------------------------------------------------------------------------//

void UFG_AI_Attacking::Setup()
{
	OwnerPawn = Cast<ABaseEnemy>(Owner);		
	TargetingComponent = OwnerPawn->GetTargetingComponent();
	MovementComponent = OwnerPawn->GetNavMovementComponent();
	StateName = "Attack";
	PendingStateName = StateName;
}

FName UFG_AI_Attacking::TickActive(float DeltaTime)
{
	UE_LOG(LogTemp,Warning,TEXT("StateName : %s"),*StateName.ToString());

	FString Name = TargetingComponent->SensesInfo.SensedActor->GetName();
	
	if (TargetingComponent->SensesInfo.SensedActor == nullptr)
	{
		UE_LOG(LogTemp,Warning, TEXT("SensedActor Is nullptr"));
		return PendingStateName;
	}

	UE_LOG(LogTemp, Warning,TEXT(" TargetingComponent->SensesInfo.SensedActor = %s"), *Name);
	
	UHealthComponent* HealthComp = Cast<UHealthComponent>(TargetingComponent->SensesInfo.SensedActor);
	
	if (HealthComp != nullptr)
	{
		UE_LOG(LogTemp,Warning, TEXT("HealthComp Is not nullptr"));
		HealthComp->TakeDamage(TargetingComponent->SensesInfo.SensedHit, 5 * GetWorld()->DeltaTimeSeconds, OwnerPawn);
	}
	else
	{
		UE_LOG(LogTemp,Warning, TEXT("HealthComp Is nullptr"));
	}
	
	return PendingStateName;
}

void UFG_AI_Attacking::OnActivated()
{
}

void UFG_AI_Attacking::OnDeactivated()
{	
}

//--------------------------------------------------------------------------------------------------------------------//
// UFG_AI_Running
//--------------------------------------------------------------------------------------------------------------------//

void UFG_AI_Running::Setup()
{
	OwnerPawn = Cast<ABaseEnemy>(Owner);		
	TargetingComponent = OwnerPawn->GetTargetingComponent();
	MovementComponent = OwnerPawn->GetNavMovementComponent();	
	StateName = "Running";
	Running = false;
}

FName UFG_AI_Running::TickActive(float DeltaTime)
{		
	return PendingStateName;
}

void UFG_AI_Running::OnActivated()
{
	
}

void UFG_AI_Running::GetNerestOfficer()
{
	if (GetWorld() && OwnerPawn != nullptr)
	{
		AFGScreamer* screamer = Cast<AFGScreamer>(OwnerPawn);
		UNoiseComponent* noise = screamer->GetNoiseComponent();
		TArray<AFGEnemy*> Enemys;
		
		noise->FindAllEnemys(GetWorld(),Enemys);

		AFGEnemy* OfficerToMoveTo = nullptr;
		if (Enemys.Num() != 0)
		{
			OfficerToMoveTo = Enemys[0];
		}

		FVector MyLocation = Owner->GetActorLocation();
		float NerestOfficer = INFINITY;// 
	
		for (AFGEnemy* Enemy : Enemys)
		{
			if (Enemy != nullptr) 
			{
				float DistanceToEnemySq = MyLocation.DistSquared(Enemy->GetActorLocation(), MyLocation);

				if (DistanceToEnemySq < NerestOfficer)
				{
					NerestOfficer = DistanceToEnemySq;
					OfficerToMoveTo = Enemy;
				}
			}
		}

		if (OfficerToMoveTo != nullptr) 
		{
			TargetingComponent->Move(OfficerToMoveTo->GetActorLocation());
		}
	}
	else
	{
		ChangeState("Patrol");
	}	
}
