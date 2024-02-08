// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CameraPlayer.h"
#include "CameraPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TRENCHESDEFENSE_API ACameraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACameraPlayer* CameraPlayer;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
};
