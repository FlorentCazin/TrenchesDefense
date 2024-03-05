// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "SettingsWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRENCHESDEFENSE_API USettingsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//Language
	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	UImage* FrenchLanguagePicture;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	UImage* EnglishLanguagePicture;

	//PreviousAction
	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	UImage* PreviousActionPicture;

	//resolution
	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	UButton* ResolutionButtonPrevious;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	UButton* ResolutionButtonNext;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	class UTextBlock* ResolutionText;

	//quality
	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	UButton* QualityButtonPrevious;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	UButton* QualityButtonNext;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	class UTextBlock* QualityText;
	
	//VSync
	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	UButton* VSyncButtonPrevious;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	UButton* VSyncButtonNext;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	class UTextBlock* VSyncText;

	//FullScreen
	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	UButton* FullScreenButtonPrevious;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	UButton* FullScreenButtonNext;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "SettingsWidget")
	class UTextBlock* FullScreenText;

public:

	UFUNCTION(BlueprintCallable)
	void ChangeWindowModeText(FString text);

	UFUNCTION(BlueprintCallable)
	void ChangeResolutionText(FString text);

	UFUNCTION(BlueprintCallable)
	void ChangeGraphicsText(FString text);

	UFUNCTION(BlueprintCallable)
	void ChangeVSyncText(FString text);
};
