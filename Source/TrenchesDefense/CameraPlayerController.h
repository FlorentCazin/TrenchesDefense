// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CameraPlayer.h"
#include "CameraPlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TRENCHESDEFENSE_API ACameraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
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

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
};
