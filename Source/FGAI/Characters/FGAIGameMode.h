// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FGAIGameMode.generated.h"

class ABaseEnemy;
class AFGEnemy;
class AFGNoiseActor;

UCLASS(minimalapi)
class AFGAIGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFGAIGameMode();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ABaseEnemy*> BaseEnemys;
    void GetAllBaseEnemys(TArray<ABaseEnemy*> Out);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AFGEnemy*> FGEnemys;
	void GetAllFGEnemys(TArray<AFGEnemy*> Out);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AFGNoiseActor*> NoiseActorsList;	
	void GetNoiseActors(TArray<AFGNoiseActor*> NoiseActors);	
};


