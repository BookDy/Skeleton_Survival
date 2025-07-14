// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleUIPlayerController.h"
#include "Blueprint/UserWidget.h"

void ATitleUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (titleUIWidget != NULL)
	{
		titleUIWidget->bIsFocusable = true;
		titleUIWidget->AddToViewport();
		
		FInputModeUIOnly Mode;
		Mode.SetWidgetToFocus(titleUIWidget->GetCachedWidget());
		SetInputMode(Mode);
		bShowMouseCursor = true;
	}
}
