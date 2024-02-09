// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayer.h"

// Sets default values
ACameraPlayer::ACameraPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BoxCollision configuration
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CameraBoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

// Called when the game starts or when spawned
void ACameraPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACameraPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACameraPlayer::LeftAxisMovement() { //Y
    //Creation of the axes needed transform vector using world coordinates
    FVector localDisplacementVector = FVector(0.f, CameraSpeed, 0.f);
    //Transform this vector in local, and apply it for the local coordinates of the actor. Giving back the transformation applied in the world coordinates
    FVector localOffset = GetActorTransform().TransformVectorNoScale(localDisplacementVector);
    //apply this transform on the actor using world coordinates
	SetActorLocation(GetActorLocation() + localOffset);
}

void ACameraPlayer::RightAxisMovement() { //-Y
    //Creation of the axes needed transform vector using world coordinates
    FVector localDisplacementVector = FVector(0.f, -CameraSpeed, 0.f);
    //Transform this vector in local, and apply it for the local coordinates of the actor. Giving back the transformation applied in the world coordinates
    FVector localOffset = GetActorTransform().TransformVectorNoScale(localDisplacementVector);
    //apply this transform on the actor using world coordinates
    SetActorLocation(GetActorLocation() + localOffset);
}

void ACameraPlayer::TopAxisMovement() { //-X
    //Creation of the axes needed transform vector using world coordinates
    FVector localDisplacementVector = FVector(-CameraSpeed, 0.f, 0.f);
    //Transform this vector in local, and apply it for the local coordinates of the actor. Giving back the transformation applied in the world coordinates
    FVector localOffset = GetActorTransform().TransformVectorNoScale(localDisplacementVector);
    //apply this transform on the actor using world coordinates
    SetActorLocation(GetActorLocation() + localOffset);
}

void ACameraPlayer::DownAxisMovement() { //X
    //Creation of the axes needed transform vector using world coordinates
    FVector localDisplacementVector = FVector(CameraSpeed, 0.f, 0.f);
    //Transform this vector in local, and apply it for the local coordinates of the actor. Giving back the transformation applied in the world coordinates
    FVector localOffset = GetActorTransform().TransformVectorNoScale(localDisplacementVector);
    //apply this transform on the actor using world coordinates
    SetActorLocation(GetActorLocation() + localOffset);
}

/* PROBLEME QUAND JUTILISE DIRECTEMENT WORLD LOCATION SI JE PIVOTE CA RESPECTE PLUS LAXE
void ACameraPlayer::DownAxisMovement() {
    FVector locationCamera = GetActorLocation();
    locationCamera.X -= CameraSpeed;
    SetActorLocation(locationCamera);
}*/

//ROTATION: X=ROLL Y=PITCH Z=YAW

void ACameraPlayer::LeftAxisRotation() { //X
    FRotator localRotationVector = FRotator(1.f, 0.f, 0.f);
    AddActorLocalRotation(localRotationVector);
}


void ACameraPlayer::RightAxisRotation() { //-X
    FRotator localRotationVector = FRotator( -1.f, 0.f, 0.f);
    AddActorLocalRotation(localRotationVector);
}


void ACameraPlayer::TopAxisRotation() { //Y
    FRotator localRotationVector = FRotator(0.f, 1.f, 0.f);
    AddActorLocalRotation(localRotationVector);
}


void ACameraPlayer::DownAxisRotation() { //Y
    FRotator localRotationVector = FRotator(0.f, -1.f, 0.f);
    AddActorLocalRotation(localRotationVector);
}