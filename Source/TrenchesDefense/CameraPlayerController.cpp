// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


void ACameraPlayerController::BeginPlay() {
	bShowMouseCursor = true;
	CameraPlayer = Cast<ACameraPlayer>(GetPawn());
	RightClickPressed = false;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ACameraPlayerController::Tick(float DeltaSeconds) {
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
			if (x <= 50) { //at left
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer->LeftAxisMovement();
			}
			if (x >= ViewportSize.X - 50) { //at right
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer ->RightAxisMovement();
			}
			if (y <= 50) { //at top
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer->TopAxisMovement();
			}
			if (y >= ViewportSize.Y - 50) { //at bottom
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer->DownAxisMovement();
			}
		}
		//Used for the rotation
		PreviousMouseLocationX = x;
		PreviousMouseLocationY = y;
	}
}