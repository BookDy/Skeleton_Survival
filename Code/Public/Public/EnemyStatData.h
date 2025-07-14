// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyStatData.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAMPIREPROJECT_API UEnemyStatData : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyStatData();
	
	void SetDefaultStat();

	void SetHeavyStat();

	void SetFastStat();

	UPROPERTY(EditDefaultsOnly, Category = Stat)
	float enemyHealth;

	UPROPERTY(EditDefaultsOnly, Category = Stat)
	float enemyDamage;

	UPROPERTY(EditDefaultsOnly, Category = Stat)
	float enemyExp;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float enemyMoveSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float enemyAttackSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float enemyMoveAnimSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Damage)
	float enemyDamageDelayTime;


		
};
