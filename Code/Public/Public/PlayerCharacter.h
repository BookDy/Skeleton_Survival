// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnExpChangedDelegate);

UCLASS()
class VAMPIREPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* camComp;

	class APlayerController* playerController;


public:
	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputMappingContext* imc;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ia_Move;

	FVector direction = FVector::ZeroVector;

	void Move(const struct FInputActionValue& inputValue);


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	class USkeletalMeshComponent* gunComp;

	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
	TSubclassOf<class ABullet> bulletFactory;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	class UInputAction* ia_Fire;

	UFUNCTION()
	void InputFire(const struct FInputActionValue& inputValue);



public:
	//스탯
	UPROPERTY(VisibleAnywhere, Category = Stat)
	float currentHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float maxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float healthRegen = 10;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float maxExp;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float currentExp;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float moveSpeed = 200;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float bulletDmg = 50;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float bulletSpeed = 200;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float fireRate = 1.5;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float newFireRate = 1.5;

	FTimerHandle bulletTimerHandle;

	bool canFire = true;


	FTimerHandle hitedReactionTimerHandle;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float hitedReactionTime = 0.2f;

	bool canHit = true;

	

	void CanFireOn();


	void InitStat();

	void Hited(float damage);

	void HitedReaction();

	void HitedReactionEnd();

	void SetMaxHp(float newMaxHp);

	void SetMaxExp(float newMaxExp);

	void SetMovementSpeed(float newMovementSpeed);

	void SetBulletSpeed(float newBulletSpeed);

	void SetBulletDmg(float newBulletDmg);

	void SetFireRate(float newfireRate);

	void SetHealthRegen(float newHealthRegen);

	void SetHp(float newHp);

	void SetExp(float newExp);

	float GetHPRatio();

	float GetExpRatio();



public:
	/*
	UPROPERTY(EditDefaultsOnly, Category = Sound)
	class USoundBase* bulletSound;
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Niagara)
	class UNiagaraComponent* gunNiagaraComp;



public:
	UPROPERTY(EditDefaultsOnly, Category = UIComponent)
	class UWidgetComponent* HPBarWidget;

	UPROPERTY(EditDefaultsOnly, Category = UIComponent)
	class UCharacterWidget* characterWidget;

	FOnHPChangedDelegate OnHPChange;
	FOnExpChangedDelegate OnExpChange;


protected:
	void HpRegen();
private:
	float hpRegenTime = 0;

	class UPlayerAnim* anim;


public:

	UPROPERTY(EditDefaultsOnly, Category = WaveAndScoreUI)
	class UWaveAndScroeWidget* waveAndScoreWidget;

	UPROPERTY(EditDefaultsOnly, Category = LevelUpUI)
	class ULevelUpWidget* levelUpWidget;

	UPROPERTY(EditDefaultsOnly, Category = GameOverUI)
	class UGameOverWidget* gameOverWidget;

	UPROPERTY(EditDefaultsOnly, Category = GameClearUI)
	class UGameClearWidget* gameClearWidget;

	void LevelUp();

	void LevelUpEnd();

	void PlayerDied();

	void GameClear();

	void ChangeInputMode(bool bGameMode = true);

	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;

private:
	UPROPERTY(EditDefaultsOnly, Category = SoundComponent)
	class UPlayerSoundComponent* playerSoundComponent;

	bool isPlayerDead = false;

};
