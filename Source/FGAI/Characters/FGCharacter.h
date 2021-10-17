#pragma once

#include "FGAI/AI/Sensing/FGVisionSensingTargetComponent.h"
#include "FGAI/Components/HealthComponent.h"
#include "FGAI/Components/NoiseComponent.h"
#include "FGAI/Weapons/ImpaleProjectile.h"
#include "GameFramework/Pawn.h"
#include "FGCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCapsuleComponent;
class UCameraComponent;
class UFGMovementComponent;
class UNoiseComponent;

UCLASS()
class AFGCharacter : public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleDefaultsOnly, Category=Collision)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UFGMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, Category = Sound)
	UNoiseComponent* NoiseComponent;

	UPROPERTY(BlueprintReadWrite,VisibleAnywhere , Category = Health)
	UHealthComponent* HealthComponent;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UFGVisionSensingTargetComponent* VisionTargetComponent;
	
	AFGCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	virtual void Tick(float DeltaTime) override;
	bool IsCrouch;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AImpaleProjectile> ImpaleProjectile;

	UFUNCTION(BlueprintCallable)
	float GetHealth()	{		return HealthComponent->Health;	};
	UFUNCTION(BlueprintCallable)
	float GetMaxHealth()	{		return HealthComponent->MaxHealth;	};

protected:
	virtual void BeginPlay();

protected:

	UPROPERTY(EditAnywhere, Category = Movement)
	float Speed;

	UPROPERTY(EditAnywhere, Category = Movement)
	float Gravity;

	FVector InputVector = FVector::ZeroVector;
	FVector LookVector = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ETraceTypeQuery> TraceType;
	
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void OnFire();

	void EndCrouch();
	void StartCrouch();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UCapsuleComponent* GetCapsule() const { return Capsule; }

	UHealthComponent* GetHealthComponent(){return HealthComponent;}
private:
	float spawnDelay = 0.3f;
	float spawnTime = 0;

};

