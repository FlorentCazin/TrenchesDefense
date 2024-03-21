// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesDefenseAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "ObjectifToReach.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TeamWorldSubsystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "Math/Vector.h"
#include "Containers/Array.h"
#include "Kismet/KismetMathLibrary.h"
#include "TrenchesDefenseGameMode.h"
#include "AIController.h"

ATrenchesDefenseAIController::ATrenchesDefenseAIController() {
	PrimaryActorTick.bCanEverTick = true;
	//Create AIPerception and default settings (because character==nullptr here)
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	UAISenseConfig_Sight* viewSense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("ViewSense"));
	viewSense->SightRadius = 0;
	viewSense->LoseSightRadius = 0;
	viewSense->PeripheralVisionAngleDegrees = 0;
	FAISenseAffiliationFilter SenseAffiliationFilter;
	SenseAffiliationFilter.bDetectEnemies = true;
	SenseAffiliationFilter.bDetectNeutrals = true;
	viewSense->DetectionByAffiliation = SenseAffiliationFilter;
	AIPerception->ConfigureSense(*viewSense);
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ATrenchesDefenseAIController::OnPerceptionUpdated);
	TargetsInSightIndex = 0;
	alreadyHasLineOfSight = false;
}

void ATrenchesDefenseAIController::BeginPlay() {
	Super::BeginPlay();
}

void ATrenchesDefenseAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}


void ATrenchesDefenseAIController::OnPossess(APawn *InPawn) {
	Super::OnPossess(InPawn);
	RunBehaviorTree(BehaviorTree);
	characterControlled = Cast<ATrenchesDefenseCharacter>(InPawn);
	//characterControlledLocalSubSystem = GetWorld()->GetGameInstance()->GetSubsystem<UTrenchesDefLocalPlayerSubsystem>();
	FAISenseID viewID = UAISense::GetSenseID(UAISense_Sight::StaticClass());
	UAISenseConfig_Sight *viewSense = Cast<UAISenseConfig_Sight>(AIPerception->GetSenseConfig(viewID));
	viewSense->SightRadius = characterControlled->CharacterDataAsset->MaxDistanceVision;
	viewSense->LoseSightRadius = viewSense->SightRadius + 20;
	viewSense->PeripheralVisionAngleDegrees = (characterControlled->CharacterDataAsset->DegreeOfVision) /2.f;
	AIPerception->RequestStimuliListenerUpdate();

	//Get objectif location
	UTeamComponent* teamComponent = characterControlled->CharacterDataAsset->CharacterTeamComponent;
	if (teamComponent) {
		//if multi => to change
		if (teamComponent->name.Equals(TEXT("Enemy"), ESearchCase::IgnoreCase)) {
			UTeamWorldSubsystem* TWS = GetWorld()->GetSubsystem<UTeamWorldSubsystem>();
			FVector FinalObjectifToReach = TWS->GetObjectiveToReach(FGameplayTag::RequestGameplayTag(FName("Team.enemy")));
			GetBlackboardComponent()->SetValueAsVector("FinalObjectifToReach", FinalObjectifToReach);
		} 
		//else if ally to add for the multi?
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController teamComponent is null"));
	}
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


void ATrenchesDefenseAIController::Attack(ATrenchesDefenseCharacter* Target) {
	//si un enemy deja target par un allié ne pas lattaquer? ajouter boolean isAttacked si c'est ca

	if (Target && !Target->IsDead) {
		//in his vision
		FVector actualLocation = characterControlled->GetActorLocation();
		FVector targetLocation = Target->GetActorLocation();
		FVector vectorBetweenBoth = targetLocation - actualLocation;
		double dot = FVector::DotProduct(vectorBetweenBoth, characterControlled->GetActorForwardVector()) / vectorBetweenBoth.Size();
		double degresACos = FMath::Acos(dot);

		// Convertissez l'angle en degrés
		double AngleInDegrees = FMath::RadiansToDegrees(degresACos);


		if (AngleInDegrees <= characterControlled->CharacterDataAsset->DegreeOfVision / 2) {

			;
			if (Target->LifeComponent->TakeDamage(characterControlled->CharacterDataAsset->AttackDamage)) { //target is dead
				if (!Target->IsDead) { //init the target to dead, give money to player
					Target->IsDead = true;
					//characterControlledLocalSubSystem->ChangeMoney(characterControlled->SoldierDataAsset->MoneyPerKill);
					ATrenchesDefenseAIController* targetController = Cast<ATrenchesDefenseAIController>(Target->GetController());
					if (targetController) {
						targetController->GetBlackboardComponent()->SetValueAsBool("IsDead", true);
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("targetController attack problem is null"));
					}

					//Give money
					//If a soldier do the kill
					if (!characterControlled->IsZombie) {
						characterControlled->PlayerLocalSubsystem->GiveMoneyEvent.Broadcast(characterControlled->SoldierDataAsset->MoneyPerKill);
					}
				}
				TargetsInSight.RemoveAt(TargetsInSightIndex);
				TargetsInSight.Shrink(); //reduce the array size
				GetBlackboardComponent()->SetValueAsBool("CanAttack", false);
				ChangeTargetToAttack();
			}
		}
		else {
			TargetsInSight.RemoveAt(TargetsInSightIndex);
			TargetsInSight.Shrink(); //reduce the array size
			GetBlackboardComponent()->SetValueAsBool("CanAttack", false);
			ChangeTargetToAttack();
		}
	}
	else { //not in vision but target
		TargetsInSight.RemoveAt(TargetsInSightIndex);
		TargetsInSight.Shrink(); //reduce the array size
		GetBlackboardComponent()->SetValueAsBool("CanAttack", false);
		ChangeTargetToAttack();
	}
}

