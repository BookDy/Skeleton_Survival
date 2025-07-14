// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemySoundComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAMPIREPROJECT_API UEnemySoundComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemySoundComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	void PlayHitSound();

private:
	UPROPERTY(VisibleAnywhere, Category = owner)
	class AEnemy* owner;

	UPROPERTY(EditDefaultsOnly, Category = HitSound)
	class USoundBase* defaultHitSound;

	UPROPERTY(EditDefaultsOnly, Category = HitSound)
	class USoundBase* heavyHitSound;

	UPROPERTY(EditDefaultsOnly, Category = HitSound)
	class USoundBase* fastHitSound;

	UPROPERTY(EditDefaultsOnly, Category = HitSound)
	class USoundBase* deadSound;
		
};
