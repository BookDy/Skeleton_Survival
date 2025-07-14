// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerCharacter.h"
#include "VPGameInstance.h"
#include "WaveAndScroeWidget.h"

AVampireGameState::AVampireGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AVampireGameState::BeginPlay()
{
    Super::BeginPlay();

    Init();

}

void AVampireGameState::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    gameSeconds += DeltaTime;
}


void AVampireGameState::Init()
{
 
    gameSeconds = 0;
    SetMaxEnemyNumber(5);
    SetCurrentEnemyNumber(GetMaxEnemyNumber());
    SetScore(0);
    SetWaveCount(1);

    OnInit.Broadcast();
}

void AVampireGameState::AdvanceWave()
{

    OnWaveEnd.Broadcast();

    if (waveCount < 5) // 원래는 5 
    {
        SetMaxEnemyNumber(GetMaxEnemyNumber() + 5);
        SetCurrentEnemyNumber(GetMaxEnemyNumber());
        SetWaveCount(GetWaveCount() + 1);
    }
    else
    {
        GameClear();
    }
    
}

void AVampireGameState::GameOver()
{
}

void AVampireGameState::GameClear()
{
    auto actor = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
    if (actor)
    {
        auto player = Cast<APlayerCharacter>(actor);
        if (player)
        {
            if (scoreWidget)
            {
                scoreWidget->StopGameSeconds();
                gameSeconds = scoreWidget->GetGameSeconds();
                UVPGameInstance* tempGameInstance= Cast<UVPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

                tempGameInstance->SetCurrentTime(gameSeconds);

            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("scoreWidget is missing"));
            }

            player->GameClear();
        }
        else
        {
            UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
        }
    }
    else 
    {
        UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
    }
       
}

void AVampireGameState::SetWaveCount(int newWaveCount)
{
    waveCount = newWaveCount;
    OnWaveChange.Broadcast();
}

void AVampireGameState::SetMaxEnemyNumber(int newMaxEnemyNumber)
{
    maxEnemyNumber = newMaxEnemyNumber;
}

void AVampireGameState::SetCurrentEnemyNumber(int newCurrentEnemyNumber)
{
    currentEnemyNumber = newCurrentEnemyNumber;
}

void AVampireGameState::SetScore(int newScore)
{
    score = newScore;
    OnScoreChange.Broadcast();
}

int AVampireGameState::GetWaveCount()
{
    return waveCount;
}

int AVampireGameState::GetMaxEnemyNumber()
{
    return maxEnemyNumber;
}

int AVampireGameState::GetCurrentEnemyNumber()
{
    return currentEnemyNumber;
}

int AVampireGameState::GetScore()
{
    return score;
}

void AVampireGameState::SetScoreWidget(UWaveAndScroeWidget* newScoreWidget)
{
    if (newScoreWidget)
    {
        scoreWidget = newScoreWidget;
    }
}

float AVampireGameState::GetGameSeconds()
{
    return gameSeconds;
}


void AVampireGameState::SetGameSeconds(float newGameSeconds)
{
    gameSeconds = newGameSeconds;
}

void AVampireGameState::GainScore()
{
    SetScore(GetScore() + 1);
}

void AVampireGameState::EliminateEnemy()
{
    if (GetCurrentEnemyNumber() > 1)
    {
        SetCurrentEnemyNumber(GetCurrentEnemyNumber() - 1);
        GainScore();
    }
    else
    {
        AdvanceWave();
    }
}
