// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VPClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIREPROJECT_API UVPClearWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OntotitleBT_Clicked();

private:
	UPROPERTY()
	class UTextBlock* currentTimeText;

	UPROPERTY()
	class UTextBlock* bestTimeText;

	UPROPERTY()
	class UButton* totitleBT;

	UPROPERTY()
	class UVPGameInstance* tempInstance;


	
};
