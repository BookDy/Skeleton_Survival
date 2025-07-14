// Fill out your copyright notice in the Description page of Project Settings.


#include "VPClearWidget.h"
#include "Kismet/GameplayStatics.h"
#include "VPGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UVPClearWidget::NativeConstruct()
{

	Super::NativeConstruct();

	tempInstance = Cast<UVPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	currentTimeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_ClearTime")));
	bestTimeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_BestTime")));
	totitleBT = Cast<UButton>(GetWidgetFromName(TEXT("BT_ToTitle")));
	
	if (tempInstance)
	{
		currentTimeText->SetText(FText::FromString(FString::Printf(TEXT("Clear Time : %d"), tempInstance->GetCurrentTime())));
		bestTimeText->SetText(FText::FromString(FString::Printf(TEXT("Best  Time : %d"), tempInstance->GetBestTime())));
	}

	totitleBT->OnClicked.AddDynamic(this, &UVPClearWidget::OntotitleBT_Clicked);

}

void UVPClearWidget::OntotitleBT_Clicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}
