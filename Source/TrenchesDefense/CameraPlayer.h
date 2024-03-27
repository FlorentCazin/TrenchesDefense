// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "CameraPlayer.generated.h"

UCLASS(Blueprintable)
class TRENCHESDEFENSE_API ACameraPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPlayer();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	FVector PreviousLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UBoxComponent* BoxCollision;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	bool CameraGoingLeft;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	bool CameraGoingRight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	bool CameraGoingTop;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	bool CameraGoingBottom;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	bool LimitReachedTop;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	bool LimitReachedBottom;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	bool LimitReachedLeft;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	bool LimitReachedRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraInputsAction")
	float CameraSpeedMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraInputsAction")
	float CameraSpeedRotation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandle1;
	FTimerHandle TimerHandle2;
	FTimerHandle TimerHandle3;
	FTimerHandle TimerHandle4;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void LeftAxisMovement();

	UFUNCTION(BlueprintCallable)
	void RightAxisMovement();

	UFUNCTION(BlueprintCallable)
	void TopAxisMovement();

	UFUNCTION(BlueprintCallable)
	void DownAxisMovement();

	UFUNCTION(BlueprintCallable)
	void LeftAxisRotation();

	UFUNCTION(BlueprintCallable)
	void RightAxisRotation();

	UFUNCTION(BlueprintCallable)
	void TopAxisRotation();

	UFUNCTION(BlueprintCallable)
	void DownAxisRotation();

	UFUNCTION(BlueprintCallable)
	void Zoom();

	UFUNCTION(BlueprintCallable)
	void UnZoom();

	//for the max limitation (camera going previous position)
	void DelayedReintialiseBooleanLimitationCameraTop();
	void DelayedReintialiseBooleanLimitationCameraBottom();
	void DelayedReintialiseBooleanLimitationCameraLeft();
	void DelayedReintialiseBooleanLimitationCameraRight();

};
