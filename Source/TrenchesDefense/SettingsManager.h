// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Math/IntPoint.h"
#include "SettingsManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRENCHESDEFENSE_API USettingsManager : public UObject
{
	GENERATED_BODY()

public:

	USettingsManager();

	//Language, default = en
	UPROPERTY(BlueprintReadWrite, category="SettingsWidget save")
	FString Language;

	//Resolution x y, default = 1920x1080
	UPROPERTY(BlueprintReadWrite, category = "SettingsWidget save")
	FIntPoint Resolution;

	//Fullscreen, default = true
	UPROPERTY(BlueprintReadWrite, category = "SettingsWidget save")
	bool IsFullScreen;

	//VSync, default = false
	UPROPERTY(BlueprintReadWrite, category = "SettingsWidget save")
	bool IsVSync;

	//GraphicsIndex, default = 4 => Ultra
	UPROPERTY(BlueprintReadWrite, category = "SettingsWidget save")
	int GraphicsIndex;
	
};
