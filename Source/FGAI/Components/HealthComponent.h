#pragma once
#include "CoreMinimal.h"
#include "FGAI/AI/Sensing/FGHearingSenseComponent.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


USTRUCT(BlueprintType)
struct FstructDead
{
	GENERATED_BODY()
public:
	UPROPERTY()
	bool Alive = false;
};

struct FSensesInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFGDamageSenseDelegate, const FSensesInfo&, Results);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIsDead, const FstructDead&, Results);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FGAI_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UFUNCTION(BlueprintCallable)
	void TakeDamage(FHitResult Hit, float Damage, AActor* DamageInstigator);

	UPROPERTY(BlueprintAssignable)
	FIsDead IsDead;
	
	UPROPERTY(VisibleAnywhere)
	float Health = 100;

	FFGDamageSenseDelegate OnDamage;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
};
