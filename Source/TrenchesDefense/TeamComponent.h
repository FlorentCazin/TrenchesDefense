// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "TeamComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, DefaultToInstanced, EditInlineNew)
class TRENCHESDEFENSE_API UTeamComponent : public UObject
{
	GENERATED_BODY()

public:	

	//Team name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TeamProperties")
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TeamProperties")
	FGameplayTag TeamTag;

	//Objectif to reach (necessary for multiplayer)
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TeamProperties")
	//FVector ObjectifToReach;
		
};
