// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayerLimitation.h"
// Sets default values
ACameraPlayerLimitation::ACameraPlayerLimitation()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create BoxComponent to represent the volume
	ZoneVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("ZoneVolume"));
	RootComponent = ZoneVolume;

	// ZoneVolume configuration
	ZoneVolume->SetRelativeLocation(FVector::ZeroVector);
	ZoneVolume->SetRelativeRotation(FRotator::ZeroRotator);
	ZoneVolume->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	// Bind event for when other actors end overlap with this volume
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

//using endoverlap for performance, less events generated than on overlap
void ACameraPlayerLimitation::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){
	if (OtherActor && OtherActor->IsA(ACameraPlayer::StaticClass())) {
		ACameraPlayer* CameraPlayerTmp = Cast<ACameraPlayer>(OtherActor);
		if (CameraPlayerTmp->CameraGoingLeft) CameraPlayerTmp->LimitReachedLeft = true;
		if (CameraPlayerTmp->CameraGoingRight) CameraPlayerTmp->LimitReachedRight = true;
		if (CameraPlayerTmp->CameraGoingTop) CameraPlayerTmp->LimitReachedTop = true;
		if (CameraPlayerTmp->CameraGoingBottom) CameraPlayerTmp->LimitReachedBottom = true;
		//previous position, rollback
		CameraPlayerTmp->SetActorLocation(CameraPlayerTmp->PreviousLocation);
	}
}

