// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"


//사용할 상태 정의
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VAMPIREPROJECT_API UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	//상태 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	EEnemyState mState = EEnemyState::Idle;

	//대기 상태
	void IdleState();
	//이동 상태
	void MoveState();
	//공격 상태
	void AttackState();
	//피격 상태
	void DamageState();
	//죽음 상태
	void DieState();

	//대기 시간
	UPROPERTY(EditDefaultsOnly, Category = FSM)
	float idleDelayTime = 0.1f;
	//경과 시간
	float currentTime = 0;

	//공격 범위
	UPROPERTY(EditAnywhere, Category = FSM)
	float attackRange = 120.0f;

	//공격 대기 시간
	UPROPERTY(EditAnywhere, Category = FSM)
	float attackDelayTime = 0.2f;

	//피격시 대기 시간
	UPROPERTY(EditAnywhere, Category = FSM)
	float damageDelayTime = 0.2f;



public:
	//플레이어
	UPROPERTY(VisibleAnywhere, Category = FSM)
	class APlayerCharacter* player;

	//AI 소유 액터
	UPROPERTY()
	class AEnemy* owner;

	UPROPERTY()
	class UEnemyStatData* statData;

	UPROPERTY()
	class UEnemyAnim* anim;

	UPROPERTY()
	class AAIController* ai;


public:
	//피격 알림 이벤트 함수
	void OnDamageProcess(float damgage);


public:
	UPROPERTY()
	class AVampireGameState* gameState;


	void InitEnemyStat(int kind);


private:
	bool bScoreDone = false;
		
};
