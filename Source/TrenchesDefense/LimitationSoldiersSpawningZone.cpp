// Fill out your copyright notice in the Description page of Project Settings.


#include "LimitationSoldiersSpawningZone.h"

// Sets default values
ALimitationSoldiersSpawningZone::ALimitationSoldiersSpawningZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create boxcollision
	BoxLimitation = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox Zone Limitation"));
	BoxLimitation->SetupAttachment(RootComponent);
	BoxLimitation->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	// Ignore all collisions except Visibility
	BoxLimitation->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxLimitation->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void ALimitationSoldiersSpawningZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALimitationSoldiersSpawningZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

