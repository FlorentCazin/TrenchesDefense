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
	GetPawn()->SetActorRotation(FQuat(FinalRotationSpawningSystem));
	return true;
}

bool ATrenchesDefenseAIController::OnFail() {
	//UE_LOG(LogTemp, Log, TEXT("AIMoveTo Fail"))
	return false;
}


bool ATrenchesDefenseAIController::Attack(ATrenchesDefenseCharacter* Target) {
	//NE PAS OUBLIE DE FAIRE UN IF(! SON TEAM COMPONENT) POUR QUE LE FONCTION FONCTIONNE PEUT IMPORTE LA TEAM zombie/soldat joueur1/joueur2 multi
	//verif nbr zombie vu pour soldat depuis iaperception directement voir si nbr correspond soldierdataasset
	return false;
}

void ATrenchesDefenseAIController::Die() {
	//lifecomponent a 0, anim, destroy?
	//IsDead = true;
}