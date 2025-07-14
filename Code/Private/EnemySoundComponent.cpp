// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySoundComponent.h"

#include "Enemy.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEnemySoundComponent::UEnemySoundComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UEnemySoundComponent::BeginPlay()
{
	Super::BeginPlay();


	owner = Cast<AEnemy>(GetOwner());
	if (owner != NULL)
	{
		owner->OnHpChange.AddUObject(this, &UEnemySoundComponent::PlayHitSound);
	}
	
}

void UEnemySoundComponent::PlayHitSound()
{
	if (owner != NULL)
	{
		if (owner->currentHealth > 0)
		{
			EEnemyType temp = owner->GetEnemyType();
			switch (temp)
			{
			case EEnemyType::Default :
				if (defaultHitSound != NULL)
				{
					UGameplayStatics::PlaySoundAtLocation(this, defaultHitSound, owner->GetActorLocation());
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Skeleton's defaultHitSound Missing"));
				}
				break;

			case EEnemyType::Heavy :
				if (heavyHitSound != NULL)
				{
					UGameplayStatics::PlaySoundAtLocation(this, heavyHitSound, owner->GetActorLocation());
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Skeleton's heavyHitSound Missing"));
				}
				break;

			case EEnemyType::Fast :
				if (fastHitSound != NULL)
				{
					UGameplayStatics::PlaySoundAtLocation(this, fastHitSound, owner->GetActorLocation());
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Skeleton's fastHitSound Missing"));
				}
				break;
				
			default :
				if (defaultHitSound != NULL)
				{
					UGameplayStatics::PlaySoundAtLocation(this, defaultHitSound, owner->GetActorLocation());
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Skeleton's defaultHitSound Missing"));
				}
				break;
			}
		}
		else
		{
			if (deadSound != NULL)
			{
				UGameplayStatics::PlaySoundAtLocation(this, deadSound, owner->GetActorLocation());
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Skeleton's deadSound Missing"));
			}
		}
	}
	
}


