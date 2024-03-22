// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelMusic.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ALevelMusic::ALevelMusic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelMusic::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::SpawnSound2D(this, MusicToPlay);
}

// Called every frame
void ALevelMusic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

