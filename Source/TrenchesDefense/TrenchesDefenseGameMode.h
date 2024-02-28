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

	UPROPERTY(BlueprintReadWrite, category = "Game Info")
	int Wave;

	UPROPERTY(BlueprintReadWrite, category = "Game Info")
	int NumberOfCharactersFranceSide;

	UPROPERTY(BlueprintReadWrite, category = "Game Info")
	int NumberOfCharactersGermanySide;

	UPROPERTY(BlueprintReadWrite, category = "Gameplay Info")
	float TimeBetweenEachWave;

	UPROPERTY(BlueprintReadWrite, category = "Gameplay Info")
	bool StartWave;

	UPROPERTY(BlueprintReadWrite, category = "Gameplay Info")
	bool FinishWave;

public:

	//Incremente the wave number
	UFUNCTION(BlueprintCallable)
	void IncrWave();
	
};
