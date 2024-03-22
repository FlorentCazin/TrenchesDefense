// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemRepresentationInWorld.h"

// Sets default values
AItemRepresentationInWorld::AItemRepresentationInWorld()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemRepresentationInWorld::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemRepresentationInWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ATrenchesDefenseCharacter* AItemRepresentationInWorld::SpawnSoldier(FVector CursorHitLocation, int money) {
	if (SoldierClass) {
		if (money >= soldierDataAsset->Cost) {
			return GetWorld()->SpawnActor<ATrenchesDefenseCharacter>(SoldierClass, CursorHitLocation, FRotator::ZeroRotator);
		}
		else {
			return nullptr;
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("SoldierClass is not defined"));
		return nullptr;
	}
}