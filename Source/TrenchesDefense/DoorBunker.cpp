// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorBunker.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoorBunker::ADoorBunker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorBunker::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorBunker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorBunker::PlayDoorBunker() {
	UGameplayStatics::SpawnSound2D(this, DoorSound);
}

void ADoorBunker::ReverseDoorBunker() {

}

