// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "VPSaveScore.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIREPROJECT_API UVPSaveScore : public USaveGame
{
	GENERATED_BODY()

public:
	UVPSaveScore();

	UPROPERTY()
	int bestTime;
	
};
