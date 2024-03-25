// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "TrenchesDefenseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "TrenchesDefLocalPlayerSubsystem.h"
#include "TrencheToExplore.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "AIController")
	ATrenchesDefenseCharacter* characterControlled;

	FRotator FinalRotationSpawningSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category="AIController")
	UAIPerceptionComponent* AIPerception;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "AIController")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(BlueprintReadOnly,EditAnywhere, category = "AIControllerAttack")
	TArray<ATrenchesDefenseCharacter*> TargetsInSight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "AIControllerAttack")
	int TargetsInSightIndex;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, category = "AIControllerAttack")
	bool alreadyHasLineOfSight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ATrencheToExplore* TrencheChosenToExplore;
	

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

	UFUNCTION(BlueprintCallable)
	void Attack(ATrenchesDefenseCharacter* target);

	UFUNCTION(BlueprintCallable)
	void ChangeTargetToAttack();

	UFUNCTION(BlueprintCallable)
	void Die();

	UFUNCTION(Blueprintable)
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION(BlueprintCallable)
	void setWalkSpeed(int speed);
};
