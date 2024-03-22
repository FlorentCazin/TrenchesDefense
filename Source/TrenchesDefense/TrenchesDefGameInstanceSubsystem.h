// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TrenchesDefGameInstanceSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TRENCHESDEFENSE_API UTrenchesDefGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, category="stats")
	int TotalWave;
	
};
