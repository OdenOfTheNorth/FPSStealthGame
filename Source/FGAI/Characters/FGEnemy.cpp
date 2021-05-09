#include "FGEnemy.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "FGCharacter.h"
#include "PhysXInterfaceWrapperCore.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "FGAI/AI/Sensing/FGVisionSensingComponent.h"
#include "FGAI/AI/Movement/FGNavMovementComponent.h"
#include "FGAI/AI/Sensing/FGHearingSenseComponent.h"
#include "FGAI/AI/StateMachine/FGStateMachineComponent.h"
#include "FGAI/Components/HealthComponent.h"
#include "FGAI/AI/Sensing/FGTargetingComponent.h"
#include "FGAI/Weapons/BaseWeapon.h"
#include "Kismet/KismetMathLibrary.h"
#include "FGScreamer.h"
//#include "ToolBuilderUtil.h"
#include "Kismet/GameplayStatics.h"

static int32 DebugWeaponDrawing = 0;
FAutoConsoleVariableRef CVARDebugWeaponDrawing(
	TEXT("COOP.DebugWeapons"), 
	DebugWeaponDrawing, 
	TEXT("Draw Debug Lines for Weapons"), 
	ECVF_Cheat);

AFGEnemy::AFGEnemy()
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
	VisionTargetComponent = CreateDefaultSubobject<UFGVisionSensingTargetComponent>(TEXT("VisionTarget"));
}

float AFGEnemy::GetDefaultHalfHeight() const
{
	return Capsule->GetScaledCapsuleHalfHeight();
}

void AFGEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (!EquippedWeapon) return;
	WeaponPtr = GetWorld()->SpawnActor<ABaseWeapon>(EquippedWeapon);	
	WeaponPtr->SetOwner(this);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseEnemy::StaticClass(), BaseArray);

	QueryParams.AddIgnoredActor(this);	

	for(AActor* Base : BaseArray)
	{
		ABaseEnemy* BaseEnemy = Cast<ABaseEnemy>(Base);
		QueryParams.AddIgnoredActor(BaseEnemy);	
	}
	
}

void AFGEnemy::Tick(float DelatTime)
{
	Super::Tick(DelatTime);

	RotateTowardsMovementDirection(NavMovementComponent);	
}

/*void AFGEnemy::Shot()
{
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), TargetingComponent->SensesInfo.SensedLocation, ECC_GameTraceChannel1, QueryParams))
	{
		// Blocking hit! Process damage
		if (Hit.bBlockingHit)
		{
			AFGCharacter* HitCharacter = Cast<AFGCharacter>(Hit.GetActor());			
			if (HitCharacter == nullptr) return;
			UE_LOG(LogTemp,Warning,TEXT("HitCharacter is not nullptr"));
			UHealthComponent* HitActorHealthComponent = HitCharacter->GetHealthComponent();
			if (HitActorHealthComponent == nullptr) return;
			UE_LOG(LogTemp,Warning,TEXT("HitActorHealthComponent is not nullptr"));
			HitActorHealthComponent->TakeDamage(Hit, BaseDamage, this);
		}
	}		

	if (DebugWeaponDrawing > 0)
	{
		DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), TargetingComponent->SensesInfo.SensedLocation, FColor::White, false, 1.0f, 0, 1.0f);
	}
}*/

void AFGEnemy::RotateTowardsMovementDirection(const UFGNavMovementComponent* NavMoveComponent)
{
	FVector Velocity = NavMoveComponent->RequestedVelocity;
	if (!Velocity.IsNearlyZero())
	{	
		RotateTowardsDirection(Velocity, RotationSpeed);
	}
}

void AFGEnemy::RotateTowardsDirection(FVector direction, float Speed)
{
	direction.Z = 0.f;
	direction.Normalize();
	FRotator Rot = UKismetMathLibrary::MakeRotFromX(direction);
	SetActorRotation(FMath::Lerp(GetActorRotation(),Rot,Speed));
}
