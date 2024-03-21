// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "ItemRepresentationInWorld.h"
#include "TrenchesDefenseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SoldierDefaultSpawn.h"
#include "LimitationSoldiersSpawningZone.h"
#include "Kismet/KismetMathLibrary.h"
#include "CameraPlayerLimitation.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TrenchesDefenseAIController.h"

ACameraPlayerController::ACameraPlayerController(){
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	RightClickPressed = false;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	ScreenBorderLimitationForCameraLocation = 50;
	DEFINE_MAX_ITERATION_POSSIBLE_GIVED_BY_VISIBLE_HIT_BY_CHANNEL = 2;
	//GetLocalPlayer()->GetSubsystem<>();
}


void ACameraPlayerController::BeginPlay() {
	//Allow BeginPlay BP
	Super::BeginPlay();

	CameraPlayer = Cast<ACameraPlayer>(GetPawn());
	InitialCameraLocation = CameraPlayer->GetActorLocation();
	InitialCameraRotation = CameraPlayer->GetActorRotation();
}

void ACameraPlayerController::Tick(float DeltaSeconds) {
	//Allow EventTick BP
	Super::Tick(DeltaSeconds);

	float x, y;
	if (GetMousePosition(x, y)) {
		if (RightClickPressed) { //Ratation movement //ici faudra ajouter un boolean si on selectionne une unit� ca devient le clique droit de rotation de lunit�?
			//if (AxisXPriority) { //Left Right
				if (PreviousMouseLocationX < x) {
					//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("go vers gauche"));
					CameraPlayer->LeftAxisRotation();
				}
				if (PreviousMouseLocationX > x) {
					//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("go vers droite"));
					CameraPlayer->RightAxisRotation();
				}
			//}
			//else {
				if (PreviousMouseLocationY < y) { //Top Down
					//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("go vers haut"));
					CameraPlayer->TopAxisRotation();
				}
				if (PreviousMouseLocationY > y) {
					//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("go vers bas"));
					CameraPlayer->DownAxisRotation();
				}
			//}
		}
		else { //Axis movement
			const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY()); //take the max X,Y of the game screen
			if (x <= ScreenBorderLimitationForCameraLocation) { //at left
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer->LeftAxisMovement();
			}
			if (x >= ViewportSize.X - ScreenBorderLimitationForCameraLocation) { //at right
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer ->RightAxisMovement();
			}
			if (y <= ScreenBorderLimitationForCameraLocation) { //at top
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer->TopAxisMovement();
			}
			if (y >= ViewportSize.Y - ScreenBorderLimitationForCameraLocation) { //at bottom
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer->DownAxisMovement();
			}
		}
		//Used for the rotation
		PreviousMouseLocationX = x;
		PreviousMouseLocationY = y;
	}


	//Spawning system
	if (AlreadySelectingSoldier) { //Execute only if the player is playing the spawning system
		FVector HitImpactLocation = FVector(0.f,0.f,0.f);
		TArray<FHitResult> hitResult = TickGetMultiLineTraceByChannel();
		for (auto& Hit : hitResult) {
			HitImpactLocation = Hit.ImpactPoint;
			NumberOfHitedElementForOverlap++; //incr this variable to know how hitresult by multi line trace
			OverlapSoldierIsInLimitation = false; //reset overlap value for each multi trace line by channel (to know if it's red or green)
			if (SoldierIsPlaced) { //if the player is in the Rotation step
				if (Hit.bBlockingHit) { //looking the last Hit to rotate, avoid bug with cone previsualization
					TickSetRotationFollowingCursor(HitImpactLocation); //taking the cursor for the rotation each ticks
				}
			}
			else { //so the player is in the overlap step
				if (Hit.GetActor()->IsA(ALimitationSoldiersSpawningZone::StaticClass()) && AlreadySelectingSoldier) { //If we overlap the spawing limitation and the player have a soldier selected
					if (!OverlapSoldierIsInLimitation) { //if not already, avoid doing useless actions if it's already done
						OverlapSoldierIsInLimitation = true;
						//inside color
						SoldierToSpawn->ChangeSoldierColor(SoldierToSpawn->ColorInsideLimitation);
					}
				}
				else { //if the player is out of the soldier box spawning limitation
					if (NumberOfHitedElementForOverlap == DEFINE_MAX_ITERATION_POSSIBLE_GIVED_BY_VISIBLE_HIT_BY_CHANNEL) { //If we are at the end of the for loop
						//Outside color
						SoldierToSpawn->ChangeSoldierColor(SoldierToSpawn->ColorOutOfLimitation);
					}
				}
			}
		}
		NumberOfHitedElementForOverlap = 0; //Reset for each loop executed
		TickMoveActorForPrevisualizationDuringOverlap(HitImpactLocation); //Soldier follow the cursor
	}
}

