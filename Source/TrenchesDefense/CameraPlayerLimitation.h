// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CameraPlayer.h"
#include "CameraPlayerLimitation.generated.h"

UCLASS(Blueprintable)
class TRENCHESDEFENSE_API ACameraPlayerLimitation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraPlayerLimitation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LimitationCameraPlayer")
	UBoxComponent *ZoneVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LimitationCameraPlayer")
	ACameraPlayer* CameraPlayer;

	//*function for the event endOverlap
	//UPROPERTY(BlueprintAssignable, Category="LimitationCameraPlayer")
	//FActorEndOverlapSignature OnActorEndOverlap;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:/*
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	*/
};