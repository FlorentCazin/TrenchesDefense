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
		if (GEngine) {
		    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("X = %f , Y = %f"),x,y));

			const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY()); //take the max X,Y of the game screen
			if (x <= 5) { //at left -> go right
				CameraPlayer->RightAxisMovement();
			}
			if (x >= ViewportSize.X-5) { //at right -> go left
				CameraPlayer->LeftAxisMovement();
			}
			if (y <= 5) { //at top -> go down
				CameraPlayer->DownAxisMovement();
			}
			if (y >= ViewportSize.Y - 5) { //at bottom -> go top
				CameraPlayer->TopAxisMovement();
			}
		}
	}

}
