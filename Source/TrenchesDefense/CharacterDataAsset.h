// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TeamComponent.h"
#include "CharacterDataAsset.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRENCHESDEFENSE_API UCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="CharacterPropertiesDataAsset")
	int WalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPropertiesDataAsset")
	int RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "CharacterPropertiesDataAsset")
	UTeamComponent* CharacterTeamComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPropertiesDataAsset")
	float MaxDistanceVision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPropertiesDataAsset")
	float DegreeOfVision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPropertiesDataAsset")
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPropertiesDataAsset")
	float AttackDamage; 
	
};
