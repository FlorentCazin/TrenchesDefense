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

ATrenchesDefenseCharacter* AItemRepresentationInWorld::SpawnSoldier(FVector CursorHitLocation) {
	if (SoldierClass) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SoldierClass exist!"));
		//FActorSpawnParameters SpawnParams;
		return GetWorld()->SpawnActor<ATrenchesDefenseCharacter>(SoldierClass, CursorHitLocation, FRotator::ZeroRotator);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("SoldierClass is not defined"));
		return nullptr;
	}
}