// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WaveAndScroeWidget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIREPROJECT_API UWaveAndScroeWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual void NativeConstruct() override;

	void UpdateWaveCount();
	
	void UpdateScore();

	void ShowWaveCount();

	void HideWaveCount();

	int GetGameSeconds();

	void IncreaseGameSeconds();

	void StopGameSeconds();

private:
	UPROPERTY()
	class AVampireGameState* gameState;

	UPROPERTY()
	class UTextBlock* waveText;

	UPROPERTY()
	class UTextBlock* scoreText;

	UPROPERTY()
	class UTextBlock* waveCountText;

	UPROPERTY()
	class UTextBlock* gameSecondsText;

	int waveCount;
	int score;
	
	FTimerHandle waveCountShowTimer;

	float timeToShowWaveCount;


	FTimerHandle gameSecondsIncreaseTimer;
	int gameSeconds;

	bool isGameOver = false;
	
};
