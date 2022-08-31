// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Missle.h"
#include "Drone.generated.h"

//Ç°ÏòÉùÃ÷(forward declaration)
class UBoxComponent;
class UStaticMeshComponent;
class UPhysicsThrusterComponent;

UCLASS()
class UE4_DRONE_API ADrone : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADrone();

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* OutCollision;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Paddle1;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Paddle2;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Paddle3;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Paddle4;

	UPROPERTY(VisibleAnywhere)
	UPhysicsThrusterComponent* UpThruster;

	UPROPERTY(VisibleAnywhere)
	UPhysicsThrusterComponent* ForwardThruster;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float LiftAcc = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float LiftThrustMax = 2000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float ForwardAcc = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float ForwardThrustMax = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init")
	float TurnStrength = 500000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Init");
	float PaddleRotateSpeed = 1000.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMissle> Bullet;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
	void DoFire();

	UFUNCTION()
	void Lift(float value);

	UFUNCTION()
	void Forward(float value);

	UFUNCTION()
	void Turn(float value);

	TArray<UStaticMeshComponent*> Paddles;
	void RotatePaddle(float Delta);
};
