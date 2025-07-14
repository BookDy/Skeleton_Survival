// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIREPROJECT_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;


	UFUNCTION()
	void RestartClicked();

	UFUNCTION()
	void ToTitleClicked();

private:
	UPROPERTY()
	class UButton* BT_Restart;

	UPROPERTY()
	class UButton* BT_ToTitle;
	
};
