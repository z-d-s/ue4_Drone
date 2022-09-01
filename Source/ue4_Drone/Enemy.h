// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

class UStaticMeshComponent;
class UParticleSystem;
class USoundBase;

UCLASS()
class UE4_DRONE_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* ExplosionParticle;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, Category = "FloatSpeed")
	float FloatSpeed = 500.0f;

	UFUNCTION()
	void DestroyHandler(AActor* DestroyedActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
