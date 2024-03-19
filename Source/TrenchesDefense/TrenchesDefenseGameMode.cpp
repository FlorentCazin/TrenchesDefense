// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesDefenseGameMode.h"
#include "GameplayTagsManager.h"

void ATrenchesDefenseGameMode::BeginPlay() {
	Super::BeginPlay();

	//init timer with GameMode values
	timer = Cast<ATimerWarmup>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimerWarmup::StaticClass()));
	timer->TimeInSeconds = TimeInSeconds;
	timer->InitTimer();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnerEnemy::StaticClass(), spawnerEnemies);
	CharacterDead.AddDynamic(this, &ATrenchesDefenseGameMode::UpdateGameModeCharactersInfos);
}


ATrenchesDefenseGameMode::ATrenchesDefenseGameMode() {
	Wave = 1;
}

void ATrenchesDefenseGameMode::IncrWave() {
	Wave++;
}

void ATrenchesDefenseGameMode::StartWave() {
	InWave = true;
	//timer
	timer->SetActorHiddenInGame(true);
	for (auto &spawner: spawnerEnemies) {
		ASpawnerEnemy* spawnerEnemy = Cast<ASpawnerEnemy>(spawner);
		spawnerEnemy->StartSpawningEnemies();
	}
}

void ATrenchesDefenseGameMode::EndWave() {
	InWave = false;
	//timer
	timer->SetActorHiddenInGame(false);
	timer->StartTimer();

}

void ATrenchesDefenseGameMode::UpdateGameModeCharactersInfos(bool IsZombie, FGameplayTag TeamTag) {
	//Ally
	/*
	if (TeamTag == UGameplayTagsManager::Get().RequestGameplayTag(FName("Team.Ally"))) {
		if (IsZombie) {
			NumberOfZombieAllySide--;
		}
		else {
			NumberOfSoldierAllySide--;
		}
	}
	//Enemy
	else if (TeamTag == UGameplayTagsManager::Get().RequestGameplayTag(FName("Team.Enemy"))) {
		if (IsZombie) {
			NumberOfZombieEnemySide--;
		}
		else {
			NumberOfSoldierEnemySide--;
		}
	}	*/

}