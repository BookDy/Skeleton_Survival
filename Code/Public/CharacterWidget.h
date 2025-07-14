// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIREPROJECT_API UCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacter(class APlayerCharacter* newPlayer);


protected:
	virtual void NativeConstruct() override;

	void UpdateWidget();

private:
	class APlayerCharacter* currentCharacter;
	
	UPROPERTY()
	class UProgressBar* HpProgressBar;
	UPROPERTY()
	class UProgressBar* ExpProgressBar;
};
