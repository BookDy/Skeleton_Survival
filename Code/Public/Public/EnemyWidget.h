// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyWidget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIREPROJECT_API UEnemyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void BindEnemy(class AEnemy* newEnemy);

	void UpdateWidget();

private:
	class AEnemy* currentEnemy;

	UPROPERTY()
	class UProgressBar* HpProgressBar;
	
};
