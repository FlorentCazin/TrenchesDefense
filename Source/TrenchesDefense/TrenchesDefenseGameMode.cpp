// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesDefenseGameMode.h"

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
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("TEST"));
}