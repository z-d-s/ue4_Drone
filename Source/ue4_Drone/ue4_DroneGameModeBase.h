// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ue4_DroneGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DRONE_API Aue4_DroneGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	uint32 points;
};
