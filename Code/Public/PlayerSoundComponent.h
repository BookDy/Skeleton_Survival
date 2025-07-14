// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerSoundComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAMPIREPROJECT_API UPlayerSoundComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerSoundComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void PlayPlayerHitedSound();

	void PlayPlayerDeadSound();

	void PlayPlayerFireSound();


private:
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* playerHitedSound1;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* playerHitedSound2;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* playerDeadSound;
	
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* playerFireSound;

		
};
