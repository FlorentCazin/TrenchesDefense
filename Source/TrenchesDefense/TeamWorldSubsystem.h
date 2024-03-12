// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "ObjectifToReach.h"
#include "TeamWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TRENCHESDEFENSE_API UTeamWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
private:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

public:

	UFUNCTION(BlueprintCallable)
	FVector GetObjectiveToReach(FGameplayTag TeamTag) const;

	AActor* EnemyObjective;
	AActor* AllyObjective;
};
