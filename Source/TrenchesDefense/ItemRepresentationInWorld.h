// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrenchesDefenseCharacter.h"
#include "SoldierDataAsset.h"
#include "ItemRepresentationInWorld.generated.h"

UCLASS(Blueprintable)
class TRENCHESDEFENSE_API AItemRepresentationInWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemRepresentationInWorld();

	//class to spawn from the item
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="SoldierToSpawnItemRepresentation")
	TSubclassOf<ATrenchesDefenseCharacter> SoldierClass;

	//soldierdataasset of the soldier to spawn
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SoldierToSpawnItemRepresentation")
	USoldierDataAsset* soldierDataAsset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	ATrenchesDefenseCharacter* SpawnSoldier(FVector CursorHitLocation, int money);

};
