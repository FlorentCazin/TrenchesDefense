// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesDefenseGameMode.h"
#include "GameplayTagsManager.h"
#include "CameraPlayerController.h"

void ATrenchesDefenseGameMode::BeginPlay() {
	Super::BeginPlay();

	//init timer with GameMode values
	timer = Cast<ATimerWarmup>(UGameplayStatics::GetActorOfClass(GetWorld(), ATimerWarmup::StaticClass()));
	timer->TimeInSeconds = TimeInSeconds;
	timer->InitTimer();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnerEnemy::StaticClass(), spawnerEnemies);
	CharacterDead.AddDynamic(this, &ATrenchesDefenseGameMode::UpdateGameModeCharactersInfos);

	//if multi, use iterator
	ACameraPlayerController *LPS = Cast<ACameraPlayerController>(GetWorld()->GetFirstPlayerController());
	LPS->GetLocalPlayer()->GetSubsystem<UTrenchesDefLocalPlayerSubsystem>()->Money = MoneyToGiveBegining;
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
	NumberOfZombieAllySide = 0;
	NumberOfZombieEnemySide = 0;
	InWave = false;
	//Timer
	timer->SetActorHiddenInGame(false);
	timer->StartTimer();

	if (firstWave) {
		NewWaveEvent.Broadcast(Wave);
		FString GeneralSpeaking = FString::Printf(TEXT("Bienvenue Soldat dans Trenches Defense. Placez vos unités pour défendre votre camp, ne laissez surtout pas\
		les zombies atteintre le bunker, et attention au chrono!"));
		GeneralSpeakingEvent.Broadcast(GeneralSpeaking);
		firstWave = false;
	}
	else {
		//General Speaking
		FString GeneralSpeaking = FString::Printf(TEXT("Bravo soldat, votre bataillon a survécu a la manche %d!"), Wave);
		GeneralSpeakingEvent.Broadcast(GeneralSpeaking);
		IncrWave();
		NewWaveEvent.Broadcast(Wave);
	}
}

void ATrenchesDefenseGameMode::UpdateGameModeCharactersInfos(bool IsZombie, FGameplayTag TeamTag) {
	//Ally
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
	}
	//Next Wave
	if (NumberOfZombieAllySide <= 0 && NumberOfZombieEnemySide <= 0) {
		EndWave();
		//faire parler general "bravo next wave"
		//incr wave
		//lancer event pour afficher argent
	}
}