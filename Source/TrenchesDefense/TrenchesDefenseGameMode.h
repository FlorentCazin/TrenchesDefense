// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TrenchesDefenseGameMode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRENCHESDEFENSE_API ATrenchesDefenseGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	ATrenchesDefenseGameMode();

	UPROPERTY(BlueprintReadWrite, category = "Player Money")
	int Wave;

public:

	//Incremente the wave number
	UFUNCTION(BlueprintCallable)
	void IncrWave();
	
};
