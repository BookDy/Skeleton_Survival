// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "PlayerCharacter.h"


void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	auto ownerPawn = TryGetPawnOwner();
	player = Cast<APlayerCharacter>(ownerPawn);
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (player)
	{
		FVector velocity = player->GetVelocity();
		FVector forwardVector = player->GetActorForwardVector();
		speed = FVector::DotProduct(forwardVector, velocity);

		FVector rightVector = player->GetActorRightVector();
		direction = FVector::DotProduct(rightVector, velocity);

	}
}


void UPlayerAnimInstance::PlayAttackAnim()
{

	if (attackAnimMontage != NULL)
	{
		Montage_Play(attackAnimMontage);
	}

}

void UPlayerAnimInstance::PlayDamageAnim()
{
	if (damageAnimMontage != NULL)
	{
		Montage_JumpToSection(TEXT("Damage"), damageAnimMontage);
		Montage_Play(damageAnimMontage);
	}
}

void UPlayerAnimInstance::PlayDieAnim()
{
	if (damageAnimMontage != NULL)
	{
		Montage_JumpToSection(TEXT("Die"), damageAnimMontage);
		Montage_Play(damageAnimMontage);
	}


}

