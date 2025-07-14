// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone.h"

#include "Enemy.h"

#include "PlayerCharacter.h"

#include "Components/BoxComponent.h"

// Sets default values
AKillZone::AKillZone()
{
	killCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("KillZoneCollision"));
	killCollision->SetCollisionProfileName(TEXT("OverlapAll"));
	RootComponent = killCollision;

	killFloor = CreateDefaultSubobject<UBoxComponent>(TEXT("KillFloor"));
	killFloor->SetCollisionProfileName(TEXT("BlockAll"));
	killFloor->SetupAttachment(killCollision);
	killFloor->SetRelativeLocation(FVector(0, 0, -100));
	
}

void AKillZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (AEnemy* tempEnemy = Cast<AEnemy>(OtherActor))
	{
		tempEnemy->Dispawn();
	}
	else if(APlayerCharacter* tempPlayer = Cast<APlayerCharacter>(OtherActor))
	{
		tempPlayer->PlayerDied();
	}
}

// Called when the game starts or when spawned
void AKillZone::BeginPlay()
{
	Super::BeginPlay();
	
	killCollision->OnComponentBeginOverlap.AddDynamic(this, &AKillZone::OnOverlapBegin);
	
}
