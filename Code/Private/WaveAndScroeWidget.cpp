// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveAndScroeWidget.h"
#include "VampireGameState.h"

#include "Components/TextBlock.h"



void UWaveAndScroeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	gameState = Cast<AVampireGameState>(GetWorld()->GetGameState());

	waveText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Wave")));
	
	scoreText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Score")));

	waveCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_ShowWave")));

	gameSecondsText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_GameSeconds")));
	
	timeToShowWaveCount = 1.5f;

	if (gameState != NULL && waveText != NULL && scoreText != NULL && waveCountText != NULL)
	{
		gameState->OnWaveChange.AddUObject(this, &UWaveAndScroeWidget::UpdateWaveCount);
		gameState->OnWaveChange.AddUObject(this, &UWaveAndScroeWidget::ShowWaveCount);
		gameState->OnScoreChange.AddUObject(this, &UWaveAndScroeWidget::UpdateScore);
		gameState->SetScoreWidget(this);
		UpdateWaveCount();
		UpdateScore();
		ShowWaveCount();
	}

	gameSeconds = 0;

	isGameOver = false;

	GetWorld()->GetTimerManager().SetTimer(gameSecondsIncreaseTimer, this, &UWaveAndScroeWidget::IncreaseGameSeconds, 1.0f, true);


}




void UWaveAndScroeWidget::UpdateWaveCount()
{
	int tempWave = gameState->GetWaveCount();

	waveText->SetText(FText::FromString(FString::Printf(TEXT("Wave : %d"), tempWave)));

	UpdateScore();
}

void UWaveAndScroeWidget::UpdateScore()
{
	//int tempScore = gameState->GetScore();
	int currentZombieCount = gameState->GetCurrentEnemyNumber();
	int maxZombieCount = gameState->GetMaxEnemyNumber();


	//scoreText->SetText(FText::FromString(FString::Printf(TEXT("Score : %d"), tempScore))); 점수보단 남은 스켈레톤 수 알려주는 게 더 좋다고 생각


	scoreText->SetText(FText::FromString(FString::Printf(TEXT("Skeleton Count : %d / %d"), currentZombieCount, maxZombieCount)));
}

void UWaveAndScroeWidget::ShowWaveCount()
{
	int tempWave = gameState->GetWaveCount();

	waveCountText->SetVisibility(ESlateVisibility::Visible);

	waveCountText->SetText(FText::FromString(FString::Printf(TEXT("Wave %d Start"), tempWave)));

	GetWorld()->GetTimerManager().SetTimer(waveCountShowTimer, this, &UWaveAndScroeWidget::HideWaveCount, timeToShowWaveCount, false);
}

void UWaveAndScroeWidget::HideWaveCount()
{
	waveCountText->SetVisibility(ESlateVisibility::Hidden);
}


int UWaveAndScroeWidget::GetGameSeconds()
{
	return gameSeconds;
}



void UWaveAndScroeWidget::IncreaseGameSeconds()
{
	
	gameSeconds++;
	int tempMin = gameSeconds / 60;
	int tempSec = gameSeconds % 60;
	gameSecondsText->SetText(FText::FromString(FString::Printf(TEXT("Game Seconds  [%d : %d]"), tempMin, tempSec)));
}


void UWaveAndScroeWidget::StopGameSeconds()
{
	GetWorld()->GetTimerManager().ClearTimer(gameSecondsIncreaseTimer);
}
