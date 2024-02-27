// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "GeneralSoldierSpeakingWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRENCHESDEFENSE_API UGeneralSoldierSpeakingWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//Juste pour essayer, gerer le francais et langlais en utilisant un tableau avec translation
	
	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "WidgetGeneral")
	class UTextBlock *GeneralSpeaking;

	UPROPERTY(BlueprintReadWrite, meta = (bindWidget), category = "WidgetGeneral")
	UImage *GeneralPicture;

	UPROPERTY(BlueprintReadWrite, category="WidgetGeneral")
	bool IsAlreadyTalking;


public:

	//Change the General Speaking using a FString text parameter
	UFUNCTION(BlueprintCallable)
	void ChangeText(FString text);
	
};
