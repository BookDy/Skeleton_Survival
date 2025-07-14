// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

#include "Enemy.h"

#include "VampireGameState.h"
#include "Kismet/GameplayStatics.h"

#include "PlayerCharacter.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bTickEvenWhenPaused = true;

	spawnEnemyCount = 0;
	initTimer = 0;
	
	rootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = rootSceneComponent;

	
	
	
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	gameState = Cast<AVampireGameState>(GetWorld()->GetGameState());

	if (gameState)
	{
		gameState->OnWaveChange.AddUObject(this, &AEnemyManager::CreateEnemy);
		gameState->OnWaveEnd.AddUObject(this, &AEnemyManager::InitspawnEnemyCount);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyManager can't get GameState"));
	}

	player = (APlayerCharacter*)(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (player == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't Find player"));
	}

	InitSpawnPoints();
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	spinTime += GetWorld()->DeltaTimeSeconds;
	if (spinTime> spinThreshold)
	{
		//SetActorRelativeRotation(FRotator(0, 10, 0));
		SetActorLocation(player->GetActorLocation());
		SetPoints();
		spinTime = 0;
	}
	

}

void AEnemyManager::CreateEnemy()
{
	if (spawnEnemyCount < gameState->GetMaxEnemyNumber())
	{
		if (initTimer > 0.001)
		{
			//랜덤 위치 정하기
			int index = FMath::RandRange(0, spawnPoints.Num() - 1);
			//적 종류 배치
			int kind = FMath::RandRange(0, 3);
			/*
			//적 생성 및 배치
			AEnemy* tempEnemy = GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnPoints[index]->GetActorLocation(), FRotator(FRotator::ZeroRotator));
			*/
			if (spawnTriggerVolume)
			{
				if (spawnPoints[index]->IsOverlappingActor(spawnTriggerVolume))
				{
					AEnemy* tempEnemy = GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnPoints[index]->GetActorLocation(), FRotator(FRotator::ZeroRotator));
					tempEnemy->ChangeStat(kind);
					tempEnemy->SetEnemyManager(this);
					spawnEnemyCount++;
					SetPoints();
				}
				else
				{
					UE_LOG(LogTemp, Display, TEXT("not in triggerVolume"));
					SetPoints();
					GetWorld()->GetTimerManager().ClearTimer(spawnTimerHandle);
					//타임 매니저 등록
					GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, 0.1f);
	
					return;
				}
				
			}
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%f"), initTimer);
			initTimer += GetWorld()->GetDeltaSeconds();
	
		}

		//랜덤시간 생성
		float createTime = FMath::RandRange(minTime, maxTime);
		//타임 매니저 등록
		GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);
		return;
	}
	
	
	/*
	if (spawnEnemyCount < gameState->GetMaxEnemyNumber())
	{
		//랜덤시간 생성
		float createTime = FMath::RandRange(minTime, maxTime);
		//타임 매니저 등록
		GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::CreateEnemy, createTime);
	}
	*/

}

void AEnemyManager::InitspawnEnemyCount()
{
	spawnEnemyCount = 0;
	ResetInitTimer();
}

void AEnemyManager::killzoneDead()
{
	spawnEnemyCount--;
	CreateEnemy();
}

void AEnemyManager::InitSpawnPoints()
{
	SetActorLocation(player->GetActorLocation());

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("SpawnPoints"), spawnPoints);
	
	if (spawnPoints.Num() != 4)
	{
		UE_LOG(LogTemp, Error, TEXT("Spawnpoints are not 4, try search again"));
		//InitSpawnPoints();
		GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyManager::InitSpawnPoints, 1.0f);
	}

	TArray<AActor*> tempVolumeArray;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("SpawnVolume"), tempVolumeArray);
	spawnTriggerVolume = tempVolumeArray[0];

	if (spawnTriggerVolume == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnTriggerVolume not Found try search again"));
		InitSpawnPoints();
	}

	SetPoints();
}

void AEnemyManager::ResetInitTimer()
{
	initTimer = 0;
}

void AEnemyManager::SetPoints()
{
	
	FVector managerLocation = GetActorLocation();
	int MinusX, MinusY, PlusX, PlusY;

	MinusX = FMath::RandRange(-400, -200);
	MinusY = FMath::RandRange(-400, -200);
	PlusX = FMath::RandRange(200, 400);
	PlusY = FMath::RandRange(200, 400);
	//spawnPoints[0]->SetActorLocation(managerLocation + FVector(-200, -200, 10));
	//spawnPoints[1]->SetActorLocation(managerLocation + FVector(200, -200, 10));
	//spawnPoints[2]->SetActorLocation(managerLocation + FVector( - 200, 200, 10));
	//spawnPoints[3]->SetActorLocation(managerLocation + FVector(200, 200, 10));
	
	spawnPoints[0]->SetActorLocation(managerLocation + FVector(MinusX, MinusY, 10));
	spawnPoints[1]->SetActorLocation(managerLocation + FVector(PlusX, MinusY, 10));
	spawnPoints[2]->SetActorLocation(managerLocation + FVector(MinusX, PlusY, 10));
	spawnPoints[3]->SetActorLocation(managerLocation + FVector(PlusX, PlusY, 10));


}
