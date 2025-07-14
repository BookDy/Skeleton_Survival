// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChangedDelegate);


UENUM(BlueprintType)
enum class EEnemyType : uint8
{
	Default UMETA(DisplayName = "DefaultSkeleton"),
	Heavy UMETA(DisplayName = "HeavySkeleton"),
	Fast UMETA(DisplayName = "FastSkeleton")
};

UCLASS()
class VAMPIREPROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//AI 관리 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSMComponent)
	class UEnemyFSM* fsm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StatComponent)
	class UEnemyStatData* statData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SoundComponent)
	class UEnemySoundComponent* soundComponent;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float maxHealth = 50;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float currentHealth = 50;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float enemyDamage = 10;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float enemyExp = 30;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	float enemyMoveSpeed = 100;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	float enemyAttackSpeed = 1;

	void ChangeStat(int kind);
	//속도 변경
	void ChangeSpeed();

	void ChangeDamageDelay(float newDelay);

	//데미지
	void OnDamage(float damage);

	void HitCheck();

	float GetHpRatio();

	void GiveExp(class APlayerCharacter* player);

	void SetEnemyManager(class AEnemyManager* newEnemyManager);

	void Dispawn();

private:
	UPROPERTY(VisibleAnywhere, Category = EnemyManager)
	class AEnemyManager* enemyManager;


public:
	UPROPERTY(VisibleAnywhere, Category = SpringComp)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditDefaultsOnly, Category = UIComponent)
	class UWidgetComponent* hpWidget;

	FOnHpChangedDelegate OnHpChange;

	UPROPERTY(EditDefaultsOnly, Category = SkeletalMesh)
	class USkeletalMesh* defaultEnemySkeleton;

	UPROPERTY(EditDefaultsOnly, Category = SkeletalMesh)
	class USkeletalMesh* heavyEnemySkeleton;

	UPROPERTY(EditDefaultsOnly, Category = SkeletalMesh)
	class USkeletalMesh* fastEnemySkeleton;

	UPROPERTY(EditDefaultsOnly, Category = Material)
	class UMaterial* defaultEnemyMaterial;

	UPROPERTY(EditDefaultsOnly, Category = Material)
	class UMaterial* fastEnemyMaterial;






	void SetEnemyType(EEnemyType type);

	EEnemyType GetEnemyType();



private:
	UPROPERTY(EditDefaultsOnly, Category = "EnemyType")
	EEnemyType enemyType;

};
