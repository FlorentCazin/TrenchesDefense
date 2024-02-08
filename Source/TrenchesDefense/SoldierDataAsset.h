// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponComponent.h"
#include "SoldierDataAsset.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRENCHESDEFENSE_API USoldierDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SoldierProperties")
	int Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierProperties")
	int MoneyPerKill;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierProperties")
	TSubclassOf<UWeaponComponent> WeaponComponent;

	//UObject SelectionZone et FiringZone ? (Représentation de la zone graphiquement lors de la selection du soldat)
};