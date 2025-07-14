// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSoundComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPlayerSoundComponent::UPlayerSoundComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UPlayerSoundComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UPlayerSoundComponent::PlayPlayerHitedSound()
{
	int randIndex = FMath::RandRange(0, 1);

	switch (randIndex)
	{
	case 0 :
		if (playerHitedSound1)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), playerHitedSound1);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("playerHitedSound1 is Missing!"));
		}

		break;

	case 1:
		if (playerHitedSound2)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), playerHitedSound2);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("playerHitedSound2 is Missing!"));
		}
		break;

	default:
		UE_LOG(LogTemp, Error, TEXT("PlayPlayerHitedSound RandRange is failed"));
	}
}


void UPlayerSoundComponent::PlayPlayerFireSound()
{
	if (playerFireSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), playerFireSound);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("playerFireSound is Missing!"));
	}
}

void UPlayerSoundComponent::PlayPlayerDeadSound()
{
	if (playerDeadSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), playerDeadSound);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("playerDeadSound is Missing!"));
	}
}