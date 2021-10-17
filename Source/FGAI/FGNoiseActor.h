#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGNoiseActor.generated.h"

class USceneComponent;

UCLASS(Blueprintable, BlueprintType)
class FGAI_API AFGNoiseActor : public AActor
{
	GENERATED_BODY()	
public:	
	AFGNoiseActor();
	virtual void BeginDestroy() override;
	UPROPERTY()
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere)
	float Radius = 350.f;

	AActor* NoiseInstigator;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};


