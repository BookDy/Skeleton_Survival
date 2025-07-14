// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "VPGameInstance.generated.h"

/**
 * 
 */

//USTRUCT(BlueprintType)
//struct FVPTimeData : public FTableRowBase
//{
//	GENERATED_BODY()
//public:
//	FVPTimeData() : CurrentTime(0), BestTime(0) {}
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
//	int CurrentTime;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
//	int BestTime;
//};


UCLASS()
class VAMPIREPROJECT_API UVPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UVPGameInstance();

	virtual void Init() override;

	int GetBestTime();
	
	int GetCurrentTime();

	void SetCurrentTime(int newCurrentTime);

	void SetBestTime(int newTime);

private:
	UPROPERTY()
	FString defaultSaveSlotName;

	UPROPERTY()
	int currentTime = 0;

	UPROPERTY()
	int bestTime = 9999;
};
