// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerEnemy.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
ASpawnerEnemy::ASpawnerEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NumberOfEnemy = 100;
	TimeBetweenSpawn = 10.f;
	NumberOfIterationSpawn = 5;
	actualIteration = 0;
}

// Called when the game starts or when spawned
void ASpawnerEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (NumberOfEnemy % NumberOfIterationSpawn != 0) {
		UE_LOG(LogTemp, Warning, TEXT("SpawnerEnemy NumberOfEnemy % NumberOfIterationSpawn != 0 will cause trouble"))
	}
	World = GetWorld();
	if (EnemiesToSpawn.Num() != 2) {
		UE_LOG(LogTemp, Warning, TEXT("SpawnerEnemy EnemiesToSpawn.Num() != 2 script is working only for 2 types of enemies, make changes"));
	}
	
}

// Called every frame
void ASpawnerEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnerEnemy::StartSpawningEnemies() {
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnerEnemy::SpawnEnemies, 1.f, true, TimeBetweenSpawn);
}

void ASpawnerEnemy::SpawnEnemies() {
	if (actualIteration == NumberOfIterationSpawn) {
		GetWorldTimerManager().ClearTimer(TimerHandle);
		actualIteration = 0;
	}
	else {
		int random;
		for (int i = 0; i < NumberOfEnemy / NumberOfIterationSpawn; i++) {
			random = FMath::RandRange(1, 20);
			if (random == 5) {
				World->SpawnActor<EnemiesToSpawn[1]>(EnemiesToSpawn[1], GetActorLocation(), GetActorRotation());
			}
		}
		actualIteration++;
	}
}



