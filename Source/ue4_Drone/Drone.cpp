// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsThrusterComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ADrone::ADrone()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OutCollision = CreateDefaultSubobject<UBoxComponent>("OutCollision");
	RootComponent = OutCollision;
	OutCollision->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));			//设置碰撞盒大小
	OutCollision->SetSimulatePhysics(true);									//启用物理
	OutCollision->BodyInstance.bLockXRotation = true;
	OutCollision->BodyInstance.bLockYRotation = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(OutCollision);									//Mesh Attach到OutCollision上

	Paddle1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle1"));
	Paddle2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle2"));
	Paddle3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle3"));
	Paddle4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle4"));

	Paddle1->SetupAttachment(Mesh, TEXT("Paddle1"));
	Paddle2->SetupAttachment(Mesh, TEXT("Paddle2"));
	Paddle3->SetupAttachment(Mesh, TEXT("Paddle3"));
	Paddle4->SetupAttachment(Mesh, TEXT("Paddle4"));
	Paddles.Add(Paddle1);
	Paddles.Add(Paddle2);
	Paddles.Add(Paddle3);
	Paddles.Add(Paddle4);

	UpThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("UpThruster"));							//创建一个向上的物理推力器（UpThruster）
	UpThruster->SetupAttachment(RootComponent);
	UpThruster->ThrustStrength = 980.0f;
	UpThruster->SetAutoActivate(true);
	UpThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-1 * this->GetActorUpVector()));

	ForwardThruster = CreateDefaultSubobject<UPhysicsThrusterComponent>(TEXT("ForwardThruster"));				//创建一个向前的物理推力器（ForwardThruster）
	ForwardThruster->SetupAttachment(RootComponent);
	ForwardThruster->ThrustStrength = 0.0f;
	ForwardThruster->SetAutoActivate(true);
	ForwardThruster->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(-1 * this->GetActorForwardVector()));
}

// Called when the game starts or when spawned
void ADrone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetInputAxisValue("Lift") == 0.0f)
	{
		//参数中的-1"键"值类型参数能防止该消息被更新或刷新
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Axis Lift is 0.0f"));
		UpThruster->ThrustStrength = 980.0f;
	}

	if (GetInputAxisValue("Forward") == 0.0f)
	{
		ForwardThruster->ThrustStrength = 0.0f;

		if (Mesh->GetRelativeRotation().Pitch != 0.0f)
		{
			float currentPitch = Mesh->GetRelativeRotation().Pitch;
			Mesh->AddRelativeRotation(FRotator(-currentPitch * DeltaTime * 2.0f, 0.0f, 0.0f));
			if (FMath::Abs(Mesh->GetRelativeRotation().Pitch) <= KINDA_SMALL_NUMBER)
			{
				Mesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
			}
		}
	}

	this->RotatePaddle(DeltaTime);
}

// Called to bind functionality to input
void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADrone::DoFire);

	
	//[BindAction属于一次性的输入，比如：开火、跳跃]  [BindAxis属于持续性的输入，比如一直按住按键向前移动等]
	PlayerInputComponent->BindAxis("Lift", this, &ADrone::Lift);
	PlayerInputComponent->BindAxis("Forward", this, &ADrone::Forward);
	PlayerInputComponent->BindAxis("Turn", this, &ADrone::Turn);
}

void ADrone::DoFire()
{
	GetWorld()->SpawnActor<AMissle>(Bullet, Mesh->GetSocketTransform(TEXT("FireSocket")));
}

void ADrone::Lift(float value)
{
	UpThruster->ThrustStrength += value * LiftAcc * GetWorld()->DeltaTimeSeconds;
	UpThruster->ThrustStrength = FMath::Clamp(UpThruster->ThrustStrength, -LiftThrustMax, LiftThrustMax);
}

void ADrone::Forward(float value)
{
	ForwardThruster->ThrustStrength += value * ForwardAcc * GetWorld()->DeltaTimeSeconds;
	ForwardThruster->ThrustStrength = FMath::Clamp(ForwardThruster->ThrustStrength, -ForwardThrustMax, ForwardThrustMax);

	float pitch = Mesh->GetRelativeRotation().Pitch;
	if (FMath::Abs(pitch) < 30.0f)
	{
		Mesh->AddRelativeRotation(FRotator(-1 * value * GetWorld()->DeltaTimeSeconds * 50.0f, 0.0f, 0.0f));
	}
}

void ADrone::Turn(float value)
{
	OutCollision->AddTorqueInDegrees(-this->GetActorUpVector() * value * TurnStrength);
}

void ADrone::RotatePaddle(float Delta)
{
	for (int32 i = 0; i < Paddles.Num(); ++i)
	{
		Paddles[i]->AddRelativeRotation(FRotator(0.0f, Delta * PaddleRotateSpeed, 0.0f));
	}
}

