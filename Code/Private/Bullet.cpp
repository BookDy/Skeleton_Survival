// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Enemy.h"
#include "EnemyFSM.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	collisionComp->SetCollisionProfileName(TEXT("OverlapAll"));
	collisionComp->SetSphereRadius(10);
	RootComponent = collisionComp;

	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));

	ConstructorHelpers::FObjectFinder<UStaticMesh>tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Gun/Bullet/Bullet.Bullet'"));
	if (tempMesh.Succeeded())
	{
		bodyMeshComp->SetStaticMesh(tempMesh.Object);
		bodyMeshComp->SetupAttachment(collisionComp);
		bodyMeshComp->SetRelativeScale3D(FVector(10, 10, 10));

	}
	
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	//movementComp가 갱신시킬 Component
	movementComp->SetUpdatedComponent(collisionComp);
	//초기 속도
	movementComp->InitialSpeed = bulletSpeed;
	//최대 속도
	movementComp->MaxSpeed = bulletSpeed;
	//탄성 여부(벽에 부딪히고 떨어지는)
	movementComp->bShouldBounce = false;
	//중력 수치
	movementComp->ProjectileGravityScale = 0;


	//trailParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailParticleComp"));
	//trailParticleComp->SetupAttachment(collisionComp);


	trailNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailNiagaraComp"));
	trailNiagaraComp->SetupAttachment(collisionComp);
	trailNiagaraComp->SetRelativeRotation(FRotator(0, 0, 0));


	InitialLifeSpan = 2.0f;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	trailNiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(trailNiagaraComp->GetAsset(), trailNiagaraComp, FName("TrailStart"), FVector::ZeroVector, FRotator(0,90,0), EAttachLocation::Type::KeepRelativeOffset, true);

	collisionComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto enemy = Cast<AEnemy>(OtherActor);
	if (enemy != NULL)
	{
		enemy->fsm->OnDamageProcess(damage);
		Destroy();
	}
}


void ABullet::ChangeDamage(float newDamage)
{
	damage = newDamage;
}


void ABullet::ChangeBulletSpeed(float newBulletSpeed)
{
	bulletSpeed = newBulletSpeed;

	//총알 속도 변경
	movementComp->InitialSpeed = bulletSpeed;
	movementComp->MaxSpeed = bulletSpeed;
}
