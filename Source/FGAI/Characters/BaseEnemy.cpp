#include "BaseEnemy.h"
#include "Components/CapsuleComponent.h"
#include "FGAIGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void ABaseEnemy::BeginDestroy()
{
	Super::BeginDestroy();
	//GameMode = Cast<AFGAIGameMode>(UGameplayStatics::GetGameState(this));	
	GameMode = Cast<AFGAIGameMode>(UGameplayStatics::GetGameMode(this));

	if (GameMode)
	{
		GameMode->BaseEnemys.Remove(this);
	}
	
	//
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEnemy::RotateTowardsMovementDirection(const UFGNavMovementComponent* NavMoveComponent)
{
	
}

float ABaseEnemy::GetDefaultHalfHeight() const
{
	return Capsule->GetScaledCapsuleHalfHeight();
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
