// Fill out your copyright notice in the Description page of Project Settings.


#include "FGScreamer.h"
#include "AIController.h"
#include "FGAIGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "FGAI/AI/Sensing/FGVisionSensingComponent.h"
#include "FGAI/AI/Movement/FGNavMovementComponent.h"
#include "FGAI/AI/Sensing/FGHearingSenseComponent.h"
#include "FGAI/AI/StateMachine/FGStateMachineComponent.h"
#include "FGAI/Components/HealthComponent.h"
#include "FGAI/AI/Sensing/FGTargetingComponent.h"
#include "FGAI/Components/NoiseComponent.h"
#include "FGAI/Weapons/BaseWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFGScreamer::AFGScreamer()
{
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	// Set size for collision capsule
	Capsule->InitCapsuleSize(55.f, 96.0f);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	Mesh->SetupAttachment(Capsule);
	Mesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	VisionSensingComponent = CreateDefaultSubobject<UFGVisionSensingComponent>(TEXT("VisionSensing"));
	NavMovementComponent = CreateDefaultSubobject<UFGNavMovementComponent>(TEXT("NavMovementComponent"));
	HearingSensingComponent = CreateDefaultSubobject<UFGHearingSenseComponent>(TEXT("HearingSensing"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	StateMachine = CreateDefaultSubobject<UFGStateMachineComponent>(TEXT("StateMachineComponent"));
	TargetingComponent = CreateDefaultSubobject<UFGTargetingComponent>(TEXT("TargetingComponent"));
	NoiseComponent = CreateDefaultSubobject<UNoiseComponent>(TEXT("NoiseComponent"));
	VisionTargetComponent = CreateDefaultSubobject<UFGVisionSensingTargetComponent>(TEXT("VisionTarget"));
}

// Called when the game starts or when spawned

void AFGScreamer::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<AFGAIGameMode>(UGameplayStatics::GetGameMode(this));

	if (GameMode)
	{
		GameMode->BaseEnemys.Add(this);
	}
	else
	{
		UE_LOG(LogTemp,Warning, TEXT("AFGScreamer GameMode Was nullptr"));
	}

}

void AFGScreamer::RotateTowardsMovementDirection(const UFGNavMovementComponent* NavMoveComponent)
{
	FVector Velocity = NavMoveComponent->RequestedVelocity;
	if (!Velocity.IsNearlyZero())
	{	
		RotateTowardsDirection(Velocity, RotationSpeed);
	}
}

void AFGScreamer::RotateTowardsDirection(FVector direction, float Speed)
{
	direction.Z = 0.f;
	direction.Normalize();
	FRotator Rot = UKismetMathLibrary::MakeRotFromX(direction);
	SetActorRotation(FMath::Lerp(GetActorRotation(),Rot,Speed));
}

float AFGScreamer::GetDefaultHalfHeight() const
{	
	return Capsule->GetScaledCapsuleHalfHeight();
}

// Called every frame
void AFGScreamer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RotateTowardsMovementDirection(NavMovementComponent);
}


