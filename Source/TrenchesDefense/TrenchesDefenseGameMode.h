// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TimerWarmup.h"
#include "SpawnerEnemy.h"
#include "GeneralSoldierSpeakingWidget.h"
#include "TrenchesDefenseGameMode.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCharacterDead, bool, IsZombie, FGameplayTag, TeamTag);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGeneralSpeaking, FString, GeneralTalking);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewWave, int, Wave);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndWave);


UCLASS(Blueprintable)
class TRENCHESDEFENSE_API ATrenchesDefenseGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	ATrenchesDefenseGameMode();

	//Actual wave
	UPROPERTY(BlueprintReadOnly, category = "Game Info")
	int Wave;

	//count

	UPROPERTY(BlueprintReadOnly, category = "Game Info")
	int NumberOfZombieAllySide;

	UPROPERTY(BlueprintReadOnly, category = "Game Info")
	int NumberOfSoldierAllySide;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Game Info")
	int NumberOfZombieEnemySide;

	UPROPERTY(BlueprintReadOnly, category = "Game Info")
	int NumberOfSoldierEnemySide;

	//Initialization of the timer
	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Gameplay Info")
	int TimeInSeconds = 90; //sexec dans endwave

	UPROPERTY(BlueprintReadOnly, category = "Gameplay Info")
	bool InWave;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "Game Info")
	int MoneyToGiveBegining = 1000;

	//Timer In Map
	ATimerWarmup* timer;

	//Spawner enemies
	TArray<AActor*> spawnerEnemies;

	UPROPERTY(BlueprintAssignable, category="GameMode EventDispatcher")
	FCharacterDead CharacterDead;

	UPROPERTY(BlueprintAssignable, category = "GeneralWidget EventDispatcher")
	FGeneralSpeaking GeneralSpeakingEvent;

	UPROPERTY(BlueprintAssignable, category = "BasicInfo EventDispatcher")
	FNewWave NewWaveEvent;

	UPROPERTY(BlueprintAssignable, category = "EndWave EventDispatcher")
	FEndWave EndWaveEvent;

	//used for general first speaking
	bool firstWave = true;


public:

	//Incremente the wave number
	UFUNCTION(BlueprintCallable)
	void IncrWave();

	UFUNCTION(BlueprintCallable)
	void StartWave(); //(InWave=true, lancer event pour spawn et ouvrir bunker => en bp peut etre?) 

	UFUNCTION(BlueprintCallable)
	void EndWave(); //met le inwave a false, et lance startwave apres timebetweeneachwave

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateGameModeCharactersInfos(bool IsZombie, FGameplayTag TeamTag);
};
