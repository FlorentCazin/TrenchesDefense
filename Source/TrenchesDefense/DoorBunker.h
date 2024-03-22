// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSequenceActor.h"
#include "DoorBunker.generated.h"

UCLASS(Blueprintable)
class TRENCHESDEFENSE_API ADoorBunker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorBunker();

	UPROPERTY(EditAnywhere, category="DoorBunker")
	ALevelSequenceActor* AnimationDoor;

	UPROPERTY(EditAnywhere, category = "DoorBunker")
	UStaticMesh* Door;

	UPROPERTY(EditAnywhere, category = "DoorBunker")
	USoundWave* DoorSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void PlayDoorBunker();

	UFUNCTION(BlueprintCallable)
	void ReverseDoorBunker();
};
