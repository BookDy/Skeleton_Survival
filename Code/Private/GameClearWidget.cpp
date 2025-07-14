// Fill out your copyright notice in the Description page of Project Settings.


#include "GameClearWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameClearWidget::NativeConstruct()
{
	Super::NativeConstruct();

	BT_Totitle = Cast<UButton>(GetWidgetFromName(TEXT("BT_ToTitle")));
	BT_Exit = Cast<UButton>(GetWidgetFromName(TEXT("BT_Exit")));

	BT_Totitle->OnClicked.AddDynamic(this, &UGameClearWidget::ToTitleClicked);
	BT_Exit->OnClicked.AddDynamic(this, &UGameClearWidget::ExitClicked);
}

void UGameClearWidget::ToTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void UGameClearWidget::ExitClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
