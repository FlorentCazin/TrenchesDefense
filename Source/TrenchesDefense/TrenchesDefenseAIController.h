// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TrenchesDefenseAIController.generated.h"

/**
 * 
 */
UCLASS()
class TRENCHESDEFENSE_API ATrenchesDefenseAIController : public AAIController
{
	GENERATED_BODY()

public:

	bool MoveSuccess;

	FRotator FinalRotationSpawningSystem;
	
public:

	void MoveCharacterToLocationAndRotate(FVector TargetLocation, FRotator TargetRotation);

	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;

	bool OnSuccess();

	bool OnFail();

	//return true if success
	UFUNCTION(BlueprintCallable)
	bool Attack(TArray<ATrenchesDefenseCharacter*> targets);

	UFUNCTION(BlueprintCallable)
	void Die();
};
