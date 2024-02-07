// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayerLimitation.h"
// Sets default values
ACameraPlayerLimitation::ACameraPlayerLimitation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create BoxComponent to represent the volume
	ZoneVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("ZoneVolume"));
	RootComponent = ZoneVolume;

	// Set volume location, rotation, and scale as needed
	ZoneVolume->SetRelativeLocation(FVector::ZeroVector);
	ZoneVolume->SetRelativeRotation(FRotator::ZeroRotator);
	ZoneVolume->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f)); // You can adjust the scale as needed

	// Bind event for when other actors overlap with this volume
	ZoneVolume->OnComponentEndOverlap.AddDynamic(this, &ACameraPlayerLimitation::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ACameraPlayerLimitation::BeginPlay()
{
	Super::BeginPlay();

	//si camera en dehors de la zone, alors la placer automatiquement au centre de la zone?
	
}

// Called every frame
void ACameraPlayerLimitation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACameraPlayerLimitation::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){
	if (OtherActor && OtherActor->IsA(ACameraPlayer::StaticClass())) {
		ACameraPlayer* CameraPlayerTmp = Cast<ACameraPlayer>(OtherActor);
		CameraPlayerTmp->SetActorLocation(CameraPlayerTmp->PreviousLocation);
	}
}