void ACameraPlayerController::ResetCameraLocation() {
	CameraPlayer->SetActorLocation(InitialCameraLocation);
	CameraPlayer->SetActorRotation(InitialCameraRotation);
}


bool ACameraPlayerController::OnClickSpawnSoldier(FVector ItemRepresentationLocation) {
	//Set intensity soldier intense

	//If the player is not already using the spawing/edit functionality and the HitActor is a AItemRepresentationInWorld
	if (!AlreadySelectingSoldier && !BlockSpawnSoldier && ActorHited && ActorHited->IsA(AItemRepresentationInWorld::StaticClass())) {
		try{ //try here is useless like we check if IsA(AItemRepresentationInWorld), but it's to have an idea of how LOG and exception could be used.
			AItemRepresentationInWorld *soldierItemRepresentation = Cast<AItemRepresentationInWorld>(ActorHited);
			if (soldierItemRepresentation) { //Cast is correct
				SoldierToSpawn = soldierItemRepresentation->SpawnSoldier(ItemRepresentationLocation);
				if (SoldierToSpawn) {
					SoldierToSpawn->PlayerLocalSubsystem = GetLocalPlayer()->GetSubsystem<UTrenchesDefLocalPlayerSubsystem>();
					SoldierToSpawn->ChangeSoldierEmissive(SoldierToSpawn->MaxEmissiveColor);
					AlreadySelectingSoldier = true;
					BlockSpawnSoldier = true;
					return true;
				}
			}
			else {
				//Error during the cast
				UE_LOG(LogTemp, Log, TEXT("Cast to ItemRepresentationInWorld problem"));
			}
		}
		catch (const std::exception& e){ //Exception throwed
			UE_LOG(LogTemp, Log, TEXT("Exception: %s"), *FString(e.what()));
		}
	}
	return false;
}


bool ACameraPlayerController::OnClickSoldierToMove() {
	//If we click on a soldier already placed
	if (!AlreadySelectingSoldier && !BlockSpawnSoldier && ActorHited && ActorHited->IsA(ATrenchesDefenseCharacter::StaticClass())) {
		InitialSoldierSelectedRotation = ActorHited->GetActorRotation();
		UWorld* World = GetWorld(); //world reference
		if (World) {
			SoldierToSpawn = Cast<ATrenchesDefenseCharacter>(ActorHited);
			if (SoldierToSpawn) {
				SoldierToSpawn->ChangeSoldierEmissive(SoldierToSpawn->MaxEmissiveColor);
				//Get the SoldierDefaultSpawn object in the world
				AActor* SoldierDefaultSpawnZone = UGameplayStatics::GetActorOfClass(World, ASoldierDefaultSpawn::StaticClass());
				if (SoldierDefaultSpawnZone) {
					//Set from where the soldier will start to move
					SaveSpawnActorValue = SoldierDefaultSpawnZone->GetActorLocation();
					SoldierDefaultSpawnZone->SetActorLocation(SoldierToSpawn->GetActorLocation());
					AlreadySelectingSoldier = true;
					BlockSpawnSoldier = true;
					return true;
				}
				else {
					UE_LOG(LogTemp, Log, TEXT("Cannot retrieve SoldierDefaultSpawnZone from the world"));
				}
			}
			else {
				UE_LOG(LogTemp, Log, TEXT("Cast to ATrenchesDefenseCharacter problem"));
			}
		}
	}
	return false;
}


void ACameraPlayerController::OnClickInitFinalActorLocation(FVector ActorLocation) {
	//If the player already selectionning a soldier and the click is inside the LimitationSoldiersSpawningZone
	if (AlreadySelectingSoldier && ActorHited && ActorHited->IsA(ALimitationSoldiersSpawningZone::StaticClass())) {
		//Multi line, so multiple hits, we know that we can hit 2 things, the soldier box limitation zone or the floor, here we check if we have hited before the floor the box limitation
		ClickSpawningSoldierIsInLimitation = true;
	}
	else { //If it's not the box limitation, it's maybe the location to spawn the soldier
		if (ClickSpawningSoldierIsInLimitation && !SoldierIsPlaced) { //If we hit previously the box limitation, and the soldier is not already placed (in previsualization) to limit the access of this system
			//set the final location of the soldier
			SpawningSoldierLocation = ActorLocation;
		}
		else {
			if (AlreadySelectingSoldier && !SoldierIsPlaced) {
				//WIDGET TO SHOW OUT OF LIMITATION
			}
			//else simple click
		}
	}
}

