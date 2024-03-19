// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerEnemy.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "TrenchesDefenseGameMode.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
ASpawnerEnemy::ASpawnerEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NumberOfEnemy = 100;
	TimeBetweenSpawn = 1.f;
	NumberOfIterationSpawn = 5;
	actualIteration = 0;
	spawnActorCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	spawnParameters.SpawnCollisionHandlingOverride = spawnActorCollisionHandlingMethod;
}

// Called when the game starts or when spawned
void ASpawnerEnemy::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
	if (NumberOfEnemy % NumberOfIterationSpawn != 0) {
		UE_LOG(LogTemp, Warning, TEXT("SpawnerEnemy NumberOfEnemy % NumberOfIterationSpawn != 0 will cause trouble"))
	}
	else if (EnemiesToSpawn.Num() != 2) {
		UE_LOG(LogTemp, Warning, TEXT("SpawnerEnemy EnemiesToSpawn.Num() != 2 script is working only for 2 types of enemies, make changes"));
	}
}

// Called every frame
void ASpawnerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnerEnemy::StartSpawningEnemies() {
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnerEnemy::SpawnEnemies, TimeBetweenSpawn, true, 1.f);
}

void ASpawnerEnemy::SpawnEnemies() {
	//opti => beginplay -> .h //error dependance no time to fix this
	ATrenchesDefenseGameMode* GM = Cast<ATrenchesDefenseGameMode>(GetWorld()->GetAuthGameMode());

	if (actualIteration == NumberOfIterationSpawn) {
		GetWorldTimerManager().ClearTimer(TimerHandle);
		actualIteration = 0;
	}
	else {
		int random;
		for (int i = 0; i < NumberOfEnemy / NumberOfIterationSpawn; i++) {
			random = FMath::RandRange(1, 20);
			//configurer param spawn pour always spawn
			if (random == 5) {
				ATrenchesDefenseCharacter *tmp = World->SpawnActor<ATrenchesDefenseCharacter>(EnemiesToSpawn[1], GetActorLocation(), GetActorRotation(), spawnParameters);
				if (tmp && tmp->IsZombie) {
					if (tmp->CharacterDataAsset->CharacterTeamComponent->TeamTag == FGameplayTag::RequestGameplayTag(FName("Team.enemy"))) {
						GM->NumberOfZombieEnemySide++;
					}
					else if (tmp->CharacterDataAsset->CharacterTeamComponent->TeamTag == FGameplayTag::RequestGameplayTag(FName("Team.ally"))) {
						GM->NumberOfZombieAllySide++;
					}
				}
			}
			else {
				ATrenchesDefenseCharacter* tmp = World->SpawnActor<ATrenchesDefenseCharacter>(EnemiesToSpawn[0], GetActorLocation(), GetActorRotation(), spawnParameters);
				if (tmp && tmp->IsZombie) {
					if (tmp->CharacterDataAsset->CharacterTeamComponent->TeamTag == FGameplayTag::RequestGameplayTag(FName("Team.enemy"))) {
						GM->NumberOfZombieEnemySide++;
					}
					else if (tmp->CharacterDataAsset->CharacterTeamComponent->TeamTag == FGameplayTag::RequestGameplayTag(FName("Team.ally"))) {
						GM->NumberOfZombieAllySide++;
					}
				}
			}
		}
		actualIteration++;
	}
}



