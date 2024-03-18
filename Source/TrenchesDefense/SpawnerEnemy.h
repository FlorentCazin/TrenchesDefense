// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrenchesDefenseCharacter.h"
#include "SpawnerEnemy.generated.h"

UCLASS()
class TRENCHESDEFENSE_API ASpawnerEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerEnemy();

	//first is basic enemy, second is more rare enemy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category="SpawnerEnemy")
	TArray<TSubclassOf<ATrenchesDefenseCharacter>> EnemiesToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "SpawnerEnemy")
	int NumberOfEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "SpawnerEnemy")
	float TimeBetweenSpawn;

	//if NumberOfEnemy you can give 5 (20x5=100) but not 6 or 4.. NumberOfEnemy%NumberOfIterationSpawn=0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "SpawnerEnemy")
	int NumberOfIterationSpawn;


	int EnemySpawned;

	int actualIteration;

	UWorld* World;
	
	//for timer
	FTimerHandle TimerHandle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartSpawningEnemies();

	//Called from StartSpawningEnemies
	void SpawnEnemies();


};
