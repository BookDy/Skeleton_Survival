// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class VAMPIREPROJECT_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, Category = SceneComponent)
	class USceneComponent* rootSceneComponent;

	//스폰 위치 정보 배열
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnSetting)
	TArray<class AActor*> spawnPoints;

	//AEnemy타입의 블루프린트 할당
	UPROPERTY(EditAnywhere, Category = SpawnSetting)
	TSubclassOf<class AEnemy> enemyFactory;

private:
	//스폰 랜덤 시간 최솟값
	UPROPERTY(EditAnywhere, Category = SpawnSetting)
	float minTime = 1;

	//스폰 랜덤 시간 최댓값
	UPROPERTY(EditAnywhere, Category = SpawnSetting)
	float maxTime = 3;

	//스폰 타이머
	FTimerHandle spawnTimerHandle;

public:
	//적 생성 함수
	void CreateEnemy();

	void InitspawnEnemyCount();

	void killzoneDead();


	void InitSpawnPoints();

	void ResetInitTimer();

	void SetPoints();

public:
	UPROPERTY()
	class AVampireGameState* gameState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = SpawnTriggerVoulme)
	class AActor* spawnTriggerVolume;

private:
	UPROPERTY(VisibleAnywhere, Category = Player)
	class APlayerCharacter* player;

	UPROPERTY()
	int spawnEnemyCount = 0;

	float initTimer = 0;

	float spinTime = 0;

	float spinThreshold = 1.0f;

};
