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

	//zone
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LimitationCameraPlayer")
	UBoxComponent *ZoneVolume;

	//Get the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LimitationCameraPlayer")
	ACameraPlayer* CameraPlayer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	//out of limitation
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
