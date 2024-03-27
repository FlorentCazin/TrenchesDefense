// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPlayer.h"
#include "GameFramework/Actor.h"


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

    //For the limitation widget BP
    CameraGoingLeft= false;
    CameraGoingRight = false;
    CameraGoingTop = false;
    CameraGoingBottom = false;
    LimitReachedTop = false;
    LimitReachedBottom = false;
    LimitReachedLeft = false;
    LimitReachedRight = false;

    //Speed
    CameraSpeedMovement=1;
    CameraSpeedRotation=1;

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

void ACameraPlayer::DelayedReintialiseBooleanLimitationCameraTop(){
    CameraGoingTop ? CameraGoingTop = false: CameraGoingTop;
    LimitReachedTop ? LimitReachedTop = false : LimitReachedTop;
}

void ACameraPlayer::DelayedReintialiseBooleanLimitationCameraBottom() {
    CameraGoingBottom ? CameraGoingBottom = false : CameraGoingBottom;
    LimitReachedBottom ? LimitReachedBottom = false : LimitReachedBottom;
}

void ACameraPlayer::DelayedReintialiseBooleanLimitationCameraLeft() {
    CameraGoingLeft ? CameraGoingLeft = false : CameraGoingLeft;
    LimitReachedLeft ? LimitReachedLeft = false : LimitReachedLeft;
}

void ACameraPlayer::DelayedReintialiseBooleanLimitationCameraRight() {
    CameraGoingRight ? CameraGoingRight = false : CameraGoingRight;
    LimitReachedRight ? LimitReachedRight = false : LimitReachedRight;
}

void ACameraPlayer::LeftAxisMovement() { //Y
    CameraGoingLeft = true;
    //Creation of the axes needed transform vector using world coordinates
    FVector localDisplacementVector = FVector(0.f, -CameraSpeedMovement, 0.f);
    //Transform this vector in local, and apply it for the local coordinates of the actor. Giving back the transformation applied in the world coordinates
    FVector localOffset = GetActorTransform().TransformVectorNoScale(localDisplacementVector);
    //apply this transform on the actor using world coordinates
	SetActorLocation(GetActorLocation() + localOffset);
    // Delay before calling ReintialiseBooleanLimitationCamera
    float Delay = 0.2f; // Set the delay time in seconds
    GetWorldTimerManager().SetTimer(TimerHandle1, this, &ACameraPlayer::DelayedReintialiseBooleanLimitationCameraLeft, Delay, false);
}

void ACameraPlayer::RightAxisMovement() { //-Y
    CameraGoingRight = true;
    FVector localDisplacementVector = FVector(0.f, CameraSpeedMovement, 0.f);
    FVector localOffset = GetActorTransform().TransformVectorNoScale(localDisplacementVector);
    SetActorLocation(GetActorLocation() + localOffset);
    float Delay = 0.2f;
    GetWorldTimerManager().SetTimer(TimerHandle2, this, &ACameraPlayer::DelayedReintialiseBooleanLimitationCameraRight, Delay, false);
}

void ACameraPlayer::TopAxisMovement() { //-X
    CameraGoingTop = true;
    FVector localDisplacementVector = FVector(CameraSpeedMovement, 0.f, 0.f);
    FVector localOffset = GetActorTransform().TransformVectorNoScale(localDisplacementVector);
    SetActorLocation(GetActorLocation() + localOffset);
    float Delay = 0.2f;
    GetWorldTimerManager().SetTimer(TimerHandle3, this, &ACameraPlayer::DelayedReintialiseBooleanLimitationCameraTop, Delay, false);
}

void ACameraPlayer::DownAxisMovement() { //X
    CameraGoingBottom = true;
    FVector localDisplacementVector = FVector(-CameraSpeedMovement, 0.f, 0.f);
    FVector localOffset = GetActorTransform().TransformVectorNoScale(localDisplacementVector);
    SetActorLocation(GetActorLocation() + localOffset);
    float Delay = 0.2f;
    GetWorldTimerManager().SetTimer(TimerHandle4, this, &ACameraPlayer::DelayedReintialiseBooleanLimitationCameraBottom, Delay, false);
}

void ACameraPlayer::LeftAxisRotation() { //-Y
    FRotator RotationLocal(0.f, -CameraSpeedRotation, 0.f);
    SetActorRotation(GetActorRotation() + RotationLocal);
    
}


void ACameraPlayer::RightAxisRotation() { //Y
    FRotator RotationLocal(0.f, CameraSpeedRotation, 0.f);
    SetActorRotation(GetActorRotation() + RotationLocal);
    
}


void ACameraPlayer::TopAxisRotation() { //X
    FRotator localRotationVector = FRotator(CameraSpeedRotation, 0.f, 0.f);
    AddActorLocalRotation(localRotationVector);
}


void ACameraPlayer::DownAxisRotation() { //X
    FRotator localRotationVector = FRotator(-CameraSpeedRotation, 0.f, 0.f);
    AddActorLocalRotation(localRotationVector);
}


void ACameraPlayer::Zoom() { 
    FVector ZoomDirection = GetActorForwardVector(); 
    float ZoomFactor = 0.1f;
    // Increase the length of the vector to simulate zooming in
    ZoomDirection *= (1.0f - ZoomFactor);
    SetActorLocation(GetActorLocation() + ZoomDirection * CameraSpeedMovement);
}

void ACameraPlayer::UnZoom() {
    FVector ZoomDirection = GetActorForwardVector();
    float ZoomFactor = 2.0f;
    // Increase the length of the vector to simulate unzooming in
    ZoomDirection *= (1.0f - ZoomFactor);
    SetActorLocation(GetActorLocation() + ZoomDirection * CameraSpeedMovement);
}