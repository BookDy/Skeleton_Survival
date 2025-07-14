// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TitleUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIREPROJECT_API ATitleUIPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	class UUserWidget* titleUIWidget;
	
};
