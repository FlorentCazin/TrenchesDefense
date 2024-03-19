// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "TrenchesDefLocalPlayerSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGiveMoney, int, MoneyToGive);

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

	UPROPERTY(BlueprintAssignable, category = "TrenchesDefLocalPlayerSubsystem EventDispatcher")
	FGiveMoney GiveMoneyEvent;

public:

	//Adding or removing money
	UFUNCTION(BlueprintCallable)
	void ChangeMoney(int MoneyToGive);

	virtual void Initialize(FSubsystemCollectionBase& Collection);
	
};
