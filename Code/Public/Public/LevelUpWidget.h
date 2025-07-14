// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpWidget.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ELevelUpOptions : uint8
{
	HealthUp UMETA(DisplayName = "HealthUp"),
	HealthRegenUp UMETA(DisplayName = "HealthRegenUp"),
	SpeedUp UMETA(DisplayName = "SpeedUp"),
	BulletDmgUP UMETA(DisplayName = "BulletDmgUP"),
	BulletSpeedUp UMETA(DisplayName = "BulletSpeedUp"),
	FireRateUp UMETA(DisplayName = "FireRateUp"),
	
};

UCLASS()
class VAMPIREPROJECT_API ULevelUpWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;


	
	void ChangeOption();

	UFUNCTION(BlueprintCallable)
	void Option1_Clicked();

	UFUNCTION(BlueprintCallable)
	void Option2_Clicked();

	UFUNCTION(BlueprintCallable)
	void Option3_Clicked();

	void BindPlayer(class APlayerCharacter* player);

	void SetOptionsText();

	ELevelUpOptions ReturnEnumByIndex(int index);


protected:
	void HealthUp();
	void HealthRegenUp();
	void SpeedUp();
	void BulletDmgUp();
	void BulletSpeedUp();
	void FireRateUp();

public:
	UPROPERTY(EditAnywhere)
	ELevelUpOptions option1;

	UPROPERTY(EditAnywhere)
	ELevelUpOptions option2;

	UPROPERTY(EditAnywhere)
	ELevelUpOptions option3;


private:
	UPROPERTY()
	class APlayerCharacter* currentPlayer;

	UPROPERTY()
	class UButton* BT_Option1;
	UPROPERTY()
	class UTextBlock* TB_Option1;

	UPROPERTY()
	class UButton* BT_Option2;
	UPROPERTY()
	class UTextBlock* TB_Option2;

	UPROPERTY()
	class UButton* BT_Option3;
	UPROPERTY()
	class UTextBlock* TB_Option3;

	
};
