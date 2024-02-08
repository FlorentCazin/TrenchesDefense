// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrenchesDefenseCharacter.h"
#include "SoldierDataAsset.h"
#include "SoldierCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRENCHESDEFENSE_API ASoldierCharacter : public ATrenchesDefenseCharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="SoldierProperties")
	USoldierDataAsset *SoldierDataAsset;

public:

	bool Attack(TArray<ATrenchesDefenseCharacter*> Targets);

	UFUNCTION(BlueprintCallable)
	void GiveMoney();
};
