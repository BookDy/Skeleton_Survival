// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnActor.generated.h"

UCLASS()
class VAMPIREPROJECT_API ASpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnActor();

	UPROPERTY()
	class UBoxComponent* boxComponent;

	UPROPERTY()
	class UStaticMeshComponent* cubeComponent;

};
