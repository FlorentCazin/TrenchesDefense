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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Game Info")
	int NumberOfZombieToSpawnHistoryMod;

	//for multiplayer
	UPROPERTY(BlueprintReadWrite, category = "Game Info")
	int NumberOfZombieFranceSide;

	UPROPERTY(BlueprintReadWrite, category = "Game Info")
	int NumberOfZombieGermanySide; //si tag.enemy alors quand un meurt --, faire event dispatcher si ==0 => quand numberofzombiegermanyside = 0 && numberofzombiefranceside lancer end wave

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Gameplay Info")
	float TimeBetweenEachWave; //sexec dans endwave

	UPROPERTY(BlueprintReadWrite, category = "Gameplay Info")
	bool InWave;

public:

	//Incremente the wave number
	UFUNCTION(BlueprintCallable)
	void IncrWave();

	UFUNCTION(BlueprintCallable)
	void StartWave(); //(InWave=true, lancer event pour spawn et ouvrir bunker => en bp peut etre?) 

	UFUNCTION(BlueprintCallable)
	void EndWave(); //met le inwave a false, et lance startwave apres timebetweeneachwave
	
};
