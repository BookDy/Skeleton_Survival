// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicManager.h"

#include "Components/AudioComponent.h"

// Sets default values
AMusicManager::AMusicManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	gameBGMComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BGM Component"));
	gameBGMComponent->bIsUISound = true;

}

// Called when the game starts or when spawned
void AMusicManager::BeginPlay()
{
	Super::BeginPlay();
	
}

