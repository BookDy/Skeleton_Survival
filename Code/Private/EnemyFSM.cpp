// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"

#include "EnemyStatData.h"

#include "PlayerCharacter.h"
#include "Enemy.h"
#include <Kismet/GameplayStatics.h>
#include "EnemyAnim.h"

#include "AIController.h"

#include "Components/CapsuleComponent.h"

#include "VampireGameState.h"

// Sets default values for this component's properties
UEnemyFSM::UEnemyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	bScoreDone = false;

	// ...

	//월드에서 PlayerCharacter 액터 찾기
	auto actor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	//캐스팅
	player = Cast<APlayerCharacter>(actor);

	if (player == NULL)
	{
		owner->Dispawn();
	}

	//소유 객체 가져오기
	owner = Cast<AEnemy>(GetOwner());
	
	anim = Cast<UEnemyAnim>(owner->GetMesh()->GetAnimInstance());

	ai = Cast<AAIController>(owner->GetController());

	gameState = Cast<AVampireGameState>(GetWorld()->GetGameState());
	if (gameState)
	{
		InitEnemyStat(0);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyFSM can't get GameState"));
	}
}


// Called every frame
void UEnemyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	switch (mState)
	{
	case EEnemyState::Idle:
		IdleState();
		break;

	case EEnemyState::Move:
		MoveState();
		break;

	case EEnemyState::Attack:
		AttackState();
		break;

	case EEnemyState::Damage:
		DamageState();
		break;

	case EEnemyState::Die:
		DieState();
		break;
	}
}

void UEnemyFSM::IdleState()
{
	//시간 흐름
	currentTime += GetWorld()->DeltaTimeSeconds;
	//경과 시간이 대기 시간 초과시
	if (currentTime > idleDelayTime)
	{
		//이동 상태 전환
		mState = EEnemyState::Move;
		//경과 시간 초기화
		currentTime = 0;

		anim->animState = mState;
	}
	
}

void UEnemyFSM::MoveState()
{
	//타깃 목적지
	FVector destination = player->GetActorLocation();
	//방향 구하기
	FVector dir = destination - owner->GetActorLocation();
	///방향으로 이동
	//owner->AddMovementInput(dir.GetSafeNormal());
	ai->MoveToLocation(destination);

	//공격 범위에 들어오면 상태 전환
	if (dir.Size() < attackRange)
	{
		mState = EEnemyState::Attack;

		anim->animState = mState;
		anim->bAttackPlay = true;
		currentTime = attackDelayTime;
	}
}

void UEnemyFSM::AttackState()
{

	ai->StopMovement();

	//시간 경과
	currentTime += GetWorld()->DeltaTimeSeconds;
	//공격 시간인가?
	if (currentTime > attackDelayTime)
	{
		//공격
		//경과 시간 초기화
		currentTime = 0;
		anim->bAttackPlay = true;
	}

	if (anim->bAttackPlay == false)
	{
		//플레이어와 거리 구하기
		float distance = FVector::Distance(player->GetActorLocation(), owner->GetActorLocation());
		//공격범위와 거리 비교
		if (distance > attackRange)
		{
			//이동 상태로 변환
			mState = EEnemyState::Move;
			anim->animState = mState;
		}
	}
	
}

void UEnemyFSM::DamageState()
{
	/*
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > damageDelayTime)
	{
		mState = EEnemyState::Idle;
		currentTime = 0;
		anim->animState = mState;
	}
	ai->StopMovement();
	*/
	ai->StopMovement();

	if (anim->bDamageDone == true)
	{
		mState = EEnemyState::Idle;
		anim->animState = mState;
		anim->bDamageDone = false;
	}
}

void UEnemyFSM::DieState()
{
	ai->StopMovement();

	if (gameState != NULL && bScoreDone == false && player != NULL)
	{
		bScoreDone = true;
		owner->GiveExp(player);
		
		
		//gameState->GainScore(); -> EliminateEnemy 다음에 실행하도록 설정
		
	}
	
	if (anim->bDieDone == false)
	{
		return;
	}
	owner->Destroy();
	gameState->EliminateEnemy();
	
	
	
	
}

void UEnemyFSM::OnDamageProcess(float damage)
{
	if (owner)
	{
		owner->OnDamage(damage);

		if (owner->currentHealth > 0)
		{
			mState = EEnemyState::Damage;

			currentTime = 0;

			FString sectionName = FString::Printf(TEXT("Damage"));
			anim->PlayDamageAnim(FName(sectionName));
		}
		else
		{
			mState = EEnemyState::Die;

			owner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			
			anim->ChangeDamageAnimSpeed(1.0f);
			FString sectionName = FString::Printf(TEXT("Die"));
			anim->PlayDamageAnim(FName(sectionName));
		}

		anim->animState = mState;
	}
	
}

void UEnemyFSM::InitEnemyStat(int kind)
{
	int waveCount = gameState->GetWaveCount();
	statData = owner->statData;
	switch (kind)
	{
	case 0:
		statData->SetDefaultStat();
		anim->SetMoveAnimSpeed(statData->enemyMoveAnimSpeed);
		break;
	case 1:
		statData->SetHeavyStat();
		anim->SetMoveAnimSpeed(statData->enemyMoveAnimSpeed);
		break;
	case 2:
		statData->SetFastStat();
		anim->SetMoveAnimSpeed(statData->enemyMoveAnimSpeed);
		break;
	default:
		statData->SetDefaultStat();
		anim->SetMoveAnimSpeed(statData->enemyMoveAnimSpeed);

	}
	

	owner->maxHealth = statData->enemyHealth + 50 * (waveCount-1);
	owner->currentHealth = owner->maxHealth;
	owner->enemyDamage = statData->enemyDamage + 20 * (waveCount-1);
	owner->enemyExp = statData->enemyExp + 10 * waveCount;
	owner->enemyMoveSpeed = statData->enemyMoveSpeed + 60 * (waveCount-1);
	owner->ChangeSpeed();
	anim->attackSpeed = statData->enemyAttackSpeed + (waveCount-1) * 0.2;
	anim->ChangeDamageAnimSpeed(statData->enemyDamageDelayTime + (waveCount -1) * 0.15f);

}

