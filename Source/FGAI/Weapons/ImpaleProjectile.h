// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "ImpaleProjectile.generated.h"

UCLASS()
class FGAI_API AImpaleProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AImpaleProjectile();
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;
	
	USphereComponent* SphereComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere)
	float Speed = 500.f;

	FVector Velocity;

};
