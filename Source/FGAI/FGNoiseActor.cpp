#include "FGNoiseActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Actor.h"
#include "EngineUtils.h"
#include "Characters/FGAIGameMode.h"

AFGNoiseActor::AFGNoiseActor()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
}

void AFGNoiseActor::BeginDestroy()
{
	Super::BeginDestroy();
	AFGAIGameMode* GameMode = Cast<AFGAIGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->NoiseActorsList.Remove(this);
	}
}

void AFGNoiseActor::BeginPlay()
{
	Super::BeginPlay();
	
	AFGAIGameMode* GameMode = Cast<AFGAIGameMode>(UGameplayStatics::GetGameMode(this)); // GetGameMode

	if (GameMode)
	{
		GameMode->NoiseActorsList.Add(this);
	}	
	
	SetLifeSpan(0.4);	
}

void AFGNoiseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetActorLocation(),Radius, 8, FColor::Green, false, 0 , 6);
}