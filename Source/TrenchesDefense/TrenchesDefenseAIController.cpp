// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesDefenseAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "AIController.h"

ATrenchesDefenseAIController::ATrenchesDefenseAIController() {

	//Create AIPerception and default settings (because character==nullptr here)
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	UAISenseConfig_Sight* viewSense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("ViewSense"));
	viewSense->SightRadius = 0;
	viewSense->PeripheralVisionAngleDegrees = 0;
	AIPerception->ConfigureSense(*viewSense);
}

void ATrenchesDefenseAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATrenchesDefenseAIController::OnPossess(APawn *InPawn) {
	Super::OnPossess(InPawn);
	characterControlled = Cast<ATrenchesDefenseCharacter>(GetCharacter());
	FAISenseID viewID = UAISense::GetSenseID<UAISense_Sight>();
	UAISenseConfig_Sight *viewSense = Cast<UAISenseConfig_Sight>(AIPerception->GetSenseConfig(viewID));
	viewSense->SightRadius = characterControlled->CharacterDataAsset->MaxDistanceVision;
	viewSense->PeripheralVisionAngleDegrees = (characterControlled->CharacterDataAsset->DegreeOfVision) /2.f;
	testPrint = viewSense->SightRadius;
}

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
	//si un enemy deja target par un allié ne pas lattaquer? ajouter boolean isAttacked si c'est ca
	return false;
}

void ATrenchesDefenseAIController::Die() {
	//lifecomponent a 0, anim, destroy?
	//IsDead = true;
}