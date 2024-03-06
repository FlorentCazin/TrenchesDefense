// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MenuInGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class TRENCHESDEFENSE_API UMenuInGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//fix camera

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "menu widget")
	class UTextBlock* FixCameraText;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "menu widget")
	UButton* FixCameraButton;

	//play

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "menu widget")
	class UTextBlock* PlayText;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "menu widget")
	UButton* PlayButton;

	//settings

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "menu widget")
	class UTextBlock* SettingsText;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "menu widget")
	UButton* SettingsButton;

	//exit

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "menu widget")
	class UTextBlock* ExitText;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "menu widget")
	UButton* ExitButton;
	
};
