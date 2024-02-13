// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

ACameraPlayerController::ACameraPlayerController(){
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	RightClickPressed = false;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	ScreenBorderLimitationForCameraLocation = 50;
}


void ACameraPlayerController::BeginPlay() {
	CameraPlayer = Cast<ACameraPlayer>(GetPawn());
}

void ACameraPlayerController::Tick(float DeltaSeconds) {
	//Giving the possibility to add things in the BP eventtick
	Super::Tick(DeltaSeconds);

	float x, y;
	if (GetMousePosition(x, y)) {
		if (RightClickPressed) { //Ratation movement //ici faudra ajouter un boolean si on selectionne une unité ca devient le clique droit de rotation de lunité?
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
}