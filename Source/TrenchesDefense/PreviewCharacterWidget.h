// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TrenchesDefenseCharacter.h"
#include "Components/ProgressBar.h"
#include "PreviewCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class TRENCHESDEFENSE_API UPreviewCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* LifeText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* DamageText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* HeadShotText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* LifeProgressBar;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,category="ProgressBarColor")
	FLinearColor HighLifeColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "ProgressBarColor")
	FLinearColor MiddleLifeColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "ProgressBarColor")
	FLinearColor LowLifeColor;

public:

	UFUNCTION(BlueprintCallable)
	void SetPreviewValuesFromCharacter(ATrenchesDefenseCharacter *character);

	void ChangeProgressBarColor(int life);
	
};
