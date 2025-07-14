// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStatData.h"

// Sets default values for this component's properties
UEnemyStatData::UEnemyStatData()
{
	SetDefaultStat();
}

void UEnemyStatData::SetDefaultStat()
{
	enemyHealth = 50;
	enemyDamage = 10;
	enemyExp = 30;
	enemyMoveSpeed = 100;
	enemyMoveAnimSpeed = 1;
	enemyAttackSpeed = 1;
	enemyDamageDelayTime = 1.2f;
	
}

void UEnemyStatData::SetHeavyStat()
{
	enemyHealth = 80;
	enemyDamage = 15;
	enemyExp = 50;
	enemyMoveSpeed = 50;
	enemyMoveAnimSpeed = 0.5;
	enemyAttackSpeed = 0.7;
	enemyDamageDelayTime = 1.5f;
}

void UEnemyStatData::SetFastStat()
{
	enemyHealth = 30;
	enemyDamage = 8;
	enemyExp = 40;
	enemyMoveSpeed = 200;
	enemyMoveAnimSpeed = 1.5;
	enemyAttackSpeed = 1.3;
	enemyDamageDelayTime = 1.0f;
}

