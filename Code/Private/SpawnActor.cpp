// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	boxComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	RootComponent = boxComponent;
	
	cubeComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	cubeComponent->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh>CubeMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (CubeMesh.Succeeded())
	{
		cubeComponent->SetStaticMesh(CubeMesh.Object);
	}

}



