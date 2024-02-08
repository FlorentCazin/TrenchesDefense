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
	int CameraSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera")
	FVector PreviousLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UBoxComponent* BoxCollision;

	//la hauteur max de la camera c sa position de debut.
	//on aura la possibilité de zoomer et tourner
	//de se déplacer dans axe donné

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

};
