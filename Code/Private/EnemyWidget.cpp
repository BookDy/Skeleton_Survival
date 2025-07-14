// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWidget.h"
#include "Enemy.h"
#include "Components/ProgressBar.h"

void UEnemyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_Hp")));
	if (HpProgressBar != NULL)
	{
		UpdateWidget();
	}
}

void UEnemyWidget::BindEnemy(AEnemy* newEnemy)
{
	if (newEnemy != NULL)
	{
		currentEnemy = newEnemy;
		currentEnemy->OnHpChange.AddUObject(this, &UEnemyWidget::UpdateWidget);
	}
}

void UEnemyWidget::UpdateWidget()
{
	if (currentEnemy != NULL)
	{
		if (HpProgressBar != NULL)
		{
			HpProgressBar->SetPercent(currentEnemy->GetHpRatio());
		}
	}
}
