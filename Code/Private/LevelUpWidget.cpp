// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "PlayerCharacter.h"

void ULevelUpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ChangeOption();

	SetOptionsText();
}

void ULevelUpWidget::NativeOnInitialized()
{

	Super::NativeOnInitialized();

	BT_Option1 = Cast<UButton>(GetWidgetFromName(TEXT("BT_Option1")));
	TB_Option1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Option1")));

	BT_Option2 = Cast<UButton>(GetWidgetFromName(TEXT("BT_Option2")));
	TB_Option2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Option2")));

	BT_Option3 = Cast<UButton>(GetWidgetFromName(TEXT("BT_Option3")));
	TB_Option3 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Option3")));

}



void ULevelUpWidget::BindPlayer(APlayerCharacter* player)
{
	if (player != NULL)
	{
		currentPlayer = player;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelUpWidget can't get Player"));
	}

	
}

void ULevelUpWidget::ChangeOption()
{
	int index = FMath::RandRange(0, 5);
	option1 = ReturnEnumByIndex(index);

	int tempOption1 = index;
	while (index == tempOption1)
	{
		index = FMath::RandRange(0, 5);
	}
	option2 = ReturnEnumByIndex(index);

	int tempOption2 = index;
	while (index == tempOption1 || index == tempOption2)
	{
		index = FMath::RandRange(0, 5);
	}
	option3 = ReturnEnumByIndex(index);
	
}

void ULevelUpWidget::Option1_Clicked()
{
	switch (option1)
	{
	case ELevelUpOptions::HealthUp:
		HealthUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::HealthRegenUp:
		HealthRegenUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::SpeedUp:
		SpeedUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::BulletDmgUP:
		BulletDmgUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::BulletSpeedUp:
		BulletSpeedUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::FireRateUp:
		FireRateUp();
		currentPlayer->LevelUpEnd();
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("OptionButton Bound Over"));
		break;
	}
}

void ULevelUpWidget::Option2_Clicked()
{
	switch (option2)
	{
	case ELevelUpOptions::HealthUp:
		HealthUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::HealthRegenUp:
		HealthRegenUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::SpeedUp:
		SpeedUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::BulletDmgUP:
		BulletDmgUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::BulletSpeedUp:
		BulletSpeedUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::FireRateUp:
		FireRateUp();
		currentPlayer->LevelUpEnd();
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("OptionButton Bound Over"));
		break;
	}
}

void ULevelUpWidget::Option3_Clicked()
{
	switch (option3)
	{
	case ELevelUpOptions::HealthUp:
		HealthUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::HealthRegenUp:
		HealthRegenUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::SpeedUp:
		SpeedUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::BulletDmgUP:
		BulletDmgUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::BulletSpeedUp:
		BulletSpeedUp();
		currentPlayer->LevelUpEnd();
		break;

	case ELevelUpOptions::FireRateUp:
		FireRateUp();
		currentPlayer->LevelUpEnd();
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("OptionButton Bound Over"));
		break;
	}
}

