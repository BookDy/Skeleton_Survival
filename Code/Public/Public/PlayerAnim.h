// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIREPROJECT_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	float speed = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	float direction = 0;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	UPlayerAnim();


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	class UAnimMontage* dieMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	class UAnimMontage* defaultMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = PlayerAnim)
	class APlayerCharacter* player;

public:
	UFUNCTION()
	void AnimNotify_DieDone();
	
	void PlayAttackAnim();
	
	void PlayDamageAnim();

	void PlayDieAnim();

	

	
};
