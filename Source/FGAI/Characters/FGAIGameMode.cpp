#include "FGAIGameMode.h"
#include "FGAI/FGNoiseActor.h"
#include "BaseEnemy.h"

AFGAIGameMode::AFGAIGameMode()	: Super()
{
}

void AFGAIGameMode::GetAllBaseEnemys(TArray<ABaseEnemy*> Out)
{
	for (ABaseEnemy* base : BaseEnemys)
	{
		if (base == nullptr)	continue;
		
		Out.Add(base);
	}
}

void AFGAIGameMode::GetAllFGEnemys(TArray<AFGEnemy*> Out)
{
	for (AFGEnemy* FGEnemy : FGEnemys)
	{
		if (FGEnemy == nullptr)	continue;;
		
		Out.Add(FGEnemy);
	}
}

void AFGAIGameMode::GetNoiseActors(TArray<AFGNoiseActor*> NoiseActors)
{
	for (AFGNoiseActor* NoiseA : NoiseActorsList)
	{
		if (NoiseA == nullptr)	continue;
		
		NoiseActors.Add(NoiseA);
	}
}
