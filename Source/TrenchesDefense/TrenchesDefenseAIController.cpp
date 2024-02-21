// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesDefenseAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"


void ATrenchesDefenseAIController::MoveCharacterToLocationAndRotate(FVector TargetLocation, FRotator TargetRotation) {
	FinalRotationSpawningSystem = TargetRotation;
	this->MoveToLocation(TargetLocation);
}

//RequestId => uniqueID of the movement executed, Result => state of the movement
void ATrenchesDefenseAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) {
	Super::OnMoveCompleted(RequestID, Result);

	if (Result == EPathFollowingResult::Success) { //moving success
		OnSuccess();
	}
	else { //moving fail
		OnFail();
	}
}

bool ATrenchesDefenseAIController::OnSuccess() {
	MoveSuccess = true;
	GetPawn()->SetActorRotation(FQuat(FinalRotationSpawningSystem));
	return true;
}

bool ATrenchesDefenseAIController::OnFail() {

	//UE_LOG(LogTemp, Log, TEXT("AIMoveTo Fail"))
	MoveSuccess = false;
	return false;
}


bool ATrenchesDefenseAIController::Attack(TArray<ATrenchesDefenseCharacter*> Targets) {
	return false;
}

void ATrenchesDefenseAIController::Die() {
	//IsDead = true;
}