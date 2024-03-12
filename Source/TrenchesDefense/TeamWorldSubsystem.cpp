// Fill out your copyright notice in the Description page of Project Settings.


#include "TeamWorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

void UTeamWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UTeamWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UTeamWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	UWorld* World = GetWorld();
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(World, AObjectifToReach::StaticClass(), foundActors);

	for (auto& actor : foundActors) {
		AObjectifToReach* objectif = Cast<AObjectifToReach>(actor);
		if (objectif) {
			if (objectif->teamTag == UGameplayTagsManager::Get().RequestGameplayTag(FName("Team.Enemy"))) {
				EnemyObjective = objectif;
			}
			else if (objectif->teamTag == UGameplayTagsManager::Get().RequestGameplayTag(FName("Team.Ally"))) {
				AllyObjective = objectif;
			}
		}
	}
}

FVector UTeamWorldSubsystem::GetObjectiveToReach(FGameplayTag TeamTag) const {
	if (TeamTag == UGameplayTagsManager::Get().RequestGameplayTag(FName("Team.Enemy")))
	{
		if (EnemyObjective) {
			//il rentre pas dedans, a debug
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("HEREEEE"));
			return EnemyObjective->GetActorLocation();
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("EnemyObjective is null"));
			return FVector::Zero();
		}
	}
	else if (TeamTag == UGameplayTagsManager::Get().RequestGameplayTag(FName("Team.Ally"))) {
		if (AllyObjective) {
			return AllyObjective->GetActorLocation();
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("AllyObjective is null"));
			return FVector::Zero();
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No objectif to reach with gameplay tag founds"));
		return FVector::Zero();
	}
}