void ULevelUpWidget::SetOptionsText()
{
	switch (option1)
	{
	case ELevelUpOptions::HealthUp :
		TB_Option1->SetText(FText::FromString(FString::Printf(TEXT("최대 체력 증가"))));
		break;

	case ELevelUpOptions::HealthRegenUp:
		TB_Option1->SetText(FText::FromString(FString::Printf(TEXT("체력 재생 증가"))));
		break;

	case ELevelUpOptions::SpeedUp:
		TB_Option1->SetText(FText::FromString(FString::Printf(TEXT("스피드 증가"))));
		break;

	case ELevelUpOptions::BulletDmgUP:
		TB_Option1->SetText(FText::FromString(FString::Printf(TEXT("총알 공격력 증가"))));
		break;

	case ELevelUpOptions::BulletSpeedUp:
		TB_Option1->SetText(FText::FromString(FString::Printf(TEXT("총알 스피드 증가"))));
		break;

	case ELevelUpOptions::FireRateUp:
		TB_Option1->SetText(FText::FromString(FString::Printf(TEXT("총알 발사 속도 증가"))));
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("OptionText Bound Over"));
		break;
	}

	switch (option2)
	{
	case ELevelUpOptions::HealthUp:
		TB_Option2->SetText(FText::FromString(FString::Printf(TEXT("최대 체력 증가"))));
		break;

	case ELevelUpOptions::HealthRegenUp:
		TB_Option2->SetText(FText::FromString(FString::Printf(TEXT("체력 재생 증가"))));
		break;

	case ELevelUpOptions::SpeedUp:
		TB_Option2->SetText(FText::FromString(FString::Printf(TEXT("스피드 증가"))));
		break;

	case ELevelUpOptions::BulletDmgUP:
		TB_Option2->SetText(FText::FromString(FString::Printf(TEXT("총알 공격력 증가"))));
		break;

	case ELevelUpOptions::BulletSpeedUp:
		TB_Option2->SetText(FText::FromString(FString::Printf(TEXT("총알 스피드 증가"))));
		break;

	case ELevelUpOptions::FireRateUp:
		TB_Option2->SetText(FText::FromString(FString::Printf(TEXT("총알 발사 속도 증가"))));
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("OptionText Bound Over"));
		break;
	}

	switch (option3)
	{
	case ELevelUpOptions::HealthUp:
		TB_Option3->SetText(FText::FromString(FString::Printf(TEXT("최대 체력 증가"))));
		break;

	case ELevelUpOptions::HealthRegenUp:
		TB_Option3->SetText(FText::FromString(FString::Printf(TEXT("체력 재생 증가"))));
		break;

	case ELevelUpOptions::SpeedUp:
		TB_Option3->SetText(FText::FromString(FString::Printf(TEXT("스피드 증가"))));
		break;

	case ELevelUpOptions::BulletDmgUP:
		TB_Option3->SetText(FText::FromString(FString::Printf(TEXT("총알 공격력 증가"))));
		break;

	case ELevelUpOptions::BulletSpeedUp:
		TB_Option3->SetText(FText::FromString(FString::Printf(TEXT("총알 스피드 증가"))));
		break;

	case ELevelUpOptions::FireRateUp:
		TB_Option3->SetText(FText::FromString(FString::Printf(TEXT("총알 발사 속도 증가"))));
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("OptionText Bound Over"));
		break;
	}

}


ELevelUpOptions ULevelUpWidget::ReturnEnumByIndex(int index)
{
	switch (index)
	{
	case 0:
		return ELevelUpOptions::HealthUp;
	case 1:
		return ELevelUpOptions::HealthRegenUp;
	case 2:
		return ELevelUpOptions::SpeedUp;
	case 3:
		return ELevelUpOptions::BulletDmgUP;
	case 4:
		return ELevelUpOptions::BulletSpeedUp;
	case 5:
		return ELevelUpOptions::FireRateUp;
	default:
		UE_LOG(LogTemp, Warning, TEXT("EnumBound Over"));
		return ELevelUpOptions::HealthUp;
	}
}

void ULevelUpWidget::HealthUp()
{
	float newMaxHp = currentPlayer->maxHealth + 200;
	currentPlayer->SetMaxHp(newMaxHp);
}

void ULevelUpWidget::HealthRegenUp()
{
	float newHealthRegen = currentPlayer->healthRegen + 0.5;
	currentPlayer->SetHealthRegen(newHealthRegen);
}

void ULevelUpWidget::SpeedUp()
{
	float newMoveSpeed = currentPlayer->moveSpeed + 100;
	currentPlayer->SetMovementSpeed(newMoveSpeed);
}

void ULevelUpWidget::BulletDmgUp()
{
	float newBulletDmg = currentPlayer->bulletDmg + 30;
	currentPlayer->SetBulletDmg(newBulletDmg);
	
}

void ULevelUpWidget::BulletSpeedUp()
{
	float newBulletSpeed = currentPlayer->bulletSpeed + 100;
	currentPlayer->SetBulletSpeed(newBulletSpeed);
	
}

void ULevelUpWidget::FireRateUp()
{
	if (currentPlayer->newFireRate - 0.3 >= 0.1)
	{
		currentPlayer->newFireRate -= 0.3;
	}
	else
	{
		currentPlayer->newFireRate = 0.1;
	}
}


