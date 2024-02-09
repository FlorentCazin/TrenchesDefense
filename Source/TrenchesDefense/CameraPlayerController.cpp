// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


void ACameraPlayerController::BeginPlay() {
	bShowMouseCursor = true;
	CameraPlayer = Cast<ACameraPlayer>(GetPawn());
	RightClickPressed = false;

	//CameraPlayer = Cast<ACameraPlayer>(GetPawn());
	//bEnableClickEvents = true;
	//bEnableMouseOverEvents = true;
}

void ACameraPlayerController::Tick(float DeltaSeconds) {
	float x, y;
	if (GetMousePosition(x, y)) {
		if (RightClickPressed) {
			
		}
		else {
			const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY()); //take the max X,Y of the game screen
			if (x <= 50) { //at left -> go right
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer->RightAxisMovement();
			}
			if (x >= ViewportSize.X - 50) { //at right -> go left
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer->LeftAxisMovement();
			}
			if (y <= 50) { //at top -> go down
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer->DownAxisMovement();
			}
			if (y >= ViewportSize.Y - 50) { //at bottom -> go top
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer->TopAxisMovement();
			}
		}
	}
}