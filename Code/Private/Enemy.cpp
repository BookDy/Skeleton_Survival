// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "EnemyFSM.h"

#include "EnemyManager.h"

#include "EnemySoundComponent.h"

#include "Engine/SkeletalMesh.h"

#include "Materials/Material.h"

#include "EnemyStatData.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "PlayerCharacter.h"

#include "DrawDebugHelpers.h"

#include "GameFramework/SpringArmComponent.h"

#include "Components/WidgetComponent.h"
#include "EnemyWidget.h"






// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (GetMesh() != NULL)
	{
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
	}
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = enemyMoveSpeed;

	fsm = CreateDefaultSubobject<UEnemyFSM>(TEXT("FSM"));

	statData = CreateDefaultSubobject<UEnemyStatData>(TEXT("StatData"));

	soundComponent = CreateDefaultSubobject<UEnemySoundComponent>(TEXT("SoundComponent"));

	GetMesh()->SetSkeletalMesh(defaultEnemySkeleton);
	GetMesh()->SetMaterial(0, defaultEnemyMaterial);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeRotation(FRotator(0, 0, 0));
	springArmComp->TargetArmLength = 0;
	springArmComp->bUsePawnControlRotation = false;
	springArmComp->bDoCollisionTest = false;
	springArmComp->bInheritPitch = false;
	springArmComp->bInheritRoll = false;
	springArmComp->bInheritYaw = false;

	hpWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("UIComponent"));
	hpWidget->SetupAttachment(springArmComp);
	hpWidget->SetRelativeLocation(FVector(-80.0f, 0.0f, 0.0f));
	hpWidget->SetWidgetSpace(EWidgetSpace::Screen);
	hpWidget->SetDrawSize(FVector2D(150.0f, 50.0f));



	enemyType = EEnemyType::Default;


}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	auto enemyWidget = Cast<UEnemyWidget>(hpWidget->GetUserWidgetObject());
	if (enemyWidget != NULL)
	{
		enemyWidget->BindEnemy(this);
	}


}

void AEnemy::ChangeStat(int kind)
{
	fsm->InitEnemyStat(kind);
	switch(kind)
	{
	case 0 :
		if (defaultEnemySkeleton != NULL && defaultEnemyMaterial != NULL)
		{
			GetMesh()->SetSkeletalMesh(defaultEnemySkeleton);
			GetMesh()->SetMaterial(0, defaultEnemyMaterial);
			SetEnemyType(EEnemyType::Default);
			break;
		}
	case 1 :
		if (heavyEnemySkeleton != NULL && defaultEnemyMaterial != NULL)
		{
			GetMesh()->SetSkeletalMesh(heavyEnemySkeleton);
			GetMesh()->SetMaterial(0, defaultEnemyMaterial);
			SetEnemyType(EEnemyType::Heavy);
			break;
		}
		
	case 2 :
		if (fastEnemySkeleton != NULL && fastEnemyMaterial != NULL)
		{
			GetMesh()->SetSkeletalMesh(fastEnemySkeleton);
			GetMesh()->SetMaterial(0, fastEnemyMaterial);
			SetEnemyType(EEnemyType::Fast);
			break;
		}
		
	default :
		if (defaultEnemySkeleton != NULL && defaultEnemyMaterial != NULL)
		{
			GetMesh()->SetSkeletalMesh(defaultEnemySkeleton);
		}
	}
}

void AEnemy::ChangeSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = enemyMoveSpeed;
}



void AEnemy::OnDamage(float damage)
{
	currentHealth -= damage;
	OnHpChange.Broadcast();
}

void AEnemy::HitCheck()
{
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);
	bool bResult = GetWorld()->SweepSingleByChannel(
		hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(20.0f),
		params
	);
/* 디버그용
#if ENABLE_DRAW_DEBUG

	FVector traceVec = GetActorForwardVector() * 200.0f;
	FVector center = GetActorLocation() + traceVec * 0.5f;
	float halfHeight = 20.0f * 0.5f;
	FQuat capsuleRot = FRotationMatrix::MakeFromZ(traceVec).ToQuat();
	FColor drawColor = bResult ? FColor::Green : FColor::Red;
	float debugLifeTime = 3.0f;

	DrawDebugCapsule(GetWorld(),
		center,
		halfHeight,
		1,
		capsuleRot,
		drawColor,
		false,
		debugLifeTime
	);

#endif
*/
	if (bResult)
	{
		if (hitResult.GetActor() != NULL)
		{
			auto hitedActor = Cast<APlayerCharacter>(hitResult.GetActor());
			if (hitedActor != NULL)
			{
				hitedActor->Hited(enemyDamage);
			}
			
		}
	}
}

float AEnemy::GetHpRatio()
{
	return currentHealth/maxHealth;
}

void AEnemy::GiveExp(APlayerCharacter* player)
{
	if (player != NULL)
	{
		float newExp = player->currentExp + enemyExp;
		player->SetExp(newExp);
	}
}

void AEnemy::SetEnemyManager(AEnemyManager* newEnemyManager)
{
	enemyManager = newEnemyManager;
}

void AEnemy::Dispawn()
{
	if (enemyManager != NULL)
	{
		enemyManager->killzoneDead();
		this->Destroy();
	}
}

void AEnemy::SetEnemyType(EEnemyType type)
{
	enemyType = type;
}

EEnemyType AEnemy::GetEnemyType()
{
	return enemyType;
}



