// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesDefensePreviewCharacter.h"

// Sets default values
ATrenchesDefensePreviewCharacter::ATrenchesDefensePreviewCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrenchesDefensePreviewCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrenchesDefensePreviewCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATrenchesDefensePreviewCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATrenchesDefensePreviewCharacter::SetPreview(ATrenchesDefenseCharacter* character) {

}

void ATrenchesDefensePreviewCharacter::StopPreview() {

}
