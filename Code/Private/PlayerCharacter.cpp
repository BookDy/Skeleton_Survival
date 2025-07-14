// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "GameFramework/PlayerController.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Kismet/GameplayStatics.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Bullet.h"

#include "PlayerAnim.h"

#include "Kismet/KismetMathLibrary.h"

#include "Components/WidgetComponent.h"

#include "CharacterWidget.h"

#include "WaveAndScroeWidget.h"

#include "LevelUpWidget.h"

#include "GameOverWidget.h"

#include "GameClearWidget.h"

#include "PlayerSoundComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//스켈레탈 메시 설정
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Meshes/Twin_NoWeapon_Final.Twin_NoWeapon_Final'"));
	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	gunComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunComp"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempGunMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SK_AR4.SK_AR4'"));
	if (TempGunMesh.Succeeded())
	{
		gunComp->SetSkeletalMesh(TempGunMesh.Object);
		gunComp->SetupAttachment(GetMesh(), TEXT("GunSocket"));
		
		gunComp->SetRelativeLocationAndRotation(FVector(-5, 4, -3), FRotator(0, 100, 0));
	}

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeRotation(FRotator(-60, 0, 0));
	springArmComp->TargetArmLength = 1000;
	springArmComp->bUsePawnControlRotation = false;
	springArmComp->bDoCollisionTest = false;

	camComp = CreateDefaultSubobject<UCameraComponent>(TEXT("camComp"));
	camComp->SetupAttachment(springArmComp);
	camComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;


	gunNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("GunNiagaraComp"));
	gunNiagaraComp->SetupAttachment(gunComp);

	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;

	
	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBarWidget"));
	HPBarWidget->SetupAttachment(springArmComp);

	HPBarWidget->SetRelativeLocation(FVector(900.0f, 0.0f, -80.0f));
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	
	GameInputMode.SetConsumeCaptureMouseDown(false);

	playerSoundComponent = CreateDefaultSubobject<UPlayerSoundComponent>(TEXT("SoundComponent"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	auto pc = Cast<APlayerController>(Controller);
	if (pc)
	{
		auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(imc, 0);
		}
	}
	
	playerController = Cast<APlayerController>(GetController());
	playerController->bShowMouseCursor = true;

	InitStat();

	auto CharacterWidget = Cast<UCharacterWidget>(HPBarWidget->GetUserWidgetObject());
	if (CharacterWidget != NULL)
	{
		CharacterWidget->BindCharacter(this);
	}

	if (waveAndScoreWidget != NULL)
	{
		waveAndScoreWidget->AddToViewport(1);
	}

	if (levelUpWidget != NULL)
	{
		levelUpWidget->BindPlayer(this);
	}

	ChangeInputMode(true);
	playerController->SetPause(false);

	anim = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());

	isPlayerDead = false;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (playerController && !isPlayerDead)
	{
		FHitResult HitResult;
		playerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult
		);

		FVector Target = HitResult.Location - GetActorLocation();
		FRotator lookRotation = FRotator(0, Target.Rotation().Yaw, 0);
		Controller->SetControlRotation(lookRotation);

		AddMovementInput(direction);
		direction = FVector::ZeroVector;
	}

	HpRegen();


}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto PlayerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (PlayerInput)
	{
		PlayerInput->BindAction(ia_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		PlayerInput->BindAction(ia_Fire, ETriggerEvent::Triggered, this, &APlayerCharacter::InputFire);
	}

}

void APlayerCharacter::Move(const FInputActionValue& inputValue)
{
	FVector2D value = inputValue.Get<FVector2D>();
	direction.X = value.X;
	direction.Y = value.Y;
}

void APlayerCharacter::InputFire(const FInputActionValue& inputValue)
{
	if (canFire) 
	{
		canFire = false;

		//auto anim = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
		if (anim != NULL)
		{
			anim->PlayAttackAnim();
		}
		

		FTransform firePosition = gunComp->GetSocketTransform(TEXT("FirePosition"));
		firePosition.SetLocation(FVector(firePosition.GetLocation().X, firePosition.GetLocation().Y, firePosition.GetLocation().Z - 25));
		ABullet* tempBullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition);
		if (tempBullet != NULL)
		{
			tempBullet->ChangeDamage(bulletDmg);
			tempBullet->ChangeBulletSpeed(bulletSpeed);
		}
		

		if (gunNiagaraComp != NULL)
		{
			if (gunNiagaraComp->GetAsset() != NULL)
			{
				gunNiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(gunNiagaraComp->GetAsset(), gunComp, FName("FirePosition"), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::KeepRelativeOffset, true);
			}
		}
		
		
		/*
		if (bulletSound != NULL)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);
		}
		*/
		if (playerSoundComponent)
		{
			playerSoundComponent->PlayPlayerFireSound();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("playerSoundComponent is NULL"));
		}

		GetWorld()->GetTimerManager().SetTimer(bulletTimerHandle, this, &APlayerCharacter::CanFireOn, fireRate, false);

	}
	
}

