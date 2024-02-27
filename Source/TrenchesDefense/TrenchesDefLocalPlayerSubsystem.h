// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "TrenchesDefLocalPlayerSubsystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRENCHESDEFENSE_API UTrenchesDefLocalPlayerSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:

	UTrenchesDefLocalPlayerSubsystem();

	UPROPERTY(BlueprintReadWrite, category="Player Money")
	int Money;

	UPROPERTY(BlueprintReadWrite, category = "Player Money")
	int Wave;

public:

	//Incremente the wave number
	UFUNCTION(BlueprintCallable)
	void IncrWave();

	//Adding or removing money
	UFUNCTION(BlueprintCallable)
	void ChangeMoney(int value);
	
};