void ATrenchesDefenseAIController::ChangeTargetToAttack() {
	int targetsInSightArraySize = TargetsInSight.Num();
	if (targetsInSightArraySize == 0) {
		GetBlackboardComponent()->SetValueAsObject("TargetActor", nullptr);
		TargetsInSightIndex = 0;
		alreadyHasLineOfSight = false;
	}
	else {
		for (int i = 0; i < targetsInSightArraySize; i++) {
			ATrenchesDefenseCharacter* target = TargetsInSight[i];
			if (target) { //not nullptr
				TargetsInSightIndex = i;
				GetBlackboardComponent()->SetValueAsObject("TargetActor", TargetsInSight[TargetsInSightIndex]);
				//FVector targetLocation = target->GetActorLocation();
				//FVector characterLocation = characterControlled->GetActorLocation();
				//if the target is in his sight (angle)

				//if the target is in his sight (distance)
				//if (FVector::DistSquared(characterLocation, targetLocation) <= characterControlled->CharacterDataAsset->MaxDistanceVision) {
					//TargetsInSightIndex = i;
				//}
			}
			else if (target && !target->IsDead) { //avoid bugs
				TargetsInSight.RemoveAt(TargetsInSightIndex);
				TargetsInSight.Shrink(); //reduce the array size
			}
		}
	}
}

void ATrenchesDefenseAIController::Die() {
	ATrenchesDefenseGameMode *GM = Cast<ATrenchesDefenseGameMode>(GetWorld()->GetAuthGameMode());
	if (GM) {
		GM->CharacterDead.Broadcast(characterControlled->IsZombie, characterControlled->CharacterDataAsset->CharacterTeamComponent->TeamTag);
	}
	UnPossess();
	characterControlled->Destroy();
	Destroy();
	//lifecomponent a 0, anim, destroy?
	//IsDead = true;
}

void ATrenchesDefenseAIController::OnPerceptionUpdated(AActor *Actor, FAIStimulus Stimulus) {
	//faudra faire une verif de fin de stimulus quand souci réglé pour remove du tableau lacteur qui sort
	ATrenchesDefenseCharacter* target = Cast<ATrenchesDefenseCharacter>(Actor);
	if (target) {
		if (characterControlled) {
			//if the AI is an enemy
			if (characterControlled->CharacterDataAsset->CharacterTeamComponent->TeamTag == UGameplayTagsManager::Get().RequestGameplayTag(FName("Team.Enemy"))) {
				//if he saw an ally
				if (target->CharacterDataAsset->CharacterTeamComponent->TeamTag == UGameplayTagsManager::Get().RequestGameplayTag(FName("Team.Ally"))) {
					int findTmp;
					if (TargetsInSight.Find(target,findTmp)==false) {
						TargetsInSight.Add(target);
						if (!alreadyHasLineOfSight) {
							GetBlackboardComponent()->SetValueAsObject("TargetActor", TargetsInSight[TargetsInSightIndex]);
							alreadyHasLineOfSight = true;
						}
					}
				}
			}
			//if the AI is an ally
			else if (characterControlled->CharacterDataAsset->CharacterTeamComponent->TeamTag == UGameplayTagsManager::Get().RequestGameplayTag(FName("Team.Ally"))) {
				//if he saw an enemy
				if (target->CharacterDataAsset->CharacterTeamComponent->TeamTag == UGameplayTagsManager::Get().RequestGameplayTag(FName("Team.Enemy"))) {
					int findTmp;
					if (TargetsInSight.Find(target, findTmp) == false) {
						TargetsInSight.Add(target);
						if (!alreadyHasLineOfSight) {
							GetBlackboardComponent()->SetValueAsObject("TargetActor", TargetsInSight[TargetsInSightIndex]);
							alreadyHasLineOfSight = true;
						}
					}
				}
			}
		}
	}
	
	
		
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, Actor->GetName());
	//NE PAS OUBLIE DE FAIRE UN IF(! SON TEAM COMPONENT) POUR QUE LE FONCTION FONCTIONNE PEUT IMPORTE LA TEAM zombie/soldat joueur1/joueur2 multi
	//verif nbr zombie vu pour soldat depuis iaperception directement voir si nbr correspond soldierdataasset
	//passer bool a true etc dans blackboard

}

void ATrenchesDefenseAIController::setWalkSpeed(int speed) {
	if (characterControlled) {
		UCharacterMovementComponent *characterMovement = characterControlled->GetCharacterMovement();
		characterMovement->MaxWalkSpeed = speed;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController::setWalkSpeed characterControlled is null"));
	}
}