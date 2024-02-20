// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CameraPlayer.h"
#include "TrenchesDefenseCharacter.h"
#include "CameraPlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRENCHESDEFENSE_API ACameraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACameraPlayerController();

	ACameraPlayer* CameraPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CameraInputsAction")
	bool RightClickPressed;

	//Priority of the axe used
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraInputsAction")
	bool AxisXPriority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CameraInputsAction")
	float PreviousMouseLocationX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraInputsAction")
	float PreviousMouseLocationY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraInputsAction")
	int ScreenBorderLimitationForCameraLocation;

	//Spawning soldier variables

	//Check if the soldier is in the limitation to accept or not is final position
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierSpawningSystem")
	bool ClickSpawningSoldierIsInLimitation;

	//Check if the player already selecting a soldier (spawn/overlap)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierSpawningSystem")
	bool AlreadySelectingSoldier;

	//Check if the soldier is in the limitation when following the mouse's cursor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierSpawningSystem")
	bool OverlapSoldierIsInLimitation;

	//Check if the soldier is placed to do the next step => rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierSpawningSystem")
	bool SoldierIsPlaced;

	//Check if the player use already the spawn/edit functionnality on a soldier, avoid error
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierSpawningSystem")
	bool BlockSpawnSoldier;

	//Spawn the soldier at the soldier's item representation location or the soldier is last location (depend of the cases)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierSpawningSystem")
	FVector SpawningSoldierLocation;

	//Saving the default location of the spawning soldiers actor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierSpawningSystem")
	FVector SaveSpawnActorValue;

	//Saving the soldier created or to edit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierSpawningSystem")
	ATrenchesDefenseCharacter *SoldierToSpawn; //OU UTILISER ICI JUSTE ATRENCHESDEFENSECHARACTER pointeur et verifier avec un cast etc avant dans le code anyway? car pas pointeur donc probleme pour modifier value?

	//Saving for each hit the actor hited
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierSpawningSystem")
	AActor *ActorHited;

	//Saving the Z rotation of the soldier to make him going at the final location with the correct rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierSpawningSystem")
	float SoldierSavedZRotation;

	//Number of hitedElement used during the Overlap to check if we hit the box spawning limitation or not, necessary because of the trace multi line by channel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierSpawningSystem")
	int NumberOfHitedElementForOverlap;

	//Max possible iteration, usefull to change the soldat's color, necessary because of the trace multi line by channel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoldierSpawningSystem")
	int DEFINE_MAX_ITERATION_POSSIBLE_GIVED_BY_VISIBLE_HIT_BY_CHANNEL;





protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	void OnLeftClick();

	//Spawning soldier variables

	//Function to create a multi trace line by channel exclusivly for OnClick spawning soldier system, return an array of HitResult
	UFUNCTION(BlueprintCallable)
	TArray<FHitResult> OnClickGetMultiLineTraceByChannel();

	//Function to create a multi trace line by channel exclusivly during the EventTick used for spawning soldier system, return an array of HitResult
	UFUNCTION(BlueprintCallable)
	TArray<FHitResult> TickGetMultiLineTraceByChannel();

	//Function used to spawn a soldier when clicking on is item representation. Taking a vector of the hit location, returning a boolean if we click or not on the item representation
	UFUNCTION(BlueprintCallable)
	bool OnClickSpawnSoldier(FVector ItemRepresentationLocation);

	//Function used to get/init the final choise of the player for the soldier's location. Taking the location of the floor where to spawn the actor gived by the mouse's click
	UFUNCTION(BlueprintCallable)
	void OnClickInitFinalActorLocation(FVector ActorLocation);

	//Function Used to place the soldier using the location saved in the OnClickInitFinalActorLocation function to go to the next step => rotation
	UFUNCTION(BlueprintCallable)
	void OnClickSetFinalActorLocation();

	//Function used to set and save for each tick still the final click the rotation on Z of the actor using the mouse's cursor, taking CursorWorldLocation, the vector representing the world mouse location
	UFUNCTION(BlueprintCallable)
	void TickSetRotationFollowingCursor(FVector CursorWorldLocation);

	//Function used to moove the selectionned actor and make him following the mouse's cursor during the previsualization step (overlap). Taking FVector as parameter representing the cursor's location in the world
	UFUNCTION(BlueprintCallable)
	void TickMoveActorForPrevisualizationDuringOverlap(FVector CursorWorldLocation);

	//Function used if a problem happens during the spawning/edit system. Removing the actor, refund the player and reset variables
	UFUNCTION(BlueprintCallable)
	void ProblemSpawningActorResetValues();

	//Function used when the player click on a soldier already spawned, to change is location/rotation. Return a boolean if this is the case (false if he's not clicking on a soldier)
	UFUNCTION(BlueprintCallable)
	bool OnClickSoldierToMove();

	//Function used when the player click in a specific touch gived in BP, to rollback is action. IN PROGRESS
	//UFUNCTION(BlueprintCallable)
	//bool OnClickCancelLastAction();

	//Function IN PROGRESS, to remove collision during previsualization
	//UFUNCTION(BlueprintCallable)
	//bool IgnorePawnCollision();

	//Function IN PROGRESS, to put back collision after previsualization
	//UFUNCTION(BlueprintCallable)
	//void IgnorePawnCollision();






















	
};
