// Fill out your copyright notice in the Description page of Project Settings.


#include "VPGameInstance.h"
#include "VPSaveScore.h"
#include "Kismet/GameplayStatics.h"

UVPGameInstance::UVPGameInstance()
{
	/*
	if (VPTimeTable)
	{
		if (VPTimeTable->GetRowMap().Num() <= 0)
		{
			UE_LOG(LogTemp, Error, TEXT("TimeTable is Empty"));
			exit(1);
		}

		tempData = VPTimeTable->FindRow<FVPTimeData>(*FString::FromInt(1), TEXT(""));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TimeTable Missing"));
	}
	*///데이터 테이블은 정적 전용이 맞는듯, 세이브 게임을 통해 시간 저장하고 게임 인스턴스는 초반에 불러올 때 하는 게 맞는듯
	
	UVPSaveScore* savedScore = Cast<UVPSaveScore>(UGameplayStatics::LoadGameFromSlot(defaultSaveSlotName, 0));
	if (savedScore == nullptr)
	{
		savedScore = GetMutableDefault<UVPSaveScore>();
	}

	SetBestTime(savedScore->bestTime);

}

void UVPGameInstance::Init()
{
	Super::Init();
}

int UVPGameInstance::GetBestTime()
{
	return bestTime;
}

int UVPGameInstance::GetCurrentTime()
{
	return currentTime;
}

void UVPGameInstance::SetCurrentTime(int newCurrentTime)
{
	currentTime = newCurrentTime;
	SetBestTime(currentTime);
	
}

void UVPGameInstance::SetBestTime(int newTime)
{
	if (bestTime > newTime)
	{
		bestTime = newTime;
		UVPSaveScore* newScoreData = NewObject<UVPSaveScore>();
		newScoreData->bestTime = bestTime;
		UGameplayStatics::SaveGameToSlot(newScoreData, defaultSaveSlotName, 0);

	}
	
}

