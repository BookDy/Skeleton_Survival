// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnim.h"
#include "Enemy.h"




void UEnemyAnim::NativeInitializeAnimation()
{
	auto ownerPawn = TryGetPawnOwner();
	enemy = Cast<AEnemy>(ownerPawn);
}

void UEnemyAnim::OnEndAttackAnimation()
{
	bAttackPlay = false;
}

void UEnemyAnim::SetMoveAnimSpeed(float newMoveAnimSpeed)
{
	moveAnimSpeed = newMoveAnimSpeed;
}

void UEnemyAnim::AnimNotify_HitCheck()
{
	enemy->HitCheck();
}

void UEnemyAnim::ChangeDamageAnimSpeed(float newDamageSpeed)
{
	damageAnimSpeed = newDamageSpeed;
}
