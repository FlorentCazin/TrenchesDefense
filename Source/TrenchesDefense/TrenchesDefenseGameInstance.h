// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SettingsManager.h"
#include "TrenchesDefenseGameInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRENCHESDEFENSE_API UTrenchesDefenseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UTrenchesDefenseGameInstance();

	UPROPERTY(BlueprintReadWrite, category="SettingsManager")
	USettingsManager* SettingsManager;
	
};
