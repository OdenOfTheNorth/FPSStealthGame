#include "FGHearingSenseComponent.h"
#include "CoreMinimal.h"
#include "FGAI/Characters/BaseEnemy.h"
#include "Components/ActorComponent.h"
#include "FGAI/FGNoiseActor.h"
#include "Kismet/GameplayStatics.h"

UFGHearingSenseComponent::UFGHearingSenseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFGHearingSenseComponent::CheakNoise(TArray<AFGNoiseActor*> FoundActors)
{
	if (FoundActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("FoundActors.Num() == 0 , FGHearingSenseComponent.cpp "));
	}
	
	//Todo fixed only cheak for noise when it's spwaned	

	//AFGAIGameMode* GameMode = Cast<AFGAIGameMode>(UGameplayStatics::GetGameInstance(GetWorld())); 
	//AFGNoiseActor::GetNoiseActors(FoundActors);
	//FindAllNoiseActor(GetWorld(),FoundActors);
	//GameMode->GetNoiseActors(FoundActors);	
	//OwnerEnemy = Cast<ABaseEnemy>(GetOwner());

	if (GetOwner() != nullptr)
	{
		ABaseEnemy* OwnerEnemy = Cast<ABaseEnemy>(GetOwner());
	
		if (OwnerEnemy == nullptr)
		{		
			return;
		}	
	
		FVector MyLocation = OwnerEnemy->GetActorLocation();	
		float MyRadiusSq = FMath::Square(HearingRange);
	
		for (AFGNoiseActor* NoiseActor : FoundActors)
		{
			if (NoiseActor != nullptr) 
			{
				float DistanceToNoiseSq = MyLocation.DistSquared(NoiseActor->GetActorLocation(), MyLocation);
				float NoiseRangeSq = FMath::Square(NoiseActor->Radius);
				float NoiseRadiuses = NoiseRangeSq + MyRadiusSq;

				if (DistanceToNoiseSq < NoiseRadiuses)
				{
					FSensesInfo HearingInfo;
					HearingInfo.SensedActor = NoiseActor->NoiseInstigator;
					HearingInfo.SensedLocation = NoiseActor->GetActorLocation();
					HearingInfo.Range = NoiseActor->Radius;
					HearingInfo.bSensedActor = (NoiseActor != nullptr);
					OnNoiseHeard.Broadcast(HearingInfo);
				}
			}
		}	
		FoundActors.Empty();
	}


}

void UFGHearingSenseComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UFGHearingSenseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		
	//DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(),HearingRange, 16, FColor::Red, false, 0 , 6);
}
 
/*
void UFGHearingSenseComponent::GetAllNoiseActor(UWorld* World, TArray<AFGNoiseActor*>& Out)
{
	for (TActorIterator<AFGNoiseActor> It(World); It; ++It)
	{
		Out.Add(*It);
	}
}*/

