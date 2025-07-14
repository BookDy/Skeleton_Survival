// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


}

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BT_Restart = Cast<UButton>(GetWidgetFromName(TEXT("BT_Restart")));
	BT_ToTitle = Cast<UButton>(GetWidgetFromName(TEXT("BT_ToTitle")));

	if (BT_Restart == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("BT_Restart can't find"));
	}
	BT_Restart->OnClicked.AddDynamic(this, &UGameOverWidget::RestartClicked);
	BT_ToTitle->OnClicked.AddDynamic(this, &UGameOverWidget::ToTitleClicked);
}

void UGameOverWidget::RestartClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("RestartClicked"));
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("PlayGround"));
}

void UGameOverWidget::ToTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}
