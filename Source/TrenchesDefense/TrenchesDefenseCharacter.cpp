// Fill out your copyright notice in the Description page of Project Settings.


#include "TrenchesDefenseCharacter.h"

// Sets default values
ATrenchesDefenseCharacter::ATrenchesDefenseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrenchesDefenseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrenchesDefenseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATrenchesDefenseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//LifeComponent = CreateDefaultSubobject<ULifeComponent>(TEXT("LifeComponent"));
}

bool ATrenchesDefenseCharacter::Attack(TArray<ATrenchesDefenseCharacter*> Targets) {
	return false;
}

bool ATrenchesDefenseCharacter::GoTo(FVector TargetLocation) {
	return false;
}

void ATrenchesDefenseCharacter::Die() {
	IsDead = true;
}