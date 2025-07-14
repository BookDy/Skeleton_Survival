// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWidget.h"
#include "PlayerCharacter.h"
#include "Components/ProgressBar.h"

void UCharacterWidget::BindCharacter(APlayerCharacter* newPlayer)
{
	if (newPlayer != NULL)
	{
		currentCharacter = newPlayer;

		currentCharacter->OnHPChange.AddUObject(this, &UCharacterWidget::UpdateWidget);

		currentCharacter->OnExpChange.AddUObject(this, &UCharacterWidget::UpdateWidget);
	}
}

void UCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	ExpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_ExpBar")));

	if (HpProgressBar != NULL && ExpProgressBar != NULL)
	{
		UpdateWidget();
	}
}

void UCharacterWidget::UpdateWidget()
{
	if (currentCharacter != NULL)
	{
		if (HpProgressBar != NULL)
		{
			HpProgressBar->SetPercent(currentCharacter->GetHPRatio());
		}

		if (ExpProgressBar != NULL)
		{
			ExpProgressBar->SetPercent(currentCharacter->GetExpRatio());
		}
	}
}
