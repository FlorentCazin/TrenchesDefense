// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierDefaultSpawn.h"

// Sets default values
ASoldierDefaultSpawn::ASoldierDefaultSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoldierDefaultSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoldierDefaultSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

