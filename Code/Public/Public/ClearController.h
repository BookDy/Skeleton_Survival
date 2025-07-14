// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ClearController.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIREPROJECT_API AClearController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "ClearUIWidget")
	class UVPClearWidget* clearUIWidget;

};
