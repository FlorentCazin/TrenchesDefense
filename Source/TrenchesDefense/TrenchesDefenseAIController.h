// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "TrenchesDefenseCharacter.h"
#include "TrenchesDefenseAIController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRENCHESDEFENSE_API ATrenchesDefenseAIController : public AAIController
{
	GENERATED_BODY()

public:

	ATrenchesDefenseAIController();

	ATrenchesDefenseCharacter* characterControlled;

	FRotator FinalRotationSpawningSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAIPerceptionComponent* AIPerception;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float testPrint;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


public:

	virtual void OnPossess(APawn* InPawn) override;

	void MoveCharacterToLocationAndRotate(FVector TargetLocation, FRotator TargetRotation);

	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;

	bool OnSuccess();

	bool OnFail();

	//return true if success
	UFUNCTION(BlueprintCallable)
	bool Attack(ATrenchesDefenseCharacter* target);

	UFUNCTION(BlueprintCallable)
	void Die();

	UFUNCTION(Blueprintable)
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
