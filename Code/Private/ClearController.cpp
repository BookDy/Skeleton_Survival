// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearController.h"
#include "VPClearWidget.h"


void AClearController::BeginPlay()
{
	Super::BeginPlay();

	if (clearUIWidget != NULL)
	{
		clearUIWidget->bIsFocusable = true;
		clearUIWidget->AddToViewport();

		FInputModeUIOnly Mode;
		Mode.SetWidgetToFocus(clearUIWidget->GetCachedWidget());
		SetInputMode(Mode);
		bShowMouseCursor = true;
	}
}
