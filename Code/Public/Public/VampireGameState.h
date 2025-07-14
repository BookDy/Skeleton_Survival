// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "VampireGameState.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnScoreChange);
DECLARE_MULTICAST_DELEGATE(FOnWaveChange);
DECLARE_MULTICAST_DELEGATE(FOnInit);
DECLARE_MULTICAST_DELEGATE(FOnWaveEnd);

UCLASS()
class VAMPIREPROJECT_API AVampireGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AVampireGameState();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime)override;

	void Init();

	void AdvanceWave();

	void GameOver();

	void GameClear();


public:
	void SetWaveCount(int newWaveCount);

	void SetMaxEnemyNumber(int newMaxEnemyNumber);

	void SetCurrentEnemyNumber(int newCurrentEnemyNumber);

	void SetScore(int newScore);

	void GainScore();

	void EliminateEnemy();

public:
	int GetWaveCount();

	int GetMaxEnemyNumber();

	int GetCurrentEnemyNumber();

	int GetScore();

	void SetScoreWidget(class UWaveAndScroeWidget* newScoreWidget);


public:
	FOnScoreChange OnScoreChange;
	FOnWaveChange OnWaveChange;
	FOnInit OnInit;
	FOnWaveEnd OnWaveEnd;


	float GetGameSeconds();

	void SetGameSeconds(float newGameSeconds);

	

private:
	UPROPERTY(VisibleAnywhere, Category = Stage)
	int waveCount = 1;
	UPROPERTY(VisibleAnywhere, Category = State)
	int maxEnemyNumber = 10;
	UPROPERTY(VisibleAnywhere, Category = State)
	int currentEnemyNumber = 10;
	UPROPERTY(VisibleAnywhere, Category = GameStat)
	int score = 0;


	UPROPERTY(VisibleAnywhere, Category = GameSeconds)
	int gameSeconds = 0;



	UPROPERTY()
	class UWaveAndScroeWidget* scoreWidget;





	
};
