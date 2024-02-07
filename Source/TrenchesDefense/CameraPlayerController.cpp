// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "CameraPlayer.h"
#include "Engine/World.h"


void ACameraPlayerController::BeginPlay() {
	bShowMouseCursor = true;
	//CameraPlayer = Cast<ACameraPlayer>(GetPawn());
	//bEnableClickEvents = true;
	//bEnableMouseOverEvents = true;
}

void ACameraPlayerController::Tick(float DeltaSeconds) {
	ACameraPlayer* CameraPlayer = Cast<ACameraPlayer>(GetPawn());
	float x, y;
	if (GetMousePosition(x, y)) {
			const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY()); //take the max X,Y of the game screen
			if (x <= 5) { //at left -> go right
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer->RightAxisMovement();
			}
			if (x >= ViewportSize.X-5) { //at right -> go left
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer->LeftAxisMovement();
			}
			if (y <= 5) { //at top -> go down
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer->DownAxisMovement();
			}
			if (y >= ViewportSize.Y - 5) { //at bottom -> go top
				CameraPlayer->PreviousLocation = CameraPlayer->GetActorLocation();
				CameraPlayer->TopAxisMovement();
			}
	}
}