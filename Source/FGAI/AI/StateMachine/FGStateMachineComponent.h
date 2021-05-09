#pragma once

#include "Components/ActorComponent.h"
#include "FGAI/AI/Sensing/FGVisionSensingComponent.h"

#include "FGStateMachineComponent.generated.h"

struct FFGVisionSensingResults;
struct FFGHearingInfo;

class UFGHearingSenseComponent;
class AAIController;
class UFGAIStateBase;
class UFGAIStateMachineSheet;
class UFGNavMovementComponent;
class UFGVisionSensingComponent;

UCLASS(meta = (BlueprintSpawnableComponent))
class UFGStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFGStateMachineComponent();

	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetSheet(UFGAIStateMachineSheet* NewSheet);

	AAIController* Controller;
	APawn* OwnerPawn;

	UFUNCTION(BlueprintCallable)
	void Suspicious();		//const FFGHearingInfo& HearingSenseInfo
	UFUNCTION(BlueprintCallable)
	void PlayerSeen();		//const FFGVisionSensingResults& VisionSenseInfo
	FName GetCurrentStateName();

	void Run();
	
	UPROPERTY(VisibleAnywhere)
	UFGVisionSensingComponent* VisionSensingComponent;
	
	UPROPERTY(VisibleAnywhere)
	UFGNavMovementComponent* NavMovementComponent;
	
	UPROPERTY(VisibleAnywhere)
	UFGHearingSenseComponent* HearingSensingComponent;
	
	UPROPERTY(Transient)
	TArray<UFGAIStateBase*> AIStates;

	UPROPERTY(Transient, VisibleAnywhere)
	UFGAIStateBase* CurrentState = nullptr;
	
	UFGAIStateBase* GetStateFromName(FName StateName) const;
	
private:
	void LoadSheet();
	void UnloadSheet();

	UFGAIStateBase* GetStateFromClass(TSubclassOf<UFGAIStateBase> ClassType) const;
	

	UPROPERTY(EditAnywhere)
	UFGAIStateMachineSheet* AIStateMachineSheet = nullptr;


};
