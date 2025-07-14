// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"

#include "PlayerCharacter.h"

#include "Animation/AnimMontage.h"

UPlayerAnim::UPlayerAnim()
{
	/*
	ConstructorHelpers::FObjectFinder<UAnimMontage>temp_Montage(TEXT("/Script/Engine.AnimMontage'/Game/Player/Animation/NoWeapon/Player_AnimMontage.Player_AnimMontage'"));
	if (temp_Montage.Succeeded())
	{
		animMontage = temp_Montage.Object;
	}
	else
	{
		exit(1);
	}
	*/
}

void UPlayerAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	auto ownerPawn = TryGetPawnOwner();
	player = Cast<APlayerCharacter>(ownerPawn);
}

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
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


void UPlayerAnim::AnimNotify_DieDone()
{
	player->PlayerDied();
}

void UPlayerAnim::PlayAttackAnim()
{
	
	if (defaultMontage != NULL)
	{
		Montage_Play(defaultMontage);
		Montage_JumpToSection(TEXT("Attack"), defaultMontage);

		//UE_LOG(LogTemp, Warning, TEXT("PlayRate : %2.1f"), Montage_GetPlayRate(animMontage));
		//UE_LOG(LogTemp, Warning, TEXT("Current Section : %s"), *(Montage_GetCurrentSection(animMontage).ToString()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("defaultMontage is NULL!!!"));
	}
	
}

void UPlayerAnim::PlayDamageAnim()
{
	if (defaultMontage != NULL)
	{
		Montage_Play(defaultMontage);
		Montage_JumpToSection(TEXT("Damage"), defaultMontage);
		//UE_LOG(LogTemp, Warning, TEXT("PlayRate : %2.1f"), Montage_GetPlayRate(animMontage));
		//UE_LOG(LogTemp, Warning, TEXT("Current Section : %s"), *(Montage_GetCurrentSection(animMontage).ToString()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("defaultMontage is NULL!!!"));
	}
}

void UPlayerAnim::PlayDieAnim()
{
	if (dieMontage != NULL)
	{
		Montage_Stop(0, defaultMontage);
		Montage_Play(dieMontage);
		Montage_JumpToSection(TEXT("Die"), dieMontage);

		//UE_LOG(LogTemp, Warning, TEXT("PlayRate : %2.1f"), Montage_GetPlayRate(animMontage));
		//UE_LOG(LogTemp, Warning, TEXT("Current Section : %s"), *(Montage_GetCurrentSection(animMontage).ToString()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("dieMontage is NULL!!!"));
	}
		
	
}