void APlayerCharacter::CanFireOn()
{
	canFire = true;
	fireRate = newFireRate;
	GetWorld()->GetTimerManager().ClearTimer(bulletTimerHandle);
}

void APlayerCharacter::InitStat()
{
	maxHealth = 50;
	currentHealth = 50;
	healthRegen = 0.2f;

	maxExp = 100;
	currentExp = 0;

	moveSpeed = 200;

	bulletDmg = 40; //기본 40
	bulletSpeed = 200; //기본 200
	fireRate = 1.8f;    //기본 1.8
	newFireRate = 1.8f;
}

void APlayerCharacter::Hited(float damage)
{
	if (canHit == true)
	{
		currentHealth = currentHealth - damage;

		if (currentHealth < 0)
		{
			ChangeInputMode(false);
			levelUpWidget->RemoveFromParent();
			canHit = false;
			isPlayerDead = true;
			if (anim != NULL)
			{
				anim->PlayDieAnim();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("PlayerAnim Missing"));
			}
			if (playerSoundComponent)
			{
				playerSoundComponent->PlayPlayerDeadSound();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("playerSoundComponent is NULL"));
			}
			currentHealth = 0;
			SetHp(currentHealth);
			
		}
		else
		{
			if (anim != NULL)
			{
				anim->PlayDamageAnim();
			}
			if (playerSoundComponent)
			{
				playerSoundComponent->PlayPlayerHitedSound();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("playerSoundComponent is NULL"));
			}
			SetHp(currentHealth);
			HitedReaction();
		}

		
	}
	
}

void APlayerCharacter::HitedReaction()
{
	canHit = false;
	GetWorld()->GetTimerManager().SetTimer(hitedReactionTimerHandle, this, &APlayerCharacter::HitedReactionEnd, hitedReactionTime, false);
}

void APlayerCharacter::HitedReactionEnd()
{
	canHit = true;
	GetWorld()->GetTimerManager().ClearTimer(hitedReactionTimerHandle);
}

void APlayerCharacter::SetMaxHp(float newMaxHp)
{
	maxHealth = newMaxHp;
	currentHealth = maxHealth;
	OnHPChange.Broadcast();
}

void APlayerCharacter::SetMaxExp(float newMaxExp)
{
	maxExp = newMaxExp;
	OnExpChange.Broadcast();
}

void APlayerCharacter::SetMovementSpeed(float newMovementSpeed)
{
	moveSpeed = newMovementSpeed;
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;
}

void APlayerCharacter::SetBulletSpeed(float newBulletSpeed)
{
	bulletSpeed = newBulletSpeed;
}

void APlayerCharacter::SetBulletDmg(float newBulletDmg)
{
	bulletDmg = newBulletDmg;
}

void APlayerCharacter::SetFireRate(float newfireRate)
{
	fireRate = newfireRate;
}

void APlayerCharacter::SetHealthRegen(float newHealthRegen)
{
	healthRegen = newHealthRegen;
}

void APlayerCharacter::SetHp(float newHp)
{
	currentHealth = newHp;
	OnHPChange.Broadcast();
}

void APlayerCharacter::SetExp(float newExp)
{
	if (maxExp <= newExp)
	{
		currentExp = newExp - maxExp;
		maxExp = maxExp + 50;
		LevelUp();

	}
	else 
	{
		currentExp = newExp;
	}
	
	OnExpChange.Broadcast();
}

void APlayerCharacter::LevelUp()
{
	playerController->SetPause(true);
	ChangeInputMode(false);
	levelUpWidget->AddToViewport(2);
}

void APlayerCharacter::LevelUpEnd()
{
	ChangeInputMode(true);
	playerController->SetPause(false);
	levelUpWidget->RemoveFromParent();
}

void APlayerCharacter::PlayerDied()
{
	/*
	*/

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Dead"));
}

void APlayerCharacter::GameClear()
{
	/*
	playerController->SetPause(true);
	ChangeInputMode(false);
	levelUpWidget->RemoveFromParent();
	gameClearWidget->AddToViewport(3);
	*/
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Clear"));
}

float APlayerCharacter::GetHPRatio()
{
	return currentHealth/maxHealth;
}

float APlayerCharacter::GetExpRatio()
{
	return currentExp/maxExp;
}

void APlayerCharacter::HpRegen()
{
	hpRegenTime += GetWorld()->GetDeltaSeconds();
	if (hpRegenTime > 1)
	{
		hpRegenTime = 0;
		float tempHp = currentHealth + healthRegen;
		if (tempHp <= maxHealth)
		{
			SetHp(tempHp);
		}
	}
}

void APlayerCharacter::ChangeInputMode(bool bGameMode)
{

	if (bGameMode)
	{
		playerController->SetInputMode(GameInputMode);
	}
	else
	{
		playerController->SetInputMode(UIInputMode);
	}
}
