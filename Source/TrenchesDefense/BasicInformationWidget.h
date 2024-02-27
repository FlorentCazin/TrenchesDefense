// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "BasicInformationWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRENCHESDEFENSE_API UBasicInformationWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget))
	UImage *MoneyPicture;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget))
	UImage* WaveBackgroundPicture;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget))
	class UTextBlock* MoneyPlayer;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget))
	class UTextBlock* WaveNumber;

public:

	UFUNCTION(BlueprintCallable)
	void ChangeMoneyText(int money);

	UFUNCTION(BlueprintCallable)
	void ChangeWaveText(int wave);
	
};
