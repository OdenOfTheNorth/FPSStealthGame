#include "FGTargetingComponent.h"
#include "FGVisionSensingComponent.h"
#include "FGHearingSenseComponent.h"
#include "FGAI/Components/HealthComponent.h"
#include "AIController.h"
#include "FGAI/AI/StateMachine/FGAIStateBase.h"
#include "FGAI/AI/StateMachine/FGStateMachineComponent.h"
#include "FGAI/Characters/FGCharacter.h"
#include "FGAI/Characters/FGScreamer.h"
#include "FGAI/Weapons/BaseWeapon.h"

UFGTargetingComponent::UFGTargetingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;	
}

void UFGTargetingComponent::BeginPlay()
{
	Super::BeginPlay();
	ABaseEnemy* Base = Cast<ABaseEnemy>(GetOwner());
	VisionSensingComponent = Base->GetVisionSensingComponent();																//GetOwner()->FindComponentByClass<UFGVisionSensingComponent>();
	HealthComponent = Base->GetHealthComponent();																			//GetOwner()->FindComponentByClass<UHealthComponent>();
	HearingSensingComponent = Base->GetHearingSensingComponent();															//GetOwner()->FindComponentByClass<UFGHearingSenseComponent>();
	StateMachine = Base->GetStateMachineComponent();	
	
	if (VisionSensingComponent != nullptr)
	{
		VisionSensingComponent->OnTargetSensed.AddDynamic(this, &UFGTargetingComponent::Handle_VisionSense);
		VisionSensingComponent->OnTargetLost.AddDynamic(this, &UFGTargetingComponent::Handle_VisionLost);
	}
	
	if (HealthComponent != nullptr)
	{
		HealthComponent->OnDamage.AddDynamic(this, &UFGTargetingComponent::Handle_DamageSense);
	}
	
	if (HearingSensingComponent != nullptr)
	{
		HearingSensingComponent->OnNoiseHeard.AddDynamic(this, &UFGTargetingComponent::Handle_HearingSense);
	}
	
	if (StateMachine != nullptr)
	{
		StateMachine = Base->GetStateMachineComponent();
	}
}

void UFGTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if ("Sus" == StateMachine->GetStateFromName(StateMachine->CurrentState->TickActive(DeltaTime)))
	//{
	//	
	//}
}

void UFGTargetingComponent::Handle_DamageSense(const FSensesInfo& DamageSenseInfo)
{
	SensesInfo = DamageSenseInfo;
}

void UFGTargetingComponent::Handle_VisionSense(const FSensesInfo& VisionSenseInfo)
{
	SensesInfo = VisionSenseInfo;

	AFGCharacter* Player = Cast<AFGCharacter>(SensesInfo.SensedActor);
	
	if (Player)
	{
		AFGScreamer* Screamer = Cast<AFGScreamer>(GetOwner());
		AFGEnemy* Enemy = Cast<AFGEnemy>(GetOwner());

		if (Enemy)
			StateMachine->PlayerSeen();
	
		if (Screamer)
			StateMachine->Run();  
	}        
}

void UFGTargetingComponent::Handle_VisionLost(const FSensesInfo& VisionSenseInfo)
{
	SensesInfo = VisionSenseInfo;

	AFGCharacter* Player = Cast<AFGCharacter>(SensesInfo.SensedActor);
	
	if (Player)
	{
		AFGEnemy* Enemy = Cast<AFGEnemy>(GetOwner());
		if (Enemy)
			StateMachine->Suspicious();
	} 
}

void UFGTargetingComponent::Handle_HearingSense(const FSensesInfo& HearingSenseInfo)
{	
	SensesInfo = HearingSenseInfo;
	StateMachine->Suspicious();
}

inline void UFGTargetingComponent::Move(FVector Location)
{
	FVector distance = Location - GetOwner()->GetActorLocation();
	distance.Normalize();
	distance *= 100;
	AAIController* AIController = Cast<AAIController>(GetOwner()->GetInstigatorController());
	if (!AIController) return;
	AIController->MoveToLocation(Location - distance);	
}