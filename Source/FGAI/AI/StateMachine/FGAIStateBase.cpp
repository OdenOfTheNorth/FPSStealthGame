#include "FGAIStateBase.h"

#include "NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "FGAI/AI/Movement/FGNavMovementComponent.h"
#include "FGAI/AI/Sensing/FGTargetingComponent.h"
#include "FGAI/Characters/FGScreamer.h"


void UFGAIStateBase::Setup()
{
	OwnerPawn = Cast<ABaseEnemy>(GetOwner());
	TargetingComponent = OwnerPawn->FindComponentByClass<UFGTargetingComponent>();
	BP_Setup();
}

FName UFGAIStateBase::TickActive(float DeltaTime)
{
	BP_TickActive(DeltaTime);
	
	return PendingStateName;
}

void UFGAIStateBase::OnActivated()
{	
	BP_OnActivated();
}

void UFGAIStateBase::OnDeactivated()
{
	BP_OnDeactivated();
}

void UFGAIStateBase::OnRemoved()
{
	BP_OnRemoved();
}

void UFGAIStateBase::ChangeState(FName NewPendingStateName)
{
	UE_LOG(LogTemp,Warning,TEXT("%s"),*NewPendingStateName.ToString());
	
	PendingStateName = NewPendingStateName;	
}

AActor* UFGAIStateBase::GetOwner() const
{
	return Owner;
}

bool UFGAIStateBase::ArrviedAttDestination()
{
	if (GetOwner()->GetActorLocation() == MoveLoacation)
	{
		return true;
	}
	return false;
}

void UFGAIStateBase::GetNerestOfficer()
{
}

void UFGAIStateBase::SetNextLocation(FVector Origin, float Radius)
{
	UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, Origin,
	RandomPoint, Radius);
	MoveLoacation = RandomPoint;
	TargetingComponent->Move(MoveLoacation);	
}

void UFGAIStateBase::Move(FVector MoveLocation)
{
	AAIController* AIController = Cast<AAIController>(OwnerPawn);
    if (!AIController) return;
    AIController->MoveToLocation(MoveLocation);		
}


