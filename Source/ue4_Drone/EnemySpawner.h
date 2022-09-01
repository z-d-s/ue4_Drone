// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "Enemy.h"
#include "EnemySpawner.generated.h"

class UBoxComponent;

UCLASS()
class UE4_DRONE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* SpawnArea;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemy> EnemyType;

	UPROPERTY(EditAnywhere)
	float SpawnSpace = 1.0f;

	UFUNCTION()
	void SpawnEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle SpawnHandle;
};
