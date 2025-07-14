// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyFSM.h"
#include "EnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIREPROJECT_API UEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=FSM)
	EEnemyState animState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=FSM)
	bool bAttackPlay = false;

	UFUNCTION(BlueprintCallable, Category=FSMEvent)
	void OnEndAttackAnimation();
	
	UFUNCTION(BlueprintImplementableEvent, Category =FSMEvent)
	void PlayDamageAnim(FName sectionName);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	bool bDieDone = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	bool bDamageDone = false;


	void SetMoveAnimSpeed(float newMoveAnimSpeed);

public:
	UPROPERTY(VisibleAnywhere, Category ="Notify")
	class AEnemy* enemy;

	UFUNCTION()
	void AnimNotify_HitCheck();

	void ChangeDamageAnimSpeed(float newSpeed);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	float attackSpeed = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MoveAnim)
	float moveAnimSpeed = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DamagaeAnim)
	float damageAnimSpeed = 1.0f;
};
