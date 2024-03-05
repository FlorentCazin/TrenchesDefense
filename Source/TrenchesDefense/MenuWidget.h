// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class TRENCHESDEFENSE_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category="menu widget")
	class UTextBlock* PlayText;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "menu widget")
	UButton* PlayButton;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "menu widget")
	class UTextBlock* SettingsText;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "menu widget")
	UButton* SettingsButton;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "menu widget")
	class UTextBlock* ExitText;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "menu widget")
	UButton* ExitButton;

	
};
