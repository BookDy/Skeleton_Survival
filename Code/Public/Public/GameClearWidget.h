// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIREPROJECT_API UGameClearWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void ToTitleClicked();

	UFUNCTION()
	void ExitClicked();

private:

	UPROPERTY()
	class UButton* BT_Totitle;

	UPROPERTY()
	class UButton* BT_Exit;
	
};