void ACameraPlayerController::OnClickSetFinalActorLocation() {
	SoldierToSpawn->SetActorLocation(SpawningSoldierLocation); //optionnal, event tick doing it too
	SoldierIsPlaced = true;
	OverlapSoldierIsInLimitation = false;
}


void ACameraPlayerController::TickSetRotationFollowingCursor(FVector CursorWorldLocation) {
	//Look at the cursor and apply the rotation for the soldier forward vector is looking the world cursor location
	UWorld* World = GetWorld();
	DrawDebugCone(World,
		SoldierToSpawn->GetActorLocation(),
		SoldierToSpawn->GetActorForwardVector(),
		SoldierToSpawn->CharacterDataAsset->MaxDistanceVision,
		abs(FMath::DegreesToRadians(SoldierToSpawn->CharacterDataAsset->DegreeOfVision / 2.f)),
		0,
		32,
		FColor(SoldierToSpawn->DefaultColor.ToFColor(true)),
		false,
		0.05f);
	SoldierSavedZRotation = UKismetMathLibrary::FindLookAtRotation(SoldierToSpawn->GetActorForwardVector(), CursorWorldLocation - SoldierToSpawn->GetActorLocation()).Yaw;
	SoldierToSpawn->SetActorRotation(FQuat(FRotator(0.f,SoldierSavedZRotation,0.f)));
}


void ACameraPlayerController::TickMoveActorForPrevisualizationDuringOverlap(FVector CursorWorldLocation) {
	if (AlreadySelectingSoldier && !SoldierIsPlaced) { //If the player is already selecting a soldier but in Previsualization step (not placed yet)
		if (SoldierToSpawn) {
			FVector newLocation = CursorWorldLocation + FVector(0.f, 0.f, 90); //+90 on Z (Yaw) to fit perfectly with the floor
			SoldierToSpawn->SetActorLocation(newLocation);
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("SoldierToSpawn is not valid!"))
			ProblemSpawningActorResetValues(); //refund the player, reset values
		}
	}
}

void ACameraPlayerController::ProblemSpawningActorResetValues() {
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("ProblemSpawningActorResetValues"));
	ClickSpawningSoldierIsInLimitation = false;
	AlreadySelectingSoldier = false;
	OverlapSoldierIsInLimitation = false;
	SoldierIsPlaced = false;
	BlockSpawnSoldier = false;/*
	if (SoldierToSpawn) {
		SoldierToSpawn->Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Soldier destroyed"));
	}*/
	//Call widget refund player?
	UE_LOG(LogTemp, Log, TEXT("Fail, destroying actor, reset values, refund Player!"))
}

TArray<FHitResult> ACameraPlayerController::OnClickGetMultiLineTraceByChannel() {
	UWorld* World = GetWorld(); //world reference
	TArray<FHitResult> multiHits;
	if (World) {
		AActor* ignoredActor = UGameplayStatics::GetActorOfClass(World, ACameraPlayerLimitation::StaticClass());
		TArray<AActor*> ignoreActors = { ignoredActor };
		FVector startLocation = GetPawn()->GetActorLocation();
		FVector2D mousePosition;
		GetMousePosition(mousePosition.X, mousePosition.Y);
		FVector WorldPosition, WorldDirection;
		DeprojectScreenPositionToWorld(mousePosition.X,mousePosition.Y,WorldPosition,WorldDirection);
		FVector endLocation=WorldPosition + (WorldDirection*10000.f);
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActors(ignoreActors);
		World->LineTraceMultiByChannel(
			multiHits,
			startLocation,
			endLocation,
			ECC_Visibility,
			CollisionParams
		);
		return multiHits;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GetWorld problem!"));
		return multiHits;
	}
}

TArray<FHitResult> ACameraPlayerController::TickGetMultiLineTraceByChannel() {
	UWorld* World = GetWorld(); //world reference
	TArray<FHitResult> multiHits;
	if (World) {
		AActor* ignoredActor = UGameplayStatics::GetActorOfClass(World, ATrenchesDefenseCharacter::StaticClass());
		TArray<AActor*> ignoreActors = { ignoredActor };
		FVector startLocation = GetPawn()->GetActorLocation();
		FVector2D mousePosition;
		GetMousePosition(mousePosition.X, mousePosition.Y);
		FVector WorldPosition, WorldDirection;
		DeprojectScreenPositionToWorld(mousePosition.X, mousePosition.Y, WorldPosition, WorldDirection);
		FVector endLocation = WorldPosition + (WorldDirection * 10000.f);
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActors(ignoreActors);
		World->LineTraceMultiByChannel(
			multiHits,
			startLocation,
			endLocation,
			ECC_Visibility,
			CollisionParams
		);
		return multiHits;
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("GetWorld problem!"));
		return multiHits;
	}
}

void ACameraPlayerController::OnLeftClick() {
	TArray<FHitResult> HitResult = OnClickGetMultiLineTraceByChannel();
	for (auto& Hit : HitResult) {
		ActorHited = Hit.GetActor();
		FVector HitLocation = Hit.ImpactPoint; //impact location
		if (!OnClickSpawnSoldier(HitLocation)) { //try if the player Click on item representation to spawn soldier
			if (!OnClickSoldierToMove()) {  //try if the player Click on soldier already spawned
				OnClickInitFinalActorLocation(HitLocation); //try if the player already selected a soldier and click to choose the final location
			}
		}
	}
	if (ClickSpawningSoldierIsInLimitation && !SoldierIsPlaced) { //�f we're finished the for loop, and we have selected the final location, set the location
		OnClickSetFinalActorLocation();
		//change color to default
		SoldierToSpawn->ChangeSoldierColor(SoldierToSpawn->DefaultColor);
	}
	else {
		if (SoldierIsPlaced) { //if the player is in the rotation step
			AlreadySelectingSoldier = false;
			SoldierIsPlaced = false;
			ClickSpawningSoldierIsInLimitation = false;

			//spawn at SoldierDefaultSpawn actor location
			UWorld* World = GetWorld(); //world reference
			AActor* spawnActor = UGameplayStatics::GetActorOfClass(World, ASoldierDefaultSpawn::StaticClass());
			if (spawnActor) {
				SoldierToSpawn->ChangeSoldierEmissive(0.f);
				SoldierToSpawn->SetActorLocation(spawnActor->GetActorLocation());
				spawnActor->SetActorLocation(SaveSpawnActorValue);
				//AI
				ATrenchesDefenseAIController* SoldierController = Cast<ATrenchesDefenseAIController>(SoldierToSpawn->Controller);
				if (SoldierController) {
					SoldierController->MoveCharacterToLocationAndRotate(SpawningSoldierLocation, FRotator(0.f, SoldierSavedZRotation, 0.f));
					BlockSpawnSoldier = false;
					SoldierToSpawn->AlreadySpawned = true;
					SoldierToSpawn = nullptr;
				}
			}
			else { //spawning default actor does not exist
				UE_LOG(LogTemp, Log, TEXT("Soldier spawning default acrot does not exist!"))
				ProblemSpawningActorResetValues();
			}
		}
	}
}

void ACameraPlayerController::OnClickCancelLastAction() {
	if (SoldierIsPlaced && ClickSpawningSoldierIsInLimitation && AlreadySelectingSoldier) {
		SoldierIsPlaced = false;
		ClickSpawningSoldierIsInLimitation = false;
	}
	else {
			BlockSpawnSoldier = false;
			AlreadySelectingSoldier = false;
			if (!SoldierToSpawn->AlreadySpawned) {
				SoldierToSpawn->Destroy();
				//refind le player
			}
			else { //problems, in progress
				//spawn at SoldierDefaultSpawn actor location
				UWorld* World = GetWorld(); //world reference
				AActor* spawnActor = UGameplayStatics::GetActorOfClass(World, ASoldierDefaultSpawn::StaticClass());
				if (spawnActor) {
					SoldierToSpawn->ChangeSoldierColor(SoldierToSpawn->DefaultColor);
					SoldierToSpawn->ChangeSoldierEmissive(0.f);
					SoldierToSpawn->SetActorLocation(spawnActor->GetActorLocation());
					SoldierToSpawn->SetActorRotation(InitialSoldierSelectedRotation);
					spawnActor->SetActorLocation(SaveSpawnActorValue);
					SoldierToSpawn = nullptr;
				}
			}
		}
}